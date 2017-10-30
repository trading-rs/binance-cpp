#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    struct Balance {
      string asset;
      string free;
      string locked;
    };

    void from_json(const json& j, Balance& b) {
      b.asset = j.at("asset").get<string>();
      b.free = j.at("free").get<string>();
      b.locked = j.at("locked").get<string>();
    }

    bool operator ==(const Balance& lhs, const Balance& rhs) {
      return lhs.asset == rhs.asset && lhs.free == rhs.free && lhs.locked == rhs.locked;
    }

    struct Account {
      int maker_commission;
      int taker_commission;
      int buyer_commission;
      int seller_commission;
      bool can_trade;
      bool can_withdraw;
      bool can_deposit;
      vector<Balance> balances;
    };

    void from_json(const json& j, Account& a) {
      a.maker_commission = j.at("makerCommission").get<int>();
      a.taker_commission = j.at("takerCommission").get<int>();
      a.buyer_commission = j.at("buyerCommission").get<int>();
      a.seller_commission = j.at("sellerCommission").get<int>();
      a.can_trade = j.at("canTrade").get<bool>();
      a.can_withdraw = j.at("canWithdraw").get<bool>();
      a.can_deposit = j.at("canDeposit").get<bool>();
      a.balances = j.at("balances").get<vector<Balance>>();
    }
  }
}


