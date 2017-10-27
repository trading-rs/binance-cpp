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
  namespace types {
    struct Deposit {
      long insert_time;
      double amount;
      string asset;
      int status;
    };

    void from_json(const json& j, Deposit& o) {
      o.insert_time = j.at("insertTime").get<long>();
      o.amount = j.at("amount").get<double>();
      o.asset = j.at("asset").get<string>();
      o.status = j.at("status").get<int>();
    }

    bool operator ==(const Deposit& lhs, const Deposit& rhs) {
      return lhs.insert_time == rhs.insert_time &&
        lhs.amount == rhs.amount &&
        lhs.asset == rhs.asset &&
        lhs.status == rhs.status;
    }

    struct DepositHistory {
      vector<Deposit> deposits;
      bool success;
    };

    void from_json(const json& j, DepositHistory& o) {
      o.deposits = j.at("depositList").get<vector<Deposit>>();
      o.success = j.at("success").get<bool>();
    }
  }
}
