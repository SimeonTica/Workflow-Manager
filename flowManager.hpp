#pragma once

#include "flow.hpp"
#include <vector>

class flowManager{

private:
    std::vector<Flow *> flows;
public:
    flowManager();
    void createFlow();
    void displayFlowsTitles();
    void executeFlow(std::string title);
    void deleteFlow(std::string title);
    void printFlowAnalytics(std::string title);
};