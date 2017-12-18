// Copyright 2014 EmilW

#ifndef SOURCE_HTTPRESPONSE_H_
#define SOURCE_HTTPRESPONSE_H_

#include <string>
#include <map>
#include "StringBufferHelper.h"
#include "URL.h"
#include "Log.h"

class HttpResponse {
 public:
  HttpResponse(std::string responseData, URL* originalURL, Log log);
  ~HttpResponse();
  std::string GetHttpStatusCode();
  std::string GetHttpStatusText();
  std::string GetRawResponse();
  std::string GetHttpVersion();
  std::map<std::string, std::string> GetHttpHeaders();
  URL* GetRequestURL();
 private:
  std::string moveBufferForward(std::string buffer, int newPosition);
  void parseHttpResponseData();
  void parseHttpEnvelope();
  void parseHttpHeaders();
  StringBufferHelper* _pRawBuffer;
  std::string _httpStatusCode;
  std::string _httpStatusText;
  std::string _httpVersion;
  std::map<std::string, std::string> _headerMap;
  URL* _requestURL;
  Log _log;
};

#endif  // SOURCE_HTTPRESPONSE_H_
