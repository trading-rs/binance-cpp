#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../src/endpoint.hpp"
using namespace endpoint;

#include <memory>
using namespace std;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");

auto pre_check() {
  return api_key && api_secret;
}

TEST_CASE("Binance API") {
  REQUIRE(pre_check());
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  REQUIRE(endpoint->ping() != nullptr);
  REQUIRE(endpoint->time() != nullptr);
}
