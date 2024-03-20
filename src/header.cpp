#include "header.h"

using namespace std;
//File
File::File() {
    head={};
    address = "";
    pixel_vector={};
    filename = "Default";
}

File::File(string filename, string address, Header head) {
    this->filename = filename;
    this->head = head;
    this->address = address;
    pixel_vector = {};
}

void File::readHeader() {
    //SETUP
    Header header;
    ifstream tempFile(this->address,std::ios::binary);
    //char idLength
    tempFile.read(&header.idLength,1);
    //char colorMapType
    tempFile.read(&header.colorMapType,1);
    //char dataTypeCode
    tempFile.read(&header.dataTypeCode,1);
    //short colorMapOrigin
    tempFile.read(reinterpret_cast<char*>(&header.colorMapOrigin),2);
    //short colorMapLength
    tempFile.read(reinterpret_cast<char*>(&header.colorMapLength),2);
    //char colorMapDepth
    tempFile.read(&header.colorMapDepth,1);
    //short xOrigin
    tempFile.read(reinterpret_cast<char*>(&header.xOrigin),2);
    //short yOrigin
    tempFile.read(reinterpret_cast<char*>(&header.yOrigin),2);
    //short width
    tempFile.read(reinterpret_cast<char*>(&header.width),2);
    //short height
    tempFile.read(reinterpret_cast<char*>(&header.height),2);
    //char bitsPerPixel
    tempFile.read(&header.bitsPerPixel,1);
    //char imageDescriptor
    tempFile.read(&header.imageDescriptor,1);

    this->head=header;
}

void File::printHeader() {
    cout<<"idLength: "<<(int)head.idLength<<"\ncolorMapType: "<<(int)head.colorMapType<<"\ndataTypeCode: "<<(int)head.dataTypeCode;
    cout<<"\ncolorMapOrigin: "<<head.colorMapOrigin<<"\ncolorMapLength: "<<head.colorMapLength<<"\ncolorMapDepth: ";
    cout<<(int)head.colorMapDepth<<"\nxOrigin: "<<head.xOrigin<<"\nyOrigin: "<<head.yOrigin;
    cout<<"\nwidth: "<<head.width<<"\nheight: "<<head.height<<"\nbitsPerPixel: "<<(int)head.bitsPerPixel;
    cout<<"\nimageDescriptor: "<<(int)head.imageDescriptor;
}

void File::readFile() {
    ifstream tempFile(this->address,std::ios::binary);
    tempFile.ignore(18);
    for(int i=0;i<(this->head.height * this->head.width);i++){
        pixel pix;
        char B, G, R;
        tempFile.read(&B,1);
        tempFile.read(&G,1);
        tempFile.read(&R,1);
        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);
        this->pixel_vector.push_back(pix);
    }

}

void File::printFile(){
    for(int i=0;i<(this->head.height * this->head.width);i++){
        cout<< "B: " <<(int)this->pixel_vector.at(i).BGR.at(0);
        cout<<" G: "<<(int)this->pixel_vector.at(i).BGR.at(1);
        cout<< " R: "<<(int)this->pixel_vector.at(i).BGR.at(2);
        cout<<endl;
    }
}

void File::writeFile(std::string filename) {
    filename.insert(0,"./output/");
    filename.append(".tga");
    ofstream tempFile(filename, std::ios::binary);
    //print header
        tempFile.write(reinterpret_cast<const char*>(&this->head.idLength),1);
        tempFile.write(reinterpret_cast<const char*>(&this->head.colorMapType),1);
        tempFile.write(reinterpret_cast<const char*>(&this->head.dataTypeCode),1);
        tempFile.write(reinterpret_cast<const char*>(&this->head.colorMapOrigin),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.colorMapLength),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.colorMapDepth),1);
        tempFile.write(reinterpret_cast<const char*>(&this->head.xOrigin),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.yOrigin),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.width),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.height),2);
        tempFile.write(reinterpret_cast<const char*>(&this->head.bitsPerPixel),1);
        tempFile.write(reinterpret_cast<const char*>(&this->head.imageDescriptor),1);
    //print data
    for(int i=0;i<(this->head.height * this->head.width);i++){
        unsigned char B = this->pixel_vector.at(i).BGR.at(0);
        unsigned char G = this->pixel_vector.at(i).BGR.at(1);
        unsigned char R = this->pixel_vector.at(i).BGR.at(2);
        tempFile.write(reinterpret_cast<const char*>(&B),1);
        tempFile.write(reinterpret_cast<const char*>(&G),1);
        tempFile.write(reinterpret_cast<const char*>(&R),1);
    }

}


