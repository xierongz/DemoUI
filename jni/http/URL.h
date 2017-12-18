// Copyright 2014 EmilW

#ifndef URL_H
#define URL_H

#include <string>

  const std::string SECUREPROTOCOLPORT = "443";
  const std::string REGULAREPROTOCOLPORT = "80";
  const std::string REGULARPROTOCOL = "http";
  const std::string SECUREPROTOCOL = "https";
class URL {
public:
  URL(std::string url);
  std::string GetHostName();
  std::string GetProtocoll();
  std::string GetPortNumber();
  std::string GetFullURL();
  std::string GetRelativePath();
  std::string GetQueryString();
  bool IsSSL();
private:
  std::string _url;
  std::string _host;
  std::string _protocoll;
  std::string _portNumber;
  std::string _relativePath;
  std::string _queryString;

};


#endif /* URL_H */
