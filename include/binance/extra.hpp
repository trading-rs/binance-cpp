#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <fp/fp.hpp>
using namespace fp;

#include <functional>
using namespace std;

namespace binance {
  namespace extra {
    function<Maybe<json>(json)> print_result = [](const json &result) {
      cout << result.dump(2) << endl;
      return Nothing<json>;
    };
  }
}
