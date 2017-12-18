// Copyright 2014 EmilW

#include <string>
#include <utility>
#include <map>
#include "HttpResponse.h"

HttpResponse::HttpResponse(std::string responseData, URL* originalURL,
                            Log log) {
  _log = log;
  _requestURL = originalURL;
  _pRawBuffer = NULL;
  _log.Add("HttpResponse", "Starting parsing");

  if (responseData.substr(0, 5) == "ERROR") {
    _httpStatusCode = "999";
    _httpStatusText = responseData.substr(5, responseData.size()-5);
    _log.Add("Client handled error occured");
    _log.Add("Client handled responseData:"+responseData);
  } else {
    _pRawBuffer = new StringBufferHelper(responseData);
    parseHttpResponseData();
    _log.Add("HttpResponse", "Parsing of response went ok");
  }
}
HttpResponse::~HttpResponse(){
	if(_pRawBuffer != NULL){
		delete _pRawBuffer;
		_pRawBuffer = NULL;
	}
}
URL* HttpResponse::GetRequestURL() {
  return _requestURL;
}

std::string HttpResponse::moveBufferForward(std::string buffer,
                                            int newPosition) {
  return buffer.substr(newPosition+1, buffer.size());
}

void HttpResponse::parseHttpResponseData() {
  parseHttpEnvelope();
  parseHttpHeaders();
}

void HttpResponse::parseHttpEnvelope() {
  _httpVersion = _pRawBuffer->GetNextSegmentBySeparator(" ");
  _httpStatusCode = _pRawBuffer->GetNextSegmentBySeparator(" ");
  _httpStatusText = _pRawBuffer->GetNextSegmentBySeparator("\n");
}

void HttpResponse::parseHttpHeaders() {
	std::string key, value;

	while (true) {
		key = _pRawBuffer->GetNextSegmentBySeparator(": ");
		if (key == "NA")
			break;
		value = _pRawBuffer->GetNextSegmentBySeparator("\n");
		_headerMap.insert(std::pair<std::string, std::string>(key, value));
	}
}

std::string HttpResponse::GetHttpVersion() {
  return _httpVersion;
}

std::string HttpResponse::GetHttpStatusCode() {
  return _httpStatusCode;
}

std::string HttpResponse::GetHttpStatusText() {
  return _httpStatusText;
}

std::map<std::string, std::string> HttpResponse::GetHttpHeaders() {
  return _headerMap;
}

std::string HttpResponse::GetRawResponse() {
  if (_pRawBuffer != nullptr)
    return _pRawBuffer->GetRawData();
  return "";
}
