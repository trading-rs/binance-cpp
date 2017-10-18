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
  };

  Endpoint::Endpoint(string key, string secret) {
    this->api = make_shared<Api>(key, secret);
  }
}
