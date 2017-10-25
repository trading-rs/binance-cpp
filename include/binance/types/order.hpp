#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace types {
    struct Order {
      string symbol;
      long order_id;
      string client_order_id;
      string price;
      string orig_qty;
      string executed_qty;
      string status;
      string time_in_force;
      string type;
      string side;
      string stop_price;
      string iceberg_qty;
      long time;
    };

    void from_json(const json& j, Order& t) {
      t.symbol = j.at("symbol").get<string>();
      t.order_id = j.at("orderId").get<long>();
      t.client_order_id = j.at("clientOrderId").get<string>();
      t.price = j.at("price").get<string>();
      t.orig_qty = j.at("origQty").get<string>();
      t.executed_qty = j.at("executedQty").get<string>();
      t.status = j.at("status").get<string>();
      t.time_in_force = j.at("timeInForce").get<string>();
      t.type = j.at("type").get<string>();
      t.side = j.at("side").get<string>();
      t.stop_price = j.at("stopPrice").get<string>();
      t.iceberg_qty = j.at("icebergQty").get<string>();
      t.time = j.at("time").get<long>();
    }
  }
}
