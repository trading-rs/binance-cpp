#pragma once

#ifndef FORMAT_HEADER
#define FORMAT_HEADER
#include <fmt/format.h>
#include <fmt/format.cc>
#endif
using namespace fmt;

#include <json.hpp>
using json = nlohmann::json;

#include <vector>
#include <string>
using namespace std;

namespace binance {
  namespace models {
    struct Withdraw {
      double amount;
      string address;
      string asset;
      long apply_time;
      long success_time;
      string tx_id;
      int status;
    };

    void from_json(const json& j, Withdraw& o) {
      o.amount = j.at("amount").get<double>();
      o.address = j.at("address").get<string>();
      o.asset = j.at("asset").get<string>();
      o.apply_time = j.at("applyTime").get<long>();
      try {
        o.success_time = j.at("successTime").get<long>();
      } catch (const std::exception& e) {
        o.success_time = 0;
      }
      try {
        o.tx_id = j.at("txId").get<string>();
      } catch (const std::exception& e) {
        o.tx_id = "";
      }
      o.status = j.at("status").get<int>();
    }

    bool operator ==(const Withdraw& lhs, const Withdraw& rhs) {
      return lhs.amount == rhs.amount &&
        lhs.address == rhs.address &&
        lhs.asset == rhs.asset &&
        lhs.apply_time == rhs.apply_time &&
        lhs.success_time == rhs.success_time &&
        lhs.tx_id == rhs.tx_id;
    }

    struct WithdrawHistory {
      vector<Withdraw> withdraws;
      bool success;
    };

    void from_json(const json& j, WithdrawHistory& o) {
      o.withdraws = j.at("withdrawList").get<vector<Withdraw>>();
      o.success = j.at("success").get<bool>();
    }
  }
}
