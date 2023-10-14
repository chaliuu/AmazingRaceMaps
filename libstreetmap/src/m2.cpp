 /* 
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
 * PNG REFERENCES:
 * (doctors)hospital: https://www.pikpng.com/downpngs/ihhbmim_college-survival-guide-3-icon-hospital-icon-red/ 
 * police station: https://www.pngfind.com/download/hwRhTTm_police-icon-png-alternate-history-tripolitania-flag-transparent/ 
 * subway station: https://www.softicons.com/web-icons/awt-travel-blue-icons-by-awt-media/train-icon
 * bank: https://www.kindpng.com/imgv/hmwJhbx_flat-icon-money-blue-hd-png-download/
 * library: https://www.pngaaa.com/detail/2809995
 * (school)university: https://www.kindpng.com/imgv/iowJbh_transparent-education-icon-png-college-and-career-icon/
 * restaurant: https://www.pngaaa.com/detail/3953103
 */

#include <iostream>
#include "m1.h"
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <regex>

#include "m2.h"
#include "m3.h"
#include "m4.h"
#include "ezgl/application.hpp"
#include "ezgl/graphics.hpp"
#include "ezgl/point.hpp"
#include <cmath>

std::string map_path = "/cad2/ece297s/public/maps/toronto_canada.streets.bin";
std::string mapcity = "Toronto";
std::string mapcountry = "Canada";
class LatLon; //Forward declaration
class OSMID; //Forward declaration


//intersection data to be stored in data vector.
struct intersectionData{
    LatLon position;
    std::string name;
    bool highlight;
};

//streets data to be stored in data vector.
struct streetsData{
    bool oneWay;
    OSMID wayOSMID;
    int numCurvePoints;
    IntersectionIdx from, to;
    float speedLimit;
    StreetIdx streetID;
    StreetSegmentIdx id;
    bool highlight;
    bool highway;
    bool major;
    bool onPath;
    StreetSegmentIdx reachingEdge;
    double bestTime;
};

//POI data to be stored in data vector.
struct POIstruct{
    ezgl::point2d poiCenter;
    std::string name;
    std::string type;
};

//check where cursor is clicked.
struct click{
    LatLon position;
    bool intersection;
};

struct Node{
    std::vector<StreetSegmentIdx> outgoingEdges;
    StreetSegmentIdx reachingEdge;
    double bestTime;
};

//data structures
std::vector<intersectionData> intersections;
std::vector<streetsData> streets;
std::vector<POIstruct> POIData;
std::vector<OSMID> highways;
std::vector<OSMID> major_roads;
std::vector<size_t> islandFeatIds;
std::vector<size_t> lakeFeatIds;
std::vector<size_t> unknownFeatIds;
std::vector<size_t> parkFeatIds;
std::vector<size_t> beachFeatIds;
std::vector<size_t> riverFeatIds;
std::vector<size_t> buildingFeatIds;
std::vector<size_t> greenspaceFeatIds;
std::vector<size_t> golfcourseFeatIds;
std::vector<size_t> streamFeatIds;
extern std::vector<Node> nodes;
std::vector<StreetSegmentIdx> highlightedPaths;
std::vector <std::string> bankTasks{"Steal a pen from the counter.", "Find a staff with the same first letter in their name.", 
                    "Exchange a $10 bill in quarters and stack them in a single tower."};
std::vector <std::string> restTasks{"Make a purchase at the restaurant with the receipt totaling to current time.", "Get someone to buy your food without explicitly telling them to.", 
                    "Find all five food groups on the menu."};
std::vector <std::string> libTasks{"Find a book with an author that has your initials.", "Find 10 books with numbers 1 to 10 in the title.", 
                    "Re-shelf a cart of books for the staff."};

click cursor;

//magic numbers 
#define strtLen 150
#define ZOOM2X 18000
#define ZOOM3X 10700
#define ZOOM4X 6400
#define ZOOM5X 1500
#define ZOOM6X 510

#define squarePow 2
#define rootPow 0.5 
#define NO_EDGE -1

//global variables
double max_lat; 
double min_lat;
double max_lon;
double min_lon;

double max_y; 
double min_y;
double max_x;
double min_x;
double current_height;
double pos1;
double pos2;
int randoPOI;
int randoTask;
std::string POItype;

bool darkmode = false;
bool majorRoads = true;
bool features = true;
bool pois = false;
bool minorRoads = false;
bool majorStreetNames = false;
bool minorStreetNames = false;
bool buildings = false;
bool printIntersections = false;
bool poinames = false;
bool showpoinames = false;
bool rivers = false;
bool ifPOILib = true;
bool ifPOIDoc = true;
bool ifPOISchool = true;
bool ifPOIBank = true;
bool ifPOIResta = true;
bool rando_poi = false;
bool ifRightType = false;
bool drawMarkers = false;

//function declarations
float x_from_lon(float lon);
float y_from_lat(float lat);
float lon_from_x(float x);
float lat_from_y(float y);
void setIntersections();
void setStreets();
void type_of_street();
void setPOIs();
void draw_main_canvas(ezgl::renderer *g);
void zoom_scale(ezgl::renderer* g);
std::vector<std::string> printDirections(std::vector<StreetSegmentIdx> path);
std::pair<std::pair<double, double>, std::pair<double, double>> getVectors(LatLon point1, LatLon point2);
void act_on_mouse_click(ezgl::application* app, GdkEventButton* event, double x, double y);
void initial_setup (ezgl::application* application, bool /*new_window */);
void draw_markers(ezgl::renderer *g);
void clear_intersections_and_paths();
void directions_dialog(ezgl::application *application);
void clear_button(GtkWidget* /*widget*/, ezgl::application* application);
void POIs_button(GtkWidget* /*widget*/, ezgl::application* application);
void rando_POI_button(GtkWidget* /*widget*/, ezgl::application* application);
void rando_task_button(GtkWidget* /*widget*/, ezgl::application* application);
void find_button(GtkWidget* /*widget*/, ezgl::application* application);
void path_button(GtkWidget* /*widget*/, ezgl::application* application);
void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer /*gp*/, ezgl::application /** app*/);
void find_intersection(std::string streetpref1, std::string streetpref2, ezgl::application* application);
void find_path(std::string streetpref1, std::string streetpref2, ezgl::application* application);
void info_button(GtkWidget* /*widget*/, ezgl::application* application);
void draw_features(ezgl::renderer *g);
void sort_feat_types();
void draw_single_feature_type(ezgl::renderer *g, std::vector<size_t> typeFeatIds);
void draw_streets(ezgl::renderer *g);
void draw_streetNames(ezgl::renderer *g);
void draw_intersections(ezgl::renderer *g);
void draw_pois(ezgl::renderer *g);
void draw_rando_poi(ezgl::renderer *g);
void draw_streetName (ezgl::renderer *g);
void load_button(GtkWidget* /*widget*/, ezgl::application* application);
void city_input(std::string city, std::string country, ezgl::application* application);
void darkmode_button(GtkWidget* /*widget*/, ezgl::application* application);

// Convert lon and lat to x and y coords, and vice versa.
float x_from_lon(float lon){
    float x;
    x = kEarthRadiusInMeters*(lon*kDegreeToRadian)*cos((min_lat*(kDegreeToRadian)+max_lat*(kDegreeToRadian))/2);
    return x;
}

float lon_from_x(float x){
    float lon;
    lon = x/(kEarthRadiusInMeters*kDegreeToRadian*cos((min_lat*(kDegreeToRadian)+max_lat*(kDegreeToRadian))/2));
    return lon;
}

float y_from_lat(float lat){
    float y;
    y = kEarthRadiusInMeters*(lat*kDegreeToRadian);
    return y;
}

float lat_from_y(float y){
    float lat;
    lat = y/(kEarthRadiusInMeters*kDegreeToRadian);
    return lat;
}

//setting data structure of intersections, also updates max and min coordinates.
void setIntersections(){
    for(int i = 0; i < getNumIntersections(); i++){
        intersections[i].position = getIntersectionPosition(i);
        intersections[i].name = getIntersectionName(i);

        max_lat = std::max(max_lat, intersections[i].position.latitude());
        min_lat = std::min(min_lat, intersections[i].position.latitude());
        max_lon = std::max(max_lon, intersections[i].position.longitude());
        min_lon = std::min(min_lon, intersections[i].position.longitude());
        
        max_y = y_from_lat(max_lat);
        min_y = y_from_lat(min_lat);
        max_x = x_from_lon(max_lon);
        min_x = x_from_lon(min_lon);
    }
}

