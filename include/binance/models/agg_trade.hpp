#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(AggTrade,
                 (long, aggregate_trade_id, "a")
                 (string, price, "p")
                 (string, quantity, "q")
                 (long, first_trade_id, "f")
                 (long, last_trade_id, "l")
                 (long, timestamp, "T")
                 (bool, is_buyer_maker, "m")
                 (bool, is_best_price_match, "M"))
  }
}
