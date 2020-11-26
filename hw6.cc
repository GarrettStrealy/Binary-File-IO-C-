/*
 * File:                hw6.cc
 * Date:                11/21/2020
 * Author:              Garrett Strealy
 * Email:               garrett.strealy@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *  Perform Binary File IO and display results
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <string>
#include <bits/stdc++.h>
#include <array>

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileHeader {
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;;
};

class BinaryFileRecord { 
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//string convertToString(char* a, int size) 
//{ 
//  int i; 
//  string s = ""; 
//  for (i = 0; i < size; i++) { 
//    s = s + a[i]; 
//  } 
//  return s; 
//}

int main() {

  ifstream binInfile;
  BinaryFileHeader *myHeader = new BinaryFileHeader();

  // open supplied binary file for reading
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  if (!binInfile) {
  // An error occured.
    cout << "Error\n";
    // Reset the stream state so it is usable again
    binInfile.clear();
    return 0;
  }

  binInfile.read ((char *) myHeader, sizeof(myHeader));
  //  int binSize = sizeof (buffer) / sizeof (char);
  //  string binString = convertToString(binSize, buffer);
  
  cout << "Printing magicNumber: 0x" << std::hex << std::uppercase << myHeader->magicNumber << endl;
  cout << "Printing versionNumber: " << unsigned(myHeader->versionNumber) << endl;
  cout << "Printing numRecords: " << unsigned(myHeader->numRecords) << endl;

  binInfile.close();
  return 0;
 
   

}
























  



















































