#include <binance/binance.hpp>
using namespace binance::endpoint;
using namespace binance::websocket::client;
using namespace binance::extra;

#include <spdlog/spdlog.h>
namespace spd = spdlog;

#include <map>
#include <memory>
#include <utility>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

typedef map<double, double, greater<double>> SortedEntries;
typedef map<string, SortedEntries> DepthCache;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");
const string bid_key = "BIDS";
const string ask_key = "ASKS";

shared_ptr<spd::logger> cache_log = spd::stdout_color_mt("DEPTHCACHE_EXAMPLE");

DepthCache depth_cache;
long limit = 10;
long last_update_id;

auto pre_check() {
  if (!(api_key && api_secret))
    throw runtime_error("Please setup binance APIKEY and APISECRET!");
}

auto get_sorted_asks() -> SortedEntries {
  return depth_cache[ask_key];
}

auto get_sorted_bids() -> SortedEntries {
  return depth_cache[bid_key];
}

auto initialize_depth_cache(const string &symbol, shared_ptr<Endpoint> client) -> void {
  Maybe<OrderBook> order_book = client->order_book(symbol, 10);
  if (order_book.isJust()) {
    OrderBook ob = order_book.fromJust();
    last_update_id = ob.last_update_id;
    SortedEntries asks;
    SortedEntries bids;
    std::for_each(ob.asks.cbegin(), ob.asks.cend(), [&](const OrderBookEntry &obe) {
        asks[stod(obe.price)] = stod(obe.qty);
      });
    std::for_each(ob.asks.cbegin(), ob.asks.cend(), [&](const OrderBookEntry &obe) {
        bids[stod(obe.price)] = stod(obe.qty);
      });
    depth_cache[ask_key] = asks;
    depth_cache[bid_key] = bids;
  } else {
    cache_log->error("can not retrive order book");
  }
}

auto update_depth_cache(SortedEntries caches, const vector<OrderBookEntry> deltas) -> void {
  std::for_each(deltas.cbegin(), deltas.cend(), [&](const OrderBookEntry &delta) {
      double price = stod(delta.price);
      double quantity = stod(delta.qty);
      if (quantity == 0.0) {
        caches.erase(price);
      } else {
        caches[price] = quantity;
      }
    });
}

auto print_depth_cache() -> void {
  cout << ">>>>>>DEPTHCACHE>>>>>>" << endl;
  cout << "ASKS:" << endl;
  auto asks = get_sorted_asks();
  std::for_each(asks.cbegin(), asks.cend(), [](const pair<double, double> &pair) {
      cout << format("{0} / {1}", pair.first, pair.second) << endl;
    });
  cout << "BIDS:" << endl;
  auto bids = get_sorted_bids();
  std::for_each(bids.cbegin(), bids.cend(), [](const pair<double, double> &pair) {
      cout << format("{0} / {1}", pair.first, pair.second) << endl;
    });
  cout << format("BEST ASK: {0} / {1}", asks.crbegin()->first, asks.crbegin()->second) << endl;
  cout << format("BEST BID: {0} / {1}", bids.cbegin()->first, bids.cbegin()->second) << endl;
  cout << "<<<<<<DEPTHCACHE<<<<<<" << endl;
}

auto print_depth_volume() -> void {
  auto asks = get_sorted_asks();
  auto bids = get_sorted_bids();
  pair<double, double> ask_pair = accumulate(asks.cbegin(), asks.cend(), make_pair(0.0, 0.0), [](const pair<double, double> &result,                                       const pair<double, double> &pair) {
      return make_pair(result.first + (pair.first * pair.second), result.second + pair.second);
    });
  pair<double, double> bid_pair = accumulate(bids.cbegin(), bids.cend(), make_pair(0.0, 0.0), [](const pair<double, double> &result,                                       const pair<double, double> &pair) {
      return make_pair(result.first + (pair.first * pair.second), result.second + pair.second);
    });
  cout << format("ASK VOLUME: {0} / {1}", ask_pair.first, ask_pair.second) << endl;
  cout << format("BID VOLUME: {0} / {1}", bid_pair.first, bid_pair.second) << endl;
}

auto start_depth_event_streaming(string symbol, shared_ptr<Endpoint> client) -> void {
  transform(symbol.begin(), symbol.end(), symbol.begin(), ::tolower);
  client->depth_websocket(symbol, [&](json data) {
      DepthEvent de = data;
      if (de.update_id > last_update_id) {
        print_result<DepthEvent>(de);
        last_update_id = de.update_id;
        update_depth_cache(get_sorted_asks(), de.asks);
        update_depth_cache(get_sorted_bids(), de.bids);
        print_depth_cache();
        print_depth_volume();
      }
    });
}

int main(int argc, char** argv) {
  pre_check();
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);

  auto symbol = "LTCBTC";
  initialize_depth_cache(symbol, endpoint);
  start_depth_event_streaming(symbol, endpoint);
}
