#pragma once

#include "order_book.hpp"
using namespace binance::models;

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
  namespace models {
    struct DepthEvent {
      string event_type;
      long event_time;
      string symbol;
      long update_id;
      vector<OrderBookEntry> bids;
      vector<OrderBookEntry> asks;
    };

    void from_json(const json& j, DepthEvent& o) {
      o.event_type = j.at("e").get<string>();
      o.event_time = j.at("E").get<long>();
      o.symbol = j.at("s").get<string>();
      o.update_id = j.at("u").get<long>();
      o.bids = j.at("b").get<vector<OrderBookEntry>>();
      o.asks = j.at("a").get<vector<OrderBookEntry>>();
    }
  }
}
