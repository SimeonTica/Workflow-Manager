#include "steps.hpp"

namespace fs = std::filesystem;

std::filesystem::path currentFile2(__FILE__);
std::filesystem::path relative2 = currentFile2.parent_path();

std::string folderPath2 = relative2.string() + "\\outputs";

Step::Step() {

    this->title = "default";
}

Step::Step(std::string title) {

    this->title = title;
}

Step::Step(std::string title, std::string description) {

    this->title = title;
    this->description = description;
}

int Step::getSkipped(){

    return skipped;
}

int Step::getError(){

    return error;
}

bool Step::isNumberIstringstream(const std::string& str) {
    std::istringstream iss(str);
    double val;
    iss >> val;
    return iss.eof() && !iss.fail();
}

void titleStep::execute() {

    std::cout << "Title: " << title << std::endl << "Subtitle: " << subtitle << std::endl;
}

void titleStep::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << title << std::endl << subtitle << std::endl << std::endl;
}

void titleStep::displayStepFunc() {

    std::cout << "Title: " << title << std::endl << "Subtitle: " << subtitle << std::endl;
}

void textStep::execute() {

    std::cout << "Title: " << title << std::endl << "Copy: " << copy << std::endl;
}

void textStep::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << title << std::endl << copy << std::endl << std::endl;
    o.close();
}

void textStep::displayStepFunc() {

    std::cout << "Title: " << title << std::endl << "Copy: " << copy << std::endl;
}

template <>
void inputStep<std::string>::execute() {

    std::cout << description << std::endl;
    std::cout << "Enter input (to skip write :s)" << std::endl;
    std::cin.get();
    std::string temp;
    std::getline(std::cin, temp);
    if(temp != ":s")
        input = temp;
    else if(temp == "\n"){

        error++;
        throw std::string("Please enter a value");
    }
    else{

        skipped++;
        throw std::string("Skipped");
    }
}

template <>
void inputStep<float>::execute() {

    std::cout << description << std::endl;
    std::cout << "Enter input (to skip write :s)" << std::endl;
    std::string temp;
    std::getline(std::cin, temp);
    if(temp != ":s"){

        if(isNumberIstringstream(temp) == true){

            input = std::stof(temp);
        }
        else{
                
                error++;
                throw std::string("Please enter a number");
        }
    }
    else if(temp == "\n"){

        error++;
        throw std::string("Please enter a value");
    }
    else{

        skipped++;
        throw std::string("Skipped");
    }
}

template <>
void inputStep<std::string>::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << input << std::endl << std::endl;
    o.close();
}

template <>
void inputStep<float>::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << input << std::endl << std::endl;
    o.close();
}

template<>
void inputStep<std::string>::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << input << std::endl;
}

template<>
void inputStep<float>::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << input << std::endl;
}

calculusStep::~calculusStep(){
    
        delete nb1;
        delete nb2;
}

void calculusStep::execute() {

    if(operation == "addition") {

        product = (*nb1).input + (*nb2).input;
    } else if(operation == "subtraction") {

        product = (*nb1).input - (*nb2).input;
    } else if (operation == "multiplication") {

        product = (*nb1).input * (*nb2).input;
    } else if (operation == "division") {

        product = (*nb1).input / (*nb2).input;
    } else if (operation == "minimum") {
            
            product = std::min((*nb1).input, (*nb2).input);
    } else if (operation == "maximum") {

        product = std::max((*nb1).input, (*nb2).input);
    } else {

        std::string err = "Invalid operation";
        throw err;
    }

    std::cout << "Result: " << product << std::endl;
}

void calculusStep::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << product << std::endl << std::endl;
    o.close();
}

void calculusStep::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << operation << std::endl;
    std::cout << product << std::endl;
}

void textFileInputStep::execute() {

    std::cout << description << std::endl;
    std::cout << "Enter the name of the file (without extension, write :s to skip)" << std::endl;
    std::cin >> file;

    if(file != ":s")
        writeTxt(file);
    else if(file == "\n"){

        error++;
        throw std::string("Please enter a value");
    }
    else{

        skipped++;
        throw std::string("Skipped");
    }
}

void textFileInputStep::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << this->file + ".txt" << std::endl << std::endl;
    o.close();
}

void textFileInputStep::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << file << std::endl;

    displayTxt(file);

    std::cout << std::endl;
}

void csvFileInputStep::execute() {

    std::cout << description << std::endl;
    std::cout << "Enter the name of the file (without extension, write :s to skip)" << std::endl;
    std::cin >> file;

    if(file != ":s")
        writeCsv(file);
    else if(file == "\n"){

        error++;
        throw std::string("Please enter a value");
    }
    else{

        skipped++;
        throw std::string("Skipped");
    }
}

void csvFileInputStep::writeToFile(std::string file) {

    std::ofstream o(folderPath2 + "\\" + file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << this->file + ".csv" << std::endl << std::endl;
    o.close();
}

void csvFileInputStep::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << file << std::endl;

    displayCsv(file);

    std::cout << std::endl;
}

void displayStep::execute(){
    
    step->displayStepFunc();
}

void outputStep::execute(){

    std::ofstream o(folderPath2 + "\\" + file);

    if(!o.is_open()){
        std::string err = "Cannot open file.";
        throw err;
    }

    o << title << std::endl << description << std::endl << std::endl;

    std::cout << "Flow has been saved to " << file << std::endl;

    o.close();

    for (auto &step: steps) {

        step->writeToFile(file);
    }
}
