#include "ATP.hpp"
#include "CommandsManagement.hpp"

int main() 
{
    CommandsApp commandsApp;
    commandsApp.Run();

    return 0;
}

// int main()
// {
//     ATP myATP;
//     Box* tree = myATP.load("ATP", "../../atp.txt");
//     // myATP.printHierarchy(tree, std::cout);

//     myATP.modernize(tree, "ATP");

//     myATP.printHierarchy(tree, std::cout);

//     return 0;
// }