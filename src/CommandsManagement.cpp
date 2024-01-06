#include "CommandsManagement.hpp"
#include <iostream>
#include <vector>

void CommandsApp::run() 
{
    printWelcomeMessage();
    while (true) 
    {
        std::string input = getUserInput();
        processCommand(input);
    }
}
void CommandsApp::printWelcomeMessage() 
{
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "Welcome to our Association of Professional Tennis Players system! " << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
}
std::string CommandsApp::getUserInput() 
{
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return input;
}

void CommandsApp::printHelp() 
{
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "load <object_name> [<file_name>]                                         loads hierarchy data from a file with the supplied name and creates a tree associated with <object_name>." << std::endl;
    std::cout << "save <object_name> [<file_name>]                                         writes the specified object's hierarchy information to a file with the specified name." << std::endl;
    std::cout << "find <object_name> <employee_name>                                       checks whether an employee with the specified name exists in the specified object" << std::endl;
    std::cout << "num_subordinates <object_name> <employee_name>                           displays the number of direct subordinates of the given employee in the specified object" << std::endl; 
    std::cout << "manager <object name> <employee_name>                                    returns the name of the manager of the given employee in the specified object" << std::endl;
    std::cout << "num_employees <object_name>                                              displays the number of employees in the specified object" << std::endl;
    std::cout << "overloaded <object_name>                                                 displays the number of employees in the specified object for whom the number of subordinates (direct or indirect) is greater than 20" << std::endl;
    std::cout << "join <object_name_1> <object_name_2> <object_name_result>                merges the two specified objects into a new object named <object_name_result>" << std::endl;
    std::cout << "fire <object_name> <employee_name>                                       removes the employee from the corresponding object" << std::endl;
    std::cout << "hire <object_name> <employee_name> <manager_name>                        hires the employee in the relevant object as subordinate to the submitted supervisor" << std::endl;
    std::cout << "salary <object_name> <employee_name>                                     displays the employee's salary" << std::endl;
    std::cout << "incorporate <object_name>                                                incorporates the company" << std::endl;
    std::cout << "modernize <object_name>                                                  modernize the company" << std::endl;
    std::cout << "exit                                                                     exits the program" << std::endl;
}

ATP* CommandsApp::getATPByName(const std::string& objectName)
{
    for (ATP& atp : atpObjects)
    {
        if (atp.getName() == objectName)
        {
            return &atp;
        }
    }
    return nullptr;
}

Box* CommandsApp::processLoadCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return nullptr;
    }

    std::string objectName = tokens[1];
    std::string filePath = (tokens.size() > 2) ? tokens[2] : "";

    for (ATP& existingATP : atpObjects)
    {
        if (existingATP.getName() == objectName)
        {
            std::cerr << "An ATP object with the name " << objectName << " already exists!" << std::endl;
            return nullptr;
        }
    }

    ATP newATP(objectName);
    Box* tree = newATP.load(objectName, filePath);

    if (!tree)
    {
        return nullptr;
    }
    
    std::cout << objectName << " loaded successfully!" << std::endl;

    atpObjects.push_back(newATP);

    return tree;
}

void CommandsApp::processFindCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = getATPByName(objectName);
    if (!currentATP)
    {
        std::cerr << objectName << " is an unknown office! " << std::endl;
        return;
    }

    if(currentATP->findEmployee(employeeName))
    {
        std::cout << employeeName << " is employed in " << objectName << "." << std::endl;
    }
    else
    {
        std::cout << employeeName << " is not employed in " << objectName << "." << std::endl;
    }
}

void CommandsApp::processSaveCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string filePath = (tokens.size() > 2) ? tokens[2] : "";

    ATP* currentATP = getATPByName(objectName);
    if (!currentATP)
    {
        std::cerr << objectName << " is an unknown office! " << std::endl;
        return;
    }

    currentATP->save(filePath);
    std::cout << objectName << " saved." << std::endl;
}

void CommandsApp::processNumSubordinatesCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];
    
    ATP* currentATP = getATPByName(objectName);
    if(!currentATP->findEmployee(employeeName))
    {
        std::cout << employeeName << " is not in " << objectName << "." << std::endl;
        return;
    }

    std::size_t result = currentATP->numberOfChildren(employeeName);
    std::cout << employeeName << " has " << CommonMethods::numberToWords(result) << " subordinates." << std::endl;
}

void CommandsApp::processManagerCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = getATPByName(objectName);
    std::string result = currentATP->manager(employeeName);
    
    if (!result.empty())
    {
        std::cout << "The manager of " << employeeName <<  " is " << result << "." << std::endl;
    }
    else
    {
        std::cout << "There is no " << employeeName << " in ATP." << std::endl;
    }
}

