#include "src/root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <json.hpp>

using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

typedef std::function<void(json)> async_callback;

void fail(boost::system::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

// Sends a WebSocket message and prints the response
class session : public std::enable_shared_from_this<session> {
  tcp::resolver resolver_;
  websocket::stream<ssl::stream<tcp::socket>> ws_;
  boost::beast::multi_buffer buffer_;
  std::string host_;
  std::string path_;
  async_callback callback_;

public:
  // Resolver and socket require an io_service
  explicit session(boost::asio::io_service& ios, ssl::context& ctx)
    : resolver_(ios), ws_(ios, ctx) {};

  // Start the asynchronous operation
  void run(char const* host,
           char const* port,
           char const* path,
           async_callback callback) {
    // Save these for later
    host_ = host;
    path_ = path;
    callback_ = callback;

    // Look up the domain name
    resolver_.async_resolve({ host, port },
                            std::bind(&session::on_resolve,
                                      shared_from_this(),
                                      std::placeholders::_1,
                                      std::placeholders::_2));
  }

  void on_resolve(boost::system::error_code ec,
                  tcp::resolver::iterator result) {
    if(ec)
      return fail(ec, "resolve");

    // Make the connection on the IP address we get from a lookup
    boost::asio::async_connect(ws_.next_layer().next_layer(),
                               result,
                               std::bind(&session::on_connect,
                                         shared_from_this(),
                                         std::placeholders::_1));
  }

  void on_connect(boost::system::error_code ec) {
    if(ec)
      return fail(ec, "connect");

    // Perform the SSL handshake
    ws_.next_layer().async_handshake(ssl::stream_base::client,
                                     std::bind(&session::on_ssl_handshake,
                                               shared_from_this(),
                                               std::placeholders::_1));
  }

  void on_ssl_handshake(boost::system::error_code ec) {
    if(ec)
      return fail(ec, "ssl_handshake");

    // Perform the websocket handshake
    ws_.async_handshake(host_, path_,
                        std::bind(&session::on_handshake,
                                  shared_from_this(),
                                  std::placeholders::_1));
  }

  void on_handshake(boost::system::error_code ec) {
    if(ec)
      return fail(ec, "handshake");

    // Read a message into our buffer
    ws_.async_read(buffer_,
                   std::bind(&session::on_read,
                             shared_from_this(),
                             std::placeholders::_1,
                             std::placeholders::_2));
  }

  void on_read(boost::system::error_code ec,
               std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if(ec)
      return fail(ec, "read");

    auto data_str = boost::beast::buffers_to_string(buffer_.data());
    auto data_json = nlohmann::json::parse(data_str);
    std::cout << data_str << std::endl;

    callback_(data_json);

    buffer_.consume(buffer_.size());

    // Read a message into our buffer
    ws_.async_read(buffer_,
                   std::bind(&session::on_read,
                             shared_from_this(),
                             std::placeholders::_1,
                             std::placeholders::_2));
  }
};

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
  // Check command line arguments.
  if(argc != 4) {
    std::cerr <<
      "Usage: websocket-client-async-ssl <host> <port> <path>\n" <<
      "Example:\n" <<
      "    websocket-client-async-ssl echo.websocket.org 443 \"Hello, world!\"\n";
    return EXIT_FAILURE;
  }
  auto const host = argv[1];
  auto const port = argv[2];
  auto const path = argv[3];

  // The io_service is required for all I/O
  boost::asio::io_service ios;

  // The SSL context is required, and holds certificates
  ssl::context ctx{ssl::context::sslv23_client};

  // This holds the root certificate used for verification
  load_root_certificates(ctx);

  // Launch the asynchronous operation
  std::make_shared<session>(ios, ctx)->run(host, port, path, [](json data) {
      std::cout << data.dump(2) << std::endl;
    });

  // Run the I/O service. The call will return when
  // the get operation is complete.
  ios.run();

  return EXIT_SUCCESS;
}
