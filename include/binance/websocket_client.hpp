#pragma once

#include "root_certificates.hpp"
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
#include <spdlog/spdlog.h>

using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>
namespace spd = spdlog;

namespace binance {
  namespace websocket_client {
    typedef std::function<void(json)> async_callback;
    shared_ptr<spd::logger> logger = spd::stdout_color_mt("WEBSOCKET");

    void fail(boost::system::error_code ec, char const* what) {
      logger->error("{0}: {1}", what, ec.message());
    }

    // Sends a WebSocket message and prints the response
    class session : public std::enable_shared_from_this<session> {
      tcp::resolver resolver_;
      websocket::stream<ssl::stream<tcp::socket>> ws_;
      boost::beast::multi_buffer buffer_;
      std::string host_;
      std::string port_;
      std::string path_;
      async_callback callback_;

    public:
      // Resolver and socket require an io_service
      explicit session(boost::asio::io_service& ios, ssl::context& ctx)
        : resolver_(ios), ws_(ios, ctx) {};

      // Start the asynchronous operation
      void run(std::string path,
               async_callback callback) {
        // Save these for later
        host_ = "stream.binance.com";
        port_ = "9443";
        path_ = path;
        callback_ = callback;

        // Look up the domain name
        resolver_.async_resolve({ host_, port_ },
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

        logger->info("{0}: {1}", path_, data_str);

        auto data_json = nlohmann::json::parse(data_str);

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

    auto subscribe(std::string path, async_callback callback) -> void {
      // The io_service is required for all I/O
      boost::asio::io_service ios;

      // The SSL context is required, and holds certificates
      ssl::context ctx{ssl::context::sslv23_client};

      // This holds the root certificate used for verification
      load_root_certificates(ctx);

      // Launch the asynchronous operation
      std::make_shared<session>(ios, ctx)->run(path, callback);

      // Run the I/O service. The call will return when
      // the get operation is complete.
      ios.run();
    }
  }
}

