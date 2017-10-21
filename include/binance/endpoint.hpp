#pragma once

#include "api.hpp"
using namespace binance::api;

#include "websocket_client.hpp"
using namespace binance::websocket_client;

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
    class Endpoint {
    private:
      shared_ptr<Api> api;

    public:
      Endpoint(string key, string secret);
      auto ping() -> json;
      auto time() -> json;
      /**
         @options:
         'limit': legal range is { 50, 20, 100, 500, 5, 200, 10 }
      */
      auto depth(string symbol, const Map &options) -> json;
      auto depth(string symbol) -> json;
      /**
         @options:
         fromId
         startTime
         endTime
         limit
      */
      auto agg_trades(string symbol, const Map &options) -> json;
      auto agg_trades(string symbol) -> json;
      /**
         @options:
         limit
         startTime
         endTime
      */
      auto klines(string symbol, string interval, const Map &options) -> json;
      auto klines(string symbol, string interval) -> json;
      auto ticker_24hr(string symbol) -> json;
      auto ticker_all_prices() -> json;
      auto ticker_all_bool_tickers() -> json;
      auto order(string side, string type, string symbol, double quantity, const Map &options) -> json;
      auto order(string side, string type, string symbol, double quantity) -> json;
      auto buy_limit(string symbol, double quantity, double price, const Map &options) -> json;
      auto buy_limit(string symbol, double quantity, double price) -> json;
      auto buy_market(string symbol, double quantity,const Map &options) -> json;
      auto buy_market(string symbol, double quantity) -> json;
      auto sell_limit(string symbol, double quantity, double price, const Map &options) -> json;
      auto sell_limit(string symbol, double quantity, double price) -> json;
      auto sell_market(string symbol, double quantity, const Map &options) -> json;
      auto sell_market(string symbol, double quantity) -> json;
      auto order_status(string symbol, string order_id) -> json;
      auto cancle_order(string symbol, string order_id) -> json;
      auto open_orders(string symbol) -> json;
      /**
         @options:
         orderId: If orderId is set, it will get orders >= that orderId. Otherwise most recent orders are returned
         limit: Default 500; max 500
      */
      auto all_orders(string symbol, const Map &options) -> json;
      auto all_orders(string symbol) -> json;
      auto my_account() -> json;
      /**
         @options:
         fromId: TradeId to fetch from. Default gets most recent trades
         limit: Default 500; max 500
      */
      auto my_trades(string symbol, const Map &options) -> json;
      auto my_trades(string symbol) -> json;
      auto start_user_data_stream() -> json;
      auto keepalive_user_data_stream(string listen_key) -> json;
      auto close_user_data_stream(string listen_key) -> json;
      auto depth_websocket(string symbol, async_callback callback) -> void;
      auto kline_websocket(string symbol, string interval, async_callback callback) -> void;
      auto trades_websocket(string symbol, async_callback callback) -> void;
      auto user_data_websockets(string listen_key, async_callback callback) -> void;
    };

    Endpoint::Endpoint(string key, string secret) {
      this->api = make_shared<Api>(key, secret);
    }

    auto Endpoint::ping() -> json {
      return this->api->public_get("/api/v1/ping");
    }

    auto Endpoint::time() -> json {
      return this->api->public_get("/api/v1/time");
    }

    auto Endpoint::depth(string symbol, const Map &options) -> json {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->public_get("/api/v1/depth", params);
    }

    auto Endpoint::depth(string symbol) -> json {
      return this->depth(symbol, Map({}));
    }

    auto Endpoint::agg_trades(string symbol, const Map &options) -> json {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->public_get("/api/v1/aggTrades", params);
    }

    auto Endpoint::agg_trades(string symbol) -> json {
      return this->agg_trades(symbol, Map({}));
    }

    auto Endpoint::klines(string symbol, string interval, const Map &options) -> json {
      Map params = options;
      params["symbol"] = symbol;
      params["interval"] = interval;
      return this->api->public_get("/api/v1/klines", params);
    }

    auto Endpoint::klines(string symbol, string interval) -> json {
      return this->klines(symbol, interval, Map({}));
    }

    auto Endpoint::ticker_24hr(string symbol) -> json {
      return this->api->public_get("/api/v1/ticker/24hr", Map({{ "symbol", symbol }}));
    }

    auto Endpoint::ticker_all_prices() -> json {
      return this->api->public_get("/api/v1/ticker/allPrices");
    }

    auto Endpoint::ticker_all_bool_tickers() -> json {
      return this->api->public_get("/api/v1/ticker/allBookTickers");
    }

    auto Endpoint::order(string side, string type, string symbol, double quantity, const Map &options) -> json {
      Map params = options;
      params["side"] = side;
      params["symbol"] = symbol;
      params["quantity"] = format("{}", quantity);
      params["type"] = type;
      if (type == "LIMIT") {
        params["timeInForce"] = "GTC";
      }
      return this->api->signed_post("/api/v3/order", params);
    }

    auto Endpoint::order(string side, string type, string symbol, double quantity) -> json {
      return this->order(side, type, symbol, quantity, Map({}));
    }

    auto Endpoint::buy_limit(string symbol, double quantity, double price, const Map &options) -> json {
      Map params = options;
      params["price"] = format("{}", price);
      return this->order("BUY", "LIMIT", symbol, quantity, params);
    }

    auto Endpoint::buy_limit(string symbol, double quantity, double price) -> json {
      return this->buy_limit(symbol, quantity, price, Map({}));
    }

    auto Endpoint::buy_market(string symbol, double quantity, const Map &options) -> json {
      return this->order("BUY", "MARKET", symbol, quantity, options);
    }

    auto Endpoint::buy_market(string symbol, double quantity) -> json {
      return this->buy_market(symbol, quantity, Map({}));
    }

    auto Endpoint::sell_limit(string symbol, double quantity, double price, const Map &options) -> json {
      Map params = options;
      params["price"] = format("{}", price);
      return this->order("SELL", "LIMIT", symbol, quantity, params);
    }

    auto Endpoint::sell_limit(string symbol, double quantity, double price) -> json {
      return this->sell_limit(symbol, quantity, price, Map({}));
    }

    auto Endpoint::sell_market(string symbol, double quantity, const Map &options) -> json {
      return this->order("SELL", "MARKET", symbol, quantity, options);
    }

    auto Endpoint::sell_market(string symbol, double quantity) -> json {
      return this->sell_market(symbol, quantity, Map({}));
    }

    auto Endpoint::order_status(string symbol, string order_id) -> json {
      const Map &params = {
        { "symbol", symbol },
        { "orderId", order_id }
      };

      return this->api->signed_get("/api/v3/order", params);
    }

    auto Endpoint::cancle_order(string symbol, string order_id) -> json {
      const Map &params = {
        { "symbol", symbol },
        { "orderId", order_id }
      };

      return this->api->signed_delete("/api/v3/order", params);
    }

    auto Endpoint::open_orders(string symbol) -> json {
      return this->api->signed_get("/api/v3/openOrders", Map({{ "symbol", symbol }}));
    }

    auto Endpoint::all_orders(string symbol, const Map &options) -> json {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->signed_get("/api/v3/allOrders", params);
    }

    auto Endpoint::all_orders(string symbol) -> json {
      return this->all_orders(symbol, Map({}));
    }

    auto Endpoint::my_account() -> json {
      return this->api->signed_get("/api/v3/account", Map({}));
    }

    auto Endpoint::my_trades(string symbol, const Map &options) -> json {
      Map params = options;
      params["symbol"] = symbol;
      return this->api->signed_get("/api/v3/myTrades", params);
    }

    auto Endpoint::my_trades(string symbol) -> json {
      return this->my_trades(symbol, Map({}));
    }

    auto Endpoint::start_user_data_stream() -> json {
      return this->api->user_post("/api/v1/userDataStream", Map({}));
    }

    auto Endpoint::keepalive_user_data_stream(string listen_key) -> json {
      return this->api->user_put("/api/v1/userDataStream", Map({{ "listenKey", listen_key }}));
    }

    auto Endpoint::close_user_data_stream(string listen_key) -> json {
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
