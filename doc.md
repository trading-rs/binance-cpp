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
function<Maybe<OrderBookEntry>(OrderBook)> get_first_bid = [](const auto &ob) {
  if (ob.bids.size() == 0) {
    return Nothing<OrderBookEntry>;
  } else {
    return Maybe<OrderBookEntry>(ob.bids[0]);
  }
};
(endpoint->orderBook("LTCBTC", 5) >>= get_first_bid) >>= print_result<OrderBookEntry>;
```
<details><summary>View Output</summary><pre>0.00914100 - 2.47000000</pre></details>

#### Compressed/Aggregate trades list of a symbol
```C++
function<Maybe<AggTrade>(vector<AggTrade>)> get_first_agg_trade = [](const auto &ats) {
  if (ats.size() == 0) {
    return Nothing<AggTrade>;
  } else {
    return Maybe<AggTrade>(ats[0]);
  }
};
(endpoint->agg_trades("LTCBTC") >>= get_first_agg_trade) >>= print_result<AggTrade>;
```
<details><summary>View Output</summary><pre>aggregateTradeId = 992421, price = 0.00914900, quantity = 0.33000000, firstTradeId = 1014449, lastTradeId = 1014449, timestamp = 1508775223876, isBuyerMaker = false, isBestPriceMatch = true</pre></details>
