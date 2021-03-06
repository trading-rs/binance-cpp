#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <fp/fp.hpp>
using namespace fp;

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include <chrono>
using namespace std::chrono;

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

#include <spdlog/spdlog.h>
namespace spd = spdlog;

namespace binance {
  namespace api {
    typedef map<string, string> Map;
    shared_ptr<spd::logger> logger = spd::stdout_color_mt("API");

    enum class REQUEST_TYPE : size_t {
      GET,
      POST,
      POSTW, // for wapi endpoints
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
      explicit Api(const string &key, const string &secret);
      auto flatten_params(const Map &params) -> string;
      auto append_params(const string &url, const Map &params) -> string;
      auto append_params(const string &url, const string &params_str) -> string;
      auto response_tweak(const string &method, const string &url, const Response &response) -> Maybe<json>;
      auto add_signature(const Map &params) -> Map;
      auto params_to_payload(const Map &params) -> Payload;
      auto request(REQUEST_TYPE method, const string &url, const Header &header, const Map &params) -> Maybe<json>;
      auto public_get(const string &url, const Map &params) -> Maybe<json>;
      auto public_get(const string &url) -> Maybe<json>;
      auto user_get(const string &url, const Map &params) -> Maybe<json>;
      auto user_get(const string &url) -> Maybe<json>;
      auto signed_get(const string &url, const Map &params) -> Maybe<json>;
      auto signed_get(const string &url) -> Maybe<json>;
      auto signed_postw(const string &url, const Map &params) -> Maybe<json>;
      auto signed_postw(const string &url) -> Maybe<json>;
      auto public_post(const string &url, const Map &params) -> Maybe<json>;
      auto public_post(const string &url) -> Maybe<json>;
      auto user_post(const string &url, const Map &params) -> Maybe<json>;
      auto user_post(const string &url) -> Maybe<json>;
      auto signed_post(const string &url, const Map &params) -> Maybe<json>;
      auto signed_post(const string &url) -> Maybe<json>;
      auto public_put(const string &url, const Map &params) -> Maybe<json>;
      auto public_put(const string &url) -> Maybe<json>;
      auto user_put(const string &url, const Map &params) -> Maybe<json>;
      auto user_put(const string &url) -> Maybe<json>;
      auto signed_put(const string &url, const Map &params) -> Maybe<json>;
      auto signed_put(const string &url) -> Maybe<json>;
      auto public_delete(const string &url, const Map &params) -> Maybe<json>;
      auto public_delete(const string &url) -> Maybe<json>;
      auto user_delete(const string &url, const Map &params) -> Maybe<json>;
      auto user_delete(const string &url) -> Maybe<json>;
      auto signed_delete(const string &url, const Map &params) -> Maybe<json>;
      auto signed_delete(const string &url) -> Maybe<json>;
    };

    Api::Api(const string &key, const string &secret): api_key(key), api_secret(secret) {
      this->domain = "https://www.binance.com";
      this->public_header = {
        { "User-Agent", "Mozilla/4.0 (compatible; Node Binance API)" },
        { "Accept", "application/json" },
        { "Content-Type", "application/x-www-form-urlencoded" }
      };
      this->user_header = {
        { "User-Agent", "Mozilla/4.0 (compatible; Node Binance API)" },
        { "Accept", "application/json" },
        { "Content-Type", "application/x-www-form-urlencoded" },
        { "X-MBX-APIKEY", format("{}", this->api_key) }
      };
    }

