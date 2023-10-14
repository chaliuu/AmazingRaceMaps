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
    TEST(findPathBetweenIntersections_legality) {
        std::vector<StreetSegmentIdx> path;

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(13, 51601));
        CHECK(path_is_legal(13, 51601, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(7832, 147775));
        CHECK(path_is_legal(7832, 147775, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(9088, 89818));
        CHECK(path_is_legal(9088, 89818, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(28583, 106836));
        CHECK(path_is_legal(28583, 106836, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(35474, 9037));
        CHECK(path_is_legal(35474, 9037, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(43487, 116429));
        CHECK(path_is_legal(43487, 116429, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(50955, 110047));
        CHECK(path_is_legal(50955, 110047, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(49900, 36147));
        CHECK(path_is_legal(49900, 36147, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(55780, 7107));
        CHECK(path_is_legal(55780, 7107, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(56077, 56819));
        CHECK(path_is_legal(56077, 56819, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(60411, 57606));
        CHECK(path_is_legal(60411, 57606, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(61505, 85936));
        CHECK(path_is_legal(61505, 85936, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(66440, 110603));
        CHECK(path_is_legal(66440, 110603, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(70817, 48026));
        CHECK(path_is_legal(70817, 48026, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(76847, 148729));
        CHECK(path_is_legal(76847, 148729, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(88253, 24143));
        CHECK(path_is_legal(88253, 24143, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(90722, 92846));
        CHECK(path_is_legal(90722, 92846, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91958, 128368));
        CHECK(path_is_legal(91958, 128368, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(95180, 26717));
        CHECK(path_is_legal(95180, 26717, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(96421, 147042));
        CHECK(path_is_legal(96421, 147042, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99955, 65531));
        CHECK(path_is_legal(99955, 65531, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(113021, 99914));
        CHECK(path_is_legal(113021, 99914, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(114780, 26866));
        CHECK(path_is_legal(114780, 26866, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(114599, 98300));
        CHECK(path_is_legal(114599, 98300, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(132265, 115112));
        CHECK(path_is_legal(132265, 115112, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(135696, 18428));
        CHECK(path_is_legal(135696, 18428, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(54341, 36647));
        CHECK(path_is_legal(54341, 36647, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(137276, 131450));
        CHECK(path_is_legal(137276, 131450, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(145225, 38918));
        CHECK(path_is_legal(145225, 38918, path));

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(147089, 13864));
        CHECK(path_is_legal(147089, 13864, path));

    } //findPathBetweenIntersections_legality

} //inter_inter_path_func_legality_public

