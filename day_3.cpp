#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct fabric_measure {
    int from_left;
    int from_top;
    int width;
    int height;
};

int main() {
  int f_details;
  fabric_measure f_m;
  int key;
  map <int, fabric_measure> fabric_dict;
  FILE *file_in;
  //open file and store information
  file_in = fopen("input_3.txt", "r");
  if (file_in == NULL) {
      cout << "Unable to open file";
      exit(1);
  }
  //initialise a matrix to represent the fabrix
  int total_fabric[1000][1000];
  for (int i=0; i<1000; i++) {
    for (int j=0; j<1000; j++) {
        total_fabric[i][j]=0;
    }
  }

  int overlap=0;
  while ((f_details=fscanf(file_in, "#%d @ %d,%d: %dx%d\n", &key, &f_m.from_left, &f_m.from_top, &f_m.width, &f_m.height))==5) {
      fabric_dict[key]=f_m;
      for (int i=f_m.from_top; i<(f_m.from_top+f_m.height); i++) {
          for (int j=f_m.from_left; j<(f_m.from_left+f_m.width); j++) {
            if (total_fabric[i][j]<2) {
                total_fabric[i][j]++;
                if (total_fabric[i][j]==2) {
                    overlap++;
                }
            }
          }
      }
  }
  fclose(file_in);
  cout << overlap << "\n";
  map <int, fabric_measure>::iterator it;
  int unique_id;
  for (it=fabric_dict.begin(); it!=fabric_dict.end(); it++) {
    int unique=1;
    for (int i=it->second.from_top; i<(it->second.from_top+it->second.height); i++) {
      for (int j=it->second.from_left; j<(it->second.from_left+it->second.width); j++) {
          if (total_fabric[i][j]==2) {
              unique=0;
          }
          if (i==(it->second.from_top+it->second.height-1) && j==(it->second.from_left+it->second.width-1) && unique==1) {
              unique_id=it->first;
          }
      }
    }
  }
  cout << unique_id << "\n";
  return 0;
}
