#include <iostream>
#include <fstream>
//A space for learning about the WAV format
using namespace std;

int main() {
  //Can only use ios::binary in of and if streams, not 
  //just fstreams I guess...? Repl won't let me.
  string wavFileLoc1 = "";
  string wavFileLoc2 = "";
  cout << "Enter location of base wav file: ";
  cin >> wavFileLoc1;
  //ifstream wavFile("audio bits/a.wav", ios::binary);
  ifstream wavFile(wavFileLoc1, ios::binary);
  cout << "Enter location of the wav file to be appended to the first: \n";
  cin >> wavFileLoc2;
  //ifstream wavFile("audio bits/bA.wav", ios::binary);
  ifstream appendFile(wavFileLoc2, ios::binary);

  ofstream dataFile("data.wav", ios::binary);

  int chunkSize = 4;
  int soundDataSize = 4; //Subchunk2Size
  int riffSize = 12; //Riff size 
  int fmtSize = 24; //Size of entire fmt sub-chunk
  int newChunkSize;
  int newDataSize;
  char* riffData; //Can be the same as one of them...?
  char* fmtData; //Should be the same as one of them...?
  char* sound1Data;
  char* sound2Data;
  char* chunkIdData;
  char* formatRiffData;
  uint16_t intData1 = 0; //In order to capture size of chunks in int form 
  uint16_t intData2 = 0;
  //Collect data first, then add to new audio file
  if (wavFile.is_open() && appendFile.is_open()) {
    //Get sound data sizes
    wavFile.seekg(0); //Gets chunk data of riff
    wavFile.read((char*) (&chunkIdData), chunkSize);
    wavFile.seekg(8); //Gets format for the riff 
    wavFile.read((char*) (&formatRiffData), chunkSize);
    wavFile.seekg(12); //Gets format for fmt chunk
    wavFile.read((char*) (&fmtData), fmtSize);
    wavFile.seekg(40); //Gets sound data 
    wavFile.read((char*)(&intData1), soundDataSize);
    sound1Data = new char[intData1];
    wavFile.read(sound1Data, intData1);
    appendFile.seekg(40);
    appendFile.read((char*)(&intData2), soundDataSize);
    sound2Data = new char[intData2];
    appendFile.read(sound2Data, intData2);
    newDataSize = intData1 + intData2;
    
    //Writes RIFF data
    dataFile.write((char*)(&chunkIdData), chunkSize);
    dataFile.write((char*)(&newDataSize), chunkSize);
    dataFile.write((char*)(&formatRiffData), chunkSize);
    
    //Writes FMT data
    dataFile.write((char*)(&fmtData), fmtSize);
    
    //TODO: Write Subchunk2ID (copy Subchunk2ID from wavFile)
    
    //TODO: Write Subchunk2Size

    //Writes sound data
    dataFile.write(sound1Data, intData1);
    dataFile.write(sound2Data, intData2);

    //Delete sound data arrays to prevent memory leaks
    delete[] sound1Data;
    delete[] sound2Data; 
  }
  if (wavFile.is_open()) {
    wavFile.close();
  }
  if (appendFile.is_open()) {
    appendFile.close();
  }
  dataFile.close();
  return 0;
}

//Note: The format size between 2 16-bit wav files are the same, so I can just take the format from one of the wav files and add it to the new wav file. Chunk size is also the same, even if one of the audios is longer? Data size also appears to be the same as well.