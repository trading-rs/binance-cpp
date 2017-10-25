#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct BookTicker {
      string symbol;
      string bid_price;
      string bid_qty;
      string ask_price;
      string ask_qty;
    };

    void from_json(const json& j, BookTicker& t) {
      t.symbol = j.at("symbol").get<string>();
      t.bid_price = j.at("bidPrice").get<string>();
      t.bid_qty = j.at("bidQty").get<string>();
      t.ask_price = j.at("askPrice").get<string>();
      t.ask_qty = j.at("askQty").get<string>();
    }
  }
}
