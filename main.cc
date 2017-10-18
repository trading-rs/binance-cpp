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
  print_result(endpoint->depth("LTCBTC"));
  print_result(endpoint->depth("LTCBTC", Map({{ "limit", "5" }})));
  print_result(endpoint->agg_trades("LTCBTC"));
  print_result(endpoint->agg_trades("LTCBTC", Map({{ "limit", "5" }})));
  print_result(endpoint->klines("LTCBTC","5m"));
  print_result(endpoint->klines("LTCBTC", "5m", Map({{ "limit", "5" }})));
  print_result(endpoint->ticker_24hr("LTCBTC"));
  print_result(endpoint->ticker_all_prices());
  print_result(endpoint->ticker_all_bool_tickers());
}
