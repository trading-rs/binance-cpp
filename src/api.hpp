#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <initializer_list>
using namespace std;

#include <cpr/cpr.h>
using namespace cpr;

#ifndef FORMAT_HEADER
#define FORMAT_HEADER
#include <fmt/format.h>
#include <fmt/format.cc>
#endif
using namespace fmt;

#include <range/v3/all.hpp>

#include <cryptlite/sha256.h>
#include <cryptlite/hmac.h>
using namespace cryptlite;

namespace api {
  typedef map<string, string> Map;

  enum class REQUEST_TYPE : size_t {
    GET,
    POST,
    PUT,
    DELETE
  };

  class Api {
  private:
    string api_key;
    string api_secret;
    string domain;
    Header public_header;
    Header user_header;

  public:
    explicit Api(string key, string secret);
    auto flatten_params(const Map &params) -> string;
    auto append_params(const string &url, const Map &params) -> string;
    auto append_params(const string &url, const string &params_str) -> string;
    auto response_tweak(Response response) -> json;
    auto request(REQUEST_TYPE method, const string &url, const Header &header) -> json;
    auto add_signature(const Map &params) -> Map;
    auto public_get(const string &url, const Map &params) -> json;
    auto public_get(const string &url) -> json;
    auto user_get(const string &url, const  Map &params) -> json;
    auto user_get(const string &url) -> json;
    auto signed_get(const string &url, const  Map &params) -> json;
    auto signed_get(const string &url) -> json;
    auto public_post(const string &url, const Map &params) -> json;
    auto public_post(const string &url) -> json;
    auto user_post(const string &url, const  Map &params) -> json;
    auto user_post(const string &url) -> json;
    auto signed_post(const string &url, const  Map &params) -> json;
    auto signed_post(const string &url) -> json;
    auto public_put(const string &url, const Map &params) -> json;
    auto public_put(const string &url) -> json;
    auto user_put(const string &url, const  Map &params) -> json;
    auto user_put(const string &url) -> json;
    auto signed_put(const string &url, const  Map &params) -> json;
    auto signed_put(const string &url) -> json;
    auto public_delete(const string &url, const Map &params) -> json;
    auto public_delete(const string &url) -> json;
    auto user_delete(const string &url, const  Map &params) -> json;
    auto user_delete(const string &url) -> json;
    auto signed_delete(const string &url, const  Map &params) -> json;
    auto signed_delete(const string &url) -> json;
  };

  Api::Api(string key, string secret): api_key(key), api_secret(secret) {
    this->domain = "https://www.binance.com";
    this->public_header = {
      { "User-Agent", "Mozilla/4.0 (compatible; Node Binance API)" },
      { "accept", "application/json" },
      { "Content-Type", "application/x-www-form-urlencoded" }
    };
    this->user_header = {
      { "User-Agent", "Mozilla/4.0 (compatible; Node Binance API)" },
      { "accept", "application/json" },
      { "Content-Type", "application/x-www-form-urlencoded" },
      { "X-MBX-APIKEY", format("{}", this->api_key) }
    };
  }

  auto Api::flatten_params(const Map &params) -> string {
    vector<string> params_vec = params
      | ranges::view::transform([](const auto &pair) {
          return format("{0}={1}", pair.first, pair.second);
        });
    return params_vec | ranges::view::join('&');
  }

  auto Api::append_params(const string &url, const Map &params) -> string {
    auto params_str = flatten_params(params);
    if (params_str.empty()) {
      return url;
    } else {
      return format("{0}?{1}", url, params_str);
    }
  }

  auto Api::append_params(const string &url, const string &params_str) -> string {
    if (params_str.empty()) {
      return url;
    } else {
      return format("{0}?{1}", url, params_str);
    }
  }

  auto Api::response_tweak(Response response) -> json {
    if (response.status_code < 400) {
      return nlohmann::json::parse(response.text);
    } else {
      cout << response.status_code << " " << response.text << endl;
      return nullptr;
    }
  }

  auto Api::add_signature(const Map &params) -> Map {
    auto params_str = flatten_params(params);
    auto signature = hmac<sha256>::calc_hex(params_str, this->api_secret);
    Map new_params = params;
    new_params["signature"] = signature;
    return new_params;
  }

  auto Api::request(REQUEST_TYPE method, const string &url, const Header &header) -> json {
    Session session;
    session.SetUrl(Url{ format("{0}{1}", this->domain, url) });
    session.SetHeader(header);
    session.SetVerifySsl(VerifySsl{ false });

    Response response;
    switch (method) {
    case REQUEST_TYPE::GET: {
      response = session.Get();
      break;
    }
    case REQUEST_TYPE::POST: {
      response = session.Post();
      break;
    }
    case REQUEST_TYPE::PUT: {
      response = session.Put();
      break;
    }
    case REQUEST_TYPE::DELETE: {
      response = session.Delete();
      break;
    }
    default:
      break;
    }

    return response_tweak(response);
  }

  auto Api::public_get(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::GET, append_params(url, params), public_header);
  }

  auto Api::public_get(const string &url) -> json {
    return public_get(url, Map({}));
  }

  auto Api::user_get(const string &url, const  Map &params) -> json {
    return request(REQUEST_TYPE::GET, append_params(url, params), user_header);
  }

  auto Api::user_get(const string &url) -> json {
    return user_get(url, Map({}));
  }

  auto Api::signed_get(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::GET, append_params(url, add_signature(params)), user_header);
  }

  auto Api::signed_get(const string &url) -> json {
    return signed_get(url, Map({}));
  }

  auto Api::public_post(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::POST, append_params(url, params), public_header);
  }

  auto Api::public_post(const string &url) -> json {
    return public_post(url, Map({}));
  }

  auto Api::user_post(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::POST, append_params(url, params), user_header);
  }

  auto Api::user_post(const string &url) -> json {
    return user_post(url, Map({}));
  }

  auto Api::signed_post(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::POST, append_params(url, add_signature(params)), user_header);
  }

  auto Api::signed_post(const string &url) -> json {
    return request(REQUEST_TYPE::POST, url, user_header);
  }

  auto Api::public_put(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::PUT, append_params(url, params), public_header);
  }

  auto Api::public_put(const string &url) -> json {
    return public_put(url, Map({}));
  }

  auto Api::user_put(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::PUT, append_params(url, params), user_header);
  }

  auto Api::user_put(const string &url) -> json {
    return user_put(url, Map({}));
  }

  auto Api::signed_put(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::PUT, append_params(url, add_signature(params)), user_header);
  }

  auto Api::signed_put(const string &url) -> json {
    return signed_put(url, Map({}));
  }

  auto Api::public_delete(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::DELETE, append_params(url, params), public_header);
  }

  auto Api::public_delete(const string &url) -> json {
    return public_delete(url, Map({}));
  }

  auto Api::user_delete(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::DELETE, append_params(url, params), user_header);
  }

  auto Api::user_delete(const string &url) -> json {
    return user_delete(url, Map({}));
  }

  auto Api::signed_delete(const string &url, const Map &params) -> json {
    return request(REQUEST_TYPE::DELETE, append_params(url, add_signature(params)), user_header);
  }

  auto Api::signed_delete(const string &url) -> json {
    return signed_delete(url, Map({}));
  }
}
