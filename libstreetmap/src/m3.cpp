/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 
 * Copyright 2022 University of Toronto
 *
 * Permission is hereby granted, to use this software and associated 
 * documentation files (the "Software") in course work at the University 
 * of Toronto, or for personal use. Other uses are prohibited, in 
 * particular the distribution of the Software either publicly or to third 
 * parties.
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include <iostream>
#include "m1.h"
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include <cmath>
#include <utility>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <regex>

//#include "m2.h"
#include "ezgl/application.hpp"
#include "ezgl/graphics.hpp"
#include "ezgl/point.hpp"
#include <cmath>
#include <queue>

#include <math.h>
#include <chrono>
#include "m3.h"
#define EDGE_NULL -1
#define AVG_SPEED_LIMIT 50000 //50000 metres per hour or 50km/h

//helper function declarations
bool optimalPath(IntersectionIdx startIntID, IntersectionIdx endIntID, double turn_penalty);
bool dijktraPath(IntersectionIdx startIntID, IntersectionIdx endIntID, double turn_penalty);
std::vector<StreetSegmentIdx> pathTraceBack(int dest);
void build_graph();


class LatLon; //Forward declaration
class OSMID; //Forward declaration

//data structure to represent graph nodes
struct Node{
    std::vector<StreetSegmentIdx> connectedEdges;
    StreetSegmentIdx prevEdge;
    double bestTime;
};

//data structure to construct wave front nodes
struct wave_struct{
    IntersectionIdx node_id;
    StreetSegmentIdx edge_id;
    double travelTime;
    double timeEstimate;
    wave_struct(int n_id, int e_id, float t, float t_e){
        node_id = n_id; 
        edge_id = e_id; 
        travelTime = t; 
        timeEstimate = t_e;
    }
};

struct wave_struc_dijkstra{
    IntersectionIdx node_id;
    StreetSegmentIdx edge_id;
    double travelTime;
    wave_struc_dijkstra(int n_id, int e_id, float t){
        node_id = n_id; 
        edge_id = e_id; 
        travelTime = t; 
    }
};

struct MinHeapComparator{
    bool operator () (wave_struct wave1, wave_struct wave2){
        return wave1.timeEstimate> wave2.timeEstimate;
    }
};

struct MinHeapComparatorDijkstra{
    bool operator () (wave_struc_dijkstra wave1, wave_struc_dijkstra wave2){
        return wave1.travelTime> wave2.travelTime;
    }
};

//global data structures
std::vector<Node> nodes;
bool highlightSegments = false;

// Returns the time required to travel along the path specified, in seconds.
// The path is given as a vector of street segment ids, and this function can
// assume the vector either forms a legal path or has size == 0. The travel
// time is the sum of the length/speed-limit of each street segment, plus the
// given turn_penalty (in seconds) per turn implied by the path. If there is
// no turn, then there is no penalty. Note that whenever the street id changes
// (e.g. going from Bloor Street West to Bloor Street East) we have a turn.

double computePathTravelTime(const double turn_penalty, const std::vector<StreetSegmentIdx>& path){
   double pathTravelTime = 0.0;
    StreetIdx prevId= getStreetSegmentInfo(path[0]).streetID;
    StreetIdx currId;
    prevId = getStreetSegmentInfo(path[0]).streetID;
    for(StreetSegmentIdx i = 0; i < path.size(); i++){
       currId = getStreetSegmentInfo(path[i]).streetID;
       pathTravelTime += findStreetSegmentTravelTime(path[i]);
       if(prevId != currId){
           pathTravelTime += turn_penalty;
       }
       prevId = currId;
    }
    
    return pathTravelTime;
}


