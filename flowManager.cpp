#include "flowManager.hpp"

flowManager::flowManager(){
    std::cout << "Welcome to flow manager!" << std::endl;

    bool run = 1;
    int option;
    while(run){
        std::cout << "Flow options:" << std::endl;

        std::cout << "1. Create flow" << std::endl;
        std::cout << "2. Display flows titles" << std::endl;
        std::cout << "3. Execute flow" << std::endl;
        std::cout << "4. Delete flow" << std::endl;
        std::cout << "5. Save flow" << std::endl;
        std::cout << "6. Load flow" << std::endl;
        std::cout << "7. Exit" << std::endl;

        std::cin >> option;

        switch (option)
        {
            case 1:
            {
                createFlow();
                break;
            }
            case 2:
            {
                displayFlowsTitles();
                break;
            }
            case 3:
            {
                std::string title;
                std::cin.get();
                std::cout << "Enter flow title" << std::endl;
                std::getline(std::cin, title);
                executeFlow(title);
                break;
            }
            case 4:
            {
                std::string title;
                std::cout << "Enter flow title" << std::endl;
                std::cin >> title;
                deleteFlow(title);
                break;
            }
            case 5:
            {
                std::string file;
                std::cout << "Enter file name" << std::endl;
                std::cin >> file;
                // saveFlow(file);
                break;
            }
            case 6:
            {
                std::string file;
                std::cout << "Enter file name" << std::endl;
                std::cin >> file;
                // loadFlow(file);
                break;
            }
            case 7:
            {
                run = 0;
                break;
            }
            default:
            {
                std::cout << "Invalid option" << std::endl;
                break;
            }
        }
    }
}

void flowManager::createFlow(){
    Flow *flow = new Flow();
    flows.push_back(flow);
}

void flowManager::displayFlowsTitles(){
    for (int i = 0; i < flows.size(); i++)
    {
        std::cout << flows[i]->getTitle() << std::endl;
    }
}

void flowManager::executeFlow(std::string title){
    for (int i = 0; i < flows.size(); i++)
    {
        if (flows[i]->getTitle() == title)
        {
            flows[i]->execute();
            return;
        }
    }
    throw std::string("Flow not found");
}

void flowManager::deleteFlow(std::string title){
    for (int i = 0; i < flows.size(); i++)
    {
        if (flows[i]->getTitle() == title)
        {
            free(flows[i]);
            flows.erase(flows.begin() + i);
            return;
        }
    }
    throw std::string("Flow not found");
}