//OPERATION
float Operation::notOver(float value) {
    float temp;
    if (value>255){
        temp = 255;
    }
    else if(value<=0){
        temp = 0;
    }
    else{
        temp = value;
    }
    return temp;
}


File Operation::Multiply(File &top, File &bottom) {
    // READING

    top.readHeader();
    top.readFile();
    bottom.readHeader();
    bottom.readFile();

    // New File
    File tempFile("Multiply","./output/Multiply1",{});
    tempFile.head = top.head;

    // Math
    for(int i=0;i<(top.head.height * bottom.head.width);i++){
        File::pixel pix;
        unsigned char B,G,R;
        B = ((((((float)(top.pixel_vector.at(i).BGR.at(0)))/255)*((float(bottom.pixel_vector.at(i).BGR.at(0))/255))))*255) + .5;
        G = ((((((float)(top.pixel_vector.at(i).BGR.at(1)))/255)*((float(bottom.pixel_vector.at(i).BGR.at(1))/255))))*255) + .5;
        R = ((((((float)(top.pixel_vector.at(i).BGR.at(2)))/255)*((float(bottom.pixel_vector.at(i).BGR.at(2))/255))))*255) + .5;

        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);

        tempFile.pixel_vector.push_back(pix);
    }
    return tempFile;
}

File Operation::Subtract(File &top, File &bottom) {
    // READING
    if(top.filename != "except"){
        top.readHeader();
        top.readFile();
    }
    bottom.readHeader();
    bottom.readFile();


    // New File
    File tempFile("Subtract","./output/Subtract1",{});
    tempFile.head = top.head;

    // Math
    for(int i=0;i<(top.head.height * bottom.head.width);i++){
        File::pixel pix;
        unsigned char B,G,R;
        int temp;
        //B
        temp = (int)top.pixel_vector.at(i).BGR.at(0) - (int)bottom.pixel_vector.at(i).BGR.at(0);
        if(temp<0){
            temp = 0;
            B = (unsigned char)temp;
        }
        else if(temp>255){
            temp =255;
            B=(unsigned char)temp;
        }
        else{
            B=(unsigned char)temp;
        }

        //G
        temp = (int)top.pixel_vector.at(i).BGR.at(1) - (int)bottom.pixel_vector.at(i).BGR.at(1);
        if(temp<0){
            temp = 0;
            G = (unsigned char)temp;
        }
        else if(temp>255){
            temp =255;
            G=(unsigned char)temp;
        }
        else{
            G=(unsigned char)temp;
        }
        //R
        temp = (int)top.pixel_vector.at(i).BGR.at(2) - (int)bottom.pixel_vector.at(i).BGR.at(2);
        if(temp<0){
            temp = 0;
            R = (unsigned char)temp;
        }
        else if(temp>255){
            temp =255;
            R=(unsigned char)temp;
        }
        else{
            R=(unsigned char)temp;
        }
        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);

        tempFile.pixel_vector.push_back(pix);
    }
    return tempFile;
}

File Operation::Screen(File &top, File &bottom) {
    // New File
    File tempFile("Screen","./output/Screen",{});
    tempFile.head = top.head;

    for(int i=0;i<(top.head.height * bottom.head.width);i++){
        File::pixel pix;
        unsigned char B,G,R;
        //B
        float temp = .5+(255*(1-(((1-(float)top.pixel_vector.at(i).BGR.at(0)/255))*(1-(float)bottom.pixel_vector.at(i).BGR.at(0)/255))));
        if (abs(temp)> 255){
            temp =255;
            B= (unsigned char)temp;
        }
        else if(abs(temp)<0){
            temp = 0;
            B = (unsigned char)temp;

        }
        else{
            B = (unsigned char) temp;
        }

        //G
        temp = .5+(255*(1-((1-((float)top.pixel_vector.at(i).BGR.at(1)/255)))*(1-((float)bottom.pixel_vector.at(i).BGR.at(1)/255))));
        if (abs(temp)> 255){
            temp = 255;
            G = (unsigned char)temp;
        }
        else if(abs(temp)<0){
            temp = 0;
            G = (unsigned char)temp;
        }
        else{
            G = (unsigned char) temp;
        }

        //R
        temp = .5+(255*(1-((1-(float)top.pixel_vector.at(i).BGR.at(2)/255))*(1-(float)bottom.pixel_vector.at(i).BGR.at(2)/255)));
        if (abs(temp)> 255){
            temp = 255;
            R = (unsigned char)temp;
        }
        else if(abs(temp)<0){
            temp = 0;
            R = (unsigned char)temp;
        }
        else{
            R = (unsigned char) temp;
        }


        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);
        tempFile.pixel_vector.push_back(pix);

    }
    return tempFile;
}

