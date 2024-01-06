#pragma once

#include "FileUtils.hpp"

class CommandsApp
{
public:
    CommandsApp() = default;
    void Run();
    void PrintWelcomeMessage();
    std::string GetUserInput();
    void ProcessCommand(const std::string& input);

    void ProcessLoadCommand(const std::vector<std::string>& tokens);
    void ProcessFindCommand(const std::vector<std::string>& tokens);
    void ProcessNumSubordinatesCommand(const std::vector<std::string>& tokens);
    void ProcessManagerCommand(const std::vector<std::string>& tokens);
    void ProcessNumEmployeesCommand(const std::vector<std::string>& tokens);
    void ProcessOverloadedCommand(const std::vector<std::string>& tokens);
    void ProcessFireCommand(const std::vector<std::string>& tokens);
    void ProcessHireCommand(const std::vector<std::string>& tokens);
    void ProcessSalaryCommand(const std::vector<std::string>& tokens);

    void ProcessSaveCommand(const std::vector<std::string>& tokens);
    void PrintHelp();
    void ProcessExitCommand(); 
};