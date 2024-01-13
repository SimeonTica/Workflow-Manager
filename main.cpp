#include <iostream>
#include "flowManager.hpp"
#include <filesystem>

int main(){

    flowManager *flowMan = new flowManager();

    free(flowMan);
    return 0;

}