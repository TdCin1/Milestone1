#include "header.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    //CHECK FOR HELP
    if (argc < 2 || strcmp(argv[1],"--help")==0){
        cout << "Project 2: Image Processing, Fall 2023\n\n"<<"Usage:\n";
        cout<< "    ./project2.out [output] [firstImage] [method] [...]";
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
    string path_tracking = nameOf_trackingFile;
    string path_output = nameOf_outputFile;

    if(!(nameOf_trackingFile.substr(0,6)=="input/")){
        path_tracking = nameOf_trackingFile.insert(0,"./input/");
    }

    if(!(nameOf_outputFile.substr(0,7)=="output/")){
        path_output = nameOf_outputFile.insert(0,"./output/");
    }

    File output(nameOf_outputFile,path_output,{});

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
    string method = argv[3];
    Operation op(argc, argv);

    op.file_vector.push_back(output);
    op.file_vector.push_back(tracking);

    if(op.failure){
        cout<<"Invalid method name.";
        return 0;
    }

    //Check for correct amount of arguments and add arguments to file vector
    for(int i=0;i<op.additionalArgument;i++){
        if(argc<(4+op.additionalArgument)){
            cout<<"Missing argument.";
            return 0;
        }
        int temp = 4 + i;
        string var = argv[temp];
        if(op.isint){
            try{
                op.int_argument = stoi(var);
            }
            catch (...){
                cout<<"Invalid argument, expected number.";
                return 0;
            }
        }
        else{
            string temp_path= var;
            if(!(temp_path.substr(0,6)=="input/")){
                temp_path = var.insert(0,"./input/");
            }

            ifstream temp(temp_path);
            if(!temp.is_open()){
                cout<<"Invalid argument, file does not exist.";
                return 0;
            }
            temp.close();
            File adding(var,temp_path,{});
            adding.readHeader();
            adding.readFile();
            op.file_vector.push_back(adding);
        }

    }



    return 0;
}
