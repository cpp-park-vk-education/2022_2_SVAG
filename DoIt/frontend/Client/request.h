#pragma once

#include <sstream>
#include <string>
#include <vector>

struct Request {
  std::string method;
  std::string path;
  std::string http_version;
  std::vector<std::string> headers;
  std::vector<std::string> params;
  std::string body;

  std::string toString() {
    std::stringstream ss;
    ss << method << " " << path << " " << http_version << "\r\n";
    for (auto& header : headers)
      ss << header << "\r\n";
    ss << "\r\n";
    if (!body.empty())
      ss << body << "\r\n\r\n";
    return ss.str();
  }
};
