/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 *

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
/*
 // This routine takes in a vector of D deliveries (pickUp, dropOff
 // intersection pairs), another vector of N intersections that
 // are legal start and end points for the path (depots), and a turn
 // penalty in seconds (see m3.h for details on turn penalties).
 //
 // The first vector deliveries gives the delivery information. Each delivery
 // in this vector has pickUp and dropOff intersection ids.
 // A delivery can only be dropped-off after the associated item has been picked-up.
 //
 // The second vector depots gives the intersection ids of courier company
 // depots containing trucks; you start at any one of these depots and end at
 // any one of the depots.
 //
 // This routine returns a vector of CourierSubPath objects that form a delivery route.
 // The CourierSubPath is as defined above. The first street segment id in the
 // first subpath is connected to a depot intersection, and the last street
 // segment id of the last subpath also connects to a depot intersection.
 // A package will not be dropped off if you havent picked it up yet.
 //
 // The start_intersection of each subpath in the returned vector should be
 // at least one of the following (a pick-up and/or drop-off can only happen at
 // the start_intersection of a CourierSubPath object):
 // 1- A start depot.
 // 2- A pick-up location
 // 3- A drop-off location.
 //
 // You can assume that D is always at least one and N is always at least one
 // (i.e. both input vectors are non-empty).
 //
 // It is legal for the same intersection to appear multiple times in the pickUp
 // or dropOff list (e.g. you might have two deliveries with a pickUp
 // intersection id of #50). The same intersection can also appear as both a
 // pickUp location and a dropOff location.
 //
 // If you have two pickUps to make at an intersection, traversing the
 // intersection once is sufficient to pick up both packages. Additionally,
 // one traversal of an intersection is sufficient to drop off all the
 // (already picked up) packages that need to be dropped off at that intersection.
 //
 // Depots will never appear as pickUp or dropOff locations for deliveries.
 //
 // If no valid route to make *all* the deliveries exists, this routine must
 // return an empty (size == 0) vector.
*/ 

#include <iostream>
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include <cmath>
#include <utility>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <regex>
#include "ezgl/application.hpp"
#include "ezgl/graphics.hpp"
#include "ezgl/point.hpp"
#include <cmath>
#include <queue>
#include <math.h>

#include "m1.h"
#include "m3.h"
#include "m4.h"

#define NOT_FOUND -1

typedef int DepotIdx;
typedef int DeliveriesIdx;

//data structure to represent graph nodes
struct Node{
    std::vector<StreetSegmentIdx> connectedEdges;
    StreetSegmentIdx prevEdge;
    double bestTime;
};

//data structures declaration
extern std::vector<Node> nodes; //graph representation

//function declarations
extern void build_graph();
bool add_subpath_to_vector(IntersectionIdx start_int, IntersectionIdx end_int, std::vector<CourierSubPath> &courPath_vector, const float turn_pen, 
    double &pathT);
IntersectionIdx findClosestDelivery(LatLon my_position, std::vector<DeliveryInf>& pickUps_left, 
        std::vector<DeliveryInf>& dropOffs_avail);
std::pair<std::vector<CourierSubPath>, double> geo_greedy(DepotIdx start_depo, const float turn_penalty,
    const std::vector<DeliveryInf>& deliveries, const std::vector<IntersectionIdx>& depots);
bool legalPath(std::vector<CourierSubPath> path, const std::vector<DeliveryInf>& deliveries, IntersectionIdx intersection);
std::pair<std::vector<CourierSubPath>, double> dummy(DepotIdx start_depo, const float turn_penalty,
    const std::vector<DeliveryInf>& deliveries,
    const std::vector<IntersectionIdx>& depots);
IntersectionIdx findClosestDepot(IntersectionIdx depot_start, IntersectionIdx last_inter, std::vector<IntersectionIdx> depots);

