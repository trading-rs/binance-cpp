#include "src/endpoint.hpp"
using namespace endpoint;

#include "src/websocket_client.hpp"
using namespace websocket_client;

#include <memory>
#include <utility>
#include <iostream>
using namespace std;

const char* api_key = getenv("BINANCE_API_KEY");
const char* api_secret = getenv("BINANCE_API_SECRET");

auto pre_check() {
  if (!(api_key && api_secret))
    throw runtime_error("Please setup binance APIKEY and APISECRET!");
}

auto print_result(const json &result) -> void {
  if (result != nullptr)
    cout << result.dump(2) << endl;
}

int main(int argc, char** argv) {
  pre_check();
  auto endpoint = make_shared<Endpoint>(api_key, api_secret);
  print_result(endpoint->buy_limit("ETHBTC", "1", "0.069"));
  print_result(endpoint->buy_market("ETHBTC", "1"));
  print_result(endpoint->order_status("ETHBTC", "1"));
  print_result(endpoint->cancle_order("ETHBTC", "1"));

  auto jr = endpoint->start_user_data_stream();
  if (jr != nullptr) {
    auto listen_key = jr["listenKey"];
    endpoint->user_data_websockets(listen_key, [](json data) {
        cout << ">>>>>>user data>>>>>>" << endl;
        cout << data.dump(2) << endl;
        cout << "<<<<<<user data<<<<<<" << endl;
      });
  }

  endpoint->depth_websocket("ethbtc",  [](json data) {
      cout << ">>>>>>depth>>>>>>" << endl;
      cout << data.dump(2) << endl;
      cout << "<<<<<<depth<<<<<<" << endl;
    });
  endpoint->kline_websocket("ethbtc", "1m", [](json data) {
      cout << ">>>>>>kline>>>>>>" << endl;
      cout << data.dump(2) << endl;
      cout << "<<<<<<kline<<<<<<" << endl;
    });
  endpoint->trades_websocket("ethbtc", [](json data) {
      cout << ">>>>>>trades>>>>>>" << endl;
      cout << data.dump(2) << endl;
      cout << "<<<<<<trades<<<<<<" << endl;
    });
}