//setting data structure of street segments.
void setStreets(){
    for(StreetSegmentIdx i=0; i< getNumStreetSegments(); i++){
        StreetSegmentInfo ss = getStreetSegmentInfo(i);
        streets[i].from = ss.from;
        streets[i].wayOSMID = ss.wayOSMID;
        streets[i].to = ss.to;
        streets[i].oneWay = ss.oneWay;
        streets[i].speedLimit = ss.speedLimit;
        streets[i].streetID = ss.streetID;
        streets[i].id = i;
        streets[i].numCurvePoints = ss.numCurvePoints;
    }
}

//sets POI data structure for easy calling.
void setPOIs(){
    for(POIIdx i = 0; i < getNumPointsOfInterest(); i++){
        POIData[i].name = getPOIName(i);
        POIData[i].type = getPOIType(i);
        POIData[i].poiCenter.x = x_from_lon(getPOIPosition(i).longitude());
        POIData[i].poiCenter.y = y_from_lat(getPOIPosition(i).latitude());
    }
}

//checking what type each street segment is, either highway, major road, or street.
//uses osm bin and keys+tags.
void type_of_street(){
    for (unsigned i = 0; i < getNumberOfWays(); i++) {
        const OSMWay *currWay = getWayByIndex(i);
        for (unsigned j = 0; j < getTagCount(currWay); j++) {
            std::pair<std::string, std::string> tagPair = getTagPair(currWay, j);
            //checking major roads
            if (tagPair.first == "highway" && ((tagPair.second == "primary") || (tagPair.second == "trunk") || (tagPair.second == "secondary"))) {
                major_roads.push_back(currWay->id());
                break;
            }
            //checking highways
            else if(tagPair.first == "highway" && tagPair.second == "motorway"){
                highways.push_back(currWay->id());
                break;
            }
        }
    }
    //marking each street segment as major road or highway if applicable.
    for(int j = 0; j < major_roads.size(); j++){
        for(int k = 0; k < streets.size(); k++){
            if(streets[k].wayOSMID == major_roads[j]){
                streets[k].major = true;
            }
            else if(streets[k].wayOSMID == highways[j]){
                streets[k].highway = true;
            }
        }
    }
}

//checking the zoom scale of canvas to decide which features to draw.
//initially sets all bool features to false to account for zooming out as well.
void zoom_scale(ezgl::renderer* g){
    current_height = g->get_visible_world().height();
    majorRoads = true;
    features = true;
    minorRoads = false;
    majorStreetNames = false;
    minorStreetNames = false;
    buildings = false;
    rivers = false;
    printIntersections = false;
    poinames = false;
    
    if(current_height < ZOOM2X){ //for zoom pressed 2x
        minorRoads = true;
        rivers = true;
    }
    if(current_height < ZOOM3X){ //for zoom pressed 3x
        printIntersections = true;
        majorStreetNames = true;
    }
    if(current_height < ZOOM4X){ //for zoom pressed 4x
        minorStreetNames = true;
    }
    if(current_height < ZOOM5X){ //for zoom pressed 5x
        if(showpoinames == true){
            poinames = true;
        }
    }
    if(current_height < ZOOM6X){ //for zoom pressed 8x
        buildings = true;
    }
}

//directions helper function -> forms a pair of 2 pairs.
std::pair<std::pair<double, double>, std::pair<double, double>> getVectors(LatLon point1, LatLon point2){

    //coordinates for pair 
    double x1 = x_from_lon(point1.longitude());
    double x2 = x_from_lon(point2.longitude());
    double y1 = y_from_lat(point1.latitude());
    double y2 = y_from_lat(point2.latitude());

    // difference between x and y coordinates
    double dx_diff = x2-x1;
    double dy_diff = y2-y1;
    
    // calculating magnitude 
    double dx_diff2 = pow(dx_diff, squarePow);
    double dy_diff2 = pow(dy_diff, squarePow);
    double magRadicand = dx_diff2 + dy_diff2;
    double magnitude = pow(magRadicand, rootPow);
    
    double x = dx_diff/magnitude;
    double y = dy_diff/magnitude;
    
    //creating vector pairs
    std::pair<double, double> aVector = std::make_pair(x, y);
    std::pair<double, double> bVector = std::make_pair(-y, x);

    std::pair<std::pair<double, double>, std::pair<double, double>> vectors = std::make_pair(aVector, bVector);

    return vectors;   
}

