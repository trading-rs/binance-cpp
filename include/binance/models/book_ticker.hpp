#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(BookTicker,
                 (string, symbol, "symbol")
                 (string, bid_price, "bidPrice")
                 (string, bid_qty, "bidQty")
                 (string, ask_price, "askPrice")
                 (string, ask_qty, "askQty"))
  }
}
