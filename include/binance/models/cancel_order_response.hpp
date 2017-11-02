#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(CancelOrderResponse,
                 (string, symbol, "symbol")
                 (long, order_id, "orderId")
                 (string, client_order_id, "clientOrderId")
                 (string, orig_client_order_id, "origClientOrderId"))
  }
}
