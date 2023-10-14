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
 */
#include <iostream>
#include "m1.h"
//#include "loadHelper.h"
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <regex>

class LatLon; //Forward declaration
class OSMID; //Forward declaration

/************** helper functions declarations **************/
void build_OSMID_node_hashmap();
void build_intersection_street_segments_2dvector();
void build_street_segment_names();
void build_streetSeg_lengths_times();
//void build_intersections_of_street();
//void getIntersectionsOfStreetName(StreetIdx streetID);

/************** helper data structures declarations **************/
std::vector<std::vector<StreetSegmentIdx>> intersection_street_segments;
std::unordered_map<OSMID, LatLon> nodeCoordHash;
std::vector<std::vector<std::string>> si_names;
std::vector<double> ss_lengths;
std::vector<double> ss_times;
// loadMap will be called with the name of the file that stores the "layer-2"
// map data accessed through StreetsDatabaseAPI: the street and intersection 
// data that is higher-level than the raw OSM data). 
// This file name will always end in ".streets.bin" and you 
// can call loadStreetsDatabaseBIN with this filename to initialize the
// layer 2 (StreetsDatabase) API.
// If you need data from the lower level, layer 1, API that provides raw OSM
// data (nodes, ways, etc.) you will also need to initialize the layer 1 
// OSMDatabaseAPI by calling loadOSMDatabaseBIN. That function needs the 
// name of the ".osm.bin" file that matches your map -- just change 
// ".streets" to ".osm" in the map_streets_database_filename to get the proper
// name.

bool loadMap (std::string map_name) {
    bool load_str_successful;
    bool load_OSM_successful;
    //bool load_successful = loadStreetsDatabaseBIN(map_name);
                                                                    
    //intersection_street_segments.resize (getNumIntersections () );
    
    //catching for any load map errors
    try{
        load_str_successful = loadStreetsDatabaseBIN(map_name); 
        load_OSM_successful = loadOSMDatabaseBIN(std::regex_replace(map_name, std::regex(".streets.bin"), ".osm.bin")); 
    }catch(...){
        std::cerr<< "\n exception! \n";
        return false;
    }
    
    bool load_successful = (load_str_successful && load_OSM_successful);
    
    //checking if map exists to do rest of function
    if(load_successful) {
        
        build_intersection_street_segments_2dvector();

        build_OSMID_node_hashmap();
        
        build_street_segment_names();
        
        build_streetSeg_lengths_times();
        
    }                                                       
    //maybe build a unified hash map of street attributes i.e streetId -> StreetSeg
    
    return load_successful;
}

/******helper functions declarations*******/
// building a 2d vector of intersection street segment IDS for faster lookup
void build_intersection_street_segments_2dvector(){
    intersection_street_segments.resize (getNumIntersections());
    
    for (IntersectionIdx intersection = 0; intersection < getNumIntersections() ; ++intersection) { 
        for (int i = 0; i < getNumIntersectionStreetSegment (intersection); ++i) {
            int ss_id = getIntersectionStreetSegment (i, intersection);
            intersection_street_segments[intersection].push_back(ss_id);                                                      
        }
    }
}

//Build data structure of street segment names per intersection.
void build_street_segment_names(){
    si_names.resize (getNumIntersections());
    for(IntersectionIdx intersection = 0; intersection < getNumIntersections() ; ++intersection) {
        std::vector<StreetSegmentIdx> ss_ids = findStreetSegmentsOfIntersection(intersection);
        for(int i = 0; i < ss_ids.size(); ++i) {
            StreetSegmentInfo streetsegment = getStreetSegmentInfo(ss_ids[i]); // For each street segment, get its struct info.
            si_names[intersection].push_back(getStreetName(streetsegment.streetID)); // Add name to vector to be returned.
        }
    }
}

