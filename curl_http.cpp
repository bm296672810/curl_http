#include "curl_http.h"

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

curl_http::curl_http()
{
    m_curl = curl_easy_init();
}
std::string curl_http::request(const std::string& url)
{
    std::string respone;
    struct curl_slist *headers = nullptr;
    
    // curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");

    headers = curl_slist_append(headers, "accept: application/json");
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&respone);

    /**
    * 当多个线程都使用超时处理的时候，同时主线程中有 sleep 或是 wait 等操作。
    * 如果不设置这个选项， libcurl 将会发信号打断这个 wait 从而导致程序退出。
    */
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, CURL_CONNECT_TIMEOUT);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, CURL_OPT_TIMEOUT);

    auto r = curl_easy_perform(m_curl);

    curl_slist_free_all (headers);
    if(r != CURLE_OK)
    {
        return "";
    }

    return respone;
}
curl_http::~curl_http()
{
    curl_easy_cleanup(m_curl);
}