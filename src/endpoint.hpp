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
#include <iostream>
using namespace std;

namespace endpoint {
  enum class DEPTH_LIMIT: size_t {
    FIVE,
    TEN,
    TWENTY,
    FIFTY,
    ONE_HUNDRED,
    TWO_HUNDRED,
    FIVE_HUNDRED
  };

  auto depth_limit_str(DEPTH_LIMIT limit) -> string {
    switch (limit) {
    case DEPTH_LIMIT::FIVE:
      return "5";
    case DEPTH_LIMIT::TEN:
      return "10";
    case DEPTH_LIMIT::TWENTY:
      return "20";
    case DEPTH_LIMIT::FIFTY:
      return "50";
    case DEPTH_LIMIT::ONE_HUNDRED:
      return "100";
    case DEPTH_LIMIT::TWO_HUNDRED:
      return "200";
    case DEPTH_LIMIT::FIVE_HUNDRED:
      return "500";
    default:
      throw std::runtime_error("invalid depth limit");
    }
  }

  class Endpoint {
  private:
    shared_ptr<Api> api;

  public:
    Endpoint(string key, string secret);
    auto ping() -> json;
    auto time() -> json;
    auto depth(string symbol) -> json;
    auto depth(string symbol, DEPTH_LIMIT limit) -> json;
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

  auto Endpoint::depth(string symbol) -> json {
    return this->api->public_get("/api/v1/depth", Map({{ "symbol", symbol }}));
  }

  auto Endpoint::depth(string symbol, DEPTH_LIMIT limit) -> json {
    const Map &params = {
      { "symbol", symbol },
      { "limit", depth_limit_str(limit) }
    };
    return this->api->public_get("/api/v1/depth", params);
  }
}
