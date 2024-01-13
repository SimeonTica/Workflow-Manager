#pragma once

#include "steps.hpp"
#include <chrono>
#include <stdlib.h>

class Flow{

private:
    std::vector<Step *> steps;
    std::string title;
    std::chrono::system_clock::time_point creationTime;
    void addStep(Step *step);
    int started = 0;
    int completed = 0;
    int totalErrors = 0;
    int avgErrors = 0;

public:
    Flow();
    ~Flow();
    std::chrono::system_clock::time_point getCreationTime() const;
    void execute();
    std::string getTitle();
    int getHowManyTimesFlowWasStarted();
    int getHowManyTimesFlowWasCompleted();
    void printAnalytics();
    friend class flowManager;
};