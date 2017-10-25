#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct AggTrade {
      long aggregate_trade_id;
      string price;
      string quantity;
      long first_trade_id;
      long last_trade_id;
      long timestamp;
      bool is_buyer_maker;
      bool is_best_price_match;
    };

    void from_json(const json& j, AggTrade& a) {
      a.aggregate_trade_id = j.at("a").get<long>();
      a.price = j.at("p").get<string>();
      a.quantity = j.at("q").get<string>();
      a.first_trade_id = j.at("f").get<long>();
      a.last_trade_id = j.at("l").get<long>();
      a.timestamp = j.at("T").get<long>();
      a.is_buyer_maker = j.at("m").get<bool>();
      a.is_best_price_match = j.at("M").get<bool>();
    }
  }
}
