#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>

std::string splitWs(std::string parametro){
    std::string placeHolder;
    bool foundSpace = false;
    for (size_t i = 0; i < parametro.size(); i++) {
        if (parametro[i] == ' ' && !foundSpace) {
            foundSpace = true;
        } else if (!foundSpace) {
            placeHolder += parametro[i];
        }
    }

    return placeHolder;
}
int main()
{
    int correct = 8;
    int questions = 10;
    double score = (double)correct/questions * 100;
    std::cout << "Score: " << score << "%\n";
    
    std::cout << "What is your name?: ";
    std::string name;
    std::getline(std::cin >> std::ws, name); // Reads and comports ws, but treats as final input to the buffer

    std::cout << "What is your Age?: ";
    std::string age;
    for (;;)
    { 
        std::getline(std::cin >> std::ws,  age);
        if (std::cin.fail())
        {
            std::cout << "Invalid input, please enter a valid value.\n";
            std::cout << "What is your Age?: ";
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            age = splitWs(age);
            break;
        }
    }

    std::cout << "What is your Level?: ";
    int level;
    for (;;)
    {
        std::cin >> level;
        if (std::cin.fail())
        {
            std::cout << "Invalid input, please enter a valid value.\n";
            std::cout << "What is your Level?: ";
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            age = splitWs(age);
            break;
        }
    }

    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Level: " << level << "\n";

    return 0;
}