#include <fstream>
#include <iostream>

using namespace std;

int main() {
    fstream audioFile;
    fstream outFile; //For now, I will see if I can make a copy of an audio file, then I will see if
    //I can append audio data from one audio file to another
    streampos size;
    char* audioData;
    audioFile.open("audio bits/a.wav", ios::binary | ios::ate);
    outFile.open("test.wav", ios::binary);
    if (audioFile.is_open()) {
        size = audioFile.tellg();
        audioData = new char[size];
        audioFile.seekg(0, ios::beg);
        audioFile.read(audioData, size);
        outFile.write(audioData, size);
        delete[] audioData;
    }
    else {
        cout << "Unable to open file";
    }
    audioFile.close();
    outFile.close();    
    return 0;
}