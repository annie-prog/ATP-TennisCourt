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
//     Box* tree = myATP.load("ATP");
//     myATP.printHierarchy(tree, std::cout);

//     std::cout << myATP.findEmployee("ATP", "Tsitsipas") << std::endl;

//     return 0;
// }