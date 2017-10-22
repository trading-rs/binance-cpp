## General endpoints

#### Getting Server Time
```c++
make_shared<Endpoint>(api_key, api_secret)->time() >>= print_result<long>;
```
<details><summary>View Output</summary><pre>1508687363648</pre></details>
