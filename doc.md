## Create a new endpoint client

```C++
auto endpoint = make_shared<Endpoint>(api_key, api_secret);
```

## General endpoints

#### Checking Server Responsiveness
```C++
endpoint->ping() >>= print_result<json>;
```
<details><summary>View Output</summary><pre>{}</pre></details>

#### Getting Server Time
```C++
endpoint->time() >>= print_result<long>;
```
<details><summary>View Output</summary><pre>1508687363648</pre></details>

## Market Data endpoints

#### Order book of a symbol
```C++
function<Maybe<vector<OrderBookEntry>>(OrderBook)> get_bids = [](const auto &ob) {
  return Maybe<vector<OrderBookEntry>>(ob.bids);
};
((endpoint->order_book("LTCBTC", 5) >>= get_bids) >>= head_m<OrderBookEntry>) >>= print_result<OrderBookEntry>;
```
<details><summary>View Output</summary><pre>0.00914100 - 2.47000000</pre></details>

#### Compressed/Aggregate trades list of a symbol
```C++
(endpoint->agg_trades("LTCBTC") >>= head_m<AggTrade>) >>= print_result<AggTrade>;
```
<details><summary>View Output</summary><pre>aggregate_trade_id = 992421, price = 0.00914900, quantity = 0.33000000, first_trade_id = 1014449, last_trade_id = 1014449, timestamp = 1508775223876, is_buyer_maker = false, is_best_price_match = true</pre></details>

#### Candlestick bars for a symbol
```C++
(endpoint->candlestick_bars("LTCBTC", "5m") >>= head_m<CandleStick>) >>= print_result<CandleStick>;
```
<details><summary>View Output</summary><pre>open_time = 1508712000000, open = 0.00948600, high = 0.00948600, low = 0.00947000, close = 0.00947000, volumn = 146.69000000, close_time = 1508712299999, quote_asset_volumn = 1.39052521, number_of_trades = 28, taker_buy_base_asset_volume = 18.46000000, taker_buy_quote_asset_volume = 0.17494542</pre></details>
