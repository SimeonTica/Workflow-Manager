#include "flow.hpp"

std::chrono::system_clock::time_point Flow::getCreationTime() const {
        return creationTime;
    }

Flow::Flow() : creationTime(std::chrono::system_clock::now()) {

    bool run = 1;
    int option;

    std::cin.get();
    std::cout << "Enter flow title" << std::endl;
    std::getline(std::cin, title);

    while (run)
    {
        std::cout << "Step options:" << std::endl;

        std::cout << "1. Title: add a header for the next components" << std::endl;
        std::cout << "2. Text: add a component of plain text" << std::endl;
        std::cout << "3. Input: component that lets the user add numerical or text input" << std::endl;
        std::cout << "4. Calculus: component that allows you to define different calculations" << std::endl;
        std::cout << "5. Text file input: allows you to write a text file and save it" << std::endl;
        std::cout << "6. Csv file input: allows you to write a csv file and save it" << std::endl;
        std::cout << "7. Display step: component that logs to the console a certain step" << std::endl;
        std::cout << "8. Output step: saves the flow to a file" << std::endl;
        std::cout << "9. End flow creation" << std::endl;

        std::cin >> option;

        switch (option)
        {
            case 1:
            {
                std::string title;
                std::string subtitle;
                std::cout << "Enter title" << std::endl;
                std::cin.get();
                std::getline(std::cin, title);
                std::cout << "Enter subtitle" << std::endl;
                std::getline(std::cin, subtitle);
                Step *step = new titleStep(title, subtitle);
                addStep(step);
                break;
            }
            case 2:
            {
                std::string title;
                std::string copy;
                std::cin.get();
                std::cout << "Enter title" << std::endl;
                std::getline(std::cin, title);
                std::cout << "Enter copy" << std::endl;
                std::getline(std::cin, copy);
                Step *step = new textStep(title, copy);
                addStep(step);
                break;
            }
            case 3:
            {
                case_3:
                std::string description;
                int type;
                Step *step;

                std::cout << "Enter type (1 = text, 2 = float)" << std::endl;
                std::cin >> type;
                if(type != 1 && type != 2){

                    char answer;
                    std::cout << "Invalid type" << std::endl;
                    std::cout << "Do you want to try again? (y/n)" << std::endl;
                    std::cin >> answer;
                    if(answer == 'y')
                        goto case_3;
                    else
                        break;
                }
                std::cin.get();
                std::cout << "Enter description" << std::endl;
                std::getline(std::cin, description);
                if (type == 1)
                {
                    step = new inputStep<std::string>(description);
                }
                else if (type == 2)
                {
                    step = new inputStep<float>(description);
                }
                
                addStep(step);
                break;
            }
            case 4:
            {
                std::string opDescription;
                std::string calculus;
                int first, second;

                std::cout << "Enter operation description" << std::endl;
                std::cin.get();
                std::getline(std::cin, opDescription);
                std::cout << "Enter the first step index to be taken in consideration" << std::endl;
                std::cin >> first;
                std::cout << "Enter the second step index to be taken in consideration" << std::endl;
                std::cin >> second;

                calculus:
                try{
                    std::cout << "Enter calculus type" << std::endl;
                    std::cin.get();
                    std::getline(std::cin, calculus);

                    if(calculus != "addition" && calculus != "subtraction" && calculus != "multiplication" && calculus != "division" && calculus != "minimum" && calculus != "maximum")
                        throw std::string("Invalid calculus type");


                    inputStep<float> *nb1 = dynamic_cast<inputStep<float> *>(steps[first - 1]);
                    inputStep<float> *nb2 = dynamic_cast<inputStep<float> *>(steps[second - 1]);
                    Step *step = new calculusStep(opDescription, calculus, nb1, nb2);
                    addStep(step);
                }
                catch(std::string err){
                    if (err == "Invalid calculus type")
                        goto calculus;
                }
                break;
            }
            case 5:
            {
                std::string description;
                std::cin.get();
                std::cout << "Enter description" << std::endl;
                std::getline(std::cin, description);
                Step *step = new textFileInputStep(description);
                addStep(step);
                break;
            }
            case 6:
            {
                std::string description;
                std::cin.get();
                std::cout << "Enter description" << std::endl;
                std::getline(std::cin, description);
                Step *step = new csvFileInputStep(description);
                addStep(step);
                break;
            }
            case 7:
            {
                int stepNumber;
                std::cout << "Enter step number you want displayed" << std::endl;
                std::cin >> stepNumber;
                Step *step = steps[stepNumber - 1];
                Step *displayStepinstance = new displayStep(step);
                addStep(displayStepinstance);
                break;
            }
            case 8:
            {
                std::string title, description;
                std::vector<Step *> stepsToAdd;
                std::cin.get();
                std::cout << "Enter title" << std::endl;
                std::getline(std::cin, title);
                std::cout << "Enter description" << std::endl;
                std::getline(std::cin, description);
                std::cout << "Enter step numbers you want to add to the output step (write -1 to stop)" << std::endl;
                int stepNumber;
                std::cin >> stepNumber;
                while (stepNumber != -1)
                {
                    stepsToAdd.push_back(steps[stepNumber - 1]);
                    std::cin >> stepNumber;
                }
                Step *step = new outputStep(stepsToAdd, title, description);
                addStep(step);
                break;
            }
            case 9:
            {
                run = 0;
                break;
            }
        }
    }
}

void Flow::addStep(Step *step) {

    steps.push_back(step);
}

void Flow::execute(){
    
    started++;

    for (auto &step: steps) {

        retry:
        try
        {
            step->execute();   
        }
        catch(std::string e)
        {
            std::cout << e << '\n';
            if(e == "Please enter a value" || e == "Please enter a number"){
                goto retry;
            }
            else if(e != "Step skipped"){
                throw e;
            }
        }
    }
    completed++;
}

std::string Flow::getTitle() {
    return title;
}

int Flow::getHowManyTimesFlowWasStarted() {
    return started;
}

int Flow::getHowManyTimesFlowWasCompleted() {
    return completed;
}

void Flow::printAnalytics(){

    std::cout << "Flow title: " << title << std::endl;
    std::cout << "Flow created at " << std::chrono::system_clock::to_time_t(creationTime) << std::endl;
    std::cout << "Flow started " << started << " times" << std::endl;
    std::cout << "Flow completed " << completed << " times" << std::endl;

    int i = 1;

    for(auto& step: steps){

        std::cout << "Step " << i << " has been skipped " << step->getSkipped() << " times" << std::endl;
        std::cout << "Step " << i << " had " << step->getError() << " errors" << std::endl;
        totalErrors += step->getError();
        i++;
    }

    avgErrors = totalErrors / completed;

    std::cout << "Average no errors on flow run: " << avgErrors << std::endl;

}