File Operation::Overlay(File &top, File &bottom) {
    File result("result","./output/Overlay",{});
    result.head = top.head;
    for (int i = 0; i < (top.head.height * bottom.head.width); i++) {
        File::pixel pix;
        unsigned char B,G,R;
        //B
        if((((float)bottom.pixel_vector.at(i).BGR.at(0))/255) > .5f){
            float temp = .5+(255*(1-(2*(((1-(float)top.pixel_vector.at(i).BGR.at(0)/255))*(1-(float)bottom.pixel_vector.at(i).BGR.at(0)/255)))));
            B=(unsigned char)temp;
        }
        else{
            float temp = .5f+(255*(2*((float)top.pixel_vector.at(i).BGR.at(0)/255)*((float)bottom.pixel_vector.at(i).BGR.at(0)/255)));
            temp = notOver(temp);
            B=(unsigned char)temp;
        }

        // G
        if(((float)(bottom.pixel_vector.at(i).BGR.at(1))/255) > .5f){
            float temp = .5f+(255*(1-(2*(((1-((float)top.pixel_vector.at(i).BGR.at(1)/255)))*(1-((float)bottom.pixel_vector.at(i).BGR.at(1)/255))))));
            temp = notOver(temp);
            G=(unsigned char)temp;
        }
        else{
            float temp = .5f+(255*(2*((float)top.pixel_vector.at(i).BGR.at(1)/255)*((float)bottom.pixel_vector.at(i).BGR.at(1)/255)));
            temp = notOver(temp);
            G=(unsigned char)temp;
        }

        // R
        if(((float)(bottom.pixel_vector.at(i).BGR.at(2))/255) > .5f){
            float temp = .5f+(255*(1-(2*(((1-((float)top.pixel_vector.at(i).BGR.at(2)/255)))*(1-((float)bottom.pixel_vector.at(i).BGR.at(2)/255))))));
            temp = notOver(temp);
            R =(unsigned char)temp;
        }
        else{
            float temp = .5f+(255*(2*((float)top.pixel_vector.at(i).BGR.at(2)/255)*((float)bottom.pixel_vector.at(i).BGR.at(2)/255)));
            temp = notOver(temp);
            R =(unsigned char)temp;
        }

        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);
        result.pixel_vector.push_back(pix);
    }
    return result;
}

//TASKS
void Operation::Task1() {
    File layer1("layer1","./input/layer1.tga",{});
    File pattern1("pattern1","./input/pattern1.tga",{});
    File temp = this->Multiply(layer1,pattern1);
    temp.writeFile("part1");
}

void Operation::Task2(){
    File layer2("layer2","./input/layer2.tga",{});
    File car("car","./input/car.tga",{});
    Operation op;
    File temp = this->Subtract(car, layer2);
    temp.writeFile("part2");
}

void Operation::Task3(){
    File layer1("layer1","./input/layer1.tga",{});
    File pattern2("pattern2","./input/pattern2.tga",{});
    layer1.readHeader();
    layer1.readFile();
    pattern2.readHeader();
    pattern2.readFile();
    File afterMult = this->Multiply(layer1,pattern2);

    File text("text","./input/text.tga",{});
    text.readHeader();
    text.readFile();

    File result = this->Screen(afterMult,text);
    result.writeFile("part3");
}

void Operation::Task4(){
    File layer2("layer2","./input/layer2.tga",{});
    layer2.readHeader();
    layer2.readFile();
    File circles("circles","./input/circles.tga",{});
    circles.readHeader();
    circles.readFile();
    File pattern2("pattern1","./input/pattern2.tga",{});

    File temp = Multiply(circles,layer2);
    temp.filename = "except";

    File result = Subtract(temp,pattern2);
    result.writeFile("part4");
}

