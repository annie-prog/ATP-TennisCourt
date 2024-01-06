#pragma once

#include "FileUtils.hpp"
#include "ATP.hpp"

class CommandsApp
{
private:
    std::vector<ATP> atpObjects;

public:
    CommandsApp() = default;
    void Run();
    void PrintWelcomeMessage();
    std::string GetUserInput();
    void ProcessCommand(const std::string& input); 

    Box* ProcessLoadCommand(const std::vector<std::string>& tokens);
    void ProcessFindCommand(const std::vector<std::string>& tokens); 
    void ProcessNumSubordinatesCommand(const std::vector<std::string>& tokens); 
    void ProcessManagerCommand(const std::vector<std::string>& tokens); 
    void ProcessNumEmployeesCommand(const std::vector<std::string>& tokens); 
    void ProcessOverloadedCommand(const std::vector<std::string>& tokens);

    void ProcessJoinCommand(const std::vector<std::string>& tokens); // does not work

    void ProcessFireCommand(const std::vector<std::string>& tokens);
    void ProcessHireCommand(const std::vector<std::string>& tokens);
    void ProcessSalaryCommand(const std::vector<std::string>& tokens);

    void ProcessIncorporateCommand(const std::vector<std::string>& tokens);
    void ProcessModernizeCommand(const std::vector<std::string>& tokens);

    void ProcessSaveCommand(const std::vector<std::string>& tokens);
    void PrintHelp();
    void ProcessExitCommand(); 

    ATP* GetATPByName(const std::string& objectName);
};