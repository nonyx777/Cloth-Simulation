#include "../include/Rigidbody.hpp"

void Rigidbody::linearEuler(sf::Shape *shape)
{
    this->linearAcceleration += this->force;
    this->linearVelocity += this->linearAcceleration;
    shape->move(this->linearVelocity);

    this->linearAcceleration = sf::Vector2f(0.f, 0.f);
    this->force = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::linearEuler(sf::Shape *shape, bool &pin)
{
    if (pin)
    {
        this->force = sf::Vector2f(0.f, 0.f);
        this->linearAcceleration = sf::Vector2f(0.f, 0.f);
        this->linearVelocity = sf::Vector2f(0.f, 0.f);
        return;
    }

    this->force += gravity;
    this->damping = this->linearVelocity * -0.01f;
    this->force += damping;
    this->linearAcceleration += force;
    this->linearVelocity += this->linearAcceleration;
    shape->move(this->linearVelocity + this->damping);

    this->linearAcceleration = sf::Vector2f(0.f, 0.f);
    this->force = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::verlet(sf::Shape *shape, bool &pin)
{
    if (pin)
    {
        this->force = sf::Vector2f(0.f, 0.f);
        this->linearAcceleration = sf::Vector2f(0.f, 0.f);
        this->linearVelocity = sf::Vector2f(0.f, 0.f);
        return;
    }

    this->force += gravity;
    this->linearAcceleration += this->force;

    current = shape->getPosition();
    this->linearVelocity = (current - previous) + this->linearAcceleration;
    shape->move(this->linearVelocity);
    previous = current;

    this->force = sf::Vector2f(0.f, 0.f);
    this->linearAcceleration = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::angularEuler(sf::Shape *shape, Entity *entity)
{
    this->calcTorque(shape);
    this->calcAngularAcceleration(entity);

    this->angularVelocity += this->angularAcceleration;
    shape->rotate(this->angularVelocity);

    this->angularAcceleration = 0.f;
}

void Rigidbody::calcTorque(sf::Shape *shape)
{
    // t = frsin@
    this->torque = shape->getPosition().x * this->force.y - shape->getPosition().y * this->force.x;
}

void Rigidbody::calcAngularAcceleration(Entity *entity)
{
    this->angularAcceleration = this->torque / entity->momentOfInertia;
}