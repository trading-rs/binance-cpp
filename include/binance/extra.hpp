#pragma once

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
  }
}
