#include <iostream>
#include "curl_http.h"

int main(int argc, char* argv[])
{
    curl_http ch;
    std::string req = ch.request("http://iot.smartkit.io:8005/api/applications");
    std::cout << req << std::endl;
    return 0;
}