#include "catch.hpp"

#include <binance/binance.hpp>
using namespace binance::types;

TEST_CASE("Test deserialization for OrderBook") {
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

TEST_CASE("Test deserialization for AggTrade") {
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

TEST_CASE("Test deserialization for CandleStick") {
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

TEST_CASE("Test deserialization for TickerStatistics") {
  json j = json::parse("{\"priceChange\":\"-94.99999800\",\"priceChangePercent\":\"-95.960\",\"weightedAvgPrice\":\"0.29628482\",\"prevClosePrice\":\"0.10002000\",\"lastPrice\":\"4.00000200\",\"bidPrice\":\"4.00000000\",\"askPrice\":\"4.00000200\",\"openPrice\":\"99.00000000\",\"highPrice\":\"100.00000000\",\"lowPrice\":\"0.10000000\",\"volume\":\"8913.30000000\",\"openTime\":1499783499040,\"closeTime\":1499869899040,\"firstId\":28385,\"lastId\":28460,\"count\":76}");
  TickerStatistics ts = j;
  REQUIRE(ts.price_change == "-94.99999800");
  REQUIRE(ts.price_change_percent == "-95.960");
  REQUIRE(ts.weighted_avg_price == "0.29628482");
  REQUIRE(ts.prev_close_price == "0.10002000");
  REQUIRE(ts.last_price == "4.00000200");
  REQUIRE(ts.bid_price == "4.00000000");
  REQUIRE(ts.ask_price == "4.00000200");
  REQUIRE(ts.open_price == "99.00000000");
  REQUIRE(ts.high_price == "100.00000000");
  REQUIRE(ts.low_price == "0.10000000");
  REQUIRE(ts.volume == "8913.30000000");
  REQUIRE(ts.open_time == 1499783499040);
  REQUIRE(ts.close_time == 1499869899040);
  REQUIRE(ts.first_id == 28385);
  REQUIRE(ts.last_id == 28460);
  REQUIRE(ts.count == 76);
}

TEST_CASE("Test deserialization for TickerPrice") {
  json j = json::parse("[{\"symbol\":\"LTCBTC\",\"price\":\"4.00000200\"},{\"symbol\":\"ETHBTC\",\"price\":\"0.07946600\"}]");
  vector<TickerPrice> tps = j;
  REQUIRE(tps.size() == 2);
  REQUIRE(tps[0].symbol == "LTCBTC");
  REQUIRE(tps[0].price == "4.00000200");
  REQUIRE(tps[1].symbol == "ETHBTC");
  REQUIRE(tps[1].price == "0.07946600");
}

TEST_CASE("Test deserialization for BookTicker") {
  json j = json::parse("[{\"symbol\":\"LTCBTC\",\"bidPrice\":\"4.00000000\",\"bidQty\":\"431.00000000\",\"askPrice\":\"4.00000200\",\"askQty\":\"9.00000000\"},{\"symbol\":\"ETHBTC\",\"bidPrice\":\"0.07946700\",\"bidQty\":\"9.00000000\",\"askPrice\":\"100000.00000000\",\"askQty\":\"1000.00000000\"}]");
  vector<BookTicker> bts = j;
  REQUIRE(bts.size() == 2);
  REQUIRE(bts[0].symbol == "LTCBTC");
  REQUIRE(bts[0].bid_price == "4.00000000");
  REQUIRE(bts[0].bid_qty == "431.00000000");
  REQUIRE(bts[0].ask_price == "4.00000200");
  REQUIRE(bts[0].ask_qty == "9.00000000");
  REQUIRE(bts[1].symbol == "ETHBTC");
  REQUIRE(bts[1].bid_price == "0.07946700");
  REQUIRE(bts[1].bid_qty == "9.00000000");
  REQUIRE(bts[1].ask_price == "100000.00000000");
  REQUIRE(bts[1].ask_qty == "1000.00000000");
}

TEST_CASE("Test deserialization for NewOrderResponse") {
  json j = json::parse("{\"symbol\":\"LTCBTC\",\"orderId\":1,\"clientOrderId\":\"myOrder1\",\"transactTime\":1499827319559}");
  NewOrderResponse nor = j;
  REQUIRE(nor.symbol == "LTCBTC");
  REQUIRE(nor.order_id == 1);
  REQUIRE(nor.client_order_id == "myOrder1");
  REQUIRE(nor.transact_time == 1499827319559);
}

TEST_CASE("Test deserialization for Order") {
  json j = json::parse("{\"symbol\":\"LTCBTC\",\"orderId\":1,\"clientOrderId\":\"myOrder1\",\"price\":\"0.1\",\"origQty\":\"1.0\",\"executedQty\":\"0.0\",\"status\":\"NEW\",\"timeInForce\":\"GTC\",\"type\":\"LIMIT\",\"side\":\"BUY\",\"stopPrice\":\"0.0\",\"icebergQty\":\"0.0\",\"time\":1499827319559}");
  Order o = j;
  REQUIRE(o.symbol == "LTCBTC");
  REQUIRE(o.order_id == 1);
  REQUIRE(o.client_order_id == "myOrder1");
  REQUIRE(o.price == "0.1");
  REQUIRE(o.orig_qty == "1.0");
  REQUIRE(o.executed_qty == "0.0");
  REQUIRE(o.status == "NEW");
  REQUIRE(o.time_in_force == "GTC");
  REQUIRE(o.type == "LIMIT");
  REQUIRE(o.side == "BUY");
  REQUIRE(o.stop_price == "0.0");
  REQUIRE(o.iceberg_qty == "0.0");
  REQUIRE(o.time == 1499827319559);
}

TEST_CASE("Test deserialization for CancelOrderResponse") {
  json j = json::parse("{\"symbol\":\"LTCBTC\",\"origClientOrderId\":\"myOrder1\",\"orderId\":1,\"clientOrderId\":\"cancelMyOrder1\"}");
  CancelOrderResponse cop = j;
  REQUIRE(cop.symbol == "LTCBTC");
  REQUIRE(cop.order_id == 1);
  REQUIRE(cop.client_order_id == "cancelMyOrder1");
  REQUIRE(cop.orig_client_order_id == "myOrder1");
}

TEST_CASE("Test deserialization for Account") {
  json j = json::parse("{\"makerCommission\":15,\"takerCommission\":15,\"buyerCommission\":0,\"sellerCommission\":0,\"canTrade\":true,\"canWithdraw\":true,\"canDeposit\":true,\"balances\":[{\"asset\":\"BTC\",\"free\":\"4723846.89208129\",\"locked\":\"0.00000000\"},{\"asset\":\"LTC\",\"free\":\"4763368.68006011\",\"locked\":\"0.00000000\"}]}");
  Account a = j;
  vector<Balance> balances_expected = {
    Balance({ "BTC", "4723846.89208129", "0.00000000" }),
    Balance({ "LTC", "4763368.68006011", "0.00000000" })
  };
  REQUIRE(a.maker_commission == 15);
  REQUIRE(a.taker_commission == 15);
  REQUIRE(a.buyer_commission == 0);
  REQUIRE(a.seller_commission == 0);
  REQUIRE(a.can_trade == true);
  REQUIRE(a.can_withdraw == true);
  REQUIRE(a.can_deposit == true);
  REQUIRE(a.balances.size() == 2);
  REQUIRE(a.balances == balances_expected);
}

TEST_CASE("Test deserialization for Trade") {
  json j = json::parse("[{\"id\":28457,\"price\":\"4.00000100\",\"qty\":\"12.00000000\",\"commission\":\"10.10000000\",\"commissionAsset\":\"BNB\",\"time\":1499865549590,\"isBuyer\":true,\"isMaker\":false,\"isBestMatch\":true}]");
  vector<Trade> ts = j;
  REQUIRE(ts.size() == 1);
  REQUIRE(ts[0].id == 28457);
  REQUIRE(ts[0].price == "4.00000100");
  REQUIRE(ts[0].qty == "12.00000000");
  REQUIRE(ts[0].commission == "10.10000000");
  REQUIRE(ts[0].commission_asset == "BNB");
  REQUIRE(ts[0].time == 1499865549590);
  REQUIRE(ts[0].is_buyer == true);
  REQUIRE(ts[0].is_maker == false);
  REQUIRE(ts[0].is_best_match == true);
}

TEST_CASE("Test deserialization for DepthEvent") {
  json j = json::parse("{\"e\":\"depthUpdate\",\"E\":1499404630606,\"s\":\"ETHBTC\",\"u\":7913455,\"b\":[[\"0.10376590\",\"59.15767010\",[]]],\"a\":[[\"0.10376586\",\"159.15767010\",[]],[\"0.10383109\",\"345.86845230\",[]],[\"0.10490700\",\"0.00000000\",[]]]}");
  DepthEvent de = j;
  REQUIRE(de.event_type == "depthUpdate");
  REQUIRE(de.event_time == 1499404630606);
  REQUIRE(de.symbol == "ETHBTC");
  REQUIRE(de.update_id == 7913455);
  vector<OrderBookEntry> bids_expected = {
    OrderBookEntry({ "0.10376590", "59.15767010" })
  };
  vector<OrderBookEntry> asks_expected = {
    OrderBookEntry({ "0.10376586", "159.15767010" }),
    OrderBookEntry({ "0.10383109", "345.86845230" }),
    OrderBookEntry({ "0.10490700", "0.00000000" })
  };
  REQUIRE(de.bids == bids_expected);
  REQUIRE(de.asks == asks_expected);
}

TEST_CASE("Test deserialization for CandleStickEvent") {
  json j = json::parse("{\"e\":\"kline\",\"E\":1499404907056,\"s\":\"ETHBTC\",\"k\":{\"t\":1499404860000,\"T\":1499404919999,\"s\":\"ETHBTC\",\"i\":\"1m\",\"f\":77462,\"L\":77465,\"o\":\"0.10278577\",\"c\":\"0.10278645\",\"h\":\"0.10278712\",\"l\":\"0.10278518\",\"v\":\"17.47929838\",\"n\":4,\"x\":false,\"q\":\"1.79662878\",\"V\":\"2.34879839\",\"Q\":\"0.24142166\",\"B\":\"13279784.01349473\"}}");
  CandleStickEvent cse = j;
  REQUIRE(cse.event_type == "kline");
  REQUIRE(cse.event_time == 1499404907056);
  REQUIRE(cse.symbol == "ETHBTC");
  REQUIRE(cse.open_time == 1499404860000);
  REQUIRE(cse.close_time == 1499404919999);
  REQUIRE(cse.interval_id == "1m");
  REQUIRE(cse.first_trade_id == 77462);
  REQUIRE(cse.last_trade_id == 77465);
  REQUIRE(cse.open == "0.10278577");
  REQUIRE(cse.close == "0.10278645");
  REQUIRE(cse.high == "0.10278712");
  REQUIRE(cse.low == "0.10278518");
  REQUIRE(cse.volume == "17.47929838");
  REQUIRE(cse.number_of_trades == 4);
  REQUIRE(cse.is_bar_final == false);
  REQUIRE(cse.quote_asset_volume == "1.79662878");
  REQUIRE(cse.active_buy_volume == "2.34879839");
  REQUIRE(cse.quote_active_buy_volume == "0.24142166");
}
