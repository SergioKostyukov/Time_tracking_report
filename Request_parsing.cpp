#include "Request_parsing.h"

void user_request(std::vector<std::string>& request){
    std::cout << "What info you want see?(separator is '/')" << std::endl;
    std::string line, word;

    std::cin >> line;
    std::stringstream s(line);

    while(getline(s, word, '/')){
        request.push_back(word);
    }
}