void Operation::Task5(){
    //top
    File layer1("layer1","./input/layer1.tga",{});
    layer1.readHeader();
    layer1.readFile();
    //bottom
    File pattern1("pattern1","./input/pattern1.tga",{});
    pattern1.readHeader();
    pattern1.readFile();

    File temp = Overlay(layer1,pattern1);
    temp.writeFile("part5");
}

void Operation::Task6() {
    File car("car", "./input/car.tga", {});
    car.readHeader();
    car.readFile();
    for (int i = 0; i < (car.head.height * car.head.width); i++) {
        int temp = (int)car.pixel_vector.at(i).BGR.at(1) + 200;
        if (temp>255){
            temp= 255;
        }
        car.pixel_vector.at(i).BGR.at(1) = (unsigned char)temp;
    }
    car.writeFile("part6");
}

void Operation::Task7(){
    File car("car", "./input/car.tga", {});
    car.readHeader();
    car.readFile();
    for (int i = 0; i < (car.head.height * car.head.width); i++) {
        float temp = (((((float)(car.pixel_vector.at(i).BGR.at(2)))/255)*4)*255)+.5f;
        if(temp>255){
            temp =255;
        }
        car.pixel_vector.at(i).BGR.at(2) = (unsigned char)temp;
        car.pixel_vector.at(i).BGR.at(0) = (unsigned char)0;
    }
    car.writeFile("part7");
}

void Operation::Task8(){
    File car("car","./input/car.tga",{});
    car.readHeader();
    car.readFile();
    File blue("blue","./ouput/blue.tga",{});
    File red("red","./ouput/red.tga",{});
    File green("green","./ouput/green.tga",{});
    blue.head = car.head;
    red.head = car.head;
    green.head = car.head;

    for (int i = 0; i < (car.head.height * car.head.width); i++) {
        File::pixel red_pixel;
        File::pixel blue_pixel;
        File::pixel green_pixel;
        //Blue
        blue_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(0));
        blue_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(0));
        blue_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(0));

        //Green
        green_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(1));
        green_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(1));
        green_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(1));

        //Red
        red_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(2));
        red_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(2));
        red_pixel.BGR.push_back(car.pixel_vector.at(i).BGR.at(2));

        //Files
        blue.pixel_vector.push_back(blue_pixel);
        green.pixel_vector.push_back(green_pixel);
        red.pixel_vector.push_back(red_pixel);
    }
    blue.writeFile("part8_b");
    green.writeFile("part8_g");
    red.writeFile("part8_r");
}

void Operation::Task9(){
    File blue("blue","./input/layer_blue.tga",{});
    blue.readHeader();
    blue.readFile();
    File green("green","./input/layer_green.tga",{});
    green.readHeader();
    green.readFile();
    File red("red","./input/layer_red.tga",{});
    red.readHeader();
    red.readFile();

    File final("final","put/final.tga",{});
    final.head = blue.head;

    for (int i = 0; i < (blue.head.height * blue.head.width); i++) {
        File::pixel pixel;
        unsigned char B, G, R;
        B = blue.pixel_vector.at(i).BGR.at(0);
        G = green.pixel_vector.at(i).BGR.at(0);
        R = red.pixel_vector.at(i).BGR.at(0);

        pixel.BGR.push_back(B);
        pixel.BGR.push_back(G);
        pixel.BGR.push_back(R);

        final.pixel_vector.push_back(pixel);

    }
    final.writeFile("part9");
}

void Operation::Task10() {
    File text2("text2", "./input/text2.tga", {});
    text2.readHeader();
    text2.readFile();
    File opposite("opposite","./ouptut/opposite.tga",{});
    opposite.head = text2.head;

    for (int i = ((text2.head.height * text2.head.width) -1); i >= 0 ; i--) {
        unsigned char B,G,R;
        File::pixel pix;

        B = text2.pixel_vector.at(i).BGR.at(0);
        G = text2.pixel_vector.at(i).BGR.at(1);
        R = text2.pixel_vector.at(i).BGR.at(2);
        pix.BGR.push_back(B);
        pix.BGR.push_back(G);
        pix.BGR.push_back(R);
        opposite.pixel_vector.push_back(pix);
    }

    opposite.writeFile("part10");
}