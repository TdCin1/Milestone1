#include "header.h"
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]){
    cout<<"first ran"<<endl;
    Operation op;
    if(strcmp(argv[1],"0")==0){
        cout<<"hello";
    }

    if (strcmp(argv[1],"1")==0){
        cout<<"TASK1";
        op.Task1();
    }
    else if(strcmp(argv[1],"2")==0){
        op.Task2();
    }
    else if(strcmp(argv[1],"3")==0){
        op.Task3();
    }
    else if(strcmp(argv[1],"4")==0){
        op.Task4();
    }
    else if(strcmp(argv[1],"5")==0){
        op.Task5();
    }
    else if(strcmp(argv[1],"6")==0){
        op.Task6();
    }
    else if(strcmp(argv[1],"7")==0){
        op.Task7();
    }
    else if(strcmp(argv[1],"8")==0){
        op.Task8();
    }
    else if(strcmp(argv[1],"9")==0){
        op.Task9();
    }
    else if(strcmp(argv[1],"10")==0){
        op.Task10();
    }

    return 0;
}
