#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct NewOrderResponse {
      string symbol;
      long order_id;
      string client_order_id;
      long transact_time;
    };

    void to_json(json& j, const NewOrderResponse& t) {
      j = json{
        { "symbol", t.symbol },
        { "orderId", t.order_id },
        { "clientOrderId", t.client_order_id },
        { "transactTime", t.transact_time }
      };
    }

    void from_json(const json& j, NewOrderResponse& t) {
      t.symbol = j.at("symbol").get<string>();
      t.order_id = j.at("orderId").get<long>();
      t.client_order_id = j.at("clientOrderId").get<string>();
      t.transact_time = j.at("transactTime").get<long>();
    }
  }
}