void CommandsApp::processNumEmployeesCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        std::size_t result = currentATP->numEmployees();
        std::cout << "There are " << result << " employees in " << objectName << "." << std::endl;
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processOverloadedCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        std::size_t result = currentATP->overloaded();
        std::cout << CommonMethods::numberToWords(result) << " overloaded employees in " << objectName << "." << std::endl;
    } 
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processJoinCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 4) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName1 = tokens[1];
    std::string objectName2 = tokens[2];
    std::string objectName3 = tokens[3];

    ATP* currentATP1 = getATPByName(objectName1);
    ATP* currentATP2 = getATPByName(objectName2);

    if (currentATP1 && currentATP2)
    {
        ATP currentATP3(objectName3);

        Box* joinedTree = currentATP3.join(currentATP1->getRoot(), currentATP2->getRoot());
        atpObjects.push_back(currentATP3);
        std::cout << objectName3 << " created. " << std::endl;
    }
    else
    {
        std::cout << "One or both of the offices are unknown!" << std::endl;
    }
}

void CommandsApp::processFireCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        if(!currentATP->findEmployee(employeeName))
        {
            std::cout << employeeName << " is not in " << objectName << std::endl;
            return;
        }

        if (employeeName == "CEO_to")
        {
            std::cerr << "You cannot fire the CEO!" << std::endl;
            return;
        }
        else
        {
            currentATP->erase(employeeName);
            std::cout << employeeName << " was fired." << std::endl;
        }
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processHireCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 3) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];
    std::string newManagerName = tokens[3];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        if(!currentATP->findEmployee(newManagerName))
        {
            std::cout << newManagerName << " is not in " << objectName << std::endl;
            return;
        }

        if (employeeName == "CEO_to")
        {
            std::cerr << "You cannot hire the CEO!" << std::endl;
            return;
        }
        else
        {
            currentATP->hire(employeeName, newManagerName);
            std::cout << employeeName << " was hired." << std::endl;
        }
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processSalaryCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        if(!currentATP->findEmployee(employeeName))
        {
            std::cout << employeeName << " is not in " << objectName << std::endl;
            return;
        }

        std::size_t salary = currentATP->salary(employeeName);
        std::cout << "The salary is " << salary << " euro." << std::endl;
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processIncorporateCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        currentATP->incorporate();
        std::cout << objectName << " incorporated." << std::endl;
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processModernizeCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = getATPByName(objectName);
    if (currentATP)
    {
        currentATP->modernize();
        std::cout << objectName << " modernized." << std::endl;
    }
    else
    {
        std::cout << objectName << " is an unknown office! " << std::endl;
    }
}

void CommandsApp::processExitCommand() 
{
    std::string response;
    std::cout << "ATP is modified, but not saved. Do you want to save changes before exiting? (yes/no): ";
    std::cin >> response;

    if (response == "yes") 
    {
        std::string fileName;
        std::cout << "Enter file name to save the changes: ";
        std::cin >> fileName;

        for (auto object : atpObjects)
        {
            object.save(fileName);
        }

        std::cout << "ATP's saved.\nGoodbye!" << std::endl;
    } 
    else if (response == "no") 
    {
        std::cout << "Exiting the program without saving. Goodbye!" << std::endl;
        std::exit(0);
    } 
}

void CommandsApp::processCommand(const std::string& input) 
{
    std::vector<std::string> tokens = CommonMethods::split(input, ' ');

    if (tokens.empty()) 
    {
        return;
    }
    std::string command = tokens[0];

    if (command == "save") 
    {
        processSaveCommand(tokens);
    }
    else if (command == "load") 
    {
        processLoadCommand(tokens);
    }
    else if (command == "find") 
    {
        processFindCommand(tokens);
    }
    else if (command == "num_subordinates") 
    {
        processNumSubordinatesCommand(tokens);
    }
    else if (command == "manager") 
    {
        processManagerCommand(tokens);
    }
    else if (command == "num_employees") 
    {
        processNumEmployeesCommand(tokens);
    }
    else if (command == "overloaded") 
    {
        processOverloadedCommand(tokens);
    }
    else if (command == "join") 
    {
        processJoinCommand(tokens);
    }
    else if (command == "fire") 
    {
        processFireCommand(tokens);
    }
    else if (command == "hire") 
    {
        processHireCommand(tokens);
    }
    else if (command == "salary") 
    {
        processSalaryCommand(tokens);
    }
    else if (command == "incorporate") 
    {
        processIncorporateCommand(tokens);
    }
    else if (command == "modernize") 
    {
        processModernizeCommand(tokens);
    }
    else if (command == "help") 
    {
        printHelp();
    }
    else if (command == "exit") 
    {
        processExitCommand();
    }
    else 
    {
        std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
    }
}