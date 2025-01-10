#include <optional>
#include <iostream>

/* Metodo que pode ou não retornar um valor, possuindo assim bool has_value,
   e value() por si só */
std::optional<int> retornaOuNaoUmValor(int int_to_check_if_is_positive)
{
    // Retorna optional false caso if seja atendido
    if (int_to_check_if_is_positive <= -2)
    {
        return {};
    }

    return int_to_check_if_is_positive;
}

int main()
{
    int entradaNumber;
    std::cout << "Digite um numero Positivo: ";
    std::cin >> entradaNumber;
    std::optional<int> NumeroOpcional = retornaOuNaoUmValor(entradaNumber);

    if (!NumeroOpcional.has_value())
    {
        std::cout << "Sem valor positivo: " << NumeroOpcional.has_value();
    }
    else 
    {
        std::cout << "Foi recebido um valor positivo: " << NumeroOpcional.value();
    }

    return 0;   
}