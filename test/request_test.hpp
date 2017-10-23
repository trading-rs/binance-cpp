#include "catch.hpp"

#include <binance/binance.hpp>
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

  REQUIRE(endpoint->ping().isJust());
  REQUIRE(endpoint->time().isJust());
}

TEST_CASE("Test Binance market data endpoints") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->order_book("LTCBTC").isJust());
  REQUIRE(endpoint->order_book("LTCBTC", 5).isJust());
  REQUIRE(endpoint->order_book("LTCBTC", Map({{ "limit", "5" }})).isJust());
  REQUIRE(endpoint->agg_trades("LTCBTC").isJust());
  REQUIRE(endpoint->agg_trades("LTCBTC", Map({{ "limit", "5" }})).isJust());
  REQUIRE(endpoint->klines("LTCBTC","5m").isJust());
  REQUIRE(endpoint->klines("LTCBTC", "5m", Map({{ "limit", "5" }})).isJust());
  REQUIRE(endpoint->ticker_24hr("LTCBTC").isJust());
  REQUIRE(endpoint->ticker_all_prices().isJust());
  REQUIRE(endpoint->ticker_all_bool_tickers().isJust());
}

TEST_CASE("Test Binance account endpoints") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->open_orders("ETHBTC").isJust());
  REQUIRE(endpoint->all_orders("ETHBTC").isJust());
  REQUIRE(endpoint->my_account().isJust());
  REQUIRE(endpoint->my_trades("ETHBTC").isJust());

  auto jr = endpoint->start_user_data_stream();
  REQUIRE(jr.isJust());
  REQUIRE(endpoint->keepalive_user_data_stream(jr.fromJust()["listenKey"]).isJust());
  REQUIRE(endpoint->close_user_data_stream(jr.fromJust()["listenKey"]).isJust());
}
