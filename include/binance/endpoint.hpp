#pragma once

#include "api.hpp"
using namespace binance::api;

#include "websocket_client.hpp"
using namespace binance::websocket_client;

#include "types/types.hpp"
using namespace binance::types;

#ifndef FORMAT_HEADER
#define FORMAT_HEADER
#include <fmt/format.h>
#include <fmt/format.cc>
#endif
using namespace fmt;

#include <string>
#include <memory>
using namespace std;

namespace binance {
  namespace endpoint {
    shared_ptr<spd::logger> logger = spd::stdout_color_mt("ENDPOINT");

    template <typename T>
    function<Maybe<vector<T>>(json)> get_datas = [](const auto &j) {
      if (j.is_array()) {
        try {
          vector<T> datas = j;
          return Maybe<vector<T>>(datas);
        } catch (const std::exception& e) {
          logger->error("{0} when parsing {1}", e.what(), j.dump());
          return Nothing<vector<T>>;
        }
      } else {
        logger->error("{0} is not a json array!", j.dump());
        return Nothing<vector<T>>;
      }
    };

    template <typename T>
    function<Maybe<T>(json)> get_data = [](const auto &j) {
      try {
        T data = j;
        return Maybe<T>(data);
      } catch (const std::exception& e) {
        logger->error("{0} when parsing {1}", e.what(), j.dump());
        return Nothing<T>;
      }
    };

    template <typename T>
    function<function<Maybe<T>(json)>(string)> get_by_field = [](const string &field) {
      return [=](const auto &j) {
        auto st = j[field];
        if (st != nullptr) {
          return Maybe<T>(st.template get<T>());
        } else {
          logger->error("{0} does not contain `{1}` property!", j.dump(), field);
          return Nothing<T>;
        }
      };
    };

    class Endpoint {
    private:
      shared_ptr<Api> api;

    public:
      Endpoint(string key, string secret);
      auto ping() -> Maybe<json>;
      auto time() -> Maybe<long>;
      /**
         @options:
         'limit': legal range is { 50, 20, 100, 500, 5, 200, 10 }
      */
      auto order_book(string symbol, const Map &options) -> Maybe<OrderBook>;
      auto order_book(string symbol, int limit) -> Maybe <OrderBook>;
      auto order_book(string symbol) -> Maybe<OrderBook>;
      /**
         @options:
         fromId
         startTime
         endTime
         limit
      */
      auto agg_trades(string symbol, const Map &options) -> Maybe<vector<AggTrade>>;
      auto agg_trades(string symbol) -> Maybe<vector<AggTrade>>;
      /**
         @options:
         limit
         startTime
         endTime
      */
      auto candlestick_bars(string symbol, string interval, const Map &options) -> Maybe<vector<CandleStick>>;
      auto candlestick_bars(string symbol, string interval) -> Maybe<vector<CandleStick>>;
      auto ticker_24hr(string symbol) -> Maybe<TickerStatistics>;
      auto all_prices() -> Maybe<vector<TickerPrice>>;
      auto all_book_tickers() -> Maybe<vector<BookTicker>>;
      auto order(string side, string type, string symbol, double quantity, const Map &options) -> Maybe<NewOrderResponse>;
      auto order(string side, string type, string symbol, double quantity) -> Maybe<NewOrderResponse>;
      auto buy_limit(string symbol, double quantity, double price, const Map &options) -> Maybe<NewOrderResponse>;
      auto buy_limit(string symbol, double quantity, double price) -> Maybe<NewOrderResponse>;
      auto buy_market(string symbol, double quantity,const Map &options) -> Maybe<NewOrderResponse>;
      auto buy_market(string symbol, double quantity) -> Maybe<NewOrderResponse>;
      auto sell_limit(string symbol, double quantity, double price, const Map &options) -> Maybe<NewOrderResponse>;
      auto sell_limit(string symbol, double quantity, double price) -> Maybe<NewOrderResponse>;
      auto sell_market(string symbol, double quantity, const Map &options) -> Maybe<NewOrderResponse>;
      auto sell_market(string symbol, double quantity) -> Maybe<NewOrderResponse>;
      auto order_status(string symbol, long order_id) -> Maybe<Order>;
      auto cancel_order(string symbol, long order_id) -> Maybe<CancelOrderResponse>;
      auto open_orders(string symbol) -> Maybe<vector<Order>>;
      /**
         @options:
         orderId: If orderId is set, it will get orders >= that orderId. Otherwise most recent orders are returned
         limit: Default 500; max 500
      */
      auto all_orders(string symbol, const Map &options) -> Maybe<vector<Order>>;
      auto all_orders(string symbol) -> Maybe<vector<Order>>;
      auto my_account() -> Maybe<Account>;
      /**
         @options:
         fromId: TradeId to fetch from. Default gets most recent trades
         limit: Default 500; max 500
      */
      auto my_trades(string symbol, const Map &options) -> Maybe<vector<Trade>>;
      auto my_trades(string symbol) -> Maybe<vector<Trade>>;
      auto withdraw(string asset, string address, double amount, const Map &options) -> Maybe<json>;
      auto withdraw(string asset, string address, double amount) -> Maybe<json>;
      auto withdraw_history(const Map &options) -> Maybe<WithdrawHistory>;
      auto withdraw_history(string asset) -> Maybe<WithdrawHistory>;
      auto deposit_history(const Map &options) -> Maybe<DepositHistory>;
      auto deposit_history(string asset) -> Maybe<DepositHistory>;
      auto start_user_data_stream() -> Maybe<string>;
      auto keepalive_user_data_stream(string listen_key) -> Maybe<json>;
      auto close_user_data_stream(string listen_key) -> Maybe<json>;
      auto depth_websocket(string symbol, async_callback callback) -> void;
      auto kline_websocket(string symbol, string interval, async_callback callback) -> void;
      auto trades_websocket(string symbol, async_callback callback) -> void;
      auto user_data_websockets(string listen_key, async_callback callback) -> void;
    };