// prints directions for specified path
std::vector<std::string> printDirections(std::vector<StreetSegmentIdx> path){
    //utility variables
    std::vector<std::string> pathDirections;
    bool lastSeg = false;
  
    StreetSegmentIdx prevSeg = 0;
    StreetSegmentIdx firstSeg = path[0]; 
    StreetSegmentInfo firstSegInfo = getStreetSegmentInfo(firstSeg);
    LatLon firstSegStart;
    LatLon firstSegEnd;
    
    IntersectionIdx startId = 0;
    IntersectionIdx prevInter = 0;
    IntersectionIdx currInter = 0;
    IntersectionIdx nextInter = 0;
    
    std::string segDistance;
    double sameStreetDist = 0.0;
    
  //set the start and end positions of first segment by determining which side the street segment is on (up the street vs down)
  
    if(nodes[firstSegInfo.to].reachingEdge == NO_EDGE){
        startId = firstSegInfo.to; //up the road 
        prevInter = startId;  
        currInter = firstSegInfo.from;
        firstSegStart = getIntersectionPosition(startId);
        firstSegEnd = getIntersectionPosition(currInter);
    
    }else if(nodes[firstSegInfo.from].reachingEdge == NO_EDGE) {
        startId = firstSegInfo.from; // down the road 
        prevInter = startId;
        currInter = firstSegInfo.to;
        firstSegStart = getIntersectionPosition(startId);
        firstSegEnd = getIntersectionPosition(currInter);
    }
    
  //unit vectors for first segments (to use later for crossProduct and determining directions)
    double firstX = getVectors(firstSegStart, firstSegEnd).first.first; 
    double firstY = getVectors(firstSegStart, firstSegEnd).first.second;

    //display which direction to start by comparing abs x (firstX) and y (firstY)
    //and which direction the unit vector is pointing

        // logic for cardinal E,W,N,S directions:
        // abs value comparison determines N,S vs E,W 
    
        if (firstX > 0 && abs(firstX) > abs(firstY)){
        //x is positive and |x| > |y| ------> east 
            std::string startDirection = "Go East on " + getStreetName(getStreetSegmentInfo(firstSeg).streetID);
            startDirection += " for ";
            // use segDistance to calculate length of first segment of path
            segDistance = std::to_string((int)findStreetSegmentLength(firstSeg)) ;
            startDirection += segDistance + " meters.";
            pathDirections.push_back(startDirection);
        }   
    
        //x is negative and |x| > |y|  ------> west
        else if(firstX < 0 && abs(firstX) > abs(firstY)){
            std::string startDirection = "Go West on " + getStreetName(getStreetSegmentInfo(firstSeg).streetID);
            startDirection += " for ";
            segDistance = std::to_string((int)findStreetSegmentLength(firstSeg)) + segDistance;
            startDirection += " meters.";
            pathDirections.push_back(startDirection);
        }
      
        //y is positive and |y| > |x|  ------> north
        else if(firstY > 0 && abs(firstY) > abs(firstX)){
            std::string startDirection = "Go North on " + getStreetName(getStreetSegmentInfo(firstSeg).streetID);
            startDirection += " for ";
            segDistance = std::to_string((int)findStreetSegmentLength(firstSeg));
            startDirection += segDistance + " meters.";
            pathDirections.push_back(startDirection);
      
        }   
        //y is negative and |y| > |x|  ------> south
        else if(firstY < 0 && abs(firstY) > abs(firstX)){
            std::string startDirection = "Go South on " + getStreetName(getStreetSegmentInfo(firstSeg).streetID);
            startDirection += " for ";
            segDistance = std::to_string((int)findStreetSegmentLength(firstSeg));
            startDirection += segDistance + " meters.";
            pathDirections.push_back(startDirection);
        }
   
    //one output resulting from one element
    if(path.size() <= 1){
        pathDirections.push_back("\nYou have arrived at your destination.");
        return pathDirections;
    // else loop through each segment, storing the previous segment and comparing
    //compare previous segment to the new segment
    }else{
        prevSeg = path[0];
        for(int path_Ids = 1; path_Ids < path.size(); path_Ids++){
            if (path_Ids==(path.size()-1)) {
                lastSeg = true;}
            StreetSegmentIdx currSeg =  path[path_Ids];
          
            //if the streetId changes = new direction, find change in direction
            if((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID)||(lastSeg)){
                //find the positions of start and end of the previous unit vector
                LatLon prevEnd = getIntersectionPosition(currInter);
                LatLon prevStart = getIntersectionPosition(prevInter);
                LatLon currEnd;
                LatLon currStart;
                //check current unit vector to determine start and end point positions (side of road) of currSeg
                //similar to checking firstSeg position
              if(getStreetSegmentInfo(currSeg).to == currInter){
                    nextInter = getStreetSegmentInfo(currSeg).from;
                    currEnd = getIntersectionPosition(nextInter);
                    currStart = getIntersectionPosition(currInter);
              }else{
                  nextInter = getStreetSegmentInfo(currSeg).to;
                  currEnd = getIntersectionPosition(nextInter);
                  currStart = getIntersectionPosition(currInter);
              }

              //get the unit vectors of the current segment and the previous segment
              std::pair<double,double>prevSegUnit = getVectors(prevStart, prevEnd).first;
              std::pair<double,double>currSegUnit = getVectors(currStart, currEnd).first;
              
              //perform a cross production between the two vectors
              double crossProduct = prevSegUnit.first*currSegUnit.second - prevSegUnit.second*currSegUnit.first;
              
              int checkCrossProduct = crossProduct == 0;
              switch(checkCrossProduct) {
                //cross product == 0
                //directions -> continue straight
                  case 1:
                        // last seg and curr segment do not equal to prev seg -> 
                        if ((lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                            std::string routeTurn = "\nFinally, merge on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                            routeTurn += " and continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            routeTurn += segDistance + " meters. \nYou are your destination.";
                            pathDirections.push_back(routeTurn);
                            
                        } else if ((lastSeg)&& ((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))) {
                            std::string prevMessage = "\nFinally, continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            prevMessage += segDistance + " meters and you have reached your destination.";
                            pathDirections.push_back(prevMessage);

                        } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))){
                            int thisSegDistance = (int) findStreetSegmentLength(currSeg);
                            sameStreetDist = sameStreetDist + thisSegDistance;
                          
                            //If the next segment is the last one or we change streets
                            if ((getStreetSegmentInfo(path[path_Ids+1]).streetID!=getStreetSegmentInfo(currSeg).streetID) ||((path_Ids)+1==(path.size()-1))){
                                std::string message = "Continue for ";
                                message += (std::to_string(sameStreetDist)) + " meters.";
                                sameStreetDist = 0;
                            }

                        
                        } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                            std::string routeTurn = "\nMerge on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                            routeTurn += " and continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            routeTurn += segDistance +" meters";
                            pathDirections.push_back(routeTurn);
                        }  
                      break;

                //if crossProduct is != 0  -> change directions / turn onto roads 
                  case 0:
                    
                  //crossProduct is  < 0 (right)
                  if ((lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                        std::string routeTurn = "\nFinally, turn right on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                        routeTurn += " and continue for ";
                        segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                        routeTurn += segDistance + " meters. \nYou have reached your destination.";
                        pathDirections.push_back(routeTurn);
                        
                    } else if ((lastSeg)&& ((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))) {
                        std::string prevMessage = "\nFinally, continue for ";
                        segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                        prevMessage += segDistance + " meters and you have reached your destination.";
                        pathDirections.push_back(prevMessage);

                    } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))){
                        int thisSegDistance = (int)findStreetSegmentLength(currSeg);
                        sameStreetDist = sameStreetDist + thisSegDistance;
                        //If the next segment is the last one or we change streets
                        if ((getStreetSegmentInfo(path[path_Ids+1]).streetID!=getStreetSegmentInfo(currSeg).streetID) ||((path_Ids)+1==(path.size()-1))){
                            std::string message = "Continue for ";
                            message += (std::to_string(sameStreetDist)) +" meters.";
                            sameStreetDist = 0;
                        }
                    } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                        std::string routeTurn = "\nTurn right on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                        routeTurn += " and continue for ";
                        segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                        routeTurn += segDistance +" meters";
                        pathDirections.push_back(routeTurn);
                    }
                    //if the cross product is positive, we needed rotate left to get on the current segment
                    
                    
                    //when crossProduct > 0 (left)
                    else {
                        //last seg (ending route) and curr seg don't equal to prev seg -> 
                        if ((lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                            std::string routeTurn = "\nFinally, turn left on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                            routeTurn += " and continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            routeTurn +=  segDistance + " meters. \nYou have reached destination.";
                            pathDirections.push_back(routeTurn);
                            
                        } else if ((lastSeg)&& ((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))) {
                            std::string prevMessage = "\nFinally, continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            prevMessage += segDistance +" meters and you have reached your destination";
                            pathDirections.push_back(prevMessage);
                          
                          //not the last segment of path (not ending route) and curr seg  = prev seg which means street has not changed
                        } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID == getStreetSegmentInfo(prevSeg).streetID))){
                            int thisSegDistance = (int)findStreetSegmentLength(currSeg);
                            sameStreetDist = sameStreetDist + thisSegDistance;
                          
                            //streets not changing = no change in direction or path has more segments left
                            if ((getStreetSegmentInfo(path[path_Ids+1]).streetID!=getStreetSegmentInfo(currSeg).streetID) ||((path_Ids)+1==(path.size()-1))){
                                std::string message = "Continue for ";
                                message += (std::to_string(sameStreetDist))+" meters.";
                                sameStreetDist = 0;
                            }
                          //we're not at the final 
                        } else if ((!lastSeg)&&((getStreetSegmentInfo(currSeg).streetID != getStreetSegmentInfo(prevSeg).streetID))){
                            std::string routeTurn = "\nTurn left on " + getStreetName(getStreetSegmentInfo(currSeg).streetID); 
                            routeTurn += " and continue for ";
                            segDistance = std::to_string((int)findStreetSegmentLength(currSeg));
                            routeTurn += segDistance +" meters";
                            pathDirections.push_back(routeTurn);
                        }
                    }
                    break;
                    default:
                    break; 
              }
 
              
              //update new previous intersection with current intersection 
              //update new current intersection with next intersection 
              //then update new previous segment with current segment 
              prevInter = currInter;
              currInter = nextInter;
              prevSeg = currSeg;
            } 
        }
    }
    return pathDirections;
}    

//call-back function for load map button.
//checks city and country inputs and refreshes drawing accordingly.
void city_input(std::string city, std::string country, ezgl::application* application){
    std::string new_map_path;
    std::string cityholder = city;
    std::string countryholder = country;
    
    std::for_each(city.begin(), city.end(), [](char & C){ //change to lower case
        C = ::tolower(C);
    });
    
    std::for_each(country.begin(), country.end(), [](char & C){ //change to lower case
        C = ::tolower(C);
    });
    
    city = std::regex_replace(city, std::regex(" "), "-");
    country = std::regex_replace(country, std::regex(" "), "-"); //remove spaces
    
    if(city == "n/a"){ //if only country has name
        new_map_path = "/cad2/ece297s/public/maps/" + country + ".streets.bin";
    }
    else if(country == "n/a"){ //if only city has name
        new_map_path = "/cad2/ece297s/public/maps/" + city + ".streets.bin";
    }
    else{
        new_map_path = "/cad2/ece297s/public/maps/"+city+"_"+country+".streets.bin";
    }
    closeMap(); //close old map
    bool load_successful = loadMap(new_map_path);
    
    if(!load_successful){ //if could not load new map, name input is wrong, old map gets reprinted.
        std::cout << "Invalid input!\n";
        new_map_path = map_path;
        loadMap(new_map_path);
        application->update_message(mapcity + " " + mapcountry);
    }
    else{ //successfully loaded new map, setting coordinates and data structures, then drawing map.
        mapcity = cityholder;
        mapcountry = countryholder;
        map_path = new_map_path;
        
        max_lat = getIntersectionPosition(0).latitude(); 
        min_lat = max_lat;
        max_lon = getIntersectionPosition(0).longitude();
        min_lon = max_lon;
        
        max_y = y_from_lat(max_lat);
        min_y = y_from_lat(min_lat);
        max_x = x_from_lon(max_lon);
        min_x = x_from_lon(min_lon);

        intersections.resize(getNumIntersections());
        setIntersections();
        streets.resize(getNumStreetSegments());
        setStreets();
        type_of_street();
        POIData.resize(getNumPointsOfInterest());
        setPOIs();
        sort_feat_types();

        ezgl::rectangle new_world({min_x, min_y}, {max_x, max_y});
        application->change_canvas_world_coordinates(application->get_main_canvas_id(), new_world);
        application->update_message(mapcity + " " + mapcountry);
    }
    
    application->refresh_drawing();
}

