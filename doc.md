## General endpoints

#### Checking Server Responsiveness
```C++
make_shared<Endpoint>(api_key, api_secret)->ping() >>= print_result<json>;
```
<details><summary>View Output</summary><pre>{}</pre></details>

#### Getting Server Time
```C++
make_shared<Endpoint>(api_key, api_secret)->time() >>= print_result<long>;
```
<details><summary>View Output</summary><pre>1508687363648</pre></details>
