#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(TickerPrice,
                 (string, symbol, "symbol")
                 (string, price, "price"))
  }
}
