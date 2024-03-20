#include "header.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    Operation op;

    //CHECK FOR HELP
    if (argc < 2 || strcmp(argv[1],"--help")==0){
        cout << "You didn't pass any arguments!\t";
        return 0;
    }

    //CORRECT NUM OF ARGS
    if (argc < 3){
        cout<<"Invalid file name.";
        return 0;
    }

    //GET NAMES
    string nameOf_outputFile = argv[1];
    string nameOf_trackingFile = argv[2];
    string path_tracking = nameOf_trackingFile.insert(0,"./input/");

    //CHECK FOR FILE EXTENSION
    if(nameOf_outputFile.size()>3 && nameOf_trackingFile.size()>3){
        string last3 = nameOf_outputFile.substr(nameOf_outputFile.length() - 4);
        string last3_track = nameOf_trackingFile.substr(nameOf_trackingFile.length() - 4);
        if (!(last3 == ".tga")){
            cout<<"Invalid file name.";
            return 0;
        }
        if(!(last3_track ==".tga")){
            cout<<"Invalid file name.";
            return 0;
        }

        //CHECKS IF TRACKING EXISTS
        ifstream temp(path_tracking);
        if(!temp.is_open()){
            cout<<"File does not exist.";
            return 0;
        }
        temp.close();
    }
    else{
        cout<<"Invalid file name.";
        return 0;
    }

    // WE LOAD TRACKING IMAGE
    File tracking("tracking",path_tracking,{});
    tracking.readHeader();
    tracking.readFile();

    //CHECK THIRD ARGUMENT IS THERE
    if (argc <4){
        cout<<"Invalid method name.";
        return 0;
    }



    return 0;
}
