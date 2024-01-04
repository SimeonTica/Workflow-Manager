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
        std::cout << "Flow options:" << std::endl;

        std::cout << "1. Create flow" << std::endl;
        std::cout << "2. Display flows titles" << std::endl;
        std::cout << "3. Execute flow" << std::endl;
        std::cout << "4. Delete flow" << std::endl;
        std::cout << "5. Save flow" << std::endl;
        std::cout << "6. Load flow" << std::endl;
        std::cout << "7. Print flow analytics" << std::endl;
        std::cout << "8. Exit" << std::endl;

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
                case_5:
                std::string file;
                std::cout << "Enter flow name" << std::endl;
                std::cin >> file;
                try
                {
                    saveFlow(file);
                }
                catch(std::string err){
                    std::cout << err << std::endl;
                    goto case_5;
                }
                break;
            }
            case 6:
            {
                std::string file;
                std::cout << "Enter file name" << std::endl;
                std::cin >> file;
                try{
                    loadFlow(file);
                }
                catch(std::string error){
                    std::cout << error << std::endl;
                }
                break;
            }
            case 7:
            {
                case_7:
                std::string title;
                std::cout << "Enter flow title" << std::endl;
                std::cin.get();
                std::getline(std::cin, title);
                try
                {
                    printFlowAnalytics(title);  
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
            case 8:
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
            try{

            flows[i]->execute();
            }
            catch(const std::string e)
            {
                std::cerr << e << '\n';
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

void flowManager::saveFlow(std::string title){
    std::string path = folderPath1 + "\\" + title + ".flow";

    std::ofstream o(path, std::ios::binary);

    if(!o.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    for( auto& flow: flows){

        if (flow->getTitle() == title)
        {
            o.write((char*)&flow, sizeof(flow));
            o.close();
            return;
        }
    }
    throw std::string("Flow not found");
}

void flowManager::loadFlow(std::string file){
    std::string path = folderPath1 + "\\" + file + ".flow";

    std::ifstream i(path, std::ios::binary);

    if(!i.is_open()){
        std::string err = "Cannot open file";
        throw err;
    }

    Flow *flow;

    i.read((char*)&flow, sizeof(flow));

    if(!i.good()){
        std::string err = "Cannot read file";
        throw err;
    }

    i.close();

    flows.push_back(flow);
}