    auto Api::flatten_params(const Map &params) -> string {
      auto it = params.find("signature");
      string signature("");
      Map new_params = params;
      if (it != params.end()) {
        signature = params.at("signature");
        new_params.erase("signature");
      }
      new_params.erase("signature");
      vector<string> params_vec = new_params
        | ranges::view::transform([](const auto &pair) {
            return format("{0}={1}", pair.first, pair.second);
          });
      string params_str = params_vec | ranges::view::join('&');
      if (signature.empty()) {
        return params_str;
      } else {
        // for wapi endpoints, signature always has to be the last request parameter
        return format("{0}&signature={1}", params_str, signature);
      }
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

    auto Api::response_tweak(const string &method, const string &url, const Response &response) -> Maybe<json> {
      if (response.status_code < 400) {
        logger->info("{0} {1}, status code: {2}, content: {3}", method, url, response.status_code, response.text);
        return Maybe<json>(nlohmann::json::parse(response.text));
      } else {
        logger->error("{0} {1}, status code: {2}, content: {3}", method, url, response.status_code, response.text);
        return Nothing<json>;
      }
    }

    auto Api::add_signature(const Map &params) -> Map {
      milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
      Map new_params = params;
      new_params["timestamp"] = to_string(ms.count());
      new_params["recvWindow"] = "6000000";
      auto params_str = flatten_params(new_params);
      auto signature = hmac<sha256>::calc_hex(params_str, this->api_secret);
      new_params["signature"] = signature;
      return new_params;
    }

    auto Api::params_to_payload(const Map &params) -> Payload {
      auto payload = Payload(initializer_list<Pair>({}));
      std::for_each(params.cbegin(), params.cend(), [&](const pair<string, string> &pair) {
          payload.AddPair(Pair(pair.first, pair.second));
        });
      return payload;
    }

    auto Api::request(REQUEST_TYPE method, const string &url, const Header &header, const Map &params) -> Maybe<json> {
      Session session;
      session.SetUrl(Url{ format("{0}{1}", this->domain, url) });
      session.SetHeader(header);
      session.SetVerifySsl(VerifySsl{ false });

      Response response;
      string method_str;
      switch (method) {
      case REQUEST_TYPE::GET: {
        response = session.Get();
        method_str = "GET";
        break;
      }
      case REQUEST_TYPE::POST: {
        session.SetPayload(params_to_payload(params));
        response = session.Post();
        method_str = "POST";
        break;
      }
      case REQUEST_TYPE::POSTW: {
        session.SetPayload(Payload{});
        response = session.Post();
        method_str = "POSTW";
        break;
      }
      case REQUEST_TYPE::PUT: {
        session.SetPayload(params_to_payload(params));
        response = session.Put();
        method_str = "PUT";
        break;
      }
      case REQUEST_TYPE::DELETE: {
        session.SetPayload(params_to_payload(params));
        response = session.Delete();
        method_str = "DELETE";
        break;
      }
      default:
        break;
      }

      return response_tweak(method_str, url, response);
    }

    auto Api::public_get(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::GET, append_params(url, params), public_header, Map({}));
    }

    auto Api::public_get(const string &url) -> Maybe<json> {
      return public_get(url, Map({}));
    }

    auto Api::user_get(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::GET, append_params(url, params), user_header, Map({}));
    }

    auto Api::user_get(const string &url) -> Maybe<json> {
      return user_get(url, Map({}));
    }

    auto Api::signed_get(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::GET, append_params(url, add_signature(params)), user_header, Map({}));
    }

    auto Api::signed_get(const string &url) -> Maybe<json> {
      return signed_get(url, Map({}));
    }

    auto Api::signed_postw(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::POSTW, append_params(url, add_signature(params)), user_header, Map({}));
    }

    auto Api::signed_postw(const string &url) -> Maybe<json> {
      return signed_postw(url, Map({}));
    }

    auto Api::public_post(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::POST, url, public_header, params);
    }

    auto Api::public_post(const string &url) -> Maybe<json> {
      return public_post(url, Map({}));
    }

    auto Api::user_post(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::POST, url, user_header, params);
    }

    auto Api::user_post(const string &url) -> Maybe<json> {
      return user_post(url, Map({}));
    }

    auto Api::signed_post(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::POST, url, user_header, add_signature(params));
    }

    auto Api::signed_post(const string &url) -> Maybe<json> {
      return signed_post(url, Map({}));
    }

    auto Api::public_put(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::PUT, url, public_header, params);
    }

    auto Api::public_put(const string &url) -> Maybe<json> {
      return public_put(url, Map({}));
    }

    auto Api::user_put(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::PUT, url, user_header, params);
    }

    auto Api::user_put(const string &url) -> Maybe<json> {
      return user_put(url, Map({}));
    }

    auto Api::signed_put(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::PUT, url, user_header, add_signature(params));
    }

    auto Api::signed_put(const string &url) -> Maybe<json> {
      return signed_put(url, Map({}));
    }

    auto Api::public_delete(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::DELETE, url, public_header, params);
    }

    auto Api::public_delete(const string &url) -> Maybe<json> {
      return public_delete(url, Map({}));
    }

    auto Api::user_delete(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::DELETE, url, user_header, params);
    }

    auto Api::user_delete(const string &url) -> Maybe<json> {
      return user_delete(url, Map({}));
    }

    auto Api::signed_delete(const string &url, const Map &params) -> Maybe<json> {
      return request(REQUEST_TYPE::DELETE, url, user_header, add_signature(params));
    }

    auto Api::signed_delete(const string &url) -> Maybe<json> {
      return signed_delete(url, Map({}));
    }
  }
}