//Gtk button to load new map from user input in dialog box.
void load_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Loading New Map");
    application->refresh_drawing(); 
    
    //setting widgets
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    GtkWidget *city;
    GtkWidget *country;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Load Map ", (GtkWindow*) window, GTK_DIALOG_MODAL, ("OK"), GTK_RESPONSE_ACCEPT, ("CANCEL"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    label = gtk_label_new("Enter city and country name: \nIf not applicable, enter n/a.\nPress OK or CANCEL to close.");
    
    //creating text boxes
    city = gtk_entry_new();
    country = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(city), "City");
    gtk_entry_set_placeholder_text(GTK_ENTRY(country), "Country");

    //adding to dialog box
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), city);
    gtk_container_add(GTK_CONTAINER(content_area), country);
    gtk_widget_show_all(dialog);
    
    
    std::string cityname;
    std::string countryname;
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //based on user action, decide what happens next
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if they hit OK, check for input; if both boxes were NOT filled, then simply destroy dialog box.
            cityname = gtk_entry_get_text(GTK_ENTRY(city));
            countryname = gtk_entry_get_text(GTK_ENTRY(country));
            if((cityname.empty() == false) && (countryname.empty() == false)){
                gtk_widget_destroy(GTK_WIDGET (dialog));
                std::cout << "Drawing " << cityname << " " << countryname << "\n";
                city_input(cityname, countryname, application);
                break;
            }
            else{
                gtk_widget_destroy(GTK_WIDGET (dialog));
                application->update_message(mapcity + " " + mapcountry);
                break;
            }
         //the rest all close dialog box and do not change canvas.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit cancel \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing(); 
}

void directions_dialog(ezgl::application *application){
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Path Directions", (GtkWindow*) window, GTK_DIALOG_MODAL, ("OK"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    std::vector<std::string> directionsString = printDirections(highlightedPaths);
    std::string stringprint;
    for(int k = 0; k<directionsString.size(); k++){
        stringprint.append(directionsString[k]);
    }
    
    char pathChar[stringprint.size() + 1];
    strcpy(pathChar, stringprint.c_str());  
    //info to be printed in dialog box.
    label = gtk_label_new(pathChar);
    
    //adding all buttons to window.
    gtk_container_add(GTK_CONTAINER(content_area), label);
    
    gtk_widget_show_all(dialog);
    
    //call-back function for user action.
    g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
    
}

//identify where on canvas user clicked.
//decide what happens based on location clicked.
//passed in drawMap().
void act_on_mouse_click(ezgl::application* app, GdkEventButton* /*event*/, double x, double y){
    std::cout << "Mouse clicked at (" << x << "," << y << ")\n";
    LatLon pos = LatLon(lat_from_y(y), lon_from_x(x));
    std::stringstream ss;
    int count = 0;
    
    //if clicked on or very close to an intersection, highlight the intersection.
    IntersectionIdx id = findClosestIntersection(pos);
    if(findDistanceBetweenTwoPoints(std::make_pair(intersections[id].position, pos)) <= 50){
        if((intersections[id].highlight) == true){
            intersections[id].highlight = false;
            drawMarkers = false;
            for(int i = 0; i<streets.size(); i++){ //de-highlighting path if one or both of intersections are de-selected
                streets[i].onPath = false;
            }
            goto end;
        }
        else{
            intersections[id].highlight = true;
            pos1 = id;
            for(IntersectionIdx i = 0; i<intersections.size(); i++){
                pos2 = i;
                if((intersections[i].highlight == true) && (i != id)){
                    count++;//call find closest path function between pos1 and pos2
                    std::pair<IntersectionIdx, IntersectionIdx> inter_ids = std::make_pair(pos2, pos1);
                    highlightedPaths = findPathBetweenIntersections(15, inter_ids);
                    for(int ix = 0; ix<streets.size(); ix++){
                        for(int j = 0; j<highlightedPaths.size(); j++){
                            if(streets[ix].id == highlightedPaths[j]){
                                streets[ix].onPath = true;
                            }
                        }
                    }
                    count = i;
                    std::cout << "Displaying path between " << intersections[id].name << " and " << intersections[count].name << "\n";
                    std::cout << "Displaying directions:\n";
                    directions_dialog(app);
                    drawMarkers = true;
                    pos1 = i;
                    pos2 = id;
                    break;
                }  
            }
        }
        ss << "Intersection name: " << intersections[id].name << "          ";
        ss << "Intersection position: " << intersections[id].position.longitude() << ", " << intersections[id].position.latitude() << "   ";
    }
    //otherwise, place a png pin onto canvas.
    else{
        cursor.position = pos;
        cursor.intersection = false;
    }
    end:
    app->update_message(ss.str());
    app->refresh_drawing();
    
}

//setting all buttons on GUI.
//passed in drawMap().
void initial_setup (ezgl::application* application, bool /*new_window */){
    application->create_button ("Find Intersection", 6, find_button);
    application->create_button ("Find Path", 7, path_button);
    application->create_button("POI Filter", 8, POIs_button);
    application->create_button("Load Map", 9, load_button);
    application->create_button("Random POI", 10, rando_POI_button);
    application->create_button("Random Task", 11, rando_task_button);
    application->create_button("Clear", 12, clear_button);
    application->create_button("Dark Mode", 13, darkmode_button);
    application->create_button("Information", 14, info_button);
}

//dark mode button
//turns the map dark by altering colours
void darkmode_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Displaying map in dark mode.");
    application->refresh_drawing(); 
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Dark Mode", (GtkWindow*) window, GTK_DIALOG_MODAL, ("Display"), GTK_RESPONSE_ACCEPT, ("Hide"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Click to enter dark mode.");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit display, make dark mode bool true
            darkmode = true;
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit hide \n";
            darkmode = false;
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
    
}

void clear_intersections_and_paths(){
    for(int i = 0; i<streets.size(); i++){
        streets[i].onPath = false;
    }
    
    for(int j = 0; j<intersections.size(); j++){
        intersections[j].highlight = false;
    }
    
    drawMarkers = false;
    rando_poi = false;
    
}

void clear_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Clearing all intersections and paths.");
    application->refresh_drawing(); 
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;

    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Clear All", (GtkWindow*) window, GTK_DIALOG_MODAL, ("Clear"), GTK_RESPONSE_ACCEPT, ("Cancel"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Click to clear all intersections and paths.");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            std::cout << "User hit clear \n";
            clear_intersections_and_paths();
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            //std::cout << current_height;
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit cancel \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
    
}

//poi button to display all pois on map
void POIs_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Displaying points of interest.");
    application->refresh_drawing(); 
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;

    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Points Of Interest", (GtkWindow*) window, GTK_DIALOG_MODAL, ("Display"), GTK_RESPONSE_ACCEPT, ("Hide"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Click to display or hide POIs.");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            pois = true;
            showpoinames = true;
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message("Points of interest in " + mapcity + " " + mapcountry);
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit hide \n";
            pois = false;
            showpoinames = false;
            poinames = false;
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
    
}

