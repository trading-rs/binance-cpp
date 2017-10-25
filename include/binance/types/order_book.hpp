#pragma once

#ifndef FORMAT_HEADER
#define FORMAT_HEADER
#include <fmt/format.h>
#include <fmt/format.cc>
#endif
using namespace fmt;

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
struct OrderBookEntry {
      string price;
      string qty; // quantity
    };

    void from_json(const json& j, OrderBookEntry& o) {
      if (j.is_array()) {
        o.price = j.at(0).get<string>();
        o.qty = j.at(1).get<string>();
      } else {
        throw std::runtime_error(format("{} is not array for order entry", j.dump()));
      }
    }

    struct OrderBook {
      long last_update_id;
      vector<OrderBookEntry> bids;
      vector<OrderBookEntry> asks;
    };

    void from_json(const json& j, OrderBook& o) {
      o.last_update_id = j.at("lastUpdateId").get<long>();
      o.bids = j.at("bids").get<vector<OrderBookEntry>>();
      o.asks = j.at("asks").get<vector<OrderBookEntry>>();
    }
  }
}
