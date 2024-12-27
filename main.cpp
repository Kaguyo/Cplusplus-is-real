#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int retornaUmInteiro(int idade1, int idade2){
    cout << "idade1: " << idade1 << " idade2: " << idade2 << "\n";

    return 0;
}
std::string ExplainTransformation(std::string NomeDaForma, int poderLuta){

    string transformationName;
    string explainedTransformation;

    std::tolower();
    if (NomeDaForma == "Kaioken"){
        transformationName = "Kaioken";
        explainedTransformation = "Aumenta o poder de luta da forma base x2";
        poderLuta *= 2;

    } else if (NomeDaForma == "Super Sayajin"){
        transformationName = "Super Sayajin";
        explainedTransformation = "Aumenta o poder de luta da forma base em x50";
        poderLuta *= 50;

    } else if (NomeDaForma == "Super Sayajin Kaioken"){
        transformationName = "Super Sayajin Kaioken";
        explainedTransformation = "Aumenta o poder de luta da forma base em x100";
        poderLuta *= 100;
    
    }

    cout << "Forma: " << NomeDaForma << "\n";
    cout << explainedTransformation << "\n" << "Poder de Luta nessa forma: " << poderLuta << "\n";


    return transformationName;
}

int main(){
     
    // int idade = 7;
    // cout << "idade: " << idade << "\n";

    // idade = retornaUmInteiro(75, 30);
    // cout << "idade: " << idade << "\n";
    // int valorRetornado = retornaUmInteiro(14, 19);
    // cout << valorRetornado << "\n";
    ExplainTransformation("kAiOkEn", 3000000);
    return 0;
}