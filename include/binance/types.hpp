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
      long last_update_id;
      vector<OrderBookEntry> bids;
      vector<OrderBookEntry> asks;
    };

    void to_json(json& j, const OrderBook& o) {
      j = json{
        { "lastUpdateId", o.last_update_id },
        { "bids", o.bids },
        { "asks", o.asks }
      };
    }

    void from_json(const json& j, OrderBook& o) {
      o.last_update_id = j.at("lastUpdateId").get<long>();
      o.bids = j.at("bids").get<vector<OrderBookEntry>>();
      o.asks = j.at("asks").get<vector<OrderBookEntry>>();
    }

    struct AggTrade {
      long aggregate_trade_id;
      string price;
      string quantity;
      long first_trade_id;
      long last_trade_id;
      long timestamp;
      bool is_buyer_maker;
      bool is_best_price_match;
    };

    void to_json(json& j, const AggTrade& a) {
      j = json{
        { "a", a.aggregate_trade_id },
        { "p", a.price },
        { "q", a.quantity },
        { "f", a.first_trade_id },
        { "l", a.last_trade_id },
        { "T", a.timestamp },
        { "m", a.is_buyer_maker },
        { "M", a.is_best_price_match }
      };
    }

    void from_json(const json& j, AggTrade& a) {
      a.aggregate_trade_id = j.at("a").get<long>();
      a.price = j.at("p").get<string>();
      a.quantity = j.at("q").get<string>();
      a.first_trade_id = j.at("f").get<long>();
      a.last_trade_id = j.at("l").get<long>();
      a.timestamp = j.at("T").get<long>();
      a.is_buyer_maker = j.at("m").get<bool>();
      a.is_best_price_match = j.at("M").get<bool>();
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
