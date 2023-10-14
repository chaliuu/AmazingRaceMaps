#include <random>
#include <iostream>
#include <string>
#include <UnitTest++/UnitTest++.h>

#include "unit_test_util.h"

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

namespace ezgl {
	extern void set_disable_event_loop (bool new_setting);
}

std::string map_name = "/cad2/ece297s/public/maps/saint-helena.streets.bin";

int main(int argc, char** argv) {
    //Disable interactive graphics
    ezgl::set_disable_event_loop(true);

    bool load_success = loadMap(map_name);

    if(!load_success) {
        std::cout << "ERROR: Could not load map file: '" << map_name << "'!";
        std::cout << " Subsequent tests will likely fail." << std::endl;
        //Don't abort tests, since we still want to show that all
        //tests fail.
    }

    //Run the unit tests
    int num_failures = UnitTest::RunAllTests();

    closeMap();

    return num_failures;
}

struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(0);
        rand_intersection = std::uniform_int_distribution<IntersectionIdx>(0, getNumIntersections()-1);
        rand_street = std::uniform_int_distribution<StreetIdx>(1, getNumStreets()-1);
        rand_segment = std::uniform_int_distribution<StreetSegmentIdx>(0, getNumStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<POIIdx>(0, getNumPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<float>(-16.00203, -7.925433);
        rand_lon = std::uniform_real_distribution<float>(-14.41355, -5.649098);
        rand_turn_penalty = std::uniform_real_distribution<double>(0., 30.);
        rand_walking_speed = std::uniform_real_distribution<double>(0.8, 5.);
        rand_walking_time_limit = std::uniform_real_distribution<double>(0., 300.);
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<IntersectionIdx> rand_intersection;
    std::uniform_int_distribution<StreetIdx> rand_street;
    std::uniform_int_distribution<StreetSegmentIdx> rand_segment;
    std::uniform_int_distribution<POIIdx> rand_poi;
    std::uniform_real_distribution<float> rand_lat;
    std::uniform_real_distribution<float> rand_lon;
    std::uniform_real_distribution<double> rand_turn_penalty;
    std::uniform_real_distribution<double> rand_walking_speed;
    std::uniform_real_distribution<double> rand_walking_time_limit;
};

TEST_FIXTURE(MapFixture, valgrind_exercise) {

    for(size_t i = 0; i < 10; i++) {

        IntersectionIdx source = rand_intersection(rng);
        IntersectionIdx destination = rand_intersection(rng);
        double turn_penalty = rand_turn_penalty(rng);

        std::vector<StreetSegmentIdx> path = findPathBetweenIntersections(turn_penalty, std::make_pair(source, destination));

        double path_cost = computePathTravelTime(turn_penalty, path);
    }

};
