#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct Balance {
      string asset;
      double free;
      double locked;
    };

    void to_json(json& j, const Balance& b) {
      j = json{
        { "asset", b.asset },
        { "free", b.free },
        { "locked", b.locked }
      };
    }

    void from_json(const json& j, Balance& b) {
      b.asset = j.at("asset").get<string>();
      b.free = j.at("free").get<double>();
      b.locked = j.at("locked").get<double>();
    }
  }
}


