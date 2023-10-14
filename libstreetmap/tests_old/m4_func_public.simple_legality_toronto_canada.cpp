#include <random>
#include <iostream>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"
#include "m4.h"

#include "unit_test_util.h"
#include "courier_verify.h"

using ece297test::relative_error;
using ece297test::courier_path_is_legal;


SUITE(simple_legality_toronto_canada_public) {
    TEST(simple_legality_toronto_canada) {
        std::vector<DeliveryInf> deliveries;
        std::vector<IntersectionIdx> depots;
        std::vector<CourierSubPath> result_path;
        float turn_penalty;

        deliveries = {DeliveryInf(25800, 30752)};
        depots = {6};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(23975, 52829), DeliveryInf(28343, 20239), DeliveryInf(100949, 118269)};
        depots = {11317, 1263, 141824};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(25477, 55023), DeliveryInf(35408, 24013)};
        depots = {67848, 85070};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(57390, 13433)};
        depots = {119982, 87927};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(93593, 4518)};
        depots = {132366, 125813};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(120765, 79772)};
        depots = {4544};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(14585, 119452), DeliveryInf(123587, 68913), DeliveryInf(74536, 97555), DeliveryInf(97409, 44068), DeliveryInf(71656, 71966)};
        depots = {53327, 51064, 86229};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(24950, 93929), DeliveryInf(27890, 3553)};
        depots = {73887};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(33220, 131157)};
        depots = {28038, 28409};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(33543, 131865), DeliveryInf(96806, 131865), DeliveryInf(33543, 59623), DeliveryInf(96806, 42871), DeliveryInf(91583, 59623), DeliveryInf(96806, 101696), DeliveryInf(96806, 131865), DeliveryInf(91724, 59623), DeliveryInf(51383, 123952)};
        depots = {14091, 78131, 81358};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(40220, 37954), DeliveryInf(90705, 82446), DeliveryInf(29107, 44932), DeliveryInf(28232, 60062), DeliveryInf(28232, 82070), DeliveryInf(45899, 26959), DeliveryInf(28232, 120267), DeliveryInf(90705, 120353)};
        depots = {26612, 45787, 77377};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(46812, 71491), DeliveryInf(133567, 126914), DeliveryInf(29206, 127536), DeliveryInf(122540, 35334), DeliveryInf(100594, 108615)};
        depots = {48279, 73609, 123137};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(49969, 12547), DeliveryInf(60078, 74045), DeliveryInf(67523, 34896), DeliveryInf(67523, 51623), DeliveryInf(2201, 21690), DeliveryInf(67523, 31728), DeliveryInf(2201, 62560), DeliveryInf(52690, 111006)};
        depots = {71331, 147022, 141242};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(68520, 96047), DeliveryInf(36149, 18461), DeliveryInf(36121, 146650), DeliveryInf(20823, 146187), DeliveryInf(93239, 18461), DeliveryInf(145396, 18461), DeliveryInf(94555, 146187), DeliveryInf(123302, 109833)};
        depots = {15009, 115194, 22009};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(122474, 97031), DeliveryInf(71346, 53400), DeliveryInf(50160, 73642), DeliveryInf(122474, 53400), DeliveryInf(52922, 99578), DeliveryInf(122474, 53400), DeliveryInf(122474, 20263), DeliveryInf(71346, 73642), DeliveryInf(119721, 73642)};
        depots = {11072, 5162, 100304};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(149400, 82788), DeliveryInf(21743, 58214)};
        depots = {30205, 104659};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(49977, 108621), DeliveryInf(123446, 89214)};
        depots = {46423};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(75622, 41876), DeliveryInf(139997, 104226), DeliveryInf(60196, 134068), DeliveryInf(62765, 54323), DeliveryInf(55302, 138790)};
        depots = {5167, 41161, 90982};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(96379, 62892), DeliveryInf(136264, 15856), DeliveryInf(54243, 31768), DeliveryInf(144993, 61637), DeliveryInf(101710, 31768), DeliveryInf(10558, 15856), DeliveryInf(6495, 31768), DeliveryInf(100123, 133538)};
        depots = {15493, 103651, 72762};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(89048, 124841), DeliveryInf(92093, 126663), DeliveryInf(140926, 94066), DeliveryInf(19309, 94066), DeliveryInf(17054, 71613), DeliveryInf(136104, 34526), DeliveryInf(146426, 124841), DeliveryInf(67424, 94066)};
        depots = {18180, 105325, 1266};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(99655, 44771), DeliveryInf(89322, 21865), DeliveryInf(9876, 137279), DeliveryInf(2854, 46399), DeliveryInf(9876, 88790), DeliveryInf(125171, 86061), DeliveryInf(9876, 25893), DeliveryInf(99655, 85082)};
        depots = {76795, 58438, 96807};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(101600, 138295), DeliveryInf(23126, 39080), DeliveryInf(52954, 134045)};
        depots = {23381, 49737, 60236};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(148921, 34458), DeliveryInf(112460, 37093), DeliveryInf(52386, 34604)};
        depots = {57912, 50185, 139133};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(5521, 131170), DeliveryInf(10521, 87530), DeliveryInf(132952, 26607), DeliveryInf(114707, 25583), DeliveryInf(149378, 97856)};
        depots = {114664, 53413, 139429};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(38830, 136475), DeliveryInf(15217, 124110), DeliveryInf(121748, 35896), DeliveryInf(63152, 74188), DeliveryInf(7027, 14365)};
        depots = {92254, 143981, 53219};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(90652, 105394), DeliveryInf(90652, 124757), DeliveryInf(2471, 124757), DeliveryInf(60308, 105394), DeliveryInf(60308, 145272), DeliveryInf(60308, 21051), DeliveryInf(62673, 124757), DeliveryInf(31763, 58192), DeliveryInf(60308, 105394)};
        depots = {77594, 78459, 149884};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(90750, 65433), DeliveryInf(64885, 143555), DeliveryInf(138036, 109754), DeliveryInf(25504, 94), DeliveryInf(140805, 143249)};
        depots = {119668, 70757, 43226};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(133155, 125006), DeliveryInf(124066, 149377)};
        depots = {72612, 95315};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(141581, 90147), DeliveryInf(129274, 121217)};
        depots = {114279};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

        deliveries = {DeliveryInf(141989, 57556)};
        depots = {118824};
        turn_penalty = 30.000000000;
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        CHECK(courier_path_is_legal(deliveries, depots, result_path));

    } //simple_legality_toronto_canada

} //simple_legality_toronto_canada_public

