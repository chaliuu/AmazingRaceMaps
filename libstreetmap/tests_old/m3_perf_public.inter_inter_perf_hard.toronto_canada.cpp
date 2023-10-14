#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_path_perf_hard_public) {
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
    TEST_FIXTURE(MapFixture, findPathBetweenIntersections_perf_hard) {
        //Verify Functionality
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(5408, 124088));
        CHECK(path_is_legal(5408, 124088, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1703.62501469468202231);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(5670, 41794));
        CHECK(path_is_legal(5670, 41794, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1517.68044209899653652);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(4085, 145871));
        CHECK(path_is_legal(4085, 145871, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1644.33839935472610705);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(19221, 139238));
        CHECK(path_is_legal(19221, 139238, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1622.66620462650325862);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(23387, 24914));
        CHECK(path_is_legal(23387, 24914, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1697.20792769861145644);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(24868, 60697));
        CHECK(path_is_legal(24868, 60697, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1225.94095238019326644);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(29402, 150410));
        CHECK(path_is_legal(29402, 150410, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1070.77710262177470213);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(23256, 88135));
        CHECK(path_is_legal(23256, 88135, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 802.79032669576929493);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(44457, 56663));
        CHECK(path_is_legal(44457, 56663, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2900.13684154867223697);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(44260, 73743));
        CHECK(path_is_legal(44260, 73743, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1383.22875877412593582);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(47427, 39034));
        CHECK(path_is_legal(47427, 39034, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2269.72180132939502073);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(48937, 111224));
        CHECK(path_is_legal(48937, 111224, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2182.71025503378359645);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(52019, 49906));
        CHECK(path_is_legal(52019, 49906, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2243.78795495590293285);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(54467, 45095));
        CHECK(path_is_legal(54467, 45095, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 780.51744425253230020);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(57200, 125884));
        CHECK(path_is_legal(57200, 125884, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1245.69159386020123748);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(57987, 18591));
        CHECK(path_is_legal(57987, 18591, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2319.82754957128372553);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(64910, 6880));
        CHECK(path_is_legal(64910, 6880, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1433.07542993515676244);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(68308, 140634));
        CHECK(path_is_legal(68308, 140634, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2093.09416440763061473);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(93193, 119472));
        CHECK(path_is_legal(93193, 119472, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1015.08447037882524455);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(99005, 4463));
        CHECK(path_is_legal(99005, 4463, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1255.64046301427697472);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(103153, 136389));
        CHECK(path_is_legal(103153, 136389, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1544.76559572852056590);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(100649, 16348));
        CHECK(path_is_legal(100649, 16348, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 921.31703881859948524);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(114863, 94613));
        CHECK(path_is_legal(114863, 94613, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2059.00809824379030033);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(122562, 59231));
        CHECK(path_is_legal(122562, 59231, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1327.95673085534667734);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(122668, 143113));
        CHECK(path_is_legal(122668, 143113, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1333.52451146606290422);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(127308, 49214));
        CHECK(path_is_legal(127308, 49214, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1967.69912380510868388);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(129349, 99110));
        CHECK(path_is_legal(129349, 99110, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1420.68496369490185316);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(133213, 34805));
        CHECK(path_is_legal(133213, 34805, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 979.29438390546192750);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(142761, 29400));
        CHECK(path_is_legal(142761, 29400, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1152.73008239563250754);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(147895, 109171));
        CHECK(path_is_legal(147895, 109171, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1594.48920253184496687);

        //Generate random inputs
        std::vector<IntersectionIdx> intersection_ids1;
        std::vector<IntersectionIdx> intersection_ids2;
        std::vector<double> turn_penalties;
        for(size_t i = 0; i < 475; i++) {
            intersection_ids1.push_back(rand_intersection(rng));
            intersection_ids2.push_back(rand_intersection(rng));
            turn_penalties.push_back(rand_turn_penalty(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(31776);
            std::vector<StreetSegmentIdx> result;
            for(size_t i = 0; i < 475; i++) {
                result = findPathBetweenIntersections(turn_penalties[i], std::make_pair(intersection_ids1[i], intersection_ids2[i]));
            }
        }
    } //findPathBetweenIntersections_perf_hard

} //inter_inter_path_perf_hard_public

