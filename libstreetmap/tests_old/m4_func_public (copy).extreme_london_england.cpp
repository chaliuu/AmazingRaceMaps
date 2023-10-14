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


SUITE(extreme_london_england_public) {
    TEST(extreme_london_england) {
        std::vector<DeliveryInf> deliveries;
        std::vector<IntersectionIdx> depots;
        float turn_penalty;
        std::vector<CourierSubPath> result_path;
        bool is_legal;

        deliveries = {DeliveryInf(19542, 160031), DeliveryInf(76176, 129717), DeliveryInf(221247, 164618), DeliveryInf(59148, 108665), DeliveryInf(160671, 96051), DeliveryInf(35161, 66656), DeliveryInf(224184, 35699), DeliveryInf(88798, 104896), DeliveryInf(6328, 217202), DeliveryInf(129557, 189885), DeliveryInf(139976, 173618), DeliveryInf(148272, 95), DeliveryInf(206007, 173703), DeliveryInf(231942, 23159), DeliveryInf(37505, 194879), DeliveryInf(65305, 207927), DeliveryInf(17627, 46813), DeliveryInf(100491, 56870), DeliveryInf(113396, 73131), DeliveryInf(36148, 131541), DeliveryInf(36000, 214655), DeliveryInf(138570, 13019), DeliveryInf(1449, 12450), DeliveryInf(148129, 70963), DeliveryInf(84315, 195888), DeliveryInf(9660, 27932), DeliveryInf(20465, 64007), DeliveryInf(145917, 203206), DeliveryInf(77681, 189845), DeliveryInf(51350, 38681), DeliveryInf(48764, 219006), DeliveryInf(188274, 136737), DeliveryInf(72681, 157393), DeliveryInf(201998, 174011), DeliveryInf(216683, 14441), DeliveryInf(14263, 94541), DeliveryInf(179136, 208327), DeliveryInf(144089, 160296), DeliveryInf(80365, 54340), DeliveryInf(50153, 37095), DeliveryInf(122973, 13807), DeliveryInf(46694, 184756), DeliveryInf(39026, 66599), DeliveryInf(153666, 221132), DeliveryInf(198546, 22661), DeliveryInf(18535, 176208), DeliveryInf(13235, 87212), DeliveryInf(130792, 221019), DeliveryInf(84088, 52845), DeliveryInf(187850, 137508), DeliveryInf(142672, 231506), DeliveryInf(66043, 152471), DeliveryInf(192699, 178583), DeliveryInf(48255, 57203), DeliveryInf(135738, 63365), DeliveryInf(226203, 67798), DeliveryInf(85289, 229366), DeliveryInf(42945, 197358), DeliveryInf(236711, 192464), DeliveryInf(190157, 114464), DeliveryInf(163504, 73109), DeliveryInf(109500, 192305), DeliveryInf(218094, 82379), DeliveryInf(33447, 145267), DeliveryInf(240821, 63851)};
        depots = {38};
        turn_penalty = 30.000000000;
        {
        	ECE297_TIME_CONSTRAINT(50000);
        	
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        }

        is_legal = courier_path_is_legal(deliveries, depots, result_path);
        CHECK(is_legal);

        if(is_legal) {
        	double path_cost = ece297test::compute_courier_path_travel_time(result_path, turn_penalty);
        	std::cout << "QoR extreme_london_england: " << path_cost << std::endl;
        } else {
        	std::cout << "QoR extreme_london_england: INVALID" << std::endl;
        }

    } //extreme_london_england

} //extreme_london_england_public

