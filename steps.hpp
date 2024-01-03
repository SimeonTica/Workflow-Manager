#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "file.hpp"

class Step{

protected:
    std::string title;
    std::string description;

public:
    Step();
    Step(std::string title);
    Step(std::string title, std::string description);

    virtual void execute() = 0;
    virtual void writeToFile(std::string file) = 0;
    virtual void displayStepFunc() = 0;
};

class titleStep: public Step{

private:
    std::string subtitle;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    titleStep(std::string title, std::string subtitle) : Step(title), subtitle(subtitle) {};
    void execute() override;
};

class textStep: public Step{

private:
    std::string copy;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    textStep(std::string title, std::string copy) : Step(title), copy(copy) {};
    void execute() override;
};

template <class T>
class inputStep: public Step{

private:
    T input;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    inputStep(std::string description) : Step("", description) {};
    void execute() override;
    friend class calculusStep;
};

class calculusStep: public Step{

private:
    inputStep<float> nb1;
    inputStep<float> nb2;

    std::string operation;
    float product;

    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    calculusStep(std::string opDescription, std::string description1, std::string description2, std::string operation) : Step("", opDescription), nb1(description1), nb2(description2), operation(operation) {};
    void execute() override;
};

class textFileInputStep: public Step, public File{

private:
    std::string file;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    textFileInputStep(std::string description) : Step("", description) {};
    void execute() override;
};

class csvFileInputStep: public Step, public File{

private:
    std::string file;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    csvFileInputStep(std::string description) : Step("", description) {};
    void execute() override;
};

class displayStep: public Step, public File{

private:
    Step *step;
    void writeToFile(std::string file) override {};
    void displayStepFunc() override {};

public:
    displayStep(Step *step) : step(step) {};
    void execute() override;
};

class outputStep: public Step{

private:
    std::vector<Step *> steps;
    std::string file;
    void writeToFile(std::string file) override {};
    void displayStepFunc() override {};

public:
    outputStep(std::vector<Step *> steps, std::string title, std::string description) : steps(steps), Step(title, description) {};
    void execute() override;
};