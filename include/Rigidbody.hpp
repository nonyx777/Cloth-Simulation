#pragma once
#include <SFML/Graphics.hpp>
#include "./Entities/Entity.hpp"
#include "./Globals.hpp"
#include "./Util/Math.hpp"

class Rigidbody
{
public:
    sf::Vector2f linearVelocity;
    sf::Vector2f linearAcceleration;
    float angularVelocity;
    float angularAcceleration;
    sf::Vector2f force;
    float torque;
    float elasticity;

    void linearEuler(sf::Shape *shape);
    void linearEuler(sf::Shape *shape, bool &pin);
    void verlet(sf::Shape *shape, bool &pin);
    void angularEuler(sf::Shape *shape, Entity *entity);
    void calcTorque(sf::Shape *shape);
    void calcAngularAcceleration(Entity *entity);

    // verlet related
    sf::Vector2f current, previous;

    //....
    sf::Vector2f gravity = sf::Vector2f(0.f, 0.1f);
    sf::Vector2f damping;
    sf::Vector2f wind;

    sf::Clock clock;
    float wind_strength_x = 0.f;
    float wind_strength_y = 0.f;
    float wind_changerate = 2.f;
    float wind_amplitude = 0.01f;

    int tempo = 0;
};