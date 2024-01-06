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
    void ProcessCommand(const std::string& input); // works

    Box* ProcessLoadCommand(const std::vector<std::string>& tokens); // works
    void ProcessFindCommand(const std::vector<std::string>& tokens); // works
    void ProcessNumSubordinatesCommand(const std::vector<std::string>& tokens); // works
    void ProcessManagerCommand(const std::vector<std::string>& tokens); // works
    void ProcessNumEmployeesCommand(const std::vector<std::string>& tokens); // works
    void ProcessOverloadedCommand(const std::vector<std::string>& tokens); // works
    void ProcessFireCommand(const std::vector<std::string>& tokens); // works
    void ProcessHireCommand(const std::vector<std::string>& tokens); // works
    void ProcessSalaryCommand(const std::vector<std::string>& tokens); // works

    void ProcessIncorporateCommand(const std::vector<std::string>& tokens); // works
    void ProcessModernizeCommand(const std::vector<std::string>& tokens); // works

    void ProcessSaveCommand(const std::vector<std::string>& tokens); // works
    void PrintHelp(); // works
    void ProcessExitCommand(); 

    ATP* GetATPByName(const std::string& objectName); // works
};