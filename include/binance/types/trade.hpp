#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct Trade {
      long id;
      string price;
      string qty;
      string commission;
      string commission_asset;
      long time;
      bool is_buyer;
      bool is_maker;
      bool is_best_match;
    };

    void from_json(const json& j, Trade& t) {
      t.id = j.at("id").get<long>();
      t.price = j.at("price").get<string>();
      t.qty = j.at("qty").get<string>();
      t.commission = j.at("commission").get<string>();
      t.commission_asset = j.at("commissionAsset").get<string>();
      t.time = j.at("time").get<long>();
      t.is_buyer = j.at("isBuyer").get<bool>();
      t.is_maker = j.at("isMaker").get<bool>();
      t.is_best_match = j.at("isBestMatch").get<bool>();
    }
  }
}
