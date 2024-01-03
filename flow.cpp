#include "flow.hpp"

std::chrono::system_clock::time_point Flow::getCreationTime() const {
        return creationTime;
    }

Flow::Flow() : creationTime(std::chrono::system_clock::now()) {

    bool run = 1;
    int option;

    std::cout << "Enter flow title" << std::endl;
    std::getline(std::cin, title);

    while (run)
    {
        std::cout << "Step options:" << std::endl;

        std::cout << "1. Title" << std::endl;
        std::cout << "2. Text" << std::endl;
        std::cout << "3. Input" << std::endl;
        std::cout << "4. Calculus" << std::endl;
        std::cout << "5. Text file input" << std::endl;
        std::cout << "6. Csv file input" << std::endl;
        std::cout << "7. Display step" << std::endl;
        std::cout << "8. Output step" << std::endl;
        std::cout << "9. End flow creation creation" << std::endl;

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
                std::string description;
                int type;
                Step *step;

                std::cout << "Enter type (1 = text, 2 = float)" << std::endl;
                std::cin >> type;
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
                else
                {
                    std::cout << "Invalid type" << std::endl;
                }
                
                addStep(step);
                break;
            }
            case 4:
            {
                std::string opDescription, description1, description2;
                std::string calculus;
                std::cout << "Enter operation description" << std::endl;
                std::cin.get();
                std::getline(std::cin, opDescription);
                std::cout << "Enter first number's description" << std::endl;
                std::getline(std::cin, description1);
                std::cout << "Enter second number's description" << std::endl;
                std::getline(std::cin, description2);

                calculus:
                try{
                    std::cout << "Enter calculus type" << std::endl;
                    std::getline(std::cin, calculus);

                    if(calculus != "addition" && calculus != "subtraction" && calculus != "multiplication" && calculus != "division" && calculus != "minimum" && calculus != "maximum")
                        throw std::string("Invalid calculus type");

                    Step *step = new calculusStep(opDescription, description1, description2, calculus);
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
};

void Flow::addStep(Step *step) {

    steps.push_back(step);
}

void Flow::execute(){
    
    for (auto &step: steps) {
        step->execute();
    }
}