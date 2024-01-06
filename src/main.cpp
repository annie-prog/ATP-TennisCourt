// #define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "ATP.hpp"
#include "CommandsManagement.hpp"

// TEST_CASE("ATP::load", "[ATP]") 
// {
//     ATP atp;

//     SECTION("Load with valid object name and custom file") 
//     {
//         std::string objectName = "ATP";
//         std::string fileName = "../../atp.txt";
//         Box* loadedTree = atp.load(objectName, fileName);

//         REQUIRE(loadedTree != nullptr);
//         REQUIRE(atp.getName() == objectName);
//     }

//     SECTION("Load with invalid object name") 
//     {
//         std::string objectName = "ATP-3";
//         std::string fileName = "../../atp.txt";
//         Box* loadedTree = atp.load(objectName, fileName);

//         REQUIRE(loadedTree == nullptr);
//     }
// }

// TEST_CASE("ATP::convertTreeToString", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Convert valid tree to string") 
//     {
//         std::string result = atp.convertTreeToString(tree);

//         std::string expected =
//             "CEO_to-Dimitrov\n"
//             "CEO_to-Nishikori\n"
//             "CEO_to-Raonic\n"
//             "Dimitrov-Alcaraz\n"
//             "Dimitrov-Medvedev\n"
//             "Alcaraz-Rublev\n"
//             "Alcaraz-Zverev\n"
//             "Medvedev-Tsitsipas\n"
//             "Nishikori-Djokovic\n"
//             "Nishikori-Federer\n"
//             "Djokovic-Nadal\n"
//             "Nadal-Rune\n";

//         REQUIRE(result == expected);
//     }
// }

// TEST_CASE("ATP::findEmployee", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Find existing employee in the tree") 
//     {
//         REQUIRE(atp.findEmployee("Rune") == true);
//     }

//     SECTION("Find non-existing employee in the tree") 
//     {
//         REQUIRE(atp.findEmployee("Ruud") == false);
//     }

//     SECTION("Find employee in an empty tree") 
//     {
//         ATP emptyAtp;
//         REQUIRE(emptyAtp.findEmployee("AnyEmployee") == false);
//     }
// }

// TEST_CASE("ATP::numberOfChildren", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Number of children for existing employee") 
//     {
//         std::size_t count = atp.numberOfChildren("Dimitrov");
//         REQUIRE(count == 2);
//     }

//     SECTION("Number of children for non-existing employee") 
//     {
//         std::size_t count = atp.numberOfChildren("Ruud");
//         REQUIRE(count == 0);
//     }

//     SECTION("Number of children for employee with no children") 
//     {
//         std::size_t count = atp.numberOfChildren("Rune");
//         REQUIRE(count == 0);
//     }

//     SECTION("Number of children for an empty tree")
//     {
//         ATP emptyAtp;
//         std::size_t count = emptyAtp.numberOfChildren("Ani");
//         REQUIRE(count == 0);
//     }
// }

// TEST_CASE("ATP::numEmployees", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Find number of employees in existing employee") 
//     {
//         std::size_t count = atp.numEmployees();
//         REQUIRE(count == 13);
//     }

//     SECTION("Find number of children in an empty tree") 
//     {
//         ATP emptyAtp;
//         std::size_t count = emptyAtp.numEmployees();
//         REQUIRE(count == 0);
//     }
// }

// TEST_CASE("ATP::findPath", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Find path for existing employee") 
//     {
//         std::vector<std::string> path = atp.findPath(tree, "Rune");
//         std::vector<std::string> expected = { "CEO_to", "Nishikori", "Djokovic", "Nadal", "Rune" };
//         REQUIRE(path == expected);
//     }

//     SECTION("Find path for non-existing employee")
//     {
//         std::vector<std::string> path = atp.findPath(tree, "Ani");
//         std::vector<std::string> expected = {};
//         REQUIRE(path == expected);
//     }

//     SECTION("Find path for an empty tree") 
//     {
//         ATP emptyAtp;
//         std::vector<std::string> path = emptyAtp.findPath(nullptr, "Ani");
//         std::vector<std::string> expected = {};
//         REQUIRE(path == expected);
//     }
// }

// TEST_CASE("ATP::sizeLongestPath", "[ATP]") {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Size of longest path in non-empty tree") 
//     {
//         std::size_t size = atp.sizeLongestPath(tree);
//         REQUIRE(size == 5); 
//     }

//     SECTION("Size of longest path in an empty tree") 
//     {
//         ATP emptyAtp;
//         std::size_t size = emptyAtp.sizeLongestPath(nullptr);
//         REQUIRE(size == 0);
//     }
// }

// TEST_CASE("ATP::manager", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Manager for existing employee") 
//     {
//         std::string manager = atp.manager("Rune");
//         REQUIRE(manager == "Nadal");
//     }

//     SECTION("Manager for non-existing employee") 
//     {
//         std::string manager = atp.manager("Ani");
//         REQUIRE(manager == "");
//     }

//     SECTION("Manager for CEO") 
//     {
//         std::string manager = atp.manager("CEO_to");
//         REQUIRE(manager == "CEO_to");
//     }

//     SECTION("Manager for an empty tree") 
//     {
//         ATP emptyAtp;
//         std::string manager = emptyAtp.manager("Ani");
//         REQUIRE(manager == "");
//     }
// }

// TEST_CASE("ATP::overloaded", "[ATP]") 
// {
//     ATP atp;
//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Count overloaded employees in non-empty tree") 
//     {
//         std::size_t count = atp.overloaded();
//         REQUIRE(count == 0); 
//     }

//     SECTION("Count overloaded employees in an empty tree") 
//     {
//         ATP emptyAtp;
//         std::size_t count = emptyAtp.overloaded();
//         REQUIRE(count == 0);
//     }
// }

// TEST_CASE("ATP::salary", "[ATP]") 
// {
//     ATP atp;

//     Box* tree = atp.load("ATP", "../../atp.txt");

//     SECTION("Calculate salary for existing employee") 
//     {
//         std::size_t salary = atp.salary("Djokovic");
//         std::size_t salary1 = atp.salary("Dimitrov");
//         REQUIRE(salary == 550);
//         REQUIRE(salary1 == 1150);
//     }

//     SECTION("Calculate salary for non-existing employee") 
//     {
//         std::size_t salary = atp.salary("Ani");
//         REQUIRE(salary == 0);
//     }

//     SECTION("Calculate salary for an empty tree") 
//     {
//         ATP emptyAtp;
//         std::size_t salary = emptyAtp.salary("Ani");
//         REQUIRE(salary == 0);
//     }
// }

int main() 
{
    CommandsApp commandsApp;
    commandsApp.run();

    return 0;
}