//button to generate and display a random poi on map
void rando_POI_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Displaying random point of interest.");
    application->refresh_drawing(); 
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Random POI Generator", (GtkWindow*) window, GTK_DIALOG_MODAL, ("Generate Random POI"), GTK_RESPONSE_ACCEPT, NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Click to generate random POI.");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            pois = false;
            showpoinames = false;
            rando_poi = true;
            ifRightType = false;
            while(!ifRightType){
                srand(time(0));
                randoPOI= rand() % POIData.size();
                POItype = POIData[randoPOI].type;
        
                if(POItype == "bank" || POItype == "restaurant" || POItype == "library" ){
                    ifRightType = true;
                }
            }
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message("Generated random point of interest at: " + mapcity + " " + mapcountry);
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            rando_poi = false;
            application->update_message(mapcity + " " + mapcountry);
            break;
 
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
    
}

//button to generate and print a random task to complete associated with poi generated above.
void rando_task_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Generate Random Task.");
    application->refresh_drawing(); 
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Random Task Generator", (GtkWindow*) window, GTK_DIALOG_MODAL, ("Generate Random Task"), GTK_RESPONSE_ACCEPT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Click to generate random task.");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            srand(time(0));
            randoTask = rand() % 3;
            if(POItype == "bank"){
                application->update_message("Your task is: " + bankTasks[randoTask]);
            }
            else if(POItype == "restaurant"){
                application->update_message("Your task is: " + restTasks[randoTask]);
            }
            else if(POItype == "library"){
                application->update_message("Your task is: " + libTasks[randoTask]);
            }
            
            gtk_widget_destroy(GTK_WIDGET (dialog));
            //std::cout << current_height;
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            rando_poi = false;
            application->update_message(mapcity + " " + mapcountry);
            break;
 
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
}

//call-back for info button, simply displays user action in terminal and destroys dialog box.
void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer /*gp*/, ezgl::application /** app*/){
    // this will show the response type
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT:
            std::cout << "User hit accept \n";
            break;
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit cancel \n";
            break;
        default:
            std::cout << "UNKNOWN \n";
            break;
    }
    /*This will cause the dialog to be destroyed*/
    gtk_widget_destroy(GTK_WIDGET (dialog));
}

//find intersection from two street name inputs.
//call-back function for find button.
void find_intersection(std::string streetpref1, std::string streetpref2, ezgl::application* application){
    std::vector<StreetIdx> streets1 = findStreetIdsFromPartialStreetName(streetpref1);
    std::vector<StreetIdx> streets2 = findStreetIdsFromPartialStreetName(streetpref2);
    std::vector<IntersectionIdx> outputInter;
    std::cout << "Intersections between " << streetpref1 << " and " << streetpref2 << ": \n";
    
    //looping through the vectors of intersections for each street and combining the common ones.
    for(int i = 0; i<streets1.size(); i++){
        for(int j = 0; j<streets2.size(); j++){
            std::pair<StreetIdx, StreetIdx> street_ids = std::make_pair(streets1[i], streets2[j]);
            std::vector<IntersectionIdx> temp = findIntersectionsOfTwoStreets(street_ids);
            outputInter.insert(outputInter.end(), temp.begin(), temp.end());
        }
    }
    std::sort(outputInter.begin(), outputInter.end());  // Remove duplicate intersections at each street
    auto fixed = std::unique(outputInter.begin(), outputInter.end());
    outputInter.resize(std::distance(outputInter.begin(), fixed));
    for(int k = 0; k < outputInter.size(); k++){
        int p = outputInter[k];
        intersections[p].highlight = true; //highlighting each intersection to be displayed.
        std::cout << "Intersection Name: " << intersections[p].name << ",  Position: " << intersections[p].position.longitude() << ", " << intersections[p].position.latitude() << "\n";
    }
    application->update_message("Intersections between " + streetpref1 + " and " + streetpref2 + " are highlighted in red.");
    application->refresh_drawing();
}

//finds and highlights given path on map using user inputted names for intersections. 
void find_path(std::string streetpref1, std::string streetpref2, ezgl::application* application){
    std::string inter1 = streetpref1;
    std::string inter2 = streetpref2;
    bool foundInter1 = false;
    bool foundInter2 = false;
    std::vector<std::string> streetsNames1;
    std::vector<std::string> streetsNames2;
    std::vector<IntersectionIdx> Intersections1;
    std::vector<IntersectionIdx> Intersections2;
    
    for(int i = 0; i<streets.size(); i++){ //de-highlighting path from before.
        streets[i].onPath = false;
    }
    
    std::size_t inter1n1 = inter1.find_first_of("&");
    //std::size_t inter1n2 = inter1.find_last_of("&");
    std::size_t inter2n1 = inter2.find_first_of("&");
    //std::size_t inter2n2 = inter2.find_last_of("&");
    
    if(inter1n1==std::string::npos || inter2n1==std::string::npos){
        std::cout << "Error: no '&' used, please see information for correct syntax.\n";
        return;
    }
    else{
        std::string street1 = inter1.substr(0, inter1n1);
        std::string secondstreet1 = inter2.substr(0, inter2n1);
        streetsNames1.push_back(street1);
        streetsNames2.push_back(secondstreet1);
        std::string street2 = inter1.substr(inter1n1+1, std::string::npos);
        std::string secondstreet2 = inter2.substr(inter2n1+1, std::string::npos);
        streetsNames1.push_back(street2);
        streetsNames2.push_back(secondstreet2);
    }
    
    std::vector<StreetIdx> streetIDs1, streetIDs2, streetIDs3, streetIDs4;
    
    streetIDs1 = findStreetIdsFromPartialStreetName(streetsNames1[0]);
    streetIDs2 = findStreetIdsFromPartialStreetName(streetsNames1[1]);
    streetIDs3 = findStreetIdsFromPartialStreetName(streetsNames2[0]);
    streetIDs4 = findStreetIdsFromPartialStreetName(streetsNames2[1]);
    if(streetIDs1.size() == 0 || streetIDs2.size() == 0 || streetIDs3.size() == 0 || streetIDs4.size() == 0){
        std::cout << "Error: at least one street not recognized. Please try again with valid input.\n";
        return;
    }
    else{
        for(int i = 0; i<streetIDs1.size(); i++){
            for(int j = 0; j<streetIDs2.size(); j++){
                Intersections1 = findIntersectionsOfTwoStreets(std::make_pair(streetIDs1[i], streetIDs2[j]));
                if(Intersections1.size() !=0){
                    foundInter1 = true;
                    goto end1;
                }
            }
        }
        end1:
        for(int i = 0; i<streetIDs3.size(); i++){
            for(int j = 0; j<streetIDs4.size(); j++){
                Intersections2 = findIntersectionsOfTwoStreets(std::make_pair(streetIDs3[i], streetIDs4[j]));
                if(Intersections2.size() !=0){
                    foundInter2 = true;
                    goto end2;
                }
            }
        }
    }
    end2:

    pos1 = Intersections1[0];
    pos2 = Intersections2[0];

    if(foundInter1 && foundInter2){
        //call find closest path function using pos1 and pos2. 
        //highlight all street segments returned from function above using bool onPath
        std::cout << "Displaying path between " << streetpref1 << " and " << streetpref2 << ".\n";
        std::pair<IntersectionIdx, IntersectionIdx> inter_ids = std::make_pair(pos1, pos2);
        highlightedPaths = findPathBetweenIntersections(15, inter_ids);
        for(int i = 0; i<streets.size(); i++){
            for(int j = 0; j<highlightedPaths.size(); j++){
                if(streets[i].id == highlightedPaths[j]){
                    streets[i].onPath = true;
                }
            }
        }
        std::cout << "Displaying directions:\n";
        directions_dialog(application);
        application->refresh_drawing();
    }
    else{
        std::cout << "Invalid input, please try again with valid intersection names.\n";
        application->refresh_drawing();
    }
}

//button to allow user to input 2 intersections to find path between them.
void path_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Find path between two intersections: ");
    application->refresh_drawing(); 
    
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    GtkWidget *intersection1;
    GtkWidget *intersection2;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Find Path ", (GtkWindow*) window, GTK_DIALOG_MODAL, ("OK"), GTK_RESPONSE_ACCEPT, ("CANCEL"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Enter two intersections: \nPress OK or CANCEL to close.");
    
    //text input boxes to be printed.
    intersection1 = gtk_entry_new();
    intersection2 = gtk_entry_new();
    
    gtk_entry_set_placeholder_text(GTK_ENTRY(intersection1), "Intersection 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(intersection2), "Intersection 2");

    //adding elements to dialog box.
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), intersection1);
    gtk_container_add(GTK_CONTAINER(content_area), intersection2);
    gtk_widget_show_all(dialog);

    std::string street_pref1;
    std::string street_pref2;
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            street_pref1 = gtk_entry_get_text(GTK_ENTRY(intersection1));
            street_pref2 = gtk_entry_get_text(GTK_ENTRY(intersection2));
            if((street_pref1.empty() == false) && (street_pref2.empty() == false)){
                gtk_widget_destroy(GTK_WIDGET (dialog));
                find_path(street_pref1, street_pref2, application);
                drawMarkers = true;
            }
            else{
                gtk_widget_destroy(GTK_WIDGET (dialog));
                application->update_message(mapcity + " " + mapcountry);
            }
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit cancel \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
}

