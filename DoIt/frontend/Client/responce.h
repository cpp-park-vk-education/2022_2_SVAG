#pragma once

#include <sstream>
#include <string>
#include <vector>

struct Response {
  int status_code;
  std::string status_message;
  std::vector<std::string> headers;
  std::string http_version;
  std::string body;

  std::string toString() {
    std::stringstream ss;
    ss << http_version << " " << status_code << " " << status_message
       << "\r\n\r\n";
    for (auto& header : headers)
      ss << header << "\r\n";
    if (!body.empty())
      ss << body << "\r\n\r\n";
    return ss.str();
  }
};
