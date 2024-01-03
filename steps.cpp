#include "steps.hpp"

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

void titleStep::execute() {

    std::cout << "Title: " << title << std::endl << "Subtitle: " << subtitle << std::endl;
}

void titleStep::writeToFile(std::string file) {

    std::ofstream o(file, std::ios::app);
    
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

    std::ofstream o(file, std::ios::app);
    
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

void inputStep<class T>::execute() {

    std::cout << description << std::endl;
    std::cin >> input;
}

void inputStep<class T>::writeToFile(std::string file) {

    std::ofstream o(file, std::ios::app);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << description << std::endl << input << std::endl << std::endl;
    o.close();
}

void inputStep<class T>::displayStepFunc() {

    std::cout << description << std::endl;
    std::cout << input << std::endl;
}

void calculusStep::execute() {

    nb1.execute();
    nb2.execute();

    if(operation == "addition") {

        product = nb1.input + nb2.input;
    } else if(operation == "subtraction") {

        product = nb1.input - nb2.input;
    } else if (operation == "multiplication") {

        product = nb1.input * nb2.input;
    } else if (operation == "division") {

        product = nb1.input / nb2.input;
    } else if (operation == "minimum") {
            
            product = std::min(nb1.input, nb2.input);
    } else if (operation == "maximum") {

        product = std::max(nb1.input, nb2.input);
    } else {

        std::string err = "Invalid operation";
        throw err;
    }

    std::cout << "Result: " << product << std::endl;
}

void calculusStep::writeToFile(std::string file) {

    std::ofstream o(file, std::ios::app);
    
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
    std::cin >> file;

    writeTxt(file);
}

void textFileInputStep::writeToFile(std::string file) {

    std::ofstream o(file, std::ios::app);
    
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
    std::cin >> file;

    writeCsv(file);
}

void csvFileInputStep::writeToFile(std::string file) {

    std::ofstream o(file, std::ios::app);
    
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

    std::ofstream o(file);
    
    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    o << title << std::endl << description << std::endl;

    o.close();

    for (auto &step: steps) {

        step->writeToFile(file);
    }
}
