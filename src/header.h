#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#pragma once

using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

class File{
public:
    struct pixel{
        vector<unsigned char> BGR;
    };
    string filename;
    string address;
    Header head;
    vector<pixel> pixel_vector;
    File();
    File(string filename, string address, Header head);

    //FUNCTIONS
    //HEADER
    void readHeader();
    void printHeader();

    //FILE READ/WRITE
    void readFile();
    void printFile();
    void writeFile(string filename);

};

class Operation{
public:
    //Operations
    File Multiply(File &top, File &bottom);
    File Subtract(File &top, File &bottom);
    File Screen(File &top, File &bottom);

    //Tasks
    void Task1();
    void Task2();
    void Task3();

};