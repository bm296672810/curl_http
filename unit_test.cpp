#include <iostream>
#include "curl_http.h"

int main(int argc, char* argv[])
{
    bm::http::init_curl();

    std::string token = "bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJsb3JhLWFwcC1zZXJ2ZXIiLCJleHAiOjE2MDc0OTk2NTksImV4cGlyYXRpb25EYXRlIjoiMjAzMC0xMi0wMiIsImlzcyI6ImxvcmEtYXBwLXNlcnZlciIsIm5iZiI6MTYwNzQxMzI1OSwic3ViIjoidXNlciIsInVzZXJuYW1lIjoiMTM5MjM4NDk5ODAifQ.3iVqzBKGkvp4GKItbYJtNpaW9pvleJOXAbVKN8SuZTM";
    curl_http ch;
    http_header get_head;
    get_head.accept = "application/json";
    get_head.token = token;
    get_head.token_key = "authorization";
    std::string req = ch.get("http://iot.smartkit.io:8005/api/applications", get_head);
    std::cout << req << std::endl;

    std::string login_url = "http://iot.smartkit.io:8005/api/users/login";
    std::string data = "{\"password\": \"13923849980\",\"username\": \"13923849980\"}";

    http_header post_head;
    post_head.accept = "application/json";
    post_head.content_type = "application/json";
    post_head.token = token;
    post_head.token_key = "authorization";
    std::string d = "{\"device_queue_item\": {\"confirmed\": false,\"data\": \"ATLlPRCAAwAPHgAHEP///////////////////////////////////2VV\",\
    \"dev_eui\": \"ffffff1000017859\",\"f_port\": 2}}";
    req = ch.post("http://iot.smartkit.io:8005/api/devices/ffffff1000017859/queue", d, post_head);
    std::cout << "application:" << req << std::endl;

    std::string delete_url = "http://iot.smartkit.io:8005/api/devices/ffffff1000017859/queue";
    std::string delete_data = "";
    http_header delete_head;
    delete_head.accept = "application/json";
    delete_head.token = token;
    delete_head.token_key = "authorization";
    req = ch.del(delete_url, delete_head);
    std::cout << "delete:" << req << std::endl;

    bm::http::release_curl();
    return 0;
}