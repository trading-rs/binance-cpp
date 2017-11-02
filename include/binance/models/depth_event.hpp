#pragma once

#include <derivejson/derivejson.hpp>

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
    DEFINE_MODEL_FROM_JSON(DepthEvent,
                           (string, event_type, "e")
                           (long, event_time, "E")
                           (string, symbol, "s")
                           (long, update_id, "u")
                           (vector<OrderBookEntry>, bids, "b")
                           (vector<OrderBookEntry>, asks, "a"))
  }
}
