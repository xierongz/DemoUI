// Copyright 2014 EmilW

#include <string>
#include "HttpClient.h"
#include "URL.h"
#include "TCPClient.h"

HttpClient::HttpClient() {
	_rep = NULL;
	_urlObject = NULL;
}

HttpClient::HttpClient(Log log) {
  _log = log;
  _rep = NULL;
  _urlObject = NULL;
}
HttpClient::~HttpClient() {
	if(_urlObject != NULL){
		delete _urlObject;
		_urlObject = NULL;
	}
	if(_rep != NULL){
		delete _rep;
		_rep = NULL;
	}
}
// This needs to be refactored to go away from command line style
HttpResponse* HttpClient::RunRequest(std::string url, std::string type) {
  _urlObject = new URL(url);
  TCPClient client;
  std::string message, result;
  message = type + " /"+_urlObject->GetRelativePath()+ " HTTP/1.1"
		+"\r\nhost:" + _urlObject->GetHostName()
		+"\r\nUser-Agent:FlyThings-HttpClient/4.1.1"
		+"\r\nAccept-Encoding:gzip,deflate"
		+"\r\n\r\n";
  message += _urlObject->GetQueryString();

  _log.Add("Request message:"+message);

  if (_urlObject->IsSSL()) {
    _log.Add("Use https for the call");
    result = client.SendOverSSL(_urlObject->GetHostName(),
    		_urlObject->GetPortNumber(), message);
  } else {
    _log.Add("Use http for the call");
    result = client.Send(_urlObject->GetHostName(),
    		_urlObject->GetPortNumber(), message);
  }
  _log.Add("Request was made, parsing result");
  _rep = new HttpResponse(result, _urlObject, _log);
  _log.Add("Response was parsed sucessfully");
  return _rep;
}

void HttpClient::releaseRequest(){

	if(_urlObject != NULL){
		delete _urlObject;
		_urlObject = NULL;
	}
	if(_rep != NULL){
		delete _rep;
		_rep = NULL;
	}

}
Log HttpClient::GetFullLog() {
	return _log;
}
