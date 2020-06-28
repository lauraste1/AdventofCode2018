#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct date_t {
    int month;
    int day;
};

int main() {

	//variables that will discard
	int year;
	int hour;
    map <int, int> sleep_total;
    map <int, vector <int> > sleep_freq;
    ifstream file_in;
	int output;
	int guard_id;
	int min;
	int start;
	int finish;
	date_t s_d;

	vector <string> input;
	string line;
	ifstream myfile ("input_4.txt");
    if (myfile.is_open()) {
      while (getline (myfile, line)) {
          input.push_back(line);
      }
    }
    myfile.close();
    sort(input.begin(), input.end());
    for (int i=0; i<input.size();i++) {
    	if (input[i].find("Guard")!=string::npos) {
            sscanf(input[i].c_str(), "[%d-%d-%d %d:%d] Guard #%d begins shift", &year, &s_d.month, &s_d.day, &hour, &min, &guard_id);
    	} else if (input[i].find("falls")!=string::npos){
    		sscanf(input[i].c_str(), "[%d-%d-%d %d:%d] falls asleep", &year, &s_d.month, &s_d.day, &hour, &start);
    //		cout << input[i] << "\n";
    	} else {
            sscanf(input[i].c_str(), "[%d-%d-%d %d:%d] wakes up", &year, &s_d.month, &s_d.day, &hour, &finish);
            sleep_total[guard_id]+=(finish-1)-start;
            if (sleep_freq[guard_id].empty()) {
            	sleep_freq[guard_id].resize(60,0);
            }
            for (int i=start; i<finish; i++) {
            	sleep_freq[guard_id][i]+=1;
            }
    	}
    }
    int max_total=0;
    int max_sleeper=0;

    int max_freq=0;
    int max_minute=0;



    for (auto it = sleep_total.begin(); it != sleep_total.end(); it++) {
        if (max_total<it->second) {
           max_total=it->second;
           max_sleeper=it->first;
        }
    }
    for (int i=0; i < sleep_freq[max_sleeper].size(); i++) {
    	if (max_freq<sleep_freq[max_sleeper][i]) {
    	   max_freq=sleep_freq[max_sleeper][i];
    	   max_minute=i;
    	}
    }

    cout << max_sleeper << "\n";
    cout << max_minute << "\n";
    cout << max_minute*max_sleeper << "\n";

    int max_total_min=0;
    int max_time;
    int max_min_guard;


    for (auto it = sleep_freq.begin(); it != sleep_freq.end(); it++) {
        for (int j=0; j<it->second.size(); j++) {
            if (it->second[j] > max_total_min) {
                max_total_min = it->second[j];
                max_time = j;
                max_min_guard = it->first;
            }
        }
    }

    cout << "The guard that slept the most during a particular minute was " << max_min_guard << "\n";
    cout << "The minute he or she slept the most was " << max_time << "\n";
    cout << "The answer to part 2 is " << max_min_guard*max_time << "\n";
	return 0;
}