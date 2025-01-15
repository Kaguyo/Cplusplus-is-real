#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

/*
Examples for a sphere following the properties below
radius = 10 (in centimeters)
m = 1 (in kg)
g = 9.81m/s² (gravity for Earth)
p = 1,225kg / m³ (air density usually)
A (for Spheres) = pi * (radius in meters)² ->Result is in square meters 0,0314(m²)
A (for Rectangles) = width * height
A (for Elipses) = pi * semi-major axis * semi-minor axis
A (for Triangles) = (1 / 2) * base * height
Cd = 0.5 (drag coefficient of spheres. may vary)
Vt = sqroot( ( 2 * mass(1) * gravity(9.81)) / (( p(1,255) * A(0,0314) * Cd(0.5)
*/
class Particles
{   
public:
    static std::vector<Particles> particlesArray;
    static constexpr float deltaTime = 0.016;
    static constexpr float PI = 3.14159f;

    Particles(std::string shape, float radius, float weight, unsigned int windowWidth, unsigned int windowHeight,
              float width = 0.0f, float height = 0.0f, float elasticity = 0.0f, float gravity = 9.81f, float airDensity = 1.225f)
    {
        this->shape = shape;
        //  ---------------------------------------------------
        this->radius = radius;
        //  ---------------------------------------------------
        this->weight = weight;
        //  ---------------------------------------------------
        this->width = width;
        //  ---------------------------------------------------
        this->height = height;
        //  ---------------------------------------------------
        this->elasticity = elasticity;
        //  ---------------------------------------------------
        this->setInitialValues(windowWidth, windowHeight, gravity, airDensity);
        //  ---------------------------------------------------

        Particles::particlesArray.emplace_back(*this);
    }
    float getWidth() const { return this->width; }
    float getHeight() const { return this->height; }
    float getAxisX() const { return this->axisX; }
    float getAxisY() const { return this->axisY; }
    float getRadius() const { return this->radius; }
    float getVelocity() const { return this->velocity; }

    void setWidth(float width) { this->width = width; }
    void setHeight(float height) { this->height = height; }

    static void resetValues(unsigned int windowWidth, unsigned int windowHeight, float gravity, float airDensity)
    {
        for (auto& particle : Particles::particlesArray)
        {
            particle.setInitialValues(windowWidth, windowHeight, gravity, airDensity);
        }
    }

    auto update(float windowWidth, float windowHeight, float gravity)
    {
        if (this->axisY < windowHeight - this->radius * 2 && !this->bounce)
        {
            this->axisY += this->velocity;
            this->velocity += gravity * Particles::deltaTime;

            if (this->velocity > this->Vt)
            {
                this->velocity = this->Vt;
            }

            if (this->axisY >= windowHeight - this->radius * 2)
            {
                this->axisY = windowHeight - this->radius * 2;

                if (this->velocity < this->Vt * 0.50f)
                {
                    this->velocity = 0.0f;
                    this->bounce = false;

                    return this;
                }

                this->bounce = true;
                this->velocity *= this->elasticity;                
            }
        }
        else if (this->bounce)
        {
            this->axisY -= this->velocity;
            this->velocity -= gravity * Particles::deltaTime;

            if (this->velocity <= 0.0f)
            {
                this->velocity = 0.0f;
                this->bounce = false;
            }
        }

        return this;
    }


private:
    std::string shape;
    bool bounce = false;
    float radius = 0.0f;
    float base = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float weight = 0.0f;
    float axisX = 0.0f;
    float axisY = 0.0f;
    float elasticity = 0.0f;    // Coefficient of restitution
    float velocity = 0.0f;      // Current falling velocity
    float Vt = 0.0f;            // Terminal velocity
    float A = 0.0f;             // Cross-sectional area
    float Cd = 0.0f;            // Drag coefficient

    std::optional<float> semiMajorAxis;
    std::optional<float> semiMinorAxis;

    void setInitialValues(unsigned int windowWidth, unsigned int windowHeight, float gravity, float airDensity)
    {
        if (this->shape == "CircleShape")
        {
            this->axisX = (windowWidth / 2) - this->radius;
            this->axisY = (windowHeight / 2) - this->radius;
            this->A = Particles::PI * std::pow(radius / 100.0f, 2); // Divides radius by 100 to get radius to centimeters
            this->Cd = 0.5f;
            this->Vt = sqrt((2 * weight * gravity) / (airDensity * this->A * this->Cd));
        }
        else if (this->shape == "RectangleShape")
        {
            this->axisX = (windowWidth / 2) - this->width / 2;
            this->axisY = (windowHeight / 2) - this->height / 2;
            this->A = (this->width * this->height);
            this->Cd = 0.5f;
            this->Vt = sqrt((2 * weight * gravity) / (airDensity * this->A * this->Cd));
        }
        else if (this->shape == "TriangleShape")
        {
            this->axisX = (windowWidth / 2) - this->width / 2;
            this->axisY = (windowHeight / 2) - this->height / 2;
            this->A = (1 / 2) * this->width * this->height;
            this->Cd = 0.5f;
            this->Vt = sqrt((2 * weight * gravity) / (airDensity * this->A * this->Cd));
        }
    }
};

std::vector<Particles> Particles::particlesArray;

void renderingThread(sf::RenderWindow* window, unsigned int windowWidth, unsigned int windowHeight, 
    float gravity, float airDensity)
{
    // activate the window's context
    window->setActive(true);
    Particles particle("CircleShape", 15.0f, 0.001f, windowWidth, windowHeight, 0.f, 0.f, 0.8f, gravity, airDensity);
    sf::CircleShape circleShape(particle.getRadius());
    sf::Vector2<float> position(particle.getAxisX(), particle.getAxisY());
    
    circleShape.setFillColor(sf::Color::White);
    circleShape.setPosition(position);

    // the rendering loop
    while (window->isOpen())
    {
        // clear...
        window->clear();
        // draw...
        window->draw(circleShape);
        // end the current frame
        window->display();
        // update...
        particle.update(windowWidth, windowHeight, gravity);
        position.x = particle.getAxisX();
        position.y = particle.getAxisY();
        circleShape.setPosition(position);
    }
}

int main()
{
    unsigned int windowWidth = 800, windowHeight = 800;
    float gravity = 9.81f, airDensity = 1.255f;

    // create the window
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "OpenGL", sf::Style::Default);
    sf::ContextSettings settings;
    settings.depthBits = 32;
    // window.setVerticalSyncEnabled(true);

    // deactivate its OpenGL context
    window.setActive(false);

    // launch the rendering thread
    std::thread thread(&renderingThread, &window, windowWidth, windowHeight, gravity, airDensity);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::R)
                {
                    Particles::resetValues(windowWidth, windowHeight, gravity, airDensity);
                }
            }
        }
    }

    // release resources...
    thread.join();
}