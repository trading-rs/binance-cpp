#include <binance/binance.hpp>
using namespace binance::endpoint;
using namespace binance::websocket_client;
using namespace binance::extra;

#include <memory>
#include <utility>
#include <string>
#include <iostream>
using namespace std;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");

auto pre_check() {
  if (!(api_key && api_secret))
    throw runtime_error("Please setup binance APIKEY and APISECRET!");
}

int main(int argc, char** argv) {
  pre_check();
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  endpoint->all_book_tickers() >>= print_results<BookTicker>;

  endpoint->all_prices() >>= print_results<TickerPrice>;

  function<string(TickerStatistics)> get_last_price = [](const auto &ts) {
    return ts.last_price;
  };
  (endpoint->ticker_24hr("LTCBTC") ^ get_last_price) >>= print_result<string>;

  endpoint->ticker_24hr("LTCBTC") >>= print_result<TickerStatistics>;

  (endpoint->candlestick_bars("LTCBTC", "5m") >>= head_m<CandleStick>) >>= print_result<CandleStick>;

  (endpoint->agg_trades("LTCBTC") >>= head_m<AggTrade>) >>= print_result<AggTrade>;

  function<Maybe<vector<OrderBookEntry>>(OrderBook)> get_bids = [](const auto &ob) {
    return Maybe<vector<OrderBookEntry>>(ob.bids);
  };
  ((endpoint->order_book("LTCBTC", 5) >>= get_bids) >>= head_m<OrderBookEntry>) >>= print_result<OrderBookEntry>;

  endpoint->ping() >>= print_result<json>;
  endpoint->time() >>= print_result<long>;
  endpoint->buy_limit("ETHBTC", 1.0, 0.069) >>= print_result<NewOrderResponse>;
  endpoint->buy_market("ETHBTC", 1.0) >>= print_result<NewOrderResponse>;
  endpoint->order_status("ETHBTC", "1") >>= print_result<json>;
  endpoint->cancle_order("ETHBTC", "1") >>= print_result<json>;

  endpoint->depth_websocket("ethbtc",  [](json data) {
      cout << data.dump(2) << endl;
    });
  endpoint->kline_websocket("ethbtc", "1m", [](json data) {
      cout << data.dump(2) << endl;
    });
  endpoint->trades_websocket("ethbtc", [](json data) {
      cout << data.dump(2) << endl;
    });
  auto jr = endpoint->start_user_data_stream();
  if (jr.isJust()) {
    auto listen_key = jr.fromJust()["listenKey"];
    endpoint->user_data_websockets(listen_key, [](json data) {
        cout << data.dump(2) << endl;
      });
  }
}
