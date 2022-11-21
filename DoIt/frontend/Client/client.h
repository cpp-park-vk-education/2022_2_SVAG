#pragma once

#include <iostream>

#include "request.h"
#include "responce.h"

class NetClient {
 public:
  virtual ~NetClient() = default;

  virtual void connect() = 0;
  virtual void disconnect() = 0;
  virtual Response sendRequest(const Request &) = 0;
};

class HttpClient : public NetClient {
 public:
  HttpClient() = default;
  ~HttpClient() override = default;

  void connect() override;
  void disconnect() override;
  Response sendRequest(const Request &) override;
};
