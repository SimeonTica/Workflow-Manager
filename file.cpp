#include "file.hpp"

namespace fs = std::filesystem;

std::filesystem::path currentFile(__FILE__);
std::filesystem::path relative = currentFile.parent_path();

std::string folderPath = relative.string() + "\\files";

void File::displayCsv(std::string file){

    std::string path = folderPath + "\\" + file + ".csv";

    std::ifstream f(path);

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
        ss.clear();
    }
}

void File::displayTxt(std::string file){

    std::string path = folderPath + "\\" + file + ".txt";

    std::ifstream f(path);

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

    std::string path = folderPath + "\\" + file;

    std::ofstream o(path + ".csv");

    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::cout << "Enter CSV information line by line, each field separated by space (write :q to finish the file)" << std::endl;
    std::stringstream ss;
    std::string line, token;
    std::vector<std::string> vectorLine;
    std::cin.get();
    std::getline(std::cin, line);
    while(line != ":q"){

        std::string lineToAdd = "";

        ss << line;

        while(std::getline(ss, token, ' '))
            vectorLine.push_back(token);
        
        int k = 0;

        for (int i = 0; i < vectorLine.size() - 1; i++){

            lineToAdd += vectorLine[i] + ",";
            k++;
        }
        
        lineToAdd += vectorLine[k] + "\n";
        
        vectorLine.clear();
        line = "";
        ss.clear();

        o << lineToAdd;
        std::getline(std::cin, line);
    }

}

void File::writeTxt(std::string file){

    std::string path = folderPath + "\\" + file;

    std::ofstream o(path + ".txt");

    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    std::cout << "Write data line by line (write :q to finish the file)" << std::endl;

    std::string line;
    std::cin.get();
    std::getline(std::cin, line);

    while(line != ":q"){

        o << line << "\n";
        std::getline(std::cin, line);
    }
}
