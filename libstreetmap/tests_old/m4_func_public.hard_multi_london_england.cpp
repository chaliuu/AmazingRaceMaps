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


SUITE(hard_multi_london_england_public) {
    TEST(hard_multi_london_england) {
        std::vector<DeliveryInf> deliveries;
        std::vector<IntersectionIdx> depots;
        float turn_penalty;
        std::vector<CourierSubPath> result_path;
        bool is_legal;

        deliveries = {DeliveryInf(65119, 111133), DeliveryInf(88826, 159508), DeliveryInf(198013, 123505), DeliveryInf(237916, 243281), DeliveryInf(119599, 171647), DeliveryInf(188566, 6123), DeliveryInf(131713, 167039), DeliveryInf(191855, 83753), DeliveryInf(198013, 231620), DeliveryInf(135920, 46854), DeliveryInf(33864, 233941), DeliveryInf(87583, 137397), DeliveryInf(145508, 116407), DeliveryInf(36263, 8804), DeliveryInf(198013, 35590), DeliveryInf(141556, 54872), DeliveryInf(196035, 2228), DeliveryInf(146425, 112107), DeliveryInf(113030, 105406), DeliveryInf(22027, 197217), DeliveryInf(21905, 184173), DeliveryInf(108126, 105406), DeliveryInf(187330, 180107), DeliveryInf(95129, 115686), DeliveryInf(91336, 10952), DeliveryInf(225042, 105406), DeliveryInf(17227, 21587), DeliveryInf(97319, 113342), DeliveryInf(17053, 11556), DeliveryInf(100315, 167239), DeliveryInf(242272, 98112), DeliveryInf(120949, 233828), DeliveryInf(63689, 241110), DeliveryInf(136376, 244218), DeliveryInf(210188, 105406), DeliveryInf(135201, 106852), DeliveryInf(181091, 37054), DeliveryInf(149077, 54863), DeliveryInf(137718, 155192), DeliveryInf(33057, 179816), DeliveryInf(198013, 189445), DeliveryInf(161038, 116222), DeliveryInf(208556, 83029), DeliveryInf(151368, 216902)};
        depots = {33, 125072};
        turn_penalty = 30.000000000;
        {
        	ECE297_TIME_CONSTRAINT(50000);
        	
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        }

        is_legal = courier_path_is_legal(deliveries, depots, result_path);
        CHECK(is_legal);

        if(is_legal) {
        	double path_cost = ece297test::compute_courier_path_travel_time(result_path, turn_penalty);
        	std::cout << "QoR hard_multi_london_england: " << path_cost << std::endl;
        } else {
        	std::cout << "QoR hard_multi_london_england: INVALID" << std::endl;
        }

    } //hard_multi_london_england

} //hard_multi_london_england_public

