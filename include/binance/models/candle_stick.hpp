#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(CandleStick,
                 (long, open_time, 0)
                 (string, open, 1)
                 (string, high, 2)
                 (string, low, 3)
                 (string, close, 4)
                 (string, volumn, 5)
                 (long, close_time, 6)
                 (string, quote_asset_volume, 7)
                 (long, number_of_trades, 8)
                 (string, taker_buy_base_asset_volume, 9)
                 (string, taker_buy_quote_asset_volume, 10))
  }
}
