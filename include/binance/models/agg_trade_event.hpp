#pragma once

#include <derivejson/derivejson.hpp>

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
    DEFINE_MODEL(AggTradeEvent,
                 (string, event_type, "e")
                 (long, event_time, "E")
                 (string, symbol, "s")
                 (long, trade_id, "a")
                 (string, price, "p")
                 (string, qty, "q")
                 (long, first_breakdown_trade_id, "f")
                 (long, last_breakdown_trade_id, "l")
                 (long, trade_time, "T")
                 (bool, is_buyer_maker, "m"))
  }
}
