#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(Trade,
                 (long, id, "id")
                 (string, price, "price")
                 (string, qty, "qty")
                 (string, commission, "commission")
                 (string, commission_asset, "commissionAsset")
                 (long, time, "time")
                 (bool, is_buyer, "isBuyer")
                 (bool, is_maker, "isMaker")
                 (bool, is_best_match, "isBestMatch"))
  }
}
