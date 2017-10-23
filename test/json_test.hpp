#include "catch.hpp"

#include <binance/binance.hpp>
using namespace binance::types;

TEST_CASE("Test serialization and deserialization for OrderBook") {
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

TEST_CASE("Test serialization and deserialization for AggTrade") {
  json j = json::parse("[{\"a\":26129,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":27781,\"T\":1498793709153,\"m\":true,\"M\":true}]");
  vector<AggTrade> ats = j;
  REQUIRE(ats.size() == 1);
  REQUIRE(ats[0].aggregateTradeId == 26129);
  REQUIRE(ats[0].price == "0.01633102");
  REQUIRE(ats[0].quantity == "4.70443515");
  REQUIRE(ats[0].firstTradeId == 27781);
  REQUIRE(ats[0].lastTradeId == 27781);
  REQUIRE(ats[0].timestamp == 1498793709153);
  REQUIRE(ats[0].isBuyerMaker == true);
  REQUIRE(ats[0].isBestPriceMatch == true);
}
