#pragma once

#include "ATP.hpp"

class CommandsApp
{
private:
    std::vector<ATP> atpObjects;

public:
    CommandsApp() = default;
    void run();
    void printWelcomeMessage();
    std::string getUserInput();
    void processCommand(const std::string& input); 

    Box* processLoadCommand(const std::vector<std::string>& tokens);
    void processFindCommand(const std::vector<std::string>& tokens); 
    void processNumSubordinatesCommand(const std::vector<std::string>& tokens); 
    void processManagerCommand(const std::vector<std::string>& tokens); 
    void processNumEmployeesCommand(const std::vector<std::string>& tokens); 
    void processOverloadedCommand(const std::vector<std::string>& tokens);

    void processJoinCommand(const std::vector<std::string>& tokens); // does not work

    void processFireCommand(const std::vector<std::string>& tokens);
    void processHireCommand(const std::vector<std::string>& tokens);
    void processSalaryCommand(const std::vector<std::string>& tokens);

    void processIncorporateCommand(const std::vector<std::string>& tokens);
    void processModernizeCommand(const std::vector<std::string>& tokens);

    void processSaveCommand(const std::vector<std::string>& tokens);
    void printHelp();
    void processExitCommand(); 

    ATP* getATPByName(const std::string& objectName);
};