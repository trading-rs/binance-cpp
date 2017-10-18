#include "src/endpoint.hpp"
using namespace endpoint;

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

auto print_result(const json &result) -> void {
  if (result != nullptr)
    cout << result.dump(2) << endl;
}

int main(int argc, char** argv) {
  pre_check();
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);
  print_result(endpoint->ping());
  print_result(endpoint->time());
}
