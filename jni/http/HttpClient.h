// Copyright 2014 EmilW

#ifndef SOURCE_HTTPCLIENT_H_
#define SOURCE_HTTPCLIENT_H_

#include <string>
#include "HttpResponse.h"
#include "Log.h"

class HttpClient {
 public:
  HttpClient();
  ~HttpClient();
  explicit HttpClient(Log log);
  HttpResponse* RunRequest(std::string url, std::string type);
  void releaseRequest();
  Log GetFullLog();
 private:
  Log _log;
  HttpResponse* _rep;
  URL* _urlObject;
};

#endif  // SOURCE_HTTPCLIENT_H_
