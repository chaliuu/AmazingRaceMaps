#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_path_func_optimality_public) {
struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(4);
        rand_intersection = std::uniform_int_distribution<IntersectionIdx>(0, getNumIntersections()-1);
        rand_street = std::uniform_int_distribution<StreetIdx>(1, getNumStreets()-1);
        rand_segment = std::uniform_int_distribution<StreetSegmentIdx>(0, getNumStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<POIIdx>(0, getNumPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<double>(46.650653839, 46.711387634);
        rand_lon = std::uniform_real_distribution<double>(7.800767422, 7.915423393);
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
    TEST(findPathBetweenIntersections_optimality) {
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(0, 624));
        CHECK(path_is_legal(0, 624, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 184.71846494853420495);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(94, 1787));
        CHECK(path_is_legal(94, 1787, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 364.39941612327208986);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(109, 1086));
        CHECK(path_is_legal(109, 1086, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 75.53747844187965654);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(429, 109));
        CHECK(path_is_legal(429, 109, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 89.05587385896582475);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(525, 1408));
        CHECK(path_is_legal(525, 1408, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 418.39771948083551933);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(345, 1292));
        CHECK(path_is_legal(345, 1292, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 93.66627092400831600);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(616, 1331));
        CHECK(path_is_legal(616, 1331, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 132.58627462728637170);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(657, 443));
        CHECK(path_is_legal(657, 443, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 304.67850255887640287);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(678, 687));
        CHECK(path_is_legal(678, 687, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 142.37659768888744338);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(674, 85));
        CHECK(path_is_legal(674, 85, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 216.84734824941665465);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(730, 696));
        CHECK(path_is_legal(730, 696, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 279.05061564318606315);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(743, 1039));
        CHECK(path_is_legal(743, 1039, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 213.46824012527392256);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(803, 1337));
        CHECK(path_is_legal(803, 1337, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 487.07592583517242701);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(929, 1798));
        CHECK(path_is_legal(929, 1798, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 553.39422228443186214);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1067, 292));
        CHECK(path_is_legal(1067, 292, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 415.16710668417113084);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1151, 323));
        CHECK(path_is_legal(1151, 323, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 296.23097174230150586);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1208, 792));
        CHECK(path_is_legal(1208, 792, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 284.53033567391184988);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(603, 437));
        CHECK(path_is_legal(603, 437, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 147.97129687922918606);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(856, 580));
        CHECK(path_is_legal(856, 580, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 338.19192251442427732);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1386, 1188));
        CHECK(path_is_legal(1386, 1188, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 325.96674006225731546);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1388, 324));
        CHECK(path_is_legal(1388, 324, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 433.85336541411072631);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1599, 1392));
        CHECK(path_is_legal(1599, 1392, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 438.36518526486321434);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1641, 222));
        CHECK(path_is_legal(1641, 222, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 575.25940451970336653);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1660, 1589));
        CHECK(path_is_legal(1660, 1589, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 217.50096937969215105);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1166, 1778));
        CHECK(path_is_legal(1166, 1778, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 410.59463155849596205);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1756, 470));
        CHECK(path_is_legal(1756, 470, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 373.65959809197181585);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1367, 1208));
        CHECK(path_is_legal(1367, 1208, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 106.30502296863831191);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1097, 1123));
        CHECK(path_is_legal(1097, 1123, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 430.12087451401373528);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(1779, 167));
        CHECK(path_is_legal(1779, 167, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 611.65205989040555323);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1112, 1552));
        CHECK(path_is_legal(1112, 1552, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 145.50962542950995271);

    } //findPathBetweenIntersections_optimality

} //inter_inter_path_func_optimality_public

