#include <iostream>
#include <fstream>
//A space for learning about the WAV format
using namespace std;

int main() {
  ifstream wavFile("audioBits/a.wav", ios::binary);
  ofstream dataFile("data.wav", ios::binary);
  int chunkSize = 4;
  //int soundDataSize = 4; //Subchunk2Size
  //int riffSize = 12; //Riff size 
  //int fmtSize = 4; //Subchunk1Size
  char* soundData;
  //Do I need these other two things in order to make a copy of a WAV file?
  //char* riff;
  //char* fmt; 
  uint16_t intData = 0; //In order to capture size of chunks in int form 
  if (wavFile.is_open()) {
    wavFile.seekg(4);
    wavFile.read((char*)(&intData), chunkSize); //Regular casting seems to work
    cout << intData << '\n';
    chunkSize = intData + 8;
    wavFile.seekg(0);
    soundData = new char[chunkSize];
    wavFile.read(soundData, chunkSize);
    dataFile.write(soundData, chunkSize);
    cout << chunkSize << "\n";
    delete[] soundData; 
  }
  if (wavFile.is_open()) {
    wavFile.close();
  }
  dataFile.close();
  return 0;
}
  