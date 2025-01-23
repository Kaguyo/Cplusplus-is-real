#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <random>

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
terminalVelocity = sqroot( ( 2 * mass(1) * gravity(9.81)) / (( p(1,255) * A(0,0314) * Cd(0.5)
*/
class Particles
{
public:
    static bool reset;
    static float gravity;
    static float airDensity;
    static constexpr float deltaTime = 0.0083;
    static constexpr float PI = 3.14159f;

    Particles(std::string shape, float radius, float weight, unsigned int windowWidth, unsigned int windowHeight,
        float width, float height, float elasticity = 0.0f)
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
        this->setInitialValues(windowWidth, windowHeight);
        //  ---------------------------------------------------
    }

    float getWidth() const { return this->width; }
    float getHeight() const { return this->height; }
    float getAxisX() const { return this->axisX; }
    float getAxisY() const { return this->axisY; }
    float getRadius() const { return this->radius; }
    float getVelocity() const { return this->velocity; }

    void setWidth(float width) { this->width = width; }
    void setHeight(float height) { this->height = height; }

    static std::vector<Particles> resetValues(std::vector<Particles> particlesArray, unsigned int windowWidth, unsigned int windowHeight)
    {
        for (Particles& particle : particlesArray)
        {
            particle.velocity = 0.0f;
            particle.setInitialValues(windowWidth, windowHeight);
        }

        return particlesArray;
    }

    static std::vector<Particles> update(std::vector<Particles> particlesArray, float windowWidth, float windowHeight)
    {
        for (Particles& particle : particlesArray)
        {
            if (!particle.isGoingUp && !particle.isStall)
            {
                particle.axisY += particle.velocity; // Updates current particle's axis Y
                particle.velocity += Particles::gravity * Particles::deltaTime; // Updates current particle's velocity

                if (particle.velocity >= particle.terminalVelocity)
                    particle.velocity = particle.terminalVelocity; // Sets particle's velocity to limit 

                if (particle.axisY >= windowHeight - particle.height)
                {
                    particle.axisY = windowHeight - particle.height; // Puts particle directly onto the floor
                    if (particle.velocity <= particle.terminalVelocity * 0.02f)
                    {
                        particle.isStall = true;
                        particle.velocity = 0.0f;
                        continue;
                    }

                    particle.isGoingUp = true;
                    particle.velocity *= particle.elasticity;
                }                                                         
            }
            else if (particle.isGoingUp && !particle.isStall)
            {
                particle.axisY -= particle.velocity;
                particle.velocity -= Particles::gravity * Particles::deltaTime;

                if (particle.velocity <= 0.0f)
                {
                    particle.velocity = 0.0f;
                    particle.isGoingUp = false;
                }
            }
        }

        return particlesArray;
    }

private:
    /* Determines shape of the object. Certain provided shapes (CircleShape, RectangleShape, TriangleShape)
    will get some of their values like radius, height, width, Cross-sectional area and Drag Coefficient
    be auto calculated based on it's shape and n values.
    In case you don't match the list, your object still is constructed, just wont get all of these auto
    calculated value */
    std::string shape;

    /* Determines whether the object can move on it's axis Y or not.
    It can if false, otherwisely can't. */
    bool isStall = false;
    bool isGoingUp = false;
    float radius = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float weight = 0.0f;
    float axisX = 0.0f;
    float axisY = 0.0f;
    float elasticity = 0.0f;        // Coefficient of restitution. Ex: 0.0 - 1.0
    float velocity = 0.0f;          // Current falling velocity
    float terminalVelocity = 0.0f;
    float A = 0.0f;                 // Cross-sectional area
    float Cd = 0.0f;                // Drag coefficient

    std::optional<float> semiMajorAxis;
    std::optional<float> semiMinorAxis;

    void setInitialValues(unsigned int windowWidth, unsigned int windowHeight)
    {
        if (this->shape == "CircleShape")
        {
            this->width = this->radius * 2;
            this->height = this->radius * 2;
            this->A = Particles::PI * std::pow(radius / 100.0f, 2); // Divides radius by 100 to get radius to centimeters
            this->Cd = 0.5f;
            this->terminalVelocity = sqrt((2 * weight * Particles::gravity) / (Particles::airDensity * this->A * this->Cd));
        }
        else if (this->shape == "RectangleShape")
        {
            this->A = (this->width * this->height);
            this->Cd = 0.5f;
            this->terminalVelocity = sqrt((2 * weight * Particles::gravity) / (Particles::airDensity * this->A * this->Cd));
        }
        else if (this->shape == "TriangleShape")
        {
            this->A = (1 / 2) * this->width * this->height;
            this->Cd = 0.5f;
            this->terminalVelocity = sqrt((2 * weight * Particles::gravity) / (Particles::airDensity * this->A * this->Cd));
        }

        // Section below generates random number from 0 up to windowWidth - thisObject.width to simulate collision with the walls
        int min = 0, max = windowWidth - this->width;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        // Section below generates axisX based on random number and axisY presetted as user wishes
        this->axisX = distrib(gen);
        this->axisY = (windowHeight / 2) - this->height;

        this->isStall = false;
        this->isGoingUp = false;
    }
};

bool Particles::reset = false;
float Particles::gravity = 0.981f;
float Particles::airDensity = 1.225f;

void renderingThread(sf::RenderWindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
    // activate the window's context
    window->setActive(true);
    std::vector<Particles> particlesArray;
    std::vector<sf::CircleShape> circleShapeArray;

    unsigned int desiredSpheresAmount = 30;
    sf::Vector2<float> position;
    for (int i = 0; i < desiredSpheresAmount; i++)
    {
        particlesArray.emplace_back("CircleShape", 15.0f, 1.7f, windowWidth, windowHeight, 0.f, 0.f, 0.6f);
        circleShapeArray.emplace_back(particlesArray[i].getRadius());
        circleShapeArray[i].setFillColor(sf::Color::White);
        position.x = particlesArray[i].getAxisX();
        position.y = particlesArray[i].getAxisY();
        circleShapeArray[i].setPosition(position);
    }

    // the rendering loop
    while (window->isOpen())
    {
        if (Particles::reset)
        {
            particlesArray = Particles::resetValues(particlesArray, windowWidth, windowHeight);
            Particles::reset = false;
        }

        // clear...
        window->clear();
        // draw...
        for (sf::CircleShape& shape : circleShapeArray)
        {
            window->draw(shape);
        }

        // end the current frame
        window->display();

        // update...
        particlesArray = Particles::update(particlesArray, windowWidth, windowHeight);
        for (int i = 0; i < desiredSpheresAmount; i++)
        {
            position.x = particlesArray[i].getAxisX();
            position.y = particlesArray[i].getAxisY();
            circleShapeArray[i].setPosition(position);
        }
        
    }
}

int main()
{
    unsigned int windowWidth = 1440, windowHeight = 800;

    // create the window
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "OpenGL", sf::Style::Default);
    sf::ContextSettings settings;
    settings.depthBits = 32;
    // window.setVerticalSyncEnabled(true);

    // deactivate its OpenGL context
    window.setActive(false);

    // launch the rendering thread
    std::thread thread(&renderingThread, &window, windowWidth, windowHeight);
    bool LAlt = false;
    bool LCtrl = false;
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
                    std::cout << "Reseting\n";
                    Particles::reset = true;
                }
            }
        }
    }

    // release resources...
    thread.join();
}