//build a hashmap of (OSMID, LatLon) key-value pairs for O(1) search 
void build_OSMID_node_hashmap(){
    for(int idx = 0; idx < getNumberOfNodes(); idx++){
            nodeCoordHash[getNodeByIndex(idx)->id()] = getNodeCoords(getNodeByIndex(idx));
    }
}

void build_streetSeg_lengths_times(){
    for(StreetSegmentIdx street_segment_id = 0; street_segment_id < getNumStreetSegments(); street_segment_id++){
        StreetSegmentInfo seg_info = getStreetSegmentInfo(street_segment_id);
        double seg_length = 0.0;
        double seg_time=  0.0;
        
            LatLon pos_from = getIntersectionPosition(seg_info.from);
            LatLon pos_to= getIntersectionPosition(seg_info.to);

        if(seg_info.numCurvePoints == 0){    
            //if there are no curve pts, directly calculate distance between the 2 pts
            seg_length = findDistanceBetweenTwoPoints(std::make_pair(pos_from, pos_to)); 
            
        }else{
            //if there are curve pts, loop through each and update seg length
            LatLon start_point = pos_from;
            for (int curvePointNum = 0; curvePointNum < seg_info.numCurvePoints; curvePointNum++){
                LatLon end_point = getStreetSegmentCurvePoint (curvePointNum, street_segment_id);
                
                seg_length += findDistanceBetweenTwoPoints(std::make_pair(start_point, end_point));
                start_point = end_point;
                
            }
            seg_length += findDistanceBetweenTwoPoints(std::make_pair(start_point, pos_to));
        }
        seg_time = seg_length / seg_info.speedLimit;
        ss_lengths.push_back(seg_length);
        
        ss_times.push_back(seg_time);
    }
    
}

//Clean-up map related data structures here.
void closeMap() {
    intersection_street_segments.erase(intersection_street_segments.begin(), intersection_street_segments.end());
    si_names.erase(si_names.begin(), si_names.end());
    closeStreetDatabase();
    closeOSMDatabase();
}


// Returns the distance between two (latitude,longitude) coordinates in meters
// Speed Requirement --> moderate
double findDistanceBetweenTwoPoints(std::pair<LatLon, LatLon> points){

    double latAvg = (points.first.latitude()*(M_PI/180) + points.second.latitude()*(M_PI/180))/2;

    double x =  kEarthRadiusInMeters * (points.first.longitude()*(M_PI/180))*cos(latAvg);
    double x2 = kEarthRadiusInMeters * (points.second.longitude()* (M_PI/180))*cos(latAvg);

    double y = kEarthRadiusInMeters * (points.first.latitude()* (M_PI/180));
    double y2 = kEarthRadiusInMeters * (points.second.latitude()* (M_PI/180));

    double distance = sqrt(pow((y2-y),2)+(pow((x2-x),2)));
    
    return distance;
}

// Returns the length of the given street segment in meters
// Speed Requirement --> moderate
 double findStreetSegmentLength(StreetSegmentIdx street_segment_id){
    return ss_lengths[street_segment_id];
 }
 
// Returns the travel time to drive from one end of a street segment 
// to the other, in seconds, when driving at the speed limit
// Note: (time = distance/speed_limit)
// Speed Requirement --> high d
double findStreetSegmentTravelTime(StreetSegmentIdx street_segment_id){
    return ss_times[street_segment_id];
}

//Hiba's Functions
//Returns whether or not intersections are directly connected
bool intersectionsAreDirectlyConnected(std::pair<IntersectionIdx, IntersectionIdx> intersection_ids){
    for(int i= 0; i<intersection_street_segments[intersection_ids.first].size(); ++i){
        for(int j=0; j<intersection_street_segments[intersection_ids.second].size(); ++j){
            if(intersection_street_segments[intersection_ids.first][i] == intersection_street_segments[intersection_ids.second][j])
                return true;
        }
    }
    return false;
}

