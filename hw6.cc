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
#include "cdk.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileHeader {
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord { 
public:
  uint8_t strLength;
  char stringBuffer [maxRecordStringLength];
};

int main() {

  WINDOW        *window;
  CDKSCREEN     *cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix 

  const char *rowTitles [MATRIX_ROWS + 1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char *columnTitles [MATRIX_COLS + 1] = {"IGNORE", "a", "b", "c"};
  int colWidths [MATRIX_COLS + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes [MATRIX_COLS + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen (window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix (cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  ifstream binInfile;
 
  // open supplied binary file for reading
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  if (!binInfile) {
  // An error occured.
    cout << "Error\n";
    return 0;
  }

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  binInfile.read ((char *) myHeader, sizeof(BinaryFileHeader));

  BinaryFileRecord record[4];

  for (int i = 0; i < 4; i++) {
    // read up to 4 record
    binInfile.read((char*) &record[i],sizeof(BinaryFileRecord));
  }
  
  stringstream magicNumSS;
  magicNumSS << std::hex << std::uppercase << myHeader->magicNumber;
  string magicNumStr = magicNumSS.str();
  string magicNumStrFinal = "0x" + magicNumStr;
  string magicNumStrMatrix = "Magic: " + magicNumStrFinal;

  string versionNumStr = to_string (myHeader->versionNumber);
  string versionNumStrMatrix = "Version: " + versionNumStr;

  string numRecordsString = to_string (myHeader->numRecords);
  string numRecordsStrMatrix = "NumRecords: " + numRecordsString;

  int stringBufferLength0 = strlen(record[0].stringBuffer);
  string bufferLengthStr0 = to_string(stringBufferLength0);
  string bufferLengthMatrix0 = "strlen: " + bufferLengthStr0;

  int stringBufferLength1 = strlen(record[1].stringBuffer);
  string bufferLengthStr1 = to_string(stringBufferLength1);
  string bufferLengthMatrix1 = "strlen: " + bufferLengthStr1;

  int stringBufferLength2 = strlen(record[2].stringBuffer);
  string bufferLengthStr2 = to_string(stringBufferLength2);
  string bufferLengthMatrix2 = "strlen: " + bufferLengthStr2;

  int stringBufferLength3 = strlen(record[3].stringBuffer);
  string bufferLengthStr3 = to_string(stringBufferLength3);
  string bufferLengthMatrix3 = "strlen: " + bufferLengthStr3;
  
  stringstream stringBuffer0SS;
  stringBuffer0SS << std::hex << record[0].stringBuffer;
  string stringBuffer0Str = stringBuffer0SS.str();

  stringstream stringBuffer1SS;
  stringBuffer1SS << std::hex << record[1].stringBuffer;
  string stringBuffer1Str = stringBuffer1SS.str();

  stringstream stringBuffer2SS;
  stringBuffer2SS << std::hex << record[2].stringBuffer;
  string stringBuffer2Str = stringBuffer2SS.str();

  stringstream stringBuffer3SS;
  stringBuffer3SS << std::hex << record[3].stringBuffer;
  string stringBuffer3Str = stringBuffer3SS.str();
;

  /* Display the Matrix */
  setCDKMatrixCell (myMatrix, 1, 1, magicNumStrMatrix.c_str());
  setCDKMatrixCell (myMatrix, 1, 2, versionNumStrMatrix.c_str());
  setCDKMatrixCell (myMatrix, 1, 3, numRecordsStrMatrix.c_str());
  setCDKMatrixCell (myMatrix, 2, 1, bufferLengthMatrix0.c_str());
  setCDKMatrixCell (myMatrix, 3, 1, bufferLengthMatrix1.c_str());
  setCDKMatrixCell (myMatrix, 4, 1, bufferLengthMatrix2.c_str());
  setCDKMatrixCell (myMatrix, 5, 1, bufferLengthMatrix3.c_str());
  setCDKMatrixCell (myMatrix, 2, 2, stringBuffer0Str.c_str());  
  setCDKMatrixCell (myMatrix, 3, 2, stringBuffer1Str.c_str());
  setCDKMatrixCell (myMatrix, 4, 2, stringBuffer2Str.c_str());
  setCDKMatrixCell (myMatrix, 5, 2, stringBuffer3Str.c_str());
  drawCDKMatrix (myMatrix, true);

  // start cleaning up
  binInfile.close();
  delete myHeader;

  // if user enters a char, finish cleanup and exit
  char charInput;
  cin >> charInput;

  // finish cleanup
  endCDK();

  // exit
  return 0; 
}
























  



















































