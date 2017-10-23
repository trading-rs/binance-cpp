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

  
