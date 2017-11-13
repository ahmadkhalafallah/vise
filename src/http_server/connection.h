/** @file   connection.h
 *  @brief  Denotes a connection corresponding to a user's http request
 *
 *
 *  @author Abhishek Dutta (adutta@robots.ox.ac.uk)
 *  @date   10 Nov 2017
 */

#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/array.hpp>

class connection : public boost::enable_shared_from_this<connection>, private boost::noncopyable
{
 public:
  connection(boost::asio::io_service& io_service,
             boost::filesystem::path upload_dir_,
             boost::filesystem::path result_dir_);

  boost::asio::ip::tcp::socket& Socket();
  void process_connection();

  static const std::string crlf;
  static const std::string crlf2;
  static const std::string http_100;
  static const std::string http_200;
  static const std::string http_301;
  static const std::string http_400;
  static const std::string app_namespace;
 private:
  void on_request_data(const boost::system::error_code& e, std::size_t bytes_read);
  void on_response_write(const boost::system::error_code& e);

  boost::asio::io_service::strand strand_; // ensure that only a single thread invokes a handler
  boost::asio::ip::tcp::socket socket_; // socket instance for this connection
  std::string connection_id_;
  boost::array<char, 2048> buffer_;
  boost::asio::streambuf response_buffer_;
};

#endif
