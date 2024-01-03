#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>

class File{

protected:
    void displayCsv(std::string file);
    void displayTxt(std::string file);
    void writeCsv(std::string file);
    void writeTxt(std::string file);
};