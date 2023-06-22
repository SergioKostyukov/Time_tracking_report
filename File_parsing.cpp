#include "File_parsing.h"

vector<vector<string>> read_csv(const string& file_name){
    std::ifstream file(file_name);
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    vector<vector<string>> data;
    vector<string> line_info;
    string line, word;

    while(getline(file, line)){
        line_info.clear();
        std::stringstream s(line);

        while(getline(s, word, ';')){
            line_info.push_back(word);
        }
        data.push_back(line_info);
    }

    file.close();
    return data;
}