bool optimalPath(IntersectionIdx startIntID, IntersectionIdx endIntID, double turn_penalty){
    //estimate expected time
    double expectedTime = (findDistanceBetweenTwoPoints(std::make_pair(getIntersectionPosition(startIntID),getIntersectionPosition(endIntID)))/AVG_SPEED_LIMIT);
    
    //build wave front queue
    std::priority_queue<wave_struct, std::vector<wave_struct>, MinHeapComparator> waveFront;
    waveFront.push(wave_struct(startIntID, EDGE_NULL, 0, expectedTime));
    
    //runs while wave front has nodes
    while(!waveFront.empty()){
        wave_struct wave = waveFront.top();
        int currInterID = wave.node_id;
        
        waveFront.pop();
        
        if((wave.travelTime < nodes[currInterID].bestTime) || (nodes[currInterID].bestTime == -1)){
            nodes[currInterID].prevEdge= wave.edge_id;
            nodes[currInterID].bestTime = wave.travelTime;
            
            if(currInterID == endIntID){
                return true;
            }
                
            
            for(int outEdge = 0; outEdge < nodes[currInterID].connectedEdges.size(); outEdge++){
                
                StreetSegmentIdx outSegID = nodes[currInterID].connectedEdges[outEdge];
  
                double curr_penalty = 0;
                if(currInterID != startIntID){
                    //if street id changes incur turn penalty
                    if(getStreetSegmentInfo(outSegID).streetID != getStreetSegmentInfo(nodes[currInterID].prevEdge).streetID){
                        curr_penalty = turn_penalty;
                    }
                }
               
                if(currInterID == getStreetSegmentInfo(outSegID).to){
                    if(!getStreetSegmentInfo(outSegID).oneWay){
                        int ID_next = getStreetSegmentInfo(outSegID).from;
                        expectedTime = (findDistanceBetweenTwoPoints(std::make_pair(getIntersectionPosition(ID_next),getIntersectionPosition(endIntID)))/AVG_SPEED_LIMIT);
                        double travelTime = nodes[currInterID].bestTime + curr_penalty + findStreetSegmentTravelTime(outSegID);
                        waveFront.push(wave_struct(ID_next, outSegID, travelTime, travelTime + expectedTime));
                    }
                }
                else{
                    int ID_next = getStreetSegmentInfo(outSegID).to;
                    expectedTime = (findDistanceBetweenTwoPoints(std::make_pair(getIntersectionPosition(ID_next),getIntersectionPosition(endIntID)))/AVG_SPEED_LIMIT);
                    double travelTime = nodes[currInterID].bestTime + curr_penalty + findStreetSegmentTravelTime(outSegID);
                    waveFront.push(wave_struct(ID_next, outSegID, travelTime, travelTime + expectedTime));
                }
            }
        }
    }
    return false;
}

bool dijktraPath(IntersectionIdx startIntID, IntersectionIdx endIntID, double turn_penalty){
    
    //build wave front queue
    std::priority_queue<wave_struc_dijkstra, std::vector<wave_struc_dijkstra>, MinHeapComparatorDijkstra> waveFront;
    waveFront.push(wave_struc_dijkstra(startIntID, EDGE_NULL, 0));
    
    //runs while wave front has nodes
    while(!waveFront.empty()){
        wave_struc_dijkstra wave = waveFront.top();
        int currInterID = wave.node_id;
        
        waveFront.pop();
        
        if((wave.travelTime < nodes[currInterID].bestTime) || (nodes[currInterID].bestTime == -1)){
            nodes[currInterID].prevEdge= wave.edge_id;
            nodes[currInterID].bestTime = wave.travelTime;
            
            if(currInterID == endIntID){
                return true;
            }
                
            
            for(int outEdge = 0; outEdge < nodes[currInterID].connectedEdges.size(); outEdge++){
                
                StreetSegmentIdx outSegID = nodes[currInterID].connectedEdges[outEdge];
  
                double curr_penalty = 0;
                if(currInterID != startIntID){
                    //if street id changes incur turn penalty
                    if(getStreetSegmentInfo(outSegID).streetID != getStreetSegmentInfo(nodes[currInterID].prevEdge).streetID){
                        curr_penalty = turn_penalty;
                    }
                }
               
                if(currInterID == getStreetSegmentInfo(outSegID).to){
                    if(!getStreetSegmentInfo(outSegID).oneWay){
                        int ID_next = getStreetSegmentInfo(outSegID).from;
                        double travelTime = nodes[currInterID].bestTime + curr_penalty + findStreetSegmentTravelTime(outSegID);
                        waveFront.push(wave_struc_dijkstra(ID_next, outSegID, travelTime));
                    }
                }
                else{
                    int ID_next = getStreetSegmentInfo(outSegID).to;
                    double travelTime = nodes[currInterID].bestTime + curr_penalty + findStreetSegmentTravelTime(outSegID);
                    waveFront.push(wave_struc_dijkstra(ID_next, outSegID, travelTime));
                }
            }
        }
    }
    return false;
}