//display information about map as dialog box.
//utilizes Gtk library.
void info_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("About the map");
    application->refresh_drawing(); 
    
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Map Info", (GtkWindow*) window, GTK_DIALOG_MODAL, ("OK"), GTK_RESPONSE_ACCEPT, ("CANCEL"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //info to be printed in dialog box.
    label = gtk_label_new("One-way streets are pink.\nHighways are orange.\nHighlighted intersections and paths are red.\n'Find Path' button prints directions in terminal for desired route. "
            "Street names must be separated by &'s.\nOnly click 2 intersections at a time to highlight paths.\nPress OK or CANCEL to close.");
    
    //adding all buttons to window.
    gtk_container_add(GTK_CONTAINER(content_area), label);
    
    gtk_widget_show_all(dialog);
    
    //call-back function for user action.
    g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(on_dialog_response), NULL);
    
    application->update_message(mapcity + " " + mapcountry);
    application->refresh_drawing();
}

//find button; finds intersections between two streets.
//creates a dialog box for user to input 2 streets.
void find_button(GtkWidget* /*widget*/, ezgl::application* application){
    application->update_message("Find intersections of two streets");
    application->refresh_drawing(); 
    
    //widgets to be used.
    GObject *window;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *dialog;
    GtkWidget *street1;
    GtkWidget *street2;
    
    window = application->get_object(application->get_main_window_id().c_str());
    
    dialog = gtk_dialog_new_with_buttons("Find ", (GtkWindow*) window, GTK_DIALOG_MODAL, ("OK"), GTK_RESPONSE_ACCEPT, ("CANCEL"), GTK_RESPONSE_REJECT, NULL);
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    //text to be printed on dialog box.
    label = gtk_label_new("Enter two street names: \nPress OK or CANCEL to close.");
    
    //text input boxes to be printed.
    street1 = gtk_entry_new();
    street2 = gtk_entry_new();
    
    gtk_entry_set_placeholder_text(GTK_ENTRY(street1), "Street 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(street2), "Street 2");

    //adding elements to dialog box.
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), street1);
    gtk_container_add(GTK_CONTAINER(content_area), street2);
    gtk_widget_show_all(dialog);

    std::string street_pref1;
    std::string street_pref2;
    gint response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    
    //checking for user action.
    switch(response_id) {
        case GTK_RESPONSE_ACCEPT: //if user hit OK, check that both boxes were filled; otherwise just close dialog box.
            street_pref1 = gtk_entry_get_text(GTK_ENTRY(street1));
            street_pref2 = gtk_entry_get_text(GTK_ENTRY(street2));
            if((street_pref1.empty() == false) && (street_pref2.empty() == false)){
                gtk_widget_destroy(GTK_WIDGET (dialog));
                find_intersection(street_pref1, street_pref2, application);
            }
            else{
                gtk_widget_destroy(GTK_WIDGET (dialog));
                application->update_message(mapcity + " " + mapcountry);
            }
            break;
        //if any other button is pressed, close dialog box.
        case GTK_RESPONSE_DELETE_EVENT:
            std::cout << "User hit close \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        case GTK_RESPONSE_REJECT:
            std::cout << "User hit cancel \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
        default:
            std::cout << "UNKNOWN \n";
            gtk_widget_destroy(GTK_WIDGET (dialog));
            application->update_message(mapcity + " " + mapcountry);
            break;
    }
    application->refresh_drawing();
}

//draw features onto map
//according to feature type and zoom scale.
void draw_features(ezgl::renderer *g){
    //draw all lakes
    if(darkmode)
        g->set_color(17, 41, 69);
    else
        g->set_color(170, 218, 255);
    draw_single_feature_type(g, lakeFeatIds);
    
    
    //draw all rivers
    if(rivers){
        if(darkmode)
            g->set_color(8, 25, 46);
        else
            g->set_color(170, 218, 255);
        draw_single_feature_type(g, riverFeatIds);
    }
    //draw all islands
    if(darkmode)
        g->set_color(43, 37, 31);
    else
        g->set_color(225, 204, 153);
    draw_single_feature_type(g, islandFeatIds);
    
    //draw all green spaces
    if(darkmode)
        g->set_color(16, 46, 42);
    else
        g->set_color(195, 236, 178);
    draw_single_feature_type(g, greenspaceFeatIds);
    
    //draw all buildings
    if(buildings){
        if(darkmode)
            g->set_color(99, 103, 105);
        else
            g->set_color(232, 220, 202);
        draw_single_feature_type(g, buildingFeatIds);
    }
    //draw all beaches
    if(darkmode)
        g->set_color(59, 48, 43);
    else
        g->set_color(ezgl::BISQUE);
    draw_single_feature_type(g, beachFeatIds);

    
    //draw all parks
    if(darkmode)
        g->set_color(34, 84, 77);
    else
        g->set_color(134, 194, 156);
    draw_single_feature_type(g, parkFeatIds);

    
    //draw all unknowns
    g->set_color(ezgl::WHITE);
    draw_single_feature_type(g, unknownFeatIds);

    
    //draw all golf courses
    if(darkmode)
        g->set_color(101, 168, 159);
    else
        g->set_color(27, 162, 97);
    draw_single_feature_type(g, golfcourseFeatIds);

    
    //draw all streams
    if(rivers){
        if(darkmode)
            g->set_color(51, 102, 135);
        else
            g->set_color(170, 218, 255);
        draw_single_feature_type(g, streamFeatIds);
    }
 
      
   
    //reset color
    g->set_color(ezgl::BLACK);
}

//sorts all the features into into respective vectors of the same type
void sort_feat_types(){
    islandFeatIds.resize(0);
    lakeFeatIds.resize(0);
    riverFeatIds.resize(0);
    greenspaceFeatIds.resize(0);
    buildingFeatIds.resize(0);
    beachFeatIds.resize(0);
    parkFeatIds.resize(0);
    unknownFeatIds.resize(0);
    golfcourseFeatIds.resize(0);
    streamFeatIds.resize(0);
    
    for(size_t feature_id = 0; feature_id < getNumFeatures(); feature_id ++){
        
        //get feature type of this particular feature id
        FeatureType ftype = getFeatureType(feature_id);
        
        //sorts it into respective vectors of type
        if(ftype == ISLAND) {

            islandFeatIds.push_back(feature_id);

        }else if(ftype == LAKE){
            lakeFeatIds.push_back(feature_id);
            
        }else if(ftype == RIVER){  
            riverFeatIds.push_back(feature_id);
        }
        
        else if(ftype == GREENSPACE){
            greenspaceFeatIds.push_back(feature_id);
            
        }else if(ftype == BUILDING){
           buildingFeatIds.push_back(feature_id);
            
        }else if(ftype == BEACH){
            beachFeatIds.push_back(feature_id);
        
        }else if(ftype == PARK){
            parkFeatIds.push_back(feature_id);
        
        }else if(ftype == UNKNOWN) {
            unknownFeatIds.push_back(feature_id);
  
        }else if(ftype == GOLFCOURSE) {
            golfcourseFeatIds.push_back(feature_id);
            
        }else if(ftype == STREAM) {   
            streamFeatIds.push_back(feature_id);
        }
    }
}