    Endpoint::Endpoint(string key, string secret) {
      this->api = make_shared<Api>(key, secret);
    }

    auto Endpoint::ping() -> Maybe<json> {
      return this->api->public_get("/api/v1/ping");
    }

    auto Endpoint::time() -> Maybe<long> {
      return this->api->public_get("/api/v1/time") >>= get_by_field<long>("serverTime");
    }

    auto Endpoint::order_book(string symbol, const Map &options) -> Maybe<OrderBook> {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->public_get("/api/v1/depth", params) >>= get_data<OrderBook>;
    }

    auto Endpoint::order_book(string symbol, int limit) -> Maybe<OrderBook> {
      return this->order_book(symbol, Map({{ "limit", format("{}", limit) }}));
    }

    auto Endpoint::order_book(string symbol) -> Maybe<OrderBook> {
      return this->order_book(symbol, Map({}));
    }

    auto Endpoint::agg_trades(string symbol, const Map &options) -> Maybe<vector<AggTrade>> {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->public_get("/api/v1/aggTrades", params) >>= get_datas<AggTrade>;
    }

    auto Endpoint::agg_trades(string symbol) -> Maybe<vector<AggTrade>> {
      return this->agg_trades(symbol, Map({}));
    }

    auto Endpoint::candlestick_bars(string symbol, string interval, const Map &options) -> Maybe<vector<CandleStick>> {
      Map params = options;
      params["symbol"] = symbol;
      params["interval"] = interval;
      return this->api->public_get("/api/v1/klines", params) >>= get_datas<CandleStick>;
    }

    auto Endpoint::candlestick_bars(string symbol, string interval) -> Maybe<vector<CandleStick>> {
      return this->candlestick_bars(symbol, interval, Map({}));
    }

    auto Endpoint::ticker_24hr(string symbol) -> Maybe<TickerStatistics> {
      return this->api->public_get("/api/v1/ticker/24hr", Map({{ "symbol", symbol }})) >>= get_data<TickerStatistics>;
    }

    auto Endpoint::all_prices() -> Maybe<vector<TickerPrice>> {
      return this->api->public_get("/api/v1/ticker/allPrices") >>= get_datas<TickerPrice>;
    }

    auto Endpoint::all_book_tickers() -> Maybe<vector<BookTicker>> {
      return this->api->public_get("/api/v1/ticker/allBookTickers") >>= get_datas<BookTicker>;
    }

    auto Endpoint::order(string side, string type, string symbol, double quantity, const Map &options) -> Maybe<NewOrderResponse> {
      Map params = options;
      params["side"] = side;
      params["symbol"] = symbol;
      params["quantity"] = format("{}", quantity);
      params["type"] = type;
      if (type == "LIMIT") {
        params["timeInForce"] = "GTC";
      }
      return this->api->signed_post("/api/v3/order", params) >>= get_data<NewOrderResponse>;
    }

    auto Endpoint::order(string side, string type, string symbol, double quantity) -> Maybe<NewOrderResponse> {
      return this->order(side, type, symbol, quantity, Map({}));
    }

    auto Endpoint::buy_limit(string symbol, double quantity, double price, const Map &options) -> Maybe<NewOrderResponse> {
      Map params = options;
      params["price"] = format("{}", price);
      return this->order("BUY", "LIMIT", symbol, quantity, params);
    }

    auto Endpoint::buy_limit(string symbol, double quantity, double price) -> Maybe<NewOrderResponse> {
      return this->buy_limit(symbol, quantity, price, Map({}));
    }

    auto Endpoint::buy_market(string symbol, double quantity, const Map &options) -> Maybe<NewOrderResponse> {
      return this->order("BUY", "MARKET", symbol, quantity, options);
    }

    auto Endpoint::buy_market(string symbol, double quantity) -> Maybe<NewOrderResponse> {
      return this->buy_market(symbol, quantity, Map({}));
    }