bool add_subpath_to_vector(IntersectionIdx start_int, IntersectionIdx end_int, std::vector<CourierSubPath> &courPath_vector, const float turn_pen, 
        double &pathT){
    bool pathValid;
    
    CourierSubPath subpath;
    std::vector<IntersectionIdx> path;
        //std::cerr<<"crashTest pt1!";
    path = findPathBetweenIntersections(turn_pen, std::make_pair(start_int, end_int));
    pathValid = !path.empty();
        //std::cerr<<"crashTest pt2!";
    pathT = pathT + computePathTravelTime(turn_pen, path);
        //std::cerr<<"crashTest pt3!";
    subpath.subpath = path;
    subpath.start_intersection = start_int;
    subpath.end_intersection = end_int;
    courPath_vector.push_back(subpath);
    
    return pathValid;
}

IntersectionIdx findClosestDelivery(LatLon my_position, std::vector<DeliveryInf>& pickUps_left, 
        std::vector<DeliveryInf>& dropOffs_avail){
    float closestDelDist= std::numeric_limits<float>::infinity();
    IntersectionIdx closestDel = 0;
    DeliveriesIdx closestDelId = 0;
    bool isPickUp = false;
    bool isDropOff = false;
    
    //runs through each possible available pickups, if distance to it is closest, update closestDelDist, its id, and the corresponding intersection. 
    for(int i = 0; i<pickUps_left.size(); ++i){
        LatLon intPos = getIntersectionPosition(pickUps_left[i].pickUp);
        std::pair <LatLon, LatLon> point (my_position, intPos);
        float pointDist = findDistanceBetweenTwoPoints(point);
        
        //checking is new distance calculated is less than the previous closest distance
        //ensure the new intersection is not itself
        if(pointDist < closestDelDist && !(intPos == my_position)){
            closestDelId = i;
            closestDel = pickUps_left[i].pickUp;
            closestDelDist = pointDist;
            isPickUp = true;//update 
            isDropOff = false;
                //std::cerr<<"closestDel (pickup) :"<<closestDel<<"\n";
        } 
    }
    
    //same process but for dropOffs
    for(int i = 0; i < dropOffs_avail.size(); i++){
        LatLon intPos = getIntersectionPosition(dropOffs_avail[i].dropOff);
        std::pair <LatLon, LatLon> point2 (my_position, intPos);
        float pointDist = findDistanceBetweenTwoPoints(point2);
        
        //checking is new distance calculated is less than the previous closest distance
        //ensure the new intersection is not itself
        if(pointDist < closestDelDist &&  !(intPos == my_position)){
            closestDelId = i;
            closestDel = dropOffs_avail[i].dropOff;
            closestDelDist = pointDist;
            isPickUp = false;
            isDropOff = true;
                //std::cerr<<"closestDel (dropOff) :"<<closestDel<<"\n";
        } 
    }
    
    if(isPickUp){
       dropOffs_avail.push_back(pickUps_left[closestDelId]);
        //std::cerr<<"dropOffs pushed: "<<pickUps_left[closestDelId].dropOff<<"\n";
       pickUps_left.erase (pickUps_left.begin() + closestDelId);
        //std::cerr<<"wipe pick up\n";
    }else if (isDropOff){
        dropOffs_avail.erase(dropOffs_avail.begin() + closestDelId);
        //std::cerr<<"wipe drop off\n";
        //std::cerr<<"====Dropoffs_avail: ";
        
        //for(int i; i < dropOffs_avail.size(); i++){
            //std::cerr<<" "<<dropOffs_avail[i].dropOff<<" ";
        //}
            //std::cerr<<"===\n";
        
    }else{
        return NOT_FOUND;
    }
    
        //std::cerr<<"closestDel (final) :"<<closestDel<<"\n";
    return closestDel;
}

