#include "catch.hpp"

#include <binance/binance.hpp>
using namespace binance::types;

TEST_CASE("Test serialization and deserialization for data types") {
  json j = json::parse("{\"lastUpdateId\":1027024,\"bids\":[[\"4.00000000\",\"431.00000000\",[]]],\"asks\":[[\"4.00000200\",\"12.00000000\",[]]]}");
  OrderBook ob = j;
  REQUIRE(ob.lastUpdateId == 1027024);
  REQUIRE(ob.bids.size() == 1);
  REQUIRE(ob.bids[0].price == "4.00000000");
  REQUIRE(ob.bids[0].qty == "431.00000000");
  REQUIRE(ob.asks.size() == 1);
  REQUIRE(ob.asks[0].price == "4.00000200");
  REQUIRE(ob.asks[0].qty == "12.00000000");
}