//loops and displays a vector of feature ids
void draw_single_feature_type(ezgl::renderer *g, std::vector<size_t> typeFeatIds){
    for(int i = 0; i < typeFeatIds.size(); i++){
        //get feature id
        size_t feat_id = typeFeatIds[i];
        int numPoints = getNumFeaturePoints(feat_id);
        bool closedPolygon = false;
        
        //check if the feature is a closed polygon
        if(numPoints >= 3){
         closedPolygon = (getFeaturePoint(0, feat_id) == getFeaturePoint(numPoints-1, feat_id));
        }
        
        std::vector<ezgl::point2d> points;
        ezgl::point2d point ;
        
        //build vector of feature pts
        for(int point_no = 0; point_no < numPoints ; point_no++){
            LatLon position = getFeaturePoint(point_no,feat_id);
            point.x = x_from_lon(position.longitude());
            point.y = y_from_lat(position.latitude());
            points.push_back(point);
        }
        
        //draw feature on map 
        if(closedPolygon){
            g->fill_poly(points);
        }else{
            //Draw line segments
            for(int point_no=0; point_no < numPoints-1; point_no++){
                g->draw_line(points[point_no],points[point_no+1]);
            }
        }
    }
}

//drawing streets onto map
//according to street segment type and zoom scale.
void draw_streets(ezgl::renderer *g){
    // draw streets, major/minor roads, one ways 
    for(size_t j=0; j < streets.size(); j++){
        g->set_line_width(1);
        if(streets[j].onPath){
            g->set_color(247, 35, 81);
        }
        else if(streets[j].oneWay){
            if(darkmode)
                g->set_color(102, 18, 56);
            else
                g->set_color(ezgl::PINK);
        }
        else{
            if(darkmode)
                g->set_color(117, 122, 133);
            else
                g->set_color(ezgl::WHITE);
        }
            
        
        size_t f = streets[j].from;
        size_t t = streets[j].to;

        float x1 = x_from_lon(intersections[f].position.longitude());
        float y1 = y_from_lat(intersections[f].position.latitude());
        float x2 = x_from_lon(intersections[t].position.longitude());
        float y2 = y_from_lat(intersections[t].position.latitude());
        
        if(streets[j].numCurvePoints == 0){
            if(majorRoads){
                if(streets[j].major){
                    g->set_line_width(3);
                    g->draw_line({x1, y1}, {x2, y2});
                }
                else if(streets[j].highway){
                    g->set_line_width(3);
                    if(darkmode)    
                        g->set_color(207, 78, 19);
                    else
                        g->set_color(ezgl::ORANGE);
                    g->draw_line({x1, y1}, {x2, y2});
                }
            }
            if(minorRoads)
                g->draw_line({x1, y1}, {x2, y2});
        }
        else{
            LatLon curvept1 = getStreetSegmentCurvePoint(0, j);
            double curvept1X = x_from_lon(curvept1.longitude());
            double curvept1Y = y_from_lat(curvept1.latitude());
            
            LatLon curvept2 = getStreetSegmentCurvePoint(((streets[j].numCurvePoints) - 1), j);
            double curvept2X = x_from_lon(curvept2.longitude());
            double curvept2Y = y_from_lat(curvept2.latitude());

            if(majorRoads){
                if(streets[j].major){
                    g->set_line_width(3);
                }
                else if(streets[j].highway){
                    g->set_line_width(3);
                    if(darkmode)    
                        g->set_color(207, 78, 19);
                    else
                        g->set_color(ezgl::ORANGE);
                }
            }
            if(!streets[j].major && !streets[j].highway){
                if(!minorRoads){
                    continue;
                }
            }

            g->draw_line({x1, y1}, {curvept1X, curvept1Y});
            g->draw_line({curvept2X, curvept2Y}, {x2, y2});
            
            for(int i = 0; i<(streets[j].numCurvePoints-1); i++){
                LatLon curveptOne = getStreetSegmentCurvePoint(i, j);
                LatLon curveptTwo = getStreetSegmentCurvePoint(i+1, j);
                
                double curveptOneX = x_from_lon(curveptOne.longitude());
                double curveptOneY = y_from_lat(curveptOne.latitude());
                double curveptTwoX = x_from_lon(curveptTwo.longitude());
                double curveptTwoY = y_from_lat(curveptTwo.latitude());
                
                g->draw_line({curveptOneX, curveptOneY}, {curveptTwoX, curveptTwoY});
            }
        }
    }
}

//draws street names onto map
//according to whether it's oneWay and its rotation.
void draw_streetNames(ezgl::renderer *g){
    for(size_t j=0; j < streets.size(); j++){
        size_t f = streets[j].from;
        size_t t = streets[j].to;

        float x1 = x_from_lon(intersections[f].position.longitude());
        float y1 = y_from_lat(intersections[f].position.latitude());
        float x2 = x_from_lon(intersections[t].position.longitude());
        float y2 = y_from_lat(intersections[t].position.latitude());

    // draw street names ; j = street_id
       float dx_diff = x2-x1; 
       float dy_diff = y2-y1; 
       double rotation_angle = 0;

       if(dx_diff == 0){
           rotation_angle = 90;
       }
       else{
         if(streets[j].numCurvePoints == 0){
             dx_diff = x2-x1;
             dy_diff = y2-y1; 
             if(dx_diff != 0)
               rotation_angle = (std::atan(dy_diff/dx_diff))*(180/M_PI);
             else
                 rotation_angle = 90;
         }
         else{
             int middlepoint = streets[j].numCurvePoints/2;
             if(middlepoint != (streets[j].numCurvePoints -1)){
                 dx_diff = x_from_lon(getStreetSegmentCurvePoint(middlepoint+1, j).longitude()) - x_from_lon(getStreetSegmentCurvePoint(middlepoint, j).longitude());
                 dy_diff = y_from_lat(getStreetSegmentCurvePoint(middlepoint+1,j).latitude()) - y_from_lat(getStreetSegmentCurvePoint(middlepoint,j).latitude());
                 if(dx_diff != 0){
                     rotation_angle = (std::atan(dy_diff/dx_diff))*(180/M_PI);
                 }
                 else{
                     rotation_angle = 90;
                 }
             }
             else{
                 dx_diff = x_from_lon(intersections[t].position.longitude()) - x_from_lon(getStreetSegmentCurvePoint(middlepoint, j).longitude());
                 dy_diff = y_from_lat(intersections[t].position.latitude()) - y_from_lat(getStreetSegmentCurvePoint(middlepoint, j).latitude());
                 if(dx_diff != 0){
                     rotation_angle = (std::atan(dy_diff/dx_diff))*(180/M_PI);
                 }
                 else{
                     rotation_angle = 90;
                 }
             }
         }
       }
       if(minorStreetNames){
            if(!streets[j].highway && !streets[j].major){
               goto print;
            }
            else
                continue;      
       }
       if(majorStreetNames){
           if(streets[j].highway || streets[j].major){
               goto print;
           }
           else
                continue;   
       }
       print:
       std::string strtName = "Unknown";
       try{
            strtName = getStreetName(j);
            
            if(streets[j].oneWay){
                g->set_color(ezgl::BLACK);

                if(dx_diff <0){   // negative lat             
                    g->set_color(179, 179, 179);
                    strtName += "<-";
                    
                    g->set_text_rotation(rotation_angle);
                    g->draw_text({((x1+x2)/2),((y1+y2)/2)},strtName, strtLen, strtLen);
                    g->set_color(ezgl::BLACK);
                 }else{ 
                    g->set_color(179, 179, 179);
                     strtName += "->";
                     
                    g->set_text_rotation(rotation_angle);
                    g->draw_text({((x1+x2)/2),((y1+y2)/2)},strtName, strtLen, strtLen);
                    g->set_color(ezgl::BLACK);
                 }
            }else{              //two way streets
                g->set_color(179, 179, 179);
                g->set_text_rotation(rotation_angle);
                g->draw_text({((x1+x2)/2),((y1+y2)/2)}, strtName, strtLen, strtLen);
                g->set_color(ezgl::BLACK);
            }
       }
       catch(std::exception &e){
            g->set_color(173, 216, 230);
       } 
    } 
}

