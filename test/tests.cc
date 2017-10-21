#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <binance/endpoint.hpp>
using namespace binance::endpoint;

#include <memory>
using namespace std;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");

auto pre_check() {
  return api_key && api_secret;
}

TEST_CASE("Test Binance general endpoints") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->ping() != nullptr);
  REQUIRE(endpoint->time() != nullptr);
}

TEST_CASE("Test Binance market data endpoints") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->depth("LTCBTC") != nullptr);
  REQUIRE(endpoint->depth("LTCBTC", Map({{ "limit", "5" }})) != nullptr);
  REQUIRE(endpoint->agg_trades("LTCBTC") != nullptr);
  REQUIRE(endpoint->agg_trades("LTCBTC", Map({{ "limit", "5" }})) != nullptr);
  REQUIRE(endpoint->klines("LTCBTC","5m") != nullptr);
  REQUIRE(endpoint->klines("LTCBTC", "5m", Map({{ "limit", "5" }})) != nullptr);
  REQUIRE(endpoint->ticker_24hr("LTCBTC") != nullptr);
  REQUIRE(endpoint->ticker_all_prices() != nullptr);
  REQUIRE(endpoint->ticker_all_bool_tickers() != nullptr);
}

TEST_CASE("Test Binance account endpoints") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->open_orders("ETHBTC") != nullptr);
  REQUIRE(endpoint->all_orders("ETHBTC") != nullptr);
  REQUIRE(endpoint->my_account() != nullptr);
  REQUIRE(endpoint->my_trades("ETHBTC") != nullptr);

  auto jr = endpoint->start_user_data_stream();
  REQUIRE(jr != nullptr);
  REQUIRE(endpoint->keepalive_user_data_stream(jr["listenKey"]) != nullptr);
  REQUIRE(endpoint->close_user_data_stream(jr["listenKey"]) != nullptr);
}
