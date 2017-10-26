#pragma once

#include "order_book.hpp"
using namespace binance::types;

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
    struct CandleStickEvent {
      string event_type;
      long event_time;
      string symbol;
      long open_time;
      long close_time;
      string interval_id;
      long first_trade_id;
      long last_trade_id;
      string open;
      string close;
      string high;
      string low;
      string volume;
      long number_of_trades;
      bool is_bar_final;
      string quote_asset_volume;
      string active_buy_volume;
      string quote_active_buy_volume;
    };

    void from_json(const json& j, CandleStickEvent& o) {
      o.event_type = j.at("e").get<string>();
      o.event_time = j.at("E").get<long>();
      o.symbol = j.at("s").get<string>();
      json k = j.at("k");
      o.open_time = k.at("t").get<long>();
      o.close_time = k.at("T").get<long>();
      o.interval_id = k.at("i").get<string>();
      o.first_trade_id = k.at("f").get<long>();
      o.last_trade_id = k.at("L").get<long>();
      o.open = k.at("o").get<string>();
      o.close = k.at("c").get<string>();
      o.high = k.at("h").get<string>();
      o.low = k.at("l").get<string>();
      o.volume = k.at("v").get<string>();
      o.number_of_trades = k.at("n").get<long>();
      o.is_bar_final = k.at("x").get<bool>();
      o.quote_asset_volume = k.at("q").get<string>();
      o.active_buy_volume = k.at("V").get<string>();
      o.quote_active_buy_volume = k.at("Q").get<string>();
    }
  }
}