//finds closest depot to the last intersection
IntersectionIdx findClosestDepot(IntersectionIdx depot_start, IntersectionIdx last_inter, std::vector<IntersectionIdx> depots){
    LatLon my_position = getIntersectionPosition(last_inter);
    float closestDepDist= std::numeric_limits<float>::infinity();
    IntersectionIdx closestDepot = depot_start;
    
    //runs through each possible depot distance, if distance to it is closest, update closestDepotDist. 
    for(IntersectionIdx i = 0; i<depots.size(); ++i){
        LatLon depPos = getIntersectionPosition(depots[i]);
        std::pair <LatLon, LatLon> points (my_position, depPos);
        float pointDist = findDistanceBetweenTwoPoints(points);
        if(pointDist < closestDepDist){
            closestDepot = depots[i];
            closestDepDist = pointDist;
        } 
    }
    return closestDepot; 
}



 bool legalPath(std::vector<CourierSubPath> path, const std::vector<DeliveryInf>& deliveries, IntersectionIdx intersection){
     bool pickedUp;
     
     for(int i = 0; i<deliveries.size(); i++){
         pickedUp = false;
         if(intersection == deliveries[i].dropOff){
             for(int j = 0; j<path.size(); j++){
                 if(deliveries[i].pickUp == path[j].start_intersection || deliveries[i].pickUp == path[j].end_intersection){
                     pickedUp = true;
                 }
             }
             if(pickedUp == false){
                 return false;
             }
         }
         if(i == deliveries.size() && intersection == deliveries[0].pickUp && pickedUp){
             return true;
         }
     }
     
     for(int x = 0; x<path.size(); x++){
         if(intersection == path[x].start_intersection || intersection == path[x].end_intersection)
            return false;
     }
     
     return true;
 }

// returns a vector of courier sub paths as the result and the total travel time
std::pair<std::vector<CourierSubPath>, double> geo_greedy(DepotIdx start_depo, const float turn_penalty,
 const std::vector<DeliveryInf>& deliveries,
 const std::vector<IntersectionIdx>& depots){
    //return values
    std::vector<CourierSubPath> courPath;
    double pathTime;
    
    //vectors keeping track of available pickups/drop-offs
    std::vector<DeliveryInf> dropOffs;
    std::vector<DeliveryInf> pickUps = deliveries; 
    
    
    IntersectionIdx subPathStart;
    IntersectionIdx subPathEnd;
    
    
    
    //set starting intersection at starting depo
    subPathStart = depots[start_depo];
        //std::cerr<<"subPath Depot : "<<subPathEnd<<"====\n";
     
    // Complete all deliveries by going to closest available destination
    for(int i = 0; i < deliveries.size()*2 ; i++){
        bool pathExists = false;
        while(!pathExists){
            subPathEnd = findClosestDelivery(getIntersectionPosition(subPathStart), pickUps, dropOffs);
                //std::cerr<<"subPathEnd: "<<subPathEnd<<"====\n";
            pathExists = add_subpath_to_vector(subPathStart, subPathEnd, courPath, turn_penalty, pathTime);
            subPathStart = subPathEnd; //sets the start of next subpath as the end of this subpath
                //std::cerr<<"subPathStart: "<<subPathStart<<"====\n";
        }
    }
    
    
    // Go back to the first depot to drop off the truck
    add_subpath_to_vector(subPathStart, findClosestDepot(start_depo, subPathStart, depots), courPath, turn_penalty, pathTime);
        //std::cerr<<"subPathDestination: "<<subPathStart<<"====\n";
    std::pair result = std::make_pair(courPath, pathTime);
    
        //std::cerr<<"return geo_greedy!\n";
    return result;
}

 std::vector<CourierSubPath> travelingCourier(
 const float turn_penalty,
 const std::vector<DeliveryInf>& deliveries,
 const std::vector<IntersectionIdx>& depots){
    //return path vector
    std::vector<CourierSubPath> courPath;
    std::vector<std::pair<std::vector<CourierSubPath>, double>> result;
    std::pair<std::vector<CourierSubPath>, double> temp;


    //calls greedy algorithms by giving starting DepotIndex, turn_penalty, the deliveries vector, and depots vector
    courPath = geo_greedy(0, turn_penalty, deliveries, depots).first; 
   
    //courPath = dummy(rando_depo,  turn_penalty, deliveries, depots).first;
    
    //std::cerr<<" function called!\n";
    
    return courPath;
 }          
 