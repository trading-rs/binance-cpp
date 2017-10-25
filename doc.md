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
<pre>
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
</pre>
</details>

#### Get best price/qty on the order book for all symbols
```C++
endpoint->all_book_tickers() >>= print_results<BookTicker>;
```
<details>
<summary>View Output</summary>
<pre>
symbol = ETHBTC, bidPrice = 0.05321600, bidQty = 0.19600000, askPrice = 0.05355400, askQty = 15.00000000
symbol = LTCBTC, bidPrice = 0.00985200, bidQty = 10.00000000, askPrice = 0.00991800, askQty = 19.36000000
symbol = BNBBTC, bidPrice = 0.00021955, bidQty = 770.00000000, askPrice = 0.00022095, askQty = 20.00000000
symbol = NEOBTC, bidPrice = 0.00529200, bidQty = 17.02000000, askPrice = 0.00530000, askQty = 595.72000000
symbol = 123456, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = QTUMETH, bidPrice = 0.03465600, bidQty = 12.51000000, askPrice = 0.03513100, askQty = 3.71000000
symbol = EOSETH, bidPrice = 0.00171400, bidQty = 117.00000000, askPrice = 0.00173600, askQty = 50.00000000
symbol = SNTETH, bidPrice = 0.00008806, bidQty = 2271.00000000, askPrice = 0.00008900, askQty = 2115.00000000
symbol = BNTETH, bidPrice = 0.00657200, bidQty = 1181.58000000, askPrice = 0.00671600, askQty = 145.92000000
symbol = BCCBTC, bidPrice = 0.05867000, bidQty = 0.70500000, askPrice = 0.05899800, askQty = 11.27400000
symbol = GASBTC, bidPrice = 0.00358800, bidQty = 41.74000000, askPrice = 0.00361600, askQty = 18.64000000
symbol = BNBETH, bidPrice = 0.00410000, bidQty = 65.00000000, askPrice = 0.00414138, askQty = 6.00000000
symbol = BTMETH, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = HCCBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = BTCUSDT, bidPrice = 5415.55000000, bidQty = 0.09870000, askPrice = 5434.90000000, askQty = 0.20000000
symbol = ETHUSDT, bidPrice = 290.01000000, bidQty = 0.50000000, askPrice = 292.18000000, askQty = 1.59080000
symbol = HSRBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = OAXETH, bidPrice = 0.00133400, bidQty = 2611.00000000, askPrice = 0.00137990, askQty = 3372.00000000
symbol = DNTETH, bidPrice = 0.00021594, bidQty = 6721.00000000, askPrice = 0.00022499, askQty = 18965.00000000
symbol = MCOETH, bidPrice = 0.02708500, bidQty = 77.20000000, askPrice = 0.02788700, askQty = 231.24000000
symbol = ICNETH, bidPrice = 0.00422400, bidQty = 200.00000000, askPrice = 0.00430890, askQty = 52.00000000
symbol = ELCBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = MCOBTC, bidPrice = 0.00145200, bidQty = 4.00000000, askPrice = 0.00147000, askQty = 1.00000000
symbol = WTCBTC, bidPrice = 0.00134503, bidQty = 106.00000000, askPrice = 0.00135100, askQty = 700.00000000
symbol = WTCETH, bidPrice = 0.02530000, bidQty = 13.50000000, askPrice = 0.02550000, askQty = 26.16000000
symbol = LLTBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = LRCBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = LRCETH, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = QTUMBTC, bidPrice = 0.00187200, bidQty = 11.29000000, askPrice = 0.00188500, askQty = 40.00000000
symbol = YOYOBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = OMGBTC, bidPrice = 0.00141300, bidQty = 91.53000000, askPrice = 0.00142300, askQty = 171.55000000
symbol = OMGETH, bidPrice = 0.02649500, bidQty = 134.50000000, askPrice = 0.02682700, askQty = 17.94000000
symbol = ZRXBTC, bidPrice = 0.00003528, bidQty = 191.00000000, askPrice = 0.00003594, askQty = 2254.00000000
symbol = ZRXETH, bidPrice = 0.00065451, bidQty = 190.00000000, askPrice = 0.00067948, askQty = 3698.00000000
symbol = STRATBTC, bidPrice = 0.00071600, bidQty = 103.95000000, askPrice = 0.00072000, askQty = 130.10000000
symbol = STRATETH, bidPrice = 0.01326100, bidQty = 312.44000000, askPrice = 0.01374100, askQty = 0.99000000
symbol = SNGLSBTC, bidPrice = 0.00002414, bidQty = 872.00000000, askPrice = 0.00002449, askQty = 345.00000000
symbol = SNGLSETH, bidPrice = 0.00044853, bidQty = 220.00000000, askPrice = 0.00045586, askQty = 92.00000000
symbol = BQXBTC, bidPrice = 0.00014421, bidQty = 9.00000000, askPrice = 0.00014897, askQty = 584.00000000
symbol = BQXETH, bidPrice = 0.00268890, bidQty = 30.00000000, askPrice = 0.00288620, askQty = 2322.00000000
symbol = KNCBTC, bidPrice = 0.00018596, bidQty = 59.00000000, askPrice = 0.00018786, askQty = 207.00000000
symbol = KNCETH, bidPrice = 0.00350000, bidQty = 185.00000000, askPrice = 0.00351880, askQty = 7839.00000000
symbol = FUNBTC, bidPrice = 0.00000331, bidQty = 42600.00000000, askPrice = 0.00000338, askQty = 19256.00000000
symbol = FUNETH, bidPrice = 0.00006119, bidQty = 2000.00000000, askPrice = 0.00006480, askQty = 32149.00000000
symbol = SNMBTC, bidPrice = 0.00001817, bidQty = 3894.00000000, askPrice = 0.00001872, askQty = 595.00000000
symbol = SNMETH, bidPrice = 0.00033662, bidQty = 1492.00000000, askPrice = 0.00035866, askQty = 14807.00000000
symbol = NEOETH, bidPrice = 0.09789600, bidQty = 42.32000000, askPrice = 0.09984900, askQty = 3.00000000
symbol = IOTABTC, bidPrice = 0.00008504, bidQty = 1160.00000000, askPrice = 0.00008511, askQty = 331.00000000
symbol = IOTAETH, bidPrice = 0.00156006, bidQty = 2655.00000000, askPrice = 0.00160000, askQty = 2053.00000000
symbol = LINKBTC, bidPrice = 0.00004393, bidQty = 3585.00000000, askPrice = 0.00004440, askQty = 24944.00000000
symbol = LINKETH, bidPrice = 0.00082251, bidQty = 425.00000000, askPrice = 0.00083550, askQty = 606.00000000
symbol = XVGBTC, bidPrice = 0.00000096, bidQty = 95893.00000000, askPrice = 0.00000098, askQty = 178991.00000000
symbol = XVGETH, bidPrice = 0.00001746, bidQty = 237301.00000000, askPrice = 0.00001974, askQty = 93319.00000000
symbol = CTRBTC, bidPrice = 0.00010601, bidQty = 104.00000000, askPrice = 0.00010726, askQty = 1258.00000000
symbol = CTRETH, bidPrice = 0.00200090, bidQty = 174.00000000, askPrice = 0.00204470, askQty = 712.00000000
symbol = SALTBTC, bidPrice = 0.00052700, bidQty = 1.83000000, askPrice = 0.00053000, askQty = 62.09000000
symbol = SALTETH, bidPrice = 0.00955500, bidQty = 888.91000000, askPrice = 0.00996600, askQty = 135.93000000
symbol = MDABTC, bidPrice = 0.00022999, bidQty = 58.00000000, askPrice = 0.00023200, askQty = 200.00000000
symbol = MDAETH, bidPrice = 0.00421470, bidQty = 57.00000000, askPrice = 0.00438310, askQty = 1089.00000000
symbol = MTLBTC, bidPrice = 0.00145500, bidQty = 888.00000000, askPrice = 0.00148800, askQty = 7.00000000
symbol = MTLETH, bidPrice = 0.02700000, bidQty = 25.01000000, askPrice = 0.02931700, askQty = 0.99000000
symbol = SUBBTC, bidPrice = 0.00002593, bidQty = 6763.00000000, askPrice = 0.00002600, askQty = 118.00000000
symbol = SUBETH, bidPrice = 0.00048000, bidQty = 2710.00000000, askPrice = 0.00048987, askQty = 9223.00000000
symbol = EOSBTC, bidPrice = 0.00009144, bidQty = 278.00000000, askPrice = 0.00009249, askQty = 799.00000000
symbol = SNTBTC, bidPrice = 0.00000470, bidQty = 5600.00000000, askPrice = 0.00000477, askQty = 13105.00000000
symbol = ETC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = ETCETH, bidPrice = 0.03421900, bidQty = 20.99000000, askPrice = 0.03573100, askQty = 753.98000000
symbol = ETCBTC, bidPrice = 0.00184400, bidQty = 21.00000000, askPrice = 0.00186700, askQty = 9.99000000
symbol = MTHBTC, bidPrice = 0.00001335, bidQty = 3100.00000000, askPrice = 0.00001370, askQty = 651.00000000
symbol = MTHETH, bidPrice = 0.00025205, bidQty = 793.00000000, askPrice = 0.00026299, askQty = 50.00000000
symbol = ENGBTC, bidPrice = 0.00008029, bidQty = 206.00000000, askPrice = 0.00008290, askQty = 13916.00000000
symbol = ENGETH, bidPrice = 0.00152780, bidQty = 207.00000000, askPrice = 0.00152990, askQty = 2001.00000000
symbol = DNTBTC, bidPrice = 0.00001171, bidQty = 4764.00000000, askPrice = 0.00001181, askQty = 14100.00000000
symbol = ZECBTC, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = ZECETH, bidPrice = 0.00000000, bidQty = 0.00000000, askPrice = 0.00000000, askQty = 0.00000000
symbol = BNTBTC, bidPrice = 0.00035097, bidQty = 19.00000000, askPrice = 0.00035597, askQty = 267.00000000
symbol = ASTBTC, bidPrice = 0.00003990, bidQty = 3911.00000000, askPrice = 0.00004149, askQty = 1870.00000000
symbol = ASTETH, bidPrice = 0.00076550, bidQty = 1123.00000000, askPrice = 0.00077460, askQty = 260.00000000
symbol = DASHBTC, bidPrice = 0.05190000, bidQty = 0.10000000, askPrice = 0.05209500, askQty = 3.19400000
symbol = DASHETH, bidPrice = 0.95680000, bidQty = 117.41200000, askPrice = 1.03651000, askQty = 0.55100000
symbol = OAXBTC, bidPrice = 0.00006991, bidQty = 128.00000000, askPrice = 0.00007299, askQty = 5114.00000000
symbol = ICNBTC, bidPrice = 0.00022701, bidQty = 48.00000000, askPrice = 0.00022950, askQty = 200.00000000
symbol = BTGBTC, bidPrice = 0.03300000, bidQty = 0.30000000, askPrice = 0.03379100, askQty = 7.41000000
symbol = BTGETH, bidPrice = 0.61000000, bidQty = 0.40000000, askPrice = 0.66447300, askQty = 0.60000000
</pre>
</details>

### Account Data endpoints

#### Placing a MARKET order
```C++
endpoint->buy_market("ETHBTC", 1.0) >>= print_result<NewOrderResponse>;
```
<details>
<summary>View Output</summary>
<pre>
symbol = ETHBTC, orderId = 1321312, clientOrderId = XXXXXfc2XXzTXXGs66ZcXX, transactTime = 1508382322725
</pre>
</details>

#### Placing a LIMIT order
```C++
endpoint->buy_limit("ETHBTC", 1.0, 0.069) >>= print_result<NewOrderResponse>;
```
<details>
<summary>View Output</summary>
<pre>
symbol = ETHBTC, orderId = 1321312, clientOrderId = XXXXXfc2XXzTXXGs66ZcXX, transactTime = 1508382322725
</pre>
</details>