    auto Endpoint::sell_limit(string symbol, double quantity, double price, const Map &options) -> Maybe<NewOrderResponse> {
      Map params = options;
      params["price"] = format("{}", price);
      return this->order("SELL", "LIMIT", symbol, quantity, params);
    }

    auto Endpoint::sell_limit(string symbol, double quantity, double price) -> Maybe<NewOrderResponse> {
      return this->sell_limit(symbol, quantity, price, Map({}));
    }

    auto Endpoint::sell_market(string symbol, double quantity, const Map &options) -> Maybe<NewOrderResponse> {
      return this->order("SELL", "MARKET", symbol, quantity, options);
    }

    auto Endpoint::sell_market(string symbol, double quantity) -> Maybe<NewOrderResponse> {
      return this->sell_market(symbol, quantity, Map({}));
    }

    auto Endpoint::order_status(string symbol, long order_id) -> Maybe<Order> {
      const Map &params = {
        { "symbol", symbol },
        { "orderId", format("{}", order_id) }
      };

      return this->api->signed_get("/api/v3/order", params) >>= get_data<Order>;
    }

    auto Endpoint::cancel_order(string symbol, long order_id) -> Maybe<CancelOrderResponse> {
      const Map &params = {
        { "symbol", symbol },
        { "orderId", format("{}", order_id) }
      };

      return this->api->signed_delete("/api/v3/order", params) >>= get_data<CancelOrderResponse>;
    }

    auto Endpoint::open_orders(string symbol) -> Maybe<vector<Order>> {
      return this->api->signed_get("/api/v3/openOrders", Map({{ "symbol", symbol }})) >>= get_datas<Order>;
    }

    auto Endpoint::all_orders(string symbol, const Map &options) -> Maybe<vector<Order>> {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->signed_get("/api/v3/allOrders", params) >>= get_datas<Order>;
    }

    auto Endpoint::all_orders(string symbol) -> Maybe<vector<Order>> {
      return this->all_orders(symbol, Map({}));
    }

    auto Endpoint::my_account() -> Maybe<Account> {
      return this->api->signed_get("/api/v3/account", Map({})) >>= get_data<Account>;
    }

    auto Endpoint::my_trades(string symbol, const Map &options) -> Maybe<vector<Trade>> {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->signed_get("/api/v3/myTrades", params) >>= get_datas<Trade>;
    }

    auto Endpoint::my_trades(string symbol) -> Maybe<vector<Trade>> {
      return this->my_trades(symbol, Map({}));
    }

    auto Endpoint::withdraw(string asset, string address, double amount, const Map &options) -> Maybe<json> {
      Map params = options;
      params["asset"] = asset;
      params["address"] = address;
      params["amount"] = format("{}", amount);
      return this->api->signed_post("/wapi/v1/withdraw.html", params);
    }

    auto Endpoint::withdraw(string asset, string address, double amount) -> Maybe<json> {
      return this->withdraw(asset, address, amount, Map({}));
    }

    auto Endpoint::withdraw_history(const Map &options) -> Maybe<WithdrawHistory> {
      return this->api->signed_post("/wapi/v1/getWithdrawHistory.html", options) >>= get_data<WithdrawHistory>;
    }

    auto Endpoint::withdraw_history(string asset) -> Maybe<WithdrawHistory> {
      return this->withdraw_history(Map({{ "asset", asset }}));
    }

    auto Endpoint::deposit_history(const Map &options) -> Maybe<DepositHistory> {
      return this->api->signed_post("/wapi/v1/getDepositHistory.html", options) >>= get_data<DepositHistory>;
    }

    auto Endpoint::deposit_history(string asset) -> Maybe<DepositHistory> {
      return this->deposit_history(Map({{ "asset", asset }}));
    }

    auto Endpoint::start_user_data_stream() -> Maybe<string> {
      return this->api->user_post("/api/v1/userDataStream", Map({})) >>= get_by_field<string>("listenKey");
    }

    auto Endpoint::keepalive_user_data_stream(string listen_key) -> Maybe<json> {
      return this->api->user_put("/api/v1/userDataStream", Map({{ "listenKey", listen_key }}));
    }

    auto Endpoint::close_user_data_stream(string listen_key) -> Maybe<json> {
      return this->api->user_delete("/api/v1/userDataStream", Map({{ "listenKey", listen_key }}));
    }

    auto Endpoint::depth_websocket(string symbol, async_callback callback) -> void {
      subscribe(format("/ws/{}@depth", symbol), callback);
    }

    auto Endpoint::kline_websocket(string symbol, string interval, async_callback callback) -> void {
      subscribe(format("/ws/{0}@kline_{1}", symbol, interval), callback);
    }

    auto Endpoint::trades_websocket(string symbol, async_callback callback) -> void {
      subscribe(format("/ws/{}@aggTrade", symbol), callback);
    }

    auto Endpoint::user_data_websockets(string listen_key, async_callback callback) -> void {
      subscribe(format("/ws/{}", listen_key), callback);
    }
  }
}
