#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_path_func_legality_public) {
struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(4);
        rand_intersection = std::uniform_int_distribution<IntersectionIdx>(0, getNumIntersections()-1);
        rand_street = std::uniform_int_distribution<StreetIdx>(1, getNumStreets()-1);
        rand_segment = std::uniform_int_distribution<StreetSegmentIdx>(0, getNumStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<POIIdx>(0, getNumPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<double>(51.280006409, 51.699996948);
        rand_lon = std::uniform_real_distribution<double>(-0.599989712, 0.419978589);
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
    TEST(findPathBetweenIntersections_legality) {
        std::vector<StreetSegmentIdx> path;

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(12655, 238784));
        CHECK(path_is_legal(12655, 238784, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14685, 145134));
        CHECK(path_is_legal(14685, 145134, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(22, 83381));
        CHECK(path_is_legal(22, 83381, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(75561, 160740));
        CHECK(path_is_legal(75561, 160740, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(82337, 177822));
        CHECK(path_is_legal(82337, 177822, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(90134, 11485));
        CHECK(path_is_legal(90134, 11485, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99384, 138862));
        CHECK(path_is_legal(99384, 138862, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(114431, 77605));
        CHECK(path_is_legal(114431, 77605, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(124175, 240326));
        CHECK(path_is_legal(124175, 240326, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(97616, 93084));
        CHECK(path_is_legal(97616, 93084, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(146595, 150028));
        CHECK(path_is_legal(146595, 150028, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(148592, 207426));
        CHECK(path_is_legal(148592, 207426, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(87809, 59217));
        CHECK(path_is_legal(87809, 59217, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(107359, 178721));
        CHECK(path_is_legal(107359, 178721, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(153799, 43171));
        CHECK(path_is_legal(153799, 43171, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(155804, 237601));
        CHECK(path_is_legal(155804, 237601, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(161515, 105890));
        CHECK(path_is_legal(161515, 105890, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(142606, 39012));
        CHECK(path_is_legal(142606, 39012, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(182627, 161448));
        CHECK(path_is_legal(182627, 161448, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(185177, 158839));
        CHECK(path_is_legal(185177, 158839, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(185469, 43413));
        CHECK(path_is_legal(185469, 43413, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(57321, 14603));
        CHECK(path_is_legal(57321, 14603, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(194667, 83200));
        CHECK(path_is_legal(194667, 83200, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(90613, 91812));
        CHECK(path_is_legal(90613, 91812, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(46187, 172633));
        CHECK(path_is_legal(46187, 172633, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(213724, 186007));
        CHECK(path_is_legal(213724, 186007, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(219266, 29777));
        CHECK(path_is_legal(219266, 29777, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(221820, 212406));
        CHECK(path_is_legal(221820, 212406, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(80633, 58410));
        CHECK(path_is_legal(80633, 58410, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(234665, 62886));
        CHECK(path_is_legal(234665, 62886, path));

    } //findPathBetweenIntersections_legality

} //inter_inter_path_func_legality_public