//Returns closest intersection using position
IntersectionIdx findClosestIntersection(LatLon my_position){
    float closestIntDist= std::numeric_limits<float>::infinity();
    IntersectionIdx closestIntersection = getNumIntersections();
    
    //runs through each possible intersection, if distance to it is closest, update closestIntDist. 
    for(IntersectionIdx i = 0; i<intersection_street_segments.size(); ++i){
        LatLon intPos = getIntersectionPosition(i);
        std::pair <LatLon, LatLon> points (my_position, intPos);
        float pointDist = findDistanceBetweenTwoPoints(points);
        if(pointDist < closestIntDist){
            closestIntersection = i;
            closestIntDist = pointDist;
        } 
    }
    return closestIntersection; 
}

//Returns street segments for intersection, utilizes data structure
std::vector<StreetSegmentIdx> findStreetSegmentsOfIntersection(IntersectionIdx intersection_id){
    return intersection_street_segments[intersection_id];
}

//Returns street names for intersection, utilizes data structure
std::vector<std::string> findStreetNamesOfIntersection(IntersectionIdx intersection_id){
    return si_names[intersection_id];
}

//Returns intersections along a given street
std::vector<IntersectionIdx> findIntersectionsOfStreet(StreetIdx street_id){
    std::vector<IntersectionIdx> si_ids;
    
    //runs through all possible street segments and adds intersection IDs to vector if street IDS match
    for(StreetSegmentIdx s=0; s<getNumStreetSegments(); ++s){
        if((getStreetSegmentInfo(s).streetID) == street_id){
            si_ids.push_back(getStreetSegmentInfo(s).from);
            si_ids.push_back(getStreetSegmentInfo(s).to);
        }
    }
    
    std::unordered_set<int> s(si_ids.begin(), si_ids.end());  // Remove duplicate intersections at each street
    si_ids.assign(s.begin(), s.end());
    
    return si_ids;
}

//Charles' Functions
//returns a vector of intersection ids of 2 streets given the StreetIdx of the streets
std::vector<IntersectionIdx> findIntersectionsOfTwoStreets(std::pair<StreetIdx, StreetIdx> street_ids){
    auto streetInter1 = findIntersectionsOfStreet(street_ids.first);
    auto streetInter2 = findIntersectionsOfStreet(street_ids.second);
    
    std::vector<IntersectionIdx> outputInter;
    
    //sorts the vectors to prepare it for the set_intersection function
    std::sort(streetInter1.begin(), streetInter1.end());
    std::sort(streetInter2.begin(), streetInter2.end());
    
    //outputs the intersections of vector StreetInter1 and StreetInter2
    std::set_intersection(streetInter1.begin(),streetInter1.end(),
                        streetInter2.begin(),streetInter2.end(),
                        std::back_inserter(outputInter));
     
    std::unordered_set<int> s(outputInter.begin(), outputInter.end());  // Remove duplicate intersections at each street
    outputInter.assign(s.begin(), s.end());
 
    return outputInter;
}

// finds a vector of streetIdx from a string prefix
std::vector<StreetIdx> findStreetIdsFromPartialStreetName(std::string street_prefix){
    //std::cerr<<"Runs function! \n";
    
    std::vector<StreetIdx> streetNames = {};

    //local variable to avoid direct manipulation of input;
    std::string str_pref = street_prefix;
    //lower case version of str_pref
    std::string str_pref_lower;
    
    //turn to lower case by looping through each str_pref char
    for(int i = 0; i < str_pref.size(); i++){
                str_pref_lower.push_back(tolower(str_pref[i]));
    }

    //check if string exists
    if(!str_pref_lower.empty()){
        
        str_pref_lower.erase(std::remove_if(str_pref_lower.begin(), str_pref_lower.end(), isspace), str_pref_lower.end());
        

        for(StreetIdx i = 0; i < getNumStreets(); i++){

            //gets street name 
            std::string strtName =  getStreetName(i);
            std::string strName_lc;
            
            //turn to lower case by looping through each strName char
            for(int j = 0; j < strtName.size(); j++){
                strName_lc.push_back(tolower(strtName[j]));
            }

            //remove white spaces
            std::string::iterator end_pos = std::remove(strName_lc.begin(), strName_lc.end(), ' ');
            strName_lc.erase(end_pos, strName_lc.end());


            //use mismatch function to obtain the first position strtName_lc diverges from street_prefix
            auto mismatch_pos = std::mismatch(str_pref_lower.begin(), str_pref_lower.end(), strName_lc.begin());

            //if first position of mismatch is at the end of street_prefix that means street_prefix is a prefix of strtName_lc
            if (mismatch_pos.first ==  str_pref_lower.end()){
                streetNames.push_back(i);
            }
        }

        return streetNames; 
    }else{
        // return vector of element 0 if string empty
        return std::vector<StreetIdx>{0};
    }
  
  
}