//traces back from destination node to starting node and pushes all nodes in the way into path vector of street segments
std::vector<StreetSegmentIdx> pathTraceBack(int endNode){
    std::list<StreetSegmentIdx> path;
    int currInterID = endNode;
    StreetSegmentIdx prevId = nodes[currInterID].prevEdge;
    
    //loops until there's no previous edge
    while(prevId!= EDGE_NULL){
        //pushes previous node into path street segments
        path.push_front(prevId);
        
        //update current node based on which end of the street it is coming from
        //if current intersections is "to" end
        //set the next node to  "from end
        if(currInterID == getStreetSegmentInfo(prevId).to){
            currInterID = getStreetSegmentInfo(prevId).from;
        }
        //if current intersections is "from" end
        //set the next node to  "to" end
        else{
            currInterID = getStreetSegmentInfo(prevId).to;
        }
        
        prevId = nodes[currInterID].prevEdge;
    }
    
    std::vector<StreetSegmentIdx> returnPath;
    std::copy(path.begin(), path.end(), std::back_inserter(returnPath)); //inverts path
    
    return returnPath;
}

void build_graph(){
    nodes.clear();
    nodes.resize(getNumIntersections());
    for(int i = 0; i<getNumIntersections(); i++){
        nodes[i].connectedEdges = findStreetSegmentsOfIntersection(i);
        nodes[i].bestTime = -1;
    }
}

// Returns a path (route) between the start intersection (1st object in intersect_ids pair)
// and the destination intersection(2nd object in intersect_ids pair),
// if one exists. This routine should return the shortest path
// between the given intersections, where the time penalty to turn right or
// left is given by turn_penalty (in seconds). If no path exists, this routine
// returns an empty (size == 0) vector. If more than one path exists, the path
// with the shortest travel time is returned. The path is returned as a vector
// of street segment ids; traversing these street segments, in the returned
// order, would take one from the start to the destination intersection.
std::vector<StreetSegmentIdx> findPathBetweenIntersections(const double turn_penalty,
 const std::pair<IntersectionIdx, IntersectionIdx> intersect_ids){
    
    //create empty path vector
    std::vector<StreetSegmentIdx> shortestPath(0);
    
    //set up and build nodes vector to represent graph
    build_graph();
    
    //call optimal path to use modified A*
   // bool ifPathExist = optimalPath (intersect_ids.first, intersect_ids.second, turn_penalty);
    
    //call dijkstra instead pf A*
    auto const startTime = std::chrono::high_resolution_clock::now();
    bool ifPathExist = dijktraPath (intersect_ids.first, intersect_ids.second, turn_penalty); //dijkstra
    //bool ifPathExist = optimalPath (intersect_ids.first, intersect_ids.second, turn_penalty); //a*
    auto const endTime = std::chrono::high_resolution_clock::now();
    
    auto const timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    //std::cout<<"====CPU TIME: ";
    //std::cout<<"====CPU TIME: "<<timeDiff.count()<<" ====\n";
    //if path exists build path result vector
    if(ifPathExist){
        highlightSegments = true;
        shortestPath = pathTraceBack(intersect_ids.second);
        return shortestPath;
    }
    
    return shortestPath;
} 