//draws intersections and highlights them if they are marked.
//based on zoom scale.
void draw_intersections(ezgl::renderer *g){
    ezgl::surface *png_surface = ezgl::renderer::load_png("libstreetmap/resources/small_image_1.png");
    for(size_t i = 0; i < intersections.size(); ++i){
        float width;
        //if highlighted, make bigger and red.
        if(intersections[i].highlight){
            width = 10;
            g->set_color(237, 130, 107);
        }
        //otherwise make small and white.
        else{
            if(!printIntersections){
                goto lcursor;
            }
            else{
                width = 2;
                if(darkmode)
                    g->set_color(ezgl::GREY_55);
                else
                    g->set_color(ezgl::WHITE);
            }
        }
        
        float x = x_from_lon(intersections[i].position.longitude());
        float y = y_from_lat(intersections[i].position.latitude());
        
        g->fill_arc({x, y}, width, 0, 360);
    }
    
    //if user did not click on an intersection, print cursor pin instead.
    lcursor:
    if(cursor.intersection == false){
        int x = x_from_lon(cursor.position.longitude());
        int y = y_from_lat(cursor.position.latitude());
        g->draw_surface(png_surface, {1.0*x, 1.0*y}, 0.050);
    }
    ezgl::renderer::free_surface(png_surface);
}

//draw POIs and their names according to zoom scale.
void draw_pois(ezgl::renderer *g){
    // load all png images to be sued as icon
    ezgl::surface *lib_png = ezgl::renderer::load_png("libstreetmap/resources/library.png");
    ezgl::surface *doc_png = ezgl::renderer::load_png("libstreetmap/resources/doctors.png");
    ezgl::surface *school_png = ezgl::renderer::load_png("libstreetmap/resources/school.png");
    ezgl::surface *bank_png = ezgl::renderer::load_png("libstreetmap/resources/bank.png");
    ezgl::surface *resta_png = ezgl::renderer::load_png("libstreetmap/resources/restaurants.png");
    
    //loop through all POIs
    for(POIIdx i = 0; i < POIData.size(); i++){
        //position for POI name 
        ezgl::point2d textCenter1;
        
        textCenter1 = POIData[i].poiCenter;
        
        //lower the text 15 pixels lower than the POI icon
        textCenter1.y = textCenter1.y - 15.0;

        //draw png icons using ezgl built in functions 
        //draw all POIs with type library
        if(POIData[i].type == "library" && ifPOILib){
            g->draw_surface(lib_png , POIData[i].poiCenter, 0.05);
            g->set_color(25, 116, 210);
            if(poinames)
                g->draw_text(textCenter1, POIData[i].name);
        }
        
        //draw all POIs with type doctors
        else if(POIData[i].type == "doctors" && ifPOIDoc){
            g->draw_surface(doc_png , POIData[i].poiCenter, 0.040);
            g->set_color(25, 116, 210);
            if(poinames)
                g->draw_text(textCenter1, POIData[i].name);
        }
        
        //draw all POIs with type school
        else if(POIData[i].type == "school" && ifPOISchool){
            
            g->draw_surface(school_png, POIData[i].poiCenter, 0.01);
            g->set_color(25, 116, 210);
            if(poinames)
                g->draw_text(textCenter1, POIData[i].name);
        }
        
         //draw all POIs with type  bank
        else if(POIData[i].type == "bank" && ifPOIBank){
            g->draw_surface(bank_png , POIData[i].poiCenter, 0.025);
            g->set_color(25, 116, 210);
            if(poinames)
                g->draw_text(textCenter1, POIData[i].name);
        }
        else if(POIData[i].type == "restaurant" && ifPOIResta){
            g->draw_surface(resta_png , POIData[i].poiCenter, 0.05);
            g->set_color(25, 116, 210);
            if(poinames)
                g->draw_text(textCenter1, POIData[i].name);
        }
    }
    ezgl::renderer::free_surface(lib_png);
    ezgl::renderer::free_surface(doc_png);
    ezgl::renderer::free_surface(school_png);
    ezgl::renderer::free_surface(bank_png);
    ezgl::renderer::free_surface(resta_png);
}

//draws randomly generated poi onto map.
void draw_rando_poi(ezgl::renderer *g){
    ezgl::surface *lib_png = ezgl::renderer::load_png("libstreetmap/resources/library.png");
    ezgl::surface *bank_png = ezgl::renderer::load_png("libstreetmap/resources/bank.png");
    ezgl::surface *resta_png = ezgl::renderer::load_png("libstreetmap/resources/restaurants.png");
    
    //position for POI name 
    ezgl::point2d textCenter1;
        
    textCenter1 = POIData[randoPOI].poiCenter;
        
    //lower the text 15 pixels lower than the POI icon
    textCenter1.y = textCenter1.y - 15.0;

    //draw png icons using ezgl built in functions 
    //draw all POIs with type library
    if(POItype == "library" && ifRightType){
        g->draw_surface(lib_png , POIData[randoPOI].poiCenter, 0.05);
        g->set_color(25, 116, 210);
        g->draw_text(textCenter1, POIData[randoPOI].name);
    }
    //draw all POIs with type  bank
    else if(POItype == "bank" && ifRightType){
        g->draw_surface(bank_png , POIData[randoPOI].poiCenter, 0.025);
        g->set_color(25, 116, 210);
        g->draw_text(textCenter1, POIData[randoPOI].name);
    }
    else if(POItype == "restaurant" && ifRightType){
        g->draw_surface(resta_png , POIData[randoPOI].poiCenter, 0.05);
        g->set_color(25, 116, 210);
        g->draw_text(textCenter1, POIData[randoPOI].name);
    }
    
}

void draw_markers(ezgl::renderer *g){
    double x1 = x_from_lon(intersections[pos1].position.longitude());
    double y1 = y_from_lat(intersections[pos1].position.latitude());
    double x2 = x_from_lon(intersections[pos2].position.longitude());
    double y2 = y_from_lat(intersections[pos2].position.latitude());
    
    ezgl::point2d coords1(x1, y1);
    ezgl::point2d coords2(x2, y2);
    
    ezgl::surface *runner_png = ezgl::renderer::load_png("libstreetmap/resources/runner.png");
    ezgl::surface *flag_png = ezgl::renderer::load_png("libstreetmap/resources/flag.png");
    
    g->draw_surface(runner_png, coords1, 0.05);
    g->set_horiz_justification(ezgl::justification::left);
    g->set_vert_justification(ezgl::justification::bottom);
    g->draw_surface(flag_png, coords2, 0.06);
    
    ezgl::renderer::free_surface(runner_png);
    ezgl::renderer::free_surface(flag_png);
}
//draw main canvas; called every time drawing is refreshed.
void draw_main_canvas(ezgl::renderer *g){
    //drawing the entire base canvas.
    g->draw_rectangle({min_x, min_y}, {max_x, max_y});
    
    if(darkmode)
        g->set_color(51, 57, 69);
    else    
        g->set_color(232, 211, 185, 100);
    g->fill_rectangle({min_x, min_y}, {max_x, max_y});
    zoom_scale(g);
    
    //prints features if zoomed in enough
    if(features)
        draw_features(g); 
 
    draw_streets(g);
    
    draw_intersections(g);

    //prints out all POIs in red dots if zoomed in enough
    if(pois)
        draw_pois(g);
    if(rando_poi)
        draw_rando_poi(g);
    
    //prints street names if zoomed in enough
    if(majorStreetNames == true || minorStreetNames == true)
        draw_streetNames(g);
    
    if(drawMarkers)
        draw_markers(g);
        
}

//called in main.cpp after loadMap().
//draws and opens application.
void drawMap() {
    // Setup EZGL configuration
    max_lat = getIntersectionPosition(0).latitude(); 
    min_lat = max_lat;
    max_lon = getIntersectionPosition(0).longitude();
    min_lon = max_lon;

    max_y = y_from_lat(max_lat);
    min_y = y_from_lat(min_lat);
    max_x = x_from_lon(max_lon);
    min_x = x_from_lon(min_lon);

    intersections.resize(getNumIntersections());
    setIntersections();
    streets.resize(getNumStreetSegments());
    setStreets();
    type_of_street();
    POIData.resize(getNumPointsOfInterest());
    setPOIs();
    
    //sort all features into "buckets" of same types
    sort_feat_types();
        
    ezgl::application::settings settings;
    settings.main_ui_resource = "libstreetmap/resources/main.ui";
    settings.window_identifier = "MainWindow";
    settings.canvas_identifier = "MainCanvas";
    
    // Create EZGL application
    ezgl::application application(settings);
    
    // Define canvas
    ezgl::rectangle initial_world({min_x, min_y}, {max_x, max_y});
    application.add_canvas("MainCanvas", draw_main_canvas, initial_world);
    
    // run application, pass control to EZGL, graphics window will open
    // will not return return until graphics closed
    application.run(initial_setup, act_on_mouse_click, nullptr, nullptr);
}
