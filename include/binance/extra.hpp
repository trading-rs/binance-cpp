#pragma once

#include "types.hpp"
using namespace binance::types;

#include <json.hpp>
using json = nlohmann::json;

#include <fp/fp.hpp>
using namespace fp;

#include <functional>
using namespace std;

namespace binance {
  namespace extra {
    template <typename T> function<Maybe<json>(T)> print_result;
    template <>
    function<Maybe<json>(json)> print_result<json> = [](const auto &result) {
      cout << result.dump(2) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(long)> print_result<long> = [](const auto &result) {
      cout << result << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(OrderBookEntry)> print_result<OrderBookEntry> = [](const auto &result) {
      cout << result.price << " - " << result.qty << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(AggTrade)> print_result<AggTrade> = [](const auto &result) {
      cout << format("aggregate_trade_id = {0}, price = {1}, quantity = {2}, first_trade_id = {3}, last_trade_id = {4}, timestamp = {5}, is_buyer_maker = {6}, is_best_price_match = {7}",
                     result.aggregate_trade_id,
                     result.price,
                     result.quantity,
                     result.first_trade_id,
                     result.last_trade_id,
                     result.timestamp,
                     result.is_buyer_maker,
                     result.is_best_price_match) << endl;
      return Nothing<json>;
    };
  }
}
