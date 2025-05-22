#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

struct Usuario {
    std::string nome;
    sf::Texture fotoTexture;
    sf::Sprite fotoSprite;

    void setNome(const std::string& novoNome) {
        nome = novoNome;
    }

    // Define a imagem de perfil a partir de bytes (JPEG, etc.)
    bool setFotoPerfilFromBytes(const std::vector<uint8_t>& imagemBytes) {
        if (!fotoTexture.loadFromMemory(imagemBytes.data(), imagemBytes.size())) {
            std::cerr << "Erro ao carregar imagem dos bytes.\n";
            return false;
        }
        fotoSprite.setTexture(fotoTexture);
        return true;
    }

    void exibirNome() const {
        std::cout << "Nome: " << nome << "\n";
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}