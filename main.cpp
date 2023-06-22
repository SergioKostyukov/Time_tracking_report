#include "File_parsing.h"
#include "Request_parsing.h"
#include "Data_analysis.h"

int main() {
    map<string, int> title; // columns name
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
