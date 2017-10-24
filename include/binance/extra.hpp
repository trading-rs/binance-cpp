#pragma once

#include "types/types.hpp"
using namespace binance::types;

#include <json.hpp>
using json = nlohmann::json;

#include <fp/fp.hpp>
using namespace fp;

#include <functional>
using namespace std;

namespace binance {
  namespace extra {
    template <typename T>
    function<Maybe<T>(vector<T>)> head_m = [](const vector<T> &v) {
      if (v.size() == 0) {
        return Nothing<T>;
      } else {
        return Maybe<T>(v[0]);
      }
    };

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
    function<Maybe<json>(string)> print_result<string> = [](const auto &result) {
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
    template <>
    function<Maybe<json>(CandleStick)> print_result<CandleStick> = [](const auto &result) {
      cout << format("open_time = {0}, open = {1}, high = {2}, low = {3}, close = {4}, volumn = {5}, close_time = {6}, quote_asset_volumn = {7}, number_of_trades = {8}, taker_buy_base_asset_volume = {9}, taker_buy_quote_asset_volume = {10}",
                     result.open_time,
                     result.open,
                     result.high,
                     result.low,
                     result.close,
                     result.volumn,
                     result.close_time,
                     result.quote_asset_volume,
                     result.number_of_trades,
                     result.taker_buy_base_asset_volume,
                     result.taker_buy_quote_asset_volume) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(TickerStatistics)> print_result<TickerStatistics> = [](const auto &result) {
      cout << format("priceChange = {0}, priceChangePercent = {1}, weightedAvgPrice = {2}, prevClosePrice = {3}, lastPrice = {4}, bidPrice = {5}, askPrice = {6}, openPrice = {7}, highPrice = {8}, lowPrice = {9}, volume= {10}, openTime = {11}, closeTime = {12}, firstId = {13}, lastId = {14}, count = {15}",
                     result.price_change,
                     result.price_change_percent,
                     result.weighted_avg_price,
                     result.prev_close_price,
                     result.last_price,
                     result.bid_price,
                     result.ask_price,
                     result.open_price,
                     result.high_price,
                     result.low_price,
                     result.volume,
                     result.open_time,
                     result.close_time,
                     result.first_id,
                     result.last_id,
                     result.count) << endl;
      return Nothing<json>;
    };
  }
}
