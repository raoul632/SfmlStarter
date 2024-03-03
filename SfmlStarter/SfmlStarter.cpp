#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <string>

#define PI 3.14159265

int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Font font;
    if (!font.loadFromFile("ECHOSHIFT.ttf"))
    {
        // error...
        std::cout << "error in loading font";
    }

    sf::Text text;
    text.setFont(font); // Sélectionnez la police de caractères

    sf::Clock clock;

    float length = 100.0f;
    float theta = 45.0f; // Angle initial

    float x1 = 400;
    float y1 = 300;
    float x2 = x1 + length * std::cos(theta * PI / 180.0f);
    float y2 = y1 + length * std::sin(theta * PI / 180.0f);

    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcul du delta time
        float deltaTime = clock.restart().asSeconds();

        // Contrôles de rotation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            theta -= 180.0f * deltaTime; // Ajustez la vitesse de rotation ici
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            theta += 180.0f * deltaTime; // Ajustez la vitesse de rotation ici

        // Limiter l'angle à 360 degrés
        theta = std::fmod(theta, 360.0f);

        // Mettre à jour les coordonnées finales de la ligne
        x2 = x1 + length * std::cos(theta * PI / 180.0f);
        y2 = y1 + length * std::sin(theta * PI / 180.0f);

        // Effacement de la fenêtre
        window.clear();

        // Dessiner la ligne
        sf::Vertex line[]{
            sf::Vertex(sf::Vector2f(x1, y1)),
            sf::Vertex(sf::Vector2f(x2, y2)),
        };

        // Afficher l'angle
        text.setString("Angle: " + std::to_string(theta));
        window.draw(line, 2, sf::Lines);
        window.draw(text);

        // Affichage de la fenêtre
        window.display();
    }

    return 0;
}
