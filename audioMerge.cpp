#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream audioFile;
    ofstream outFile; //For now, I will see if I can make a copy of an audio file, then I will see if
    //I can append audio data from one audio file to another
    //streampos size;
	int size = 0;
    char* audioData;
	char c;
    audioFile.open("audio bits/a.wav", ios::binary); //Can only open wav files in binary mode if in or out file is specified...?
    outFile.open("test.wav");
    if (audioFile.is_open()) {
        //size = audioFile.tellg();
		while (audioFile.get(c)) {
			++size;
		}
        cout << "Size of file: " << size << "\n";
        audioData = new char[size];
        //audioFile.seekg(0, ios::beg);
        audioFile.read(audioData, size);
		audioFile.close(); //Added
        outFile.write(audioData, size); //Output turns out to be garbage, need to do something about this
        delete[] audioData;
    }
    else {
        cout << "Unable to open file";
        audioFile.close();
    }
    //audioFile.close();
    outFile.close();    
    return 0;
}