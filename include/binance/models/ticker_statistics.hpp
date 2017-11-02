#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(TickerStatistics,
                 (string, price_change, "priceChange")
                 (string, price_change_percent, "priceChangePercent")
                 (string, weighted_avg_price, "weightedAvgPrice")
                 (string, prev_close_price, "prevClosePrice")
                 (string, last_price, "lastPrice")
                 (string, bid_price, "bidPrice")
                 (string, ask_price, "askPrice")
                 (string, open_price, "openPrice")
                 (string, high_price, "highPrice")
                 (string, low_price, "lowPrice")
                 (string, volume, "volume")
                 (long, open_time, "openTime")
                 (long, close_time, "closeTime")
                 (long, first_id, "firstId")
                 (long, last_id, "lastId")
                 (long, count, "count"))
  }
}
