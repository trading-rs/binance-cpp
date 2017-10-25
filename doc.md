## Create a new endpoint client

```C++
#include <binance/binance.hpp>
using namespace binance::endpoint;
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

#### Latest price of a symbol
```C++
function<string(TickerStatistics)> get_last_price = [](const auto &ts) {
  return ts.last_price;
};
(endpoint->ticker_24hr("LTCBTC") ^ get_last_price) >>= print_result<string>;
```
<details><summary>View Output</summary><pre>0.01004900</pre></details>

#### Getting all latests prices
```C++
endpoint->all_prices() >>= print_results<TickerPrice>;
```
<details>
<summary>View Output</summary>
```
symbol = ETHBTC, price = 0.05255200
symbol = LTCBTC, price = 0.00987900
symbol = BNBBTC, price = 0.00021863
symbol = NEOBTC, price = 0.00530800
symbol = 123456, price = 0.00030000
symbol = QTUMETH, price = 0.03560000
symbol = EOSETH, price = 0.00174300
symbol = SNTETH, price = 0.00008753
symbol = BNTETH, price = 0.00670000
symbol = BCCBTC, price = 0.05850000
symbol = GASBTC, price = 0.00365500
symbol = BNBETH, price = 0.00410000
symbol = BTMETH, price = 0.00018900
symbol = HCCBTC, price = 0.00000180
symbol = BTCUSDT, price = 5591.20000000
symbol = ETHUSDT, price = 297.01000000
symbol = HSRBTC, price = 0.00289000
symbol = OAXETH, price = 0.00132270
symbol = DNTETH, price = 0.00022664
symbol = MCOETH, price = 0.02833300
symbol = ICNETH, price = 0.00426600
symbol = ELCBTC, price = 0.00000053
symbol = MCOBTC, price = 0.00149000
symbol = WTCBTC, price = 0.00135000
symbol = WTCETH, price = 0.02540800
symbol = LLTBTC, price = 0.00001669
symbol = LRCBTC, price = 0.00001100
symbol = LRCETH, price = 0.00016311
symbol = QTUMBTC, price = 0.00187200
symbol = YOYOBTC, price = 0.00000481
symbol = OMGBTC, price = 0.00138200
symbol = OMGETH, price = 0.02614000
symbol = ZRXBTC, price = 0.00003556
symbol = ZRXETH, price = 0.00066020
symbol = STRATBTC, price = 0.00071100
symbol = STRATETH, price = 0.01379300
symbol = SNGLSBTC, price = 0.00002441
symbol = SNGLSETH, price = 0.00045860
symbol = BQXBTC, price = 0.00014650
symbol = BQXETH, price = 0.00274010
symbol = KNCBTC, price = 0.00018799
symbol = KNCETH, price = 0.00357220
symbol = FUNBTC, price = 0.00000339
symbol = FUNETH, price = 0.00006312
symbol = SNMBTC, price = 0.00001882
symbol = SNMETH, price = 0.00036520
symbol = NEOETH, price = 0.10300000
symbol = IOTABTC, price = 0.00008289
symbol = IOTAETH, price = 0.00156000
symbol = LINKBTC, price = 0.00004400
symbol = LINKETH, price = 0.00083899
symbol = XVGBTC, price = 0.00000100
symbol = XVGETH, price = 0.00001873
symbol = CTRBTC, price = 0.00011990
symbol = CTRETH, price = 0.00219000
symbol = SALTBTC, price = 0.00052600
symbol = SALTETH, price = 0.01011000
symbol = MDABTC, price = 0.00023000
symbol = MDAETH, price = 0.00436500
symbol = MTLBTC, price = 0.00143900
symbol = MTLETH, price = 0.02635200
symbol = SUBBTC, price = 0.00002661
symbol = SUBETH, price = 0.00050499
symbol = EOSBTC, price = 0.00009239
symbol = SNTBTC, price = 0.00000461
symbol = ETC, price = 0.00000000
symbol = ETCETH, price = 0.03443100
symbol = ETCBTC, price = 0.00187000
symbol = MTHBTC, price = 0.00001340
symbol = MTHETH, price = 0.00025110
symbol = ENGBTC, price = 0.00008420
symbol = ENGETH, price = 0.00157020
symbol = DNTBTC, price = 0.00001191
symbol = ZECBTC, price = 0.00000000
symbol = ZECETH, price = 0.00000000
symbol = BNTBTC, price = 0.00036099
symbol = ASTBTC, price = 0.00003900
symbol = ASTETH, price = 0.00074000
symbol = DASHBTC, price = 0.05167400
symbol = DASHETH, price = 1.05771000
symbol = OAXBTC, price = 0.00007200
symbol = ICNBTC, price = 0.00022720
symbol = BTGBTC, price = 0.03305400
symbol = BTGETH, price = 0.69850200
```
</details>
