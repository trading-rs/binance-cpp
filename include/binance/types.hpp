#pragma once

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
#include <iostream>
using namespace std;

namespace binance {
  namespace types {
    struct OrderBookEntry {
      string price;
      string qty; // quantity
    };

    void to_json(json& j, const OrderBookEntry& o) {
      j = json::array({ o.price, o.qty });
    }

    void from_json(const json& j, OrderBookEntry& o) {
      if (j.is_array()) {
        o.price = j.at(0).get<string>();
        o.qty = j.at(1).get<string>();
      } else {
        throw std::runtime_error(format("{} is not array for order entry", j.dump()));
      }
    }

    struct OrderBook {
      long lastUpdateId;
      vector<OrderBookEntry> bids;
      vector<OrderBookEntry> asks;
    };

    void to_json(json& j, const OrderBook& o) {
      j = json{
        { "lastUpdateId", o.lastUpdateId },
        { "bids", o.bids },
        { "asks", o.asks }
      };
    }

    void from_json(const json& j, OrderBook& o) {
      o.lastUpdateId = j.at("lastUpdateId").get<long>();
      o.bids = j.at("bids").get<vector<OrderBookEntry>>();
      o.asks = j.at("asks").get<vector<OrderBookEntry>>();
    }

    struct Balance {
      string asset;
      double free;
      double locked;
    };

    void to_json(json& j, const Balance& b) {
      j = json{
        { "asset", b.asset },
        { "free", b.free },
        { "locked", b.locked }
      };
    }

    void from_json(const json& j, Balance& b) {
      b.asset = j.at("asset").get<string>();
      b.free = j.at("free").get<double>();
      b.locked = j.at("locked").get<double>();
    }
  }
}
