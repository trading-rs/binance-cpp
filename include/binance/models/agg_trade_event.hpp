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
  namespace models {
    struct AggTradeEvent {
      string event_type;
      long event_time;
      string symbol;
      long trade_id;
      string price;
      string qty;
      long first_breakdown_trade_id;
      long last_breakdown_trade_id;
      long trade_time;
      bool is_buyer_maker;
    };

    void from_json(const json& j, AggTradeEvent& o) {
      o.event_type = j.at("e").get<string>();
      o.event_time = j.at("E").get<long>();
      o.symbol = j.at("s").get<string>();
      o.trade_id = j.at("a").get<long>();
      o.price = j.at("p").get<string>();
      o.qty = j.at("q").get<string>();
      o.first_breakdown_trade_id = j.at("f").get<long>();
      o.last_breakdown_trade_id = j.at("l").get<long>();
      o.trade_time = j.at("T").get<long>();
      o.is_buyer_maker = j.at("m").get<bool>();
    }
  }
}
