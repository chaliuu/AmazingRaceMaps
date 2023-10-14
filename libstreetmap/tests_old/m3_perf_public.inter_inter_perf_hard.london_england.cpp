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
    TEST_FIXTURE(MapFixture, findPathBetweenIntersections_perf_hard) {
        //Verify Functionality
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(20306, 114839));
        CHECK(path_is_legal(20306, 114839, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1815.83583328018630709);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(26426, 122785));
        CHECK(path_is_legal(26426, 122785, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 843.03579373325908364);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(30548, 28959));
        CHECK(path_is_legal(30548, 28959, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1695.63584597117960584);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(77792, 230094));
        CHECK(path_is_legal(77792, 230094, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 952.93463904158932110);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(70888, 126927));
        CHECK(path_is_legal(70888, 126927, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2404.32392694584541459);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(82912, 229014));
        CHECK(path_is_legal(82912, 229014, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1212.54146174727088692);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(108056, 1977));
        CHECK(path_is_legal(108056, 1977, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 4113.70297278174348321);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(108797, 3920));
        CHECK(path_is_legal(108797, 3920, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1125.69181962963534716);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(117830, 131066));
        CHECK(path_is_legal(117830, 131066, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2969.55511880917129020);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(133477, 131055));
        CHECK(path_is_legal(133477, 131055, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2059.34149060128356723);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(57228, 176324));
        CHECK(path_is_legal(57228, 176324, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2587.29763298033094543);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(16239, 169807));
        CHECK(path_is_legal(16239, 169807, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1673.97704534644594787);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(143780, 100677));
        CHECK(path_is_legal(143780, 100677, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1777.42134401950579559);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(165638, 94902));
        CHECK(path_is_legal(165638, 94902, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1997.79358373867603405);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(167379, 14080));
        CHECK(path_is_legal(167379, 14080, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2292.20583452906430466);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(158520, 197068));
        CHECK(path_is_legal(158520, 197068, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2742.47791046966312933);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(174342, 68393));
        CHECK(path_is_legal(174342, 68393, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3017.02242537988604454);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(176379, 74277));
        CHECK(path_is_legal(176379, 74277, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2243.58198487526169629);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(182034, 177776));
        CHECK(path_is_legal(182034, 177776, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1308.63634388423929522);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(195669, 152715));
        CHECK(path_is_legal(195669, 152715, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1911.89416477880399725);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(200350, 80452));
        CHECK(path_is_legal(200350, 80452, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2154.82668998605777233);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(202323, 225770));
        CHECK(path_is_legal(202323, 225770, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2691.04297960888243324);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(290, 28372));
        CHECK(path_is_legal(290, 28372, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2727.79878038010156160);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(162901, 112777));
        CHECK(path_is_legal(162901, 112777, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2632.11545231522404720);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(215898, 200250));
        CHECK(path_is_legal(215898, 200250, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1748.06574791808452574);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(40554, 104111));
        CHECK(path_is_legal(40554, 104111, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3394.20655826662141408);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(113997, 204647));
        CHECK(path_is_legal(113997, 204647, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 844.82873187638290347);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(146641, 157326));
        CHECK(path_is_legal(146641, 157326, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1607.95699942388819181);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(150789, 105922));
        CHECK(path_is_legal(150789, 105922, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2701.30976435605225561);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(92594, 104714));
        CHECK(path_is_legal(92594, 104714, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1545.49260022466501141);

        //Generate random inputs
        std::vector<IntersectionIdx> intersection_ids1;
        std::vector<IntersectionIdx> intersection_ids2;
        std::vector<double> turn_penalties;
        for(size_t i = 0; i < 100; i++) {
            intersection_ids1.push_back(rand_intersection(rng));
            intersection_ids2.push_back(rand_intersection(rng));
            turn_penalties.push_back(rand_turn_penalty(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(14089);
            std::vector<StreetSegmentIdx> result;
            for(size_t i = 0; i < 100; i++) {
                result = findPathBetweenIntersections(turn_penalties[i], std::make_pair(intersection_ids1[i], intersection_ids2[i]));
            }
        }
    } //findPathBetweenIntersections_perf_hard

} //inter_inter_path_perf_hard_public

