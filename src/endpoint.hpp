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
}
