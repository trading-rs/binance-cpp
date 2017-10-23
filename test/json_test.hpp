#include "catch.hpp"

#include <binance/binance.hpp>
using namespace binance::types;

TEST_CASE("Test serialization and deserialization for OrderBook") {
  json j = json::parse("{\"lastUpdateId\":1027024,\"bids\":[[\"4.00000000\",\"431.00000000\",[]]],\"asks\":[[\"4.00000200\",\"12.00000000\",[]]]}");
  OrderBook ob = j;
  REQUIRE(ob.last_update_id == 1027024);
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
  REQUIRE(ats[0].aggregate_trade_id == 26129);
  REQUIRE(ats[0].price == "0.01633102");
  REQUIRE(ats[0].quantity == "4.70443515");
  REQUIRE(ats[0].first_trade_id == 27781);
  REQUIRE(ats[0].last_trade_id == 27781);
  REQUIRE(ats[0].timestamp == 1498793709153);
  REQUIRE(ats[0].is_buyer_maker == true);
  REQUIRE(ats[0].is_best_price_match == true);
}

TEST_CASE("Test serialization and deserialization for CandleStick") {
  json j = json::parse("[[1499040000000,\"0.01634790\",\"0.80000000\",\"0.01575800\",\"0.01577100\",\"148976.11427815\",1499644799999,\"2434.19055334\",308,\"1756.87402397\",\"28.46694368\",\"17928899.62484339\"]]");
  vector<CandleStick> css = j;
  REQUIRE(css.size() == 1);
  auto cs = css[0];
  REQUIRE(cs.open_time == 1499040000000);
  REQUIRE(cs.open == "0.01634790");
  REQUIRE(cs.high == "0.80000000");
  REQUIRE(cs.low == "0.01575800");
  REQUIRE(cs.close == "0.01577100");
  REQUIRE(cs.volumn == "148976.11427815");
  REQUIRE(cs.close_time == 1499644799999);
  REQUIRE(cs.quote_asset_volume == "2434.19055334");
  REQUIRE(cs.number_of_trades == 308);
  REQUIRE(cs.taker_buy_base_asset_volume == "1756.87402397");
  REQUIRE(cs.taker_buy_quote_asset_volume == "28.46694368");
}
