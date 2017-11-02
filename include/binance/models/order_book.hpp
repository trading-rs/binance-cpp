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
    struct OrderBookEntry {
      string price;
      string qty; // quantity
    };

    void from_json(const json& j, OrderBookEntry& o) {
      if (j.is_array()) {
        o.price = j.at(0).get<string>();
        o.qty = j.at(1).get<string>();
      } else {
        throw std::runtime_error(format("{} is not array for order entry", j.dump()));
      }
    }

    bool operator ==(const OrderBookEntry& lhs, const OrderBookEntry& rhs) {
      return lhs.price == rhs.price && lhs.qty == rhs.qty;
    }

    DEFINE_MODEL_FROM_JSON(OrderBook,
                           (long, last_update_id, "lastUpdateId")
                           (vector<OrderBookEntry>, bids, "bids")
                           (vector<OrderBookEntry>, asks, "asks"))
  }
}