//finds the length of a street in meters given a 
double findStreetLength(StreetIdx street_id){
    double strlen = 0;
    
    for(StreetSegmentIdx i = 0; i < getNumStreetSegments() ; i++){
        
        //check if segment id matches requested id
        if(getStreetSegmentInfo(i).streetID == street_id){
            //add to total street length
           strlen += findStreetSegmentLength(i);
        }
    }

    return strlen;
}

//returns a POI id of the closest POI given a LatLon object of a position and the type name of the POI
POIIdx findClosestPOI(LatLon my_position, std::string POIname){
    
    //set to infinity initially so any distance would be closer
    float closestPOIDist= std::numeric_limits<float>::infinity();
    POIIdx closestPOI = getNumPointsOfInterest();
    
    //loop through entire set of POI. if current POI closer than closest POI, set current POI as the closest
    for(POIIdx i = 0; i < getNumPointsOfInterest(); i++){
        LatLon poiPos = getPOIPosition(i);
        std::pair <LatLon, LatLon> points (my_position, poiPos);
        float poiDist = findDistanceBetweenTwoPoints(points);
        
        //update closest distance and its corresponding POI index if a loser POI distance found
        if((poiDist < closestPOIDist)  && (getPOIType(i) == POIname)){
            closestPOI = i;
            closestPOIDist = poiDist;
        }
    }
    
    return closestPOI;
}

//finds the 2d area of a closed feature in squared meters gives a FeaturIdx
// returns 0 if given feature not a closed polygon
double findFeatureArea(FeatureIdx feature_id){
    int numPoints = getNumFeaturePoints(feature_id);
    double featArea = 0;
    LatLon featPoint, prevFeatPoint;
  
    // check if it's a closed polygon: is the first feature point same as the last feature point?
    if(getFeaturePoint(0, feature_id) == getFeaturePoint(numPoints-1, feature_id)){
        //integration method taught in class
        for(FeatureIdx i = 1; i < numPoints; i++){
            featPoint = getFeaturePoint(i, feature_id);
            prevFeatPoint = getFeaturePoint(i-1, feature_id);
       
            double latAvg = (featPoint.latitude()*(M_PI/180) + prevFeatPoint.latitude()*(M_PI/180))/2;
       
            double x2 =  kEarthRadiusInMeters * featPoint.longitude()*(M_PI/180)*cos(latAvg);
            double x = kEarthRadiusInMeters * prevFeatPoint.longitude()*(M_PI/180)*cos(latAvg);

            double y2 = kEarthRadiusInMeters * featPoint.latitude()*(M_PI/180);
            double y = kEarthRadiusInMeters * prevFeatPoint.latitude()*(M_PI/180);
       
            featArea += (y2 - y)*((x2 + x)/2);
       
        }
    }else{
        return 0;
    }
    
    
    return std::abs(featArea);
}
//returns a LatLon object of the coordinates of an OSMNode 
//input: OMSID of OSMNode in question
// test with release build!
LatLon findLatLonOfOSMNode (OSMID OSMid){
   return nodeCoordHash[OSMid];
}
