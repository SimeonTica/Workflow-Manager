#include "file.hpp"

void File::displayCsv(std::string file){

    std::ifstream f(file);

    if(!f.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::stringstream ss;
    std::string line;
    while(std::getline(f, line)){
        ss << line;
        std::string token;
        while(std::getline(ss, token, ',')){
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }
}

void File::displayTxt(std::string file){

    std::ifstream f(file);

    if(!f.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::string line;
    while(std::getline(f, line)){

        std::cout << line << std::endl;
    }
}

void File::writeCsv(std::string file){

    std::ofstream o(file + ".csv");

    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::cout << "Enter CSV information line by line, each field separated by space (write :q to finish the file)" << std::endl;
    std::stringstream ss;
    std::string line, token, lineToAdd;
    std::vector<std::string> vectorLine;
    std::cin >> line;
    while(line != ":q"){

        ss << line;
        while(std::getline(ss, token, ' '))
            vectorLine.push_back(token);
        
        for (int i = 0; i < vectorLine.size() - 1; i++)
            lineToAdd += vectorLine[i] + ",";
        
        lineToAdd += vectorLine.back() + "\n";
        
        o << lineToAdd;
        std::cin >> line;
    }

}

void File::writeTxt(std::string file){

    std::ofstream o(file + ".txt");

    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::cout << "Write data line by line (write :q to finish the file)" << std::endl;

    std::string line;
    std::cin >> line;

    while(line != ":q"){

        o << line << "\n";
        std::cin >> line;
    }
}
