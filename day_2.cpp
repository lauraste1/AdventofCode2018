#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
  std::string line;
  std::vector<string> id_vect;
  std::vector<int> letter_freq(26, 0);
  //open file and store strings to vector
  ifstream myfile ("day_2_input.txt");
  if (myfile.is_open()) {
      while (getline (myfile, line)) {
          id_vect.push_back(line);
      }
  }
  myfile.close();
  std::vector<string>::iterator it;
  std::vector<char>::iterator itc;
  int index;
  bool has_twos=false;
  bool has_threes=false;
  int num_w_twos=0;
  int num_w_threes=0;
  for (it = id_vect.begin(); it != id_vect.end(); it++) {
      for (itc=it->begin(); itc!=it->end(); itc++) {
          index=(int)*itc - 97;
          letter_freq[index]++;
      }
      for (std::vector<int>::iterator itl=letter_freq.begin(); itl!=letter_freq.end(); itl++) {
          if (*itl==2) {
              has_twos=true;
          }
          if (*itl==3) {
              has_threes=true;
          }
      }
      if (has_twos == true)
          num_w_twos++;
      if (has_threes == true)
          num_w_threes++;
      has_twos=false;
      has_threes=false;
      std::fill(letter_freq.begin(), letter_freq.end(), 0);
  }
  int checksum = num_w_twos*num_w_threes;
  cout << checksum << "\n";
  int diff, diff_pos, id;
  for (int i = 0; i<id_vect.size(); i++) {
      for (int j = 0; j<id_vect.size(); j++) {
          diff=0;
          diff_pos=-1;
          if (id_vect[i]==id_vect[j]) {
              continue;
          }
          for (int k=0; k<id_vect[i].size(); k++) {
              if (id_vect[i][k] != id_vect[j][k]) {
                  diff++;
                  diff_pos = k;
              }
          }
          if (diff==1) {
             id = i;
             cout << id_vect[id] << "\n";
          }
      }
    }

//    id_vect[id].erase(id_vect[id].begin()+diff_pos);
//    cout << id_vect[id];
/*  for (it = id_vect.begin(); it != id_vect.end(); it++) {
      for (itc=it->begin(); itc!=it->end(); itc++) {
          for (its=id_set.begin(); its!=id.end(); its++) {
              if itc==id.set
          }
  }*/
  return 0;
}
