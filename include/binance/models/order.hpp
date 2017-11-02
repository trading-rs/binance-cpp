#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(Order,
                 (string, symbol, "symbol")
                 (long, order_id, "orderId")
                 (string, client_order_id, "clientOrderId")
                 (string, price, "price")
                 (string, orig_qty, "origQty")
                 (string, executed_qty, "executedQty")
                 (string, status, "status")
                 (string, time_in_force, "timeInForce")
                 (string, type, "type")
                 (string, side, "side")
                 (string, stop_price, "stopPrice")
                 (string, iceberg_qty, "icebergQty")
                 (long, time, "time"))
  }
}
