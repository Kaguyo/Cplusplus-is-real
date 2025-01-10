#include <optional>
#include <iostream>

/* Metodo que retorna um optional podendo ou nao retornar um valor. 
optionals possuem metodo has_value() e value(), dentre outros. 
Assim optional.has_value() pode ser utilizado para pegar um bool true caso 
exista um valor a esse optional, false caso contrario. (Obs: exibir o valor do metodo
has_value(); vai exibir 1 ou 0 para true ou false).
Enquanto isso optional.value() pega o valor por si so. 
Tentar acessar um valor vazio gera excessao std::bad_optional_access */
std::optional<int> retornaOuNaoUmValor(int int_to_check_if_is_positive)
{
    // Retorna optional.has_value() = false caso if seja atendido
    if (int_to_check_if_is_positive <= 0)
    {
        // return NULL; // retorna null. Obs: null e vazio sao coisas diferentes.
        return {}; // retorna optional de valor vazio.

        /* atribuir corpos vazios em optionals é equivalente a retornar um bool false
        para has_value(), e um valor vazio para value(), atencao, tentar acessar um valor vazio
        de um optional vai causar uma excecao do tipo std::bad_optional_access.
        retornar null a um optional causara has_value() = true, porem em C++ a representacao
        de valor null é 0. */
    }

    return int_to_check_if_is_positive; // retorna o parametro recebido
}

int main()
{
    int entradaNumber;
    std::cout << "Digite um numero Positivo: ";
    std::cin >> entradaNumber;
    std::optional<int> NumeroOpcional = retornaOuNaoUmValor(entradaNumber);
    
    // Verifica se o optional nao possui valor
    if (!NumeroOpcional.has_value())
    {   
        std::cout << "Valor de Entrada: " << entradaNumber << "\n";
        /* Se trocar has_value() por value() na linha abaixo, causara a excecao std::bad_optional_access
        pois o unico jeito deste if ser atendido é com o optional NAO possuindo valor */
        std::cout << "Sem valor positivo retornado: " << NumeroOpcional.has_value();
        std::cout << "\nTamanho em Bytes do retorno: " << sizeof(NumeroOpcional);
        std::cout << "\nTamanho em Bytes da entrada: " << sizeof(entradaNumber);
    }
    else
    {   
        std::cout << "Valor de Entrada: " << entradaNumber << "\n";
        std::cout << "Foi retornado um valor positivo: " << NumeroOpcional.value();
        std::cout << "\nTamanho em Bytes do retorno: " << sizeof(NumeroOpcional);
        std::cout << "\nTamanho em Bytes da entrada: " << sizeof(entradaNumber);
    }

    return 0;   
}