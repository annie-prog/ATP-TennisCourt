#include "CommandsManagement.hpp"
#include <iostream>
#include <vector>

void CommandsApp::Run() 
{
    PrintWelcomeMessage();
    while (true) 
    {
        std::string input = GetUserInput();
        ProcessCommand(input);
    }
}
void CommandsApp::PrintWelcomeMessage() 
{
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "Welcome to our Association of Professional Tennis Players system! " << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
}
std::string CommandsApp::GetUserInput() 
{
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return input;
}

void CommandsApp::PrintHelp() 
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

ATP* CommandsApp::GetATPByName(const std::string& objectName)
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

Box* CommandsApp::ProcessLoadCommand(const std::vector<std::string>& tokens) 
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

void CommandsApp::ProcessFindCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessSaveCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string filePath = (tokens.size() > 2) ? tokens[2] : "";

    ATP* currentATP = GetATPByName(objectName);
    if (!currentATP)
    {
        std::cerr << objectName << " is an unknown office! " << std::endl;
        return;
    }

    currentATP->save(filePath);
    std::cout << objectName << " saved." << std::endl;
}

void CommandsApp::ProcessNumSubordinatesCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];
    
    ATP* currentATP = GetATPByName(objectName);
    if(!currentATP->findEmployee(employeeName))
    {
        std::cout << employeeName << " is not in " << objectName << "." << std::endl;
        return;
    }

    std::size_t result = currentATP->numberOfChildren(employeeName);
    std::cout << employeeName << " has " << CommonMethods::numberToWords(result) << " subordinates." << std::endl;
}

void CommandsApp::ProcessManagerCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessNumEmployeesCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessOverloadedCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessFireCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessHireCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 3) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];
    std::string newManagerName = tokens[3];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessSalaryCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];
    std::string employeeName = tokens[2];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessIncorporateCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessModernizeCommand(const std::vector<std::string>& tokens) 
{
    if (tokens.size() < 2) 
    {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string objectName = tokens[1];

    ATP* currentATP = GetATPByName(objectName);
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

void CommandsApp::ProcessExitCommand() 
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
    else 
    {
        std::cout << "Invalid response. Exiting the program without saving. Goodbye!" << std::endl;
        std::exit(0);
    }
}

void CommandsApp::ProcessCommand(const std::string& input) 
{
    std::vector<std::string> tokens = CommonMethods::split(input, ' ');

    if (tokens.empty()) 
    {
        return;
    }
    std::string command = tokens[0];

    if (command == "save") 
    {
        ProcessSaveCommand(tokens);
    }
    else if (command == "load") 
    {
        ProcessLoadCommand(tokens);
    }
    else if (command == "find") 
    {
        ProcessFindCommand(tokens);
    }
    else if (command == "num_subordinates") 
    {
        ProcessNumSubordinatesCommand(tokens);
    }
    else if (command == "manager") 
    {
        ProcessManagerCommand(tokens);
    }
    else if (command == "num_employees") 
    {
        ProcessNumEmployeesCommand(tokens);
    }
    else if (command == "overloaded") 
    {
        ProcessOverloadedCommand(tokens);
    }
    else if (command == "fire") 
    {
        ProcessFireCommand(tokens);
    }
    else if (command == "hire") 
    {
        ProcessHireCommand(tokens);
    }
    else if (command == "salary") 
    {
        ProcessSalaryCommand(tokens);
    }
    else if (command == "incorporate") 
    {
        ProcessIncorporateCommand(tokens);
    }
    else if (command == "modernize") 
    {
        ProcessModernizeCommand(tokens);
    }
    else if (command == "help") 
    {
        PrintHelp();
    }
    else if (command == "exit") 
    {
        ProcessExitCommand();
    }
    else 
    {
        std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
    }
}