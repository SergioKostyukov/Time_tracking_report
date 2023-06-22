#ifndef MAIN_CPP_DATA_ANALYSIS_H
#define MAIN_CPP_DATA_ANALYSIS_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using std::string;
using std::vector;
using std::map;

// data analysis
bool check_user_request(vector<string>&, map<string, int>&); // check user request with columns names
void monthly_report(vector<vector<string>>&, map<string, int>&); // change the date format and add working hours
void date_change(string&); // change the date

void out_data(map<string, int>&, const vector<vector<string>>&, const vector<string>&); // output the result to the console and to a file (.csv)

#endif //MAIN_CPP_DATA_ANALYSIS_H
