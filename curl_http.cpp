#include "curl_http.h"
#include <iostream>
#include <fstream>

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void *lpVoid)
{
    std::string *str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if (nullptr == str || nullptr == buffer ) {
        return -1;
    }

    char* pData = static_cast<char*>(buffer);
    str->append(pData, size * nmemb);
    return nmemb;
}
static int curl_debug(CURL* handle, curl_infotype type, char* data,
                          size_t size, void* userptr)
{
    // std::cout << "curl log:" << std::string(data, size) << std::endl;
    std::fstream f("test.log", std::ios::app | std::ios::in);
    f << (char*)userptr << "==========================================================" << std::endl;
    f << std::string(data, size) << std::endl;
    return size;
}
curl_http::curl_http()
{
    m_curl = curl_easy_init();
}

std::string curl_http::get(const std::string& url, const http_header& head)
{
    return request(url, head);
}
std::string curl_http::post(const std::string& url, const std::string& data, const http_header& head)
{
    return request(url, head, RT_POST, data);
}
std::string curl_http::del(const std::string& url, const http_header& head)
{
    return request(url, head, RT_DELETE);
}
curl_http::~curl_http()
{
    curl_easy_cleanup(m_curl);
}

std::string curl_http::request(const std::string& url, const http_header& h, request_type t, const std::string& data)
{
    std::lock_guard<std::mutex> lock(m_lock);
    
    std::string respone;
    struct curl_slist *headers = nullptr;
    
    if(!h.accept.empty())
        headers = curl_slist_append(headers, (h.accept_key + ":"+ h.accept).c_str());
    if(!h.content_type.empty())
        headers = curl_slist_append(headers, (h.content_type_key + ":" + h.content_type).c_str());
    if(!h.token.empty())
        headers = curl_slist_append(headers, (h.token_key + ":" + h.token).c_str());
    if(!h.sign.empty())
        headers = curl_slist_append(headers, (h.sign_key + ":" + h.sign).c_str());
    if(!h.time_stamp.empty())
        headers = curl_slist_append(headers, (h.time_stamp_key + ":" + h.time_stamp).c_str());

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    switch (t)
    {
    case RT_GET:
        break;
    case RT_POST:
    {
        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, data.length());
        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(m_curl, CURLOPT_POST, 1);
    }
        break;
    case RT_DELETE:
        curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
    default:
        break;
    }

    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&respone);
    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, curl_debug);
    curl_easy_setopt(m_curl, CURLOPT_DEBUGDATA, data.data());

    /**
    * 当多个线程都使用超时处理的时候，同时主线程中有 sleep 或是 wait 等操作。
    * 如果不设置这个选项， libcurl 将会发信号打断这个 wait 从而导致程序退出。
    */
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, CURL_CONNECT_TIMEOUT);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, CURL_OPT_TIMEOUT);
    // CURLcode::CURL_LAST
    auto r = curl_easy_perform(m_curl);
    std::cout << "url:" << url << ",code:" << r << std::endl;
    curl_slist_free_all (headers);
    if(r != CURLE_OK)
    {
        return "";
    }

    return respone;
}