#pragma once

#include <string>

#include <curl/curl.h>

#define CURL_CONNECT_TIMEOUT 2
#define CURL_OPT_TIMEOUT 15

class curl_http
{
public:
    curl_http();
    std::string request(const std::string& url);
    ~curl_http();
private:
    CURL* m_curl = nullptr;
};