#pragma once

#include "steps.hpp"
#include <chrono>

class Flow{

private:
    std::vector<Step *> steps;
    std::string title;
    std::chrono::system_clock::time_point creationTime;
    void addStep(Step *step);

public:
    Flow();
    std::chrono::system_clock::time_point getCreationTime() const;
    void execute();
};