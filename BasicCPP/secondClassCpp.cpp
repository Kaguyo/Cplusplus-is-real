#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
std::string removeRepeatedWs(std::string textoParametro)
{
    std::string placeHolder;
    bool foundSpace = false;
    for (size_t i = 0; i < textoParametro.size(); i++)
    {
        if (!foundSpace)
        {
            placeHolder += textoParametro[i];
        }
        if (textoParametro[i+1] == ' ' && textoParametro[i+2] == ' ')
        {
            foundSpace = true;
        } 
        else 
        {
            foundSpace = false;
        }      
    }
    while (placeHolder[placeHolder.size() -1] == ' ')
    {
        std::string treatPlaceHolder;
        for (size_t i = 0; i < placeHolder.size() - 1; i++)
        {
            if (placeHolder[i] != ' ')
            treatPlaceHolder += placeHolder[i];
        }
        placeHolder = treatPlaceHolder;
    }

    return placeHolder;
}

std::string removeRepeatedWs(std::string textoParametro, bool isNumber)
{
    if (!isNumber)
    {
        removeRepeatedWs(textoParametro);
    }
    else 
    {
        
    }

    return textoParametro;
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
    name = removeRepeatedWs(name);
    std::cout << "What is your Age?: ";
    std::string age;
    for (;;)
    { 
        std::getline(std::cin >> std::ws, age);
        if (std::cin.fail())
        {
            std::cout << "Invalid input, please enter a valid value.\n";
            std::cout << "What is your Age?: ";
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    std::cout << "What is your Level?: ";
    std::string level;
    for (;;)
    {
        std::cin >> level;
        if (std::cin.fail())
        {
            std::cout << "Invalid input, please enter a valid value.\n";
            std::cout << "What is your Level?: ";
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        else 
        {
            break;
        }
    }

    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Level: " << level << "\n";

    return 0;
}