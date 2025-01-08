#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int main() {
    string str1 = "C++";
    string str2 = "Programming";
    int year = 2024;

    // Display the type of the variable `year`
    cout << "Tipo da variavel year: " << typeid(year).name() << "\n";

    // Convert int to string
    string yearStr = to_string(year);
    cout << "Tipo da variavel year apos casting: " << typeid(yearStr).name() << "\n";

    // Convert string back to int
    year = stoi(yearStr); 
    cout << "Tipo da variavel year apos casting back to int: " << typeid(year).name() << "\n";

    // Concatenate strings
    string strFusion = str1 + " " + str2;
    cout << strFusion << "\n";

    return 0;
}
