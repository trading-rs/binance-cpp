#include "api.hpp"
using namespace api;

#include <string>
#include <memory>
using namespace std;

namespace endpoint {
  class Endpoint {
  private:
    shared_ptr<Api> api;

  public:
    Endpoint(string key, string secret);
    auto ping() -> json;
    auto time() -> json;
  };

  Endpoint::Endpoint(string key, string secret) {
    this->api = make_shared<Api>(key, secret);
  }

  auto Endpoint::ping() -> json {
    return this->api->public_get("/api/v1/ping");
  }

  auto Endpoint::time() -> json {
    return this->api->public_get("/api/v1/time");
  }
}
