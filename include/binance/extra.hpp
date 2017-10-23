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
      cout << format("aggregateTradeId = {0}, price = {1}, quantity = {2}, firstTradeId = {3}, lastTradeId = {4}, timestamp = {5}, isBuyerMaker = {6}, isBestPriceMatch = {7}",
                     result.aggregateTradeId,
                     result.price,
                     result.quantity,
                     result.firstTradeId,
                     result.lastTradeId,
                     result.timestamp,
                     result.isBuyerMaker,
                     result.isBestPriceMatch) << endl;
      return Nothing<json>;
    };
  }
}
