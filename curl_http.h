#pragma once

#include <string>
#include <mutex>

#include <curl/curl.h>

#define CURL_CONNECT_TIMEOUT 2
#define CURL_OPT_TIMEOUT 5
class http_header
{
public:
    std::string accept_key = "accept";
    std::string accept;
    std::string content_type_key = "content-type";
    std::string content_type;
    std::string token;
    std::string token_key;
    std::string sign;
    std::string sign_key;
    std::string time_stamp;
    std::string time_stamp_key;
};

enum request_type
{
    RT_GET,
    RT_POST,
    RT_DELETE,
};
namespace yf
{
namespace http
{
// in the main() first to call
inline void init_curl()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

// end the main() to call
inline void release_curl()
{
    curl_global_cleanup();
}
}
}

class curl_http
{
public:
    curl_http();
    std::string get(const std::string& url, const http_header& head);
    std::string post(const std::string& url, const std::string& data, const http_header& head);
    std::string del(const std::string& url, const http_header& head);
    ~curl_http();
private:
    std::string request(const std::string& url, const http_header& h, request_type t = RT_GET, const std::string& data = "");
private:
    CURL* m_curl = nullptr;

    std::mutex m_lock;
};