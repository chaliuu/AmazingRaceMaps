#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_path_perf_medium_public) {
struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(4);
        rand_intersection = std::uniform_int_distribution<IntersectionIdx>(0, getNumIntersections()-1);
        rand_street = std::uniform_int_distribution<StreetIdx>(1, getNumStreets()-1);
        rand_segment = std::uniform_int_distribution<StreetSegmentIdx>(0, getNumStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<POIIdx>(0, getNumPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<double>(43.479999542, 43.919982910);
        rand_lon = std::uniform_real_distribution<double>(-79.789985657, -79.000000000);
        rand_turn_penalty = std::uniform_real_distribution<double>(0., 30.);
        rand_walking_speed = std::uniform_real_distribution<double>(0.8, 5);
        rand_walking_time_limit = std::uniform_real_distribution<double>(0.0, 300);
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<IntersectionIdx> rand_intersection;
    std::uniform_int_distribution<StreetSegmentIdx> rand_street;
    std::uniform_int_distribution<StreetSegmentIdx> rand_segment;
    std::uniform_int_distribution<POIIdx> rand_poi;
    std::uniform_real_distribution<double> rand_lat;
    std::uniform_real_distribution<double> rand_lon;
    std::uniform_real_distribution<double> rand_turn_penalty;
    std::uniform_real_distribution<double> rand_walking_speed;
    std::uniform_real_distribution<double> rand_walking_time_limit;
};
    TEST_FIXTURE(MapFixture, findPathBetweenIntersections_perf_medium) {
        //Verify Functionality
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(6319, 90906));
        CHECK(path_is_legal(6319, 90906, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 930.63184061262381874);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(13925, 92061));
        CHECK(path_is_legal(13925, 92061, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1746.62938490319038465);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14699, 23812));
        CHECK(path_is_legal(14699, 23812, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1138.18881817505280196);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(19503, 83781));
        CHECK(path_is_legal(19503, 83781, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 647.72191799180666294);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(26019, 108771));
        CHECK(path_is_legal(26019, 108771, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1588.67598845404722852);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(32704, 122317));
        CHECK(path_is_legal(32704, 122317, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1270.28885927904548225);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(33151, 10292));
        CHECK(path_is_legal(33151, 10292, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1138.84626841257045271);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(41010, 86066));
        CHECK(path_is_legal(41010, 86066, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1825.51924939377954615);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(44587, 81264));
        CHECK(path_is_legal(44587, 81264, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1255.96930436223760807);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(44353, 41850));
        CHECK(path_is_legal(44353, 41850, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 988.09395416900747477);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(46213, 138966));
        CHECK(path_is_legal(46213, 138966, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1814.08541911196630281);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(24099, 131786));
        CHECK(path_is_legal(24099, 131786, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1536.13512762995719640);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(46876, 142950));
        CHECK(path_is_legal(46876, 142950, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2560.10842295907150401);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(48237, 144974));
        CHECK(path_is_legal(48237, 144974, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1911.89265756926056383);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(48658, 10059));
        CHECK(path_is_legal(48658, 10059, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1417.71230206709083177);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(60140, 24681));
        CHECK(path_is_legal(60140, 24681, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1571.81158680091630231);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(64136, 119431));
        CHECK(path_is_legal(64136, 119431, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1399.02639564269929906);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(64439, 23377));
        CHECK(path_is_legal(64439, 23377, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 736.76921368928606171);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(74202, 67789));
        CHECK(path_is_legal(74202, 67789, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 998.06570352006599478);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(82810, 44651));
        CHECK(path_is_legal(82810, 44651, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1745.89229883966322632);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(91486, 103421));
        CHECK(path_is_legal(91486, 103421, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1573.93840298911800346);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(95885, 48270));
        CHECK(path_is_legal(95885, 48270, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 993.88336270609295298);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(101270, 129399));
        CHECK(path_is_legal(101270, 129399, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2185.40378043952478038);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(110721, 117594));
        CHECK(path_is_legal(110721, 117594, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1364.23390747874850604);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(124388, 32298));
        CHECK(path_is_legal(124388, 32298, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 561.73881435756675273);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(100474, 97875));
        CHECK(path_is_legal(100474, 97875, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1282.09684320716041839);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(128701, 88860));
        CHECK(path_is_legal(128701, 88860, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 715.98060223632546695);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(30910, 1410));
        CHECK(path_is_legal(30910, 1410, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 646.58486645992502417);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(136124, 84252));
        CHECK(path_is_legal(136124, 84252, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1695.84380209569098952);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(138577, 133400));
        CHECK(path_is_legal(138577, 133400, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1774.30763651975280482);

        //Generate random inputs
        std::vector<IntersectionIdx> intersection_ids1;
        std::vector<IntersectionIdx> intersection_ids2;
        std::vector<double> turn_penalties;
        for(size_t i = 0; i < 150; i++) {
            intersection_ids1.push_back(rand_intersection(rng));
            intersection_ids2.push_back(rand_intersection(rng));
            turn_penalties.push_back(rand_turn_penalty(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(19569);
            std::vector<StreetSegmentIdx> result;
            for(size_t i = 0; i < 150; i++) {
                result = findPathBetweenIntersections(turn_penalties[i], std::make_pair(intersection_ids1[i], intersection_ids2[i]));
            }
        }
    } //findPathBetweenIntersections_perf_medium

} //inter_inter_path_perf_medium_public

