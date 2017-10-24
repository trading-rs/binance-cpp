#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct TickerStatistics {
      string price_change;
      string price_change_percent;
      string weighted_avg_price;
      string prev_close_price;
      string last_price;
      string bid_price;
      string ask_price;
      string open_price;
      string high_price;
      string low_price;
      string volume;
      long open_time;
      long close_time;
      long first_id;
      long last_id;
      long count;
    };

    void to_json(json& j, const TickerStatistics& t) {
      j = json{
        { "priceChange", t.price_change },
        { "priceChangePercent", t.price_change_percent },
        { "weightedAvgPrice", t.weighted_avg_price },
        { "prevClosePrice", t.prev_close_price },
        { "lastPrice", t.last_price },
        { "bidPrice", t.bid_price },
        { "askPrice", t.ask_price },
        { "openPrice", t.open_price },
        { "highPrice", t.high_price },
        { "lowPrice", t.low_price },
        { "volume", t.volume },
        { "openTime", t.open_time },
        { "closeTime", t.close_time },
        { "firstId", t.first_id },
        { "lastId", t.last_id },
        { "count", t.count }
      };
    }

    void from_json(const json& j, TickerStatistics& t) {
      t.price_change = j.at("priceChange").get<string>();
      t.price_change_percent = j.at("priceChangePercent").get<string>();
      t.weighted_avg_price = j.at("weightedAvgPrice").get<string>();
      t.prev_close_price = j.at("prevClosePrice").get<string>();
      t.last_price = j.at("lastPrice").get<string>();
      t.bid_price = j.at("bidPrice").get<string>();
      t.ask_price = j.at("askPrice").get<string>();
      t.open_price = j.at("openPrice").get<string>();
      t.high_price = j.at("highPrice").get<string>();
      t.low_price = j.at("lowPrice").get<string>();
      t.volume = j.at("volume").get<string>();
      t.open_time = j.at("openTime").get<long>();
      t.close_time = j.at("closeTime").get<long>();
      t.first_id = j.at("firstId").get<long>();
      t.last_id = j.at("lastId").get<long>();
      t.count = j.at("count").get<long>();
    }
  }
}
