#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

using namespace std;

// file parsing
vector<vector<string>> read_csv(const string&);

void user_request(vector<string>&); // save user request

// data analysis
bool check_user_request(vector<string>&, map<string, int>&); // check user request with columns names
void monthly_report(vector<vector<string>>&, map<string, int>&); // change the date format and add working hours
void date_change(string&); // change the date

void out_data(map<string, int>&, const vector<vector<string>>&, const vector<string>&); // output the result to the console and to a file (.csv)

int main() {
    map<string, int> title; // columns names
    vector<vector<string>> data(read_csv("data.csv"));

    int count = 0;
    for(auto& i : data[0]){
        title[i] = count++;
    }
    data.erase(data.begin()); // clear first(columns names) line from data

    if(title.find("logged hours") != title.end()){
        monthly_report(data, title);
    }

    cout << "Information we have: " << endl;
    for(auto& i : title){
        cout << i.first << " ";
    }
    cout << endl;

    vector<string> request;
    user_request(request);
    while(!check_user_request(request, title)) {
        cout << "Error request." << endl;
        request.clear();

        user_request(request);
    }

    out_data(title, data, request);

    return 0;
}

vector<vector<string>> read_csv(const string& file_name){
    ifstream file(file_name);
    if(!file.is_open()) throw runtime_error("Could not open file");

    vector<vector<string>> data;
    vector<string> line_info;
    string line, word;

    while(getline(file, line)){
        line_info.clear();
        stringstream s(line);

        while(getline(s, word, ';')){
            line_info.push_back(word);
        }
        data.push_back(line_info);
    }

    file.close();
    return data;
}

void user_request(vector<string>& request){
    cout << "What info you want see?(separator is '/')" << endl;
    string line, word;

    cin >> line;
    stringstream s(line);

    while(getline(s, word, '/')){
        request.push_back(word);
    }
}

bool check_user_request(vector<string>& request, map<string, int>& title){
    bool res = false;

    for(auto& i : request){
        for(auto& j : title){
            if(j.first == i){
                res = true;
                break;
            }
            res = false;
        }
    }

    return res;
}

void monthly_report(vector<vector<string>>& data, map<string, int>& title){
    int name_ind = title["Name"];
    int date_ind = title["date"];
    int time_ind = title["logged hours"];

    title.erase(title.find("logged hours"));
    title["hours"] = time_ind;

    title.erase(title.find("date"));
    title["month"] = date_ind;

    for(auto& i : data){
        date_change(i[date_ind]);
    }

    int hours1 = 0, hours2 = 0;

    vector<vector<vector<string>>::iterator> to_clear;

    for(auto Iter1 = data.begin(); Iter1 != data.end(); Iter1++){
        hours1 = atoi((*Iter1)[time_ind].c_str());
        for(auto Iter2 = Iter1 + 1; Iter2 != data.end(); Iter2++){
            if(((*Iter1)[name_ind] == (*Iter2)[name_ind]) && ((*Iter1)[date_ind] == (*Iter2)[date_ind])){
                // add work hours
                hours2 = atoi((*Iter2)[time_ind].c_str());
                hours1 += hours2;
                (*Iter1)[time_ind] = to_string(hours1);

                // list of excessive lines
                to_clear.push_back(Iter2);

                // check other differences
                for(auto& i : title){
                    if(i.second != name_ind && i.second != date_ind && i.second != time_ind && (*Iter1)[i.second] != (*Iter2)[i.second]){
                        (*Iter1)[i.second] += '/' + (*Iter2)[i.second];
                    }
                }

                Iter1++;
            }
        }
    }

    for(auto& i : to_clear){
        data.erase(i);
    }
}

void date_change(string& old_date){
    map<int, string> months = {
            {1, "January"},
            {2, "February"},
            {3, "March"},
            {4, "April"},
            {5, "May"},
            {6, "June"},
            {7, "July"},
            {8, "August"},
            {9, "September"},
            {10, "October"},
            {11, "November"},
            {12, "December"},
    };

    stringstream s(old_date);

    string year;
    string month;

    getline(s, year, '-');
    getline(s, month, '-');

    old_date = months[atoi(month.c_str())] + " " + year;
}

void out_data(map<string, int>& title, const vector<vector<string>>& data, const vector<string>& request){
    fstream file("result_file.csv", ios::out);
    if(!file.is_open()) throw runtime_error("Could not open file");

    for(auto& i : request){
        file << i << ";";
    }
    file << endl;

    for(auto& i : data){
        for(auto& req : request){
            cout << i[title[req]] << ";";
            file << i[title[req]] << ";";
        }
        cout << endl;
        file << endl;
    }
    file.close();
}