#pragma once

#include <derivejson/derivejson.hpp>

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
    DEFINE_MODEL(Deposit,
                 (long, insert_time, "insertTime")
                 (double, amount, "amount")
                 (string, asset, "asset")
                 (int, status, "status"))

    DEFINE_MODEL(DepositHistory,
                 (vector<Deposit>, deposits, "depositList")
                 (bool, success, "success"))
  }
}
