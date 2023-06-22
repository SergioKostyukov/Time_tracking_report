#include "Data_analysis.h"

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
                (*Iter1)[time_ind] = std::to_string(hours1);

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

    std::stringstream s(old_date);

    string year;
    string month;

    getline(s, year, '-');
    getline(s, month, '-');

    old_date = months[atoi(month.c_str())] + " " + year;
}

void out_data(map<string, int>& title, const vector<vector<string>>& data, const vector<string>& request){
    std::fstream file("result_file.csv", std::ios::out);
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    for(auto& i : request){
        file << i << ";";
    }
    file << std::endl;

    for(auto& i : data){
        for(auto& req : request){
            std::cout << i[title[req]] << ";";
            file << i[title[req]] << ";";
        }
        std::cout << std::endl;
        file << std::endl;
    }
    file.close();
}