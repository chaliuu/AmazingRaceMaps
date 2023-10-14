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
    TEST(findPathBetweenIntersections_optimality) {
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(13, 51601));
        CHECK(path_is_legal(13, 51601, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 764.30415672172068753);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(7832, 147775));
        CHECK(path_is_legal(7832, 147775, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1297.13160448216922305);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(9088, 89818));
        CHECK(path_is_legal(9088, 89818, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1517.86493622239390788);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(28583, 106836));
        CHECK(path_is_legal(28583, 106836, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1186.75874300741838852);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(35474, 9037));
        CHECK(path_is_legal(35474, 9037, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2056.20141269164832920);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(43487, 116429));
        CHECK(path_is_legal(43487, 116429, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1391.45216944451863128);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(50955, 110047));
        CHECK(path_is_legal(50955, 110047, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1724.28315150741764228);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(49900, 36147));
        CHECK(path_is_legal(49900, 36147, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2264.15347285663574439);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(55780, 7107));
        CHECK(path_is_legal(55780, 7107, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 688.36614047347779888);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(56077, 56819));
        CHECK(path_is_legal(56077, 56819, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1005.64272177778161677);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(60411, 57606));
        CHECK(path_is_legal(60411, 57606, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 961.70604835478275163);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(61505, 85936));
        CHECK(path_is_legal(61505, 85936, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1310.40965263668431362);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(66440, 110603));
        CHECK(path_is_legal(66440, 110603, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2277.95340708114781592);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(70817, 48026));
        CHECK(path_is_legal(70817, 48026, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 3078.68147356889903676);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(76847, 148729));
        CHECK(path_is_legal(76847, 148729, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2048.65897349974602548);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(88253, 24143));
        CHECK(path_is_legal(88253, 24143, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1941.33090859425374219);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(90722, 92846));
        CHECK(path_is_legal(90722, 92846, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1635.09911060457079657);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91958, 128368));
        CHECK(path_is_legal(91958, 128368, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1096.28845820159654068);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(95180, 26717));
        CHECK(path_is_legal(95180, 26717, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 848.00638566363966220);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(96421, 147042));
        CHECK(path_is_legal(96421, 147042, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2635.00705621697079550);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99955, 65531));
        CHECK(path_is_legal(99955, 65531, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1375.79505064429827144);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(113021, 99914));
        CHECK(path_is_legal(113021, 99914, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1368.78726804559960328);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(114780, 26866));
        CHECK(path_is_legal(114780, 26866, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1449.91884603679750398);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(114599, 98300));
        CHECK(path_is_legal(114599, 98300, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 805.19954930477217658);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(132265, 115112));
        CHECK(path_is_legal(132265, 115112, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 591.84375075563809787);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(135696, 18428));
        CHECK(path_is_legal(135696, 18428, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1872.81200204227229733);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(54341, 36647));
        CHECK(path_is_legal(54341, 36647, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1025.45116880223736189);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(137276, 131450));
        CHECK(path_is_legal(137276, 131450, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1801.06660870624932613);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(145225, 38918));
        CHECK(path_is_legal(145225, 38918, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1565.25490936480514392);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(147089, 13864));
        CHECK(path_is_legal(147089, 13864, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1461.05674590629541854);

    } //findPathBetweenIntersections_optimality

} //inter_inter_path_func_optimality_public

