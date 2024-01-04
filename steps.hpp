#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "file.hpp"

class Step{

protected:
    std::string title;
    std::string description;
    int skipped = 0;
    int error = 0;
    bool isNumberIstringstream(const std::string& str);

public:
    Step();
    Step(std::string title);
    Step(std::string title, std::string description);

    virtual void execute() = 0;
    virtual void writeToFile(std::string file) = 0;
    virtual void displayStepFunc() = 0;

    int getSkipped();
    int getError();
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
    getSkipped();
    friend class calculusStep;
};

class calculusStep: public Step{

private:
    inputStep<float> *nb1;
    inputStep<float> *nb2;

    std::string operation;
    float product;

    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    calculusStep(std::string opDescription, std::string operation, inputStep<float> *nb1, inputStep<float> *nb2) : Step("", opDescription), operation(operation), nb1(nb1), nb2(nb2) {};
    void execute() override;
};

class textFileInputStep: public Step, public File{

private:
    std::string file;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    textFileInputStep(std::string description) : Step("", description) {};
    int getSkipped();
    void execute() override;
};

class csvFileInputStep: public Step, public File{

private:
    std::string file;
    void writeToFile(std::string file) override;
    void displayStepFunc() override;

public:
    csvFileInputStep(std::string description) : Step("", description) {};
    int getSkipped();
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
    outputStep(std::vector<Step *> steps, std::string title, std::string description) : steps(steps), file(title), Step(title, description) {};
    void execute() override;
};