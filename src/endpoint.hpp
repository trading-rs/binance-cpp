#pragma once

#include "api.hpp"
using namespace api;

#ifndef FORMAT_HEADER
#define FORMAT_HEADER
#include <fmt/format.h>
#include <fmt/format.cc>
#endif
using namespace fmt;

#include <string>
#include <memory>
using namespace std;

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
    auto order(string side, string type, string symbol, string quantity, const Map &options) -> json;
    auto order(string side, string type, string symbol, string quantity) -> json;
    auto buy_limit(string symbol, string quantity, string price, const Map &options) -> json;
    auto buy_limit(string symbol, string quantity, string price) -> json;
    auto buy_market(string symbol, string quantity,const Map &options) -> json;
    auto buy_market(string symbol, string quantity) -> json;
    auto sell_limit(string symbol, string quantity, string price, const Map &options) -> json;
    auto sell_limit(string symbol, string quantity, string price) -> json;
    auto sell_market(string symbol, string quantity, const Map &options) -> json;
    auto sell_market(string symbol, string quantity) -> json;
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

  auto Endpoint::order(string side, string type, string symbol, string quantity, const Map &options) -> json {
    Map params = options;
    params["side"] = side;
    params["symbol"] = symbol;
    params["quantity"] = quantity;
    params["type"] = type;
    if (type == "LIMIT") {
      params["timeInForce"] = "GTC";
    }
    return this->api->signed_post("/api/v3/order", params);
  }

  auto Endpoint::order(string side, string type, string symbol, string quantity) -> json {
    return this->order(side, type, symbol, quantity, Map({}));
  }

  auto Endpoint::buy_limit(string symbol, string quantity, string price, const Map &options) -> json {
    Map params = options;
    params["price"] = price;
    return this->order("BUY", "LIMIT", symbol, quantity, params);
  }

  auto Endpoint::buy_limit(string symbol, string quantity, string price) -> json {
    return this->buy_limit(symbol, quantity, price, Map({}));
  }

  auto Endpoint::buy_market(string symbol, string quantity, const Map &options) -> json {
    return this->order("BUY", "MARKET", symbol, quantity, options);
  }

  auto Endpoint::buy_market(string symbol, string quantity) -> json {
    return this->buy_market(symbol, quantity, Map({}));
  }

  auto Endpoint::sell_limit(string symbol, string quantity, string price, const Map &options) -> json {
    Map params = options;
    params["price"] = price;
    return this->order("SELL", "LIMIT", symbol, quantity, params);
  }

  auto Endpoint::sell_limit(string symbol, string quantity, string price) -> json {
    return this->sell_limit(symbol, quantity, price, Map({}));
  }

  auto Endpoint::sell_market(string symbol, string quantity, const Map &options) -> json {
    return this->order("SELL", "MARKET", symbol, quantity, options);
  }

  auto Endpoint::sell_market(string symbol, string quantity) -> json {
    return this->sell_market(symbol, quantity);
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
}
