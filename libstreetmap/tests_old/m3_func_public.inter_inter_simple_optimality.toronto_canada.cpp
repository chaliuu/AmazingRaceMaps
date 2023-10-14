#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_simple_path_func_optimality_public) {
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
    TEST(findPathBetweenIntersections_simple_optimality) {
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(13, 184));
        CHECK(path_is_legal(13, 184, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 16.11561347980168435);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(7832, 19097));
        CHECK(path_is_legal(7832, 19097, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.04627287575647543);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(22635, 22611));
        CHECK(path_is_legal(22635, 22611, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 13.68275676385712636);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(35474, 70532));
        CHECK(path_is_legal(35474, 70532, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 6.57492455546748111);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(46252, 46253));
        CHECK(path_is_legal(46252, 46253, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 4.62888564228953214);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(49900, 49899));
        CHECK(path_is_legal(49900, 49899, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 4.70720147641207287);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(50955, 51854));
        CHECK(path_is_legal(50955, 51854, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 18.68217707846552855);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(54341, 54340));
        CHECK(path_is_legal(54341, 54340, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.23560223918198275);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(55780, 55781));
        CHECK(path_is_legal(55780, 55781, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.25587191109654839);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(61505, 61526));
        CHECK(path_is_legal(61505, 61526, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.86894511013401399);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(48026, 66479));
        CHECK(path_is_legal(48026, 66479, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 18.87108072839834350);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(74187, 74186));
        CHECK(path_is_legal(74187, 74186, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.29265781593336460);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(76847, 76845));
        CHECK(path_is_legal(76847, 76845, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 0.70993693148941073);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(88995, 16823));
        CHECK(path_is_legal(88995, 16823, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 7.27744600709441425);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91575, 91576));
        CHECK(path_is_legal(91575, 91576, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3.09596302411011015);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91958, 91960));
        CHECK(path_is_legal(91958, 91960, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.33101636666069822);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99475, 51415));
        CHECK(path_is_legal(99475, 51415, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 62.29119239783184980);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(105659, 64711));
        CHECK(path_is_legal(105659, 64711, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 40.91931281179446245);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(106836, 83417));
        CHECK(path_is_legal(106836, 83417, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 25.64330026977781074);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(110603, 110602));
        CHECK(path_is_legal(110603, 110602, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3.72542885240789134);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(116429, 116436));
        CHECK(path_is_legal(116429, 116436, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 5.32141202505195210);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(98300, 118521));
        CHECK(path_is_legal(98300, 118521, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.56240295354630998);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(65531, 65532));
        CHECK(path_is_legal(65531, 65532, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3.05088570710683138);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(9088, 125223));
        CHECK(path_is_legal(9088, 125223, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 11.49653438177523768);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(126555, 126554));
        CHECK(path_is_legal(126555, 126554, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.73441903818609644);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99939, 81512));
        CHECK(path_is_legal(99939, 81512, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 11.72152558155547375);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(58215, 131990));
        CHECK(path_is_legal(58215, 131990, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 22.30548325673529320);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(132265, 132262));
        CHECK(path_is_legal(132265, 132262, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.40026688067219296);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(137276, 137278));
        CHECK(path_is_legal(137276, 137278, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 6.45491193869637758);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(24143, 140703));
        CHECK(path_is_legal(24143, 140703, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 8.37340003629514129);

    } //findPathBetweenIntersections_simple_optimality

} //inter_inter_simple_path_func_optimality_public

