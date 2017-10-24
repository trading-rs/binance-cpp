#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct CandleStick {
      long open_time;
      string open;
      string high;
      string low;
      string close;
      string volumn;
      long close_time;
      string quote_asset_volume;
      long number_of_trades;
      string taker_buy_base_asset_volume;
      string taker_buy_quote_asset_volume;
    };

    void to_json(json& j, const CandleStick& c) {
      j = json::array({ c.open_time , c.open, c.high, c.low, c.close, c.volumn, c.close_time, c.quote_asset_volume, c.number_of_trades, c.taker_buy_base_asset_volume, c.taker_buy_quote_asset_volume });
    }

    void from_json(const json& j, CandleStick& c) {
      c.open_time = j.at(0).get<long>();
      c.open = j.at(1).get<string>();
      c.high = j.at(2).get<string>();
      c.low = j.at(3).get<string>();
      c.close = j.at(4).get<string>();
      c.volumn = j.at(5).get<string>();
      c.close_time = j.at(6).get<long>();
      c.quote_asset_volume = j.at(7).get<string>();
      c.number_of_trades = j.at(8).get<long>();
      c.taker_buy_base_asset_volume = j.at(9).get<string>();
      c.taker_buy_quote_asset_volume = j.at(10).get<string>();
    }
  }
}
