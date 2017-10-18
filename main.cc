#include "src/api.hpp"
using namespace api;

#include <memory>
#include <utility>
#include <iostream>
using namespace std;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");

auto pre_check() {
  if (!(api_key && api_secret))
    throw std::runtime_error("Please setup binance APIKEY and APISECRET!");
}

int main(int argc, char** argv) {
  pre_check();
  auto api = make_shared<Api>(api_key, api_secret);
}
