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
    template <typename T>
    function<Maybe<json>(vector<T>)> print_results = [](const vector<T> &results) {
      std::for_each(results.cbegin(), results.cend(), [&](const T &result) {
          print_result<T>(result);
        });
      return Nothing<json>;
    };

    template <>
    function<Maybe<json>(json)> print_result<json> = [](const auto &result) {
      cout << result.dump(2) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(int)> print_result<int> = [](const auto &result) {
      cout << result << endl;
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
    template <>
    function<Maybe<json>(TickerPrice)> print_result<TickerPrice> = [](const auto &result) {
      cout << format("symbol = {0}, price = {1}",
                     result.symbol,
                     result.price) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(BookTicker)> print_result<BookTicker> = [](const auto &result) {
      cout << format("symbol = {0}, bidPrice = {1}, bidQty = {2}, askPrice = {3}, askQty = {4}",
                     result.symbol,
                     result.bid_price,
                     result.bid_qty,
                     result.ask_price,
                     result.ask_qty) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(NewOrderResponse)> print_result<NewOrderResponse> = [](const auto &result) {
      cout << format("symbol = {0}, orderId = {1}, clientOrderId = {2}, transactTime = {3}",
                     result.symbol,
                     result.order_id,
                     result.client_order_id,
                     result.transact_time) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(Order)> print_result<Order> = [](const auto &result) {
      cout << format("symbol = {0}, orderId = {1}, clientOrderId = {2}, price = {3}, origQty = {4}, executedQty = {5}, status = {6}, timeInForce = {7}, type = {8}, side = {9}, stopPrice = {10}, icebergQty = {11}, time = {12}",
                     result.symbol,
                     result.order_id,
                     result.client_order_id,
                     result.price,
                     result.orig_qty,
                     result.executed_qty,
                     result.status,
                     result.time_in_force,
                     result.type,
                     result.side,
                     result.stop_price,
                     result.iceberg_qty,
                     result.time) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(CancelOrderResponse)> print_result<CancelOrderResponse> = [](const auto &result) {
      cout << format("symbol = {0}, orderId = {1}, clientOrderId = {2}, origClientOrderId = {3}",
                     result.symbol,
                     result.order_id,
                     result.client_order_id,
                     result.orig_client_order_id) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(Balance)> print_result<Balance> = [](const auto &result) {
      cout << format("asset = {0}, free = {1}, locked = {2}",
                     result.asset,
                     result.free,
                     result.locked) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(Account)> print_result<Account> = [](const auto &result) {
      cout << format("makerCommission = {0}, takerCommission = {1}, buyerCommission = {2}, sellerCommission = {3}, canTrade = {4}, canWithdraw = {5}, canDeposit = {6}",
                     result.maker_commission,
                     result.taker_commission,
                     result.buyer_commission,
                     result.seller_commission,
                     result.can_trade,
                     result.can_deposit,
                     result.can_withdraw) << endl;
      return Maybe<vector<Balance>>(result.balances) >>= print_results<Balance>;
    };
    template <>
    function<Maybe<json>(Trade)> print_result<Trade> = [](const auto &result) {
      cout << format("id = {0}, price = {1}, qty = {2}, commission = {3}, commissionAsset = {4}, time = {5}, isBuyer = {6}, isMaker = {7}, isBestMatch = {8}",
                     result.id,
                     result.price,
                     result.qty,
                     result.commission,
                     result.commission_asset,
                     result.time,
                     result.is_buyer,
                     result.is_maker,
                     result.is_best_match) << endl;
      return Nothing<json>;
    };
    template <>
    function<Maybe<json>(DepthEvent)> print_result<DepthEvent> = [](const auto &result) {
      cout << format("e = {0}, E = {1}, s = {2}, u = {3}",
                     result.event_type,
                     result.event_time,
                     result.symbol,
                     result.update_id) << endl;
      cout << "Bids:" << endl;
      Maybe<vector<OrderBookEntry>>(result.bids) >>= print_results<OrderBookEntry>;
      cout << "Asks:" << endl;
      return Maybe<vector<OrderBookEntry>>(result.asks) >>= print_results<OrderBookEntry>;
      cout << endl;
    };
  }
}
