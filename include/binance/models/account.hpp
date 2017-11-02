#pragma once

#include <derivejson/derivejson.hpp>

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    DEFINE_MODEL(Balance,
                 (string, asset, "asset")
                 (string, free, "free")
                 (string, locked, "locked"))

    DEFINE_MODEL(Account,
                 (int, maker_commission, "makerCommission")
                 (int, taker_commission, "takerCommission")
                 (int, buyer_commission, "buyerCommission")
                 (int, seller_commission, "sellerCommission")
                 (bool, can_trade, "canTrade")
                 (bool, can_withdraw, "canWithdraw")
                 (bool, can_deposit, "canDeposit")
                 (vector<Balance>, balances, "balances"))
  }
}
