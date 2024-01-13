#include "flowManager.hpp"

namespace fs = std::filesystem;

std::filesystem::path currentFile1(__FILE__);
std::filesystem::path relative1 = currentFile1.parent_path();

std::string folderPath1 = relative1.string() + "\\saves";

flowManager::flowManager(){
    std::cout << "Welcome to flow manager!" << std::endl;

    bool run = 1;
    int option;
    while(run){
        system("cls");
        std::cout << "Flow options:" << std::endl;
        std::cout << "1. Create flow" << std::endl;
        std::cout << "2. Display flows titles" << std::endl;
        std::cout << "3. Execute flow" << std::endl;
        std::cout << "4. Delete flow" << std::endl;
        std::cout << "5. Print flow analytics" << std::endl;
        std::cout << "6. Exit" << std::endl;

        std::cin >> option;

        switch (option)
        {
            case 1:
            {
                system("cls");
                try{
                createFlow();
                }
                catch(std::string err){
                    std::cout << err << std::endl;
                    std::cout << "Press enter to continue" << std::endl;
                    std::cin.get();
                }
                break;
            }
            case 2:
            {
                system("cls");
                displayFlowsTitles();
                std::cout << std::endl << "Press enter to continue" << std::endl;
                std::cin.get();
                std::cin.get();
                break;
            }
            case 3:
            {
                system("cls");
                std::string title;
                std::cin.get();
                std::cout << "Enter flow title" << std::endl;
                std::getline(std::cin, title);
                try{
                executeFlow(title);
                }
                catch(std::string err){
                    std::cout << err << std::endl;
                    std::cout << "Press enter to continue" << std::endl;
                    std::cin.get();
                }
                break;
            }
            case 4:
            {
                system("cls");
                std::string title;
                std::cout << "Enter flow title" << std::endl;
                std::cin >> title;
                try{
                deleteFlow(title);
                }
                catch(std::string err){
                    std::cout << err << std::endl;
                    std::cout << "Press enter to continue" << std::endl;
                    std::cin.get();
                }
                break;
            }
            case 5:
            {
                system("cls");
                case_7:
                std::string title;
                std::cout << "Enter flow title" << std::endl;
                std::cin.get();
                std::getline(std::cin, title);
                try
                {
                    system("cls");
                    printFlowAnalytics(title);
                    std::cout << std::endl << "Press enter to continue" << std::endl;
                    std::cin.get();
                }
                catch(const std::string e)
                {
                    std::cerr << e << '\n';

                    if(e == "Flow not found" || e == "Invalid title")
                        std::cout << "Do you want to try again? (y/n)" << std::endl;
                        char option;
                        std::cin >> option;
                        if(option == 'y')
                            goto case_7;
                }
                break;
            }
            case 6:
            {
                run = 0;
                break;
            }
            default:
            {
                system("cls");
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
            try{

            flows[i]->execute();
            }
            catch(const std::string e)
            {
                std::cout << e << std::endl;
            }
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

void flowManager::printFlowAnalytics(std::string title){

    if(title == " " || title == "" || title == "\n")
        throw std::string("Invalid title");

    for (int i = 0; i < flows.size(); i++)
    {
        if (flows[i]->getTitle() == title)
        {
            flows[i]->printAnalytics();
            return;
        }
    }

    throw std::string("Flow not found");
}