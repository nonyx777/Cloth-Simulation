#include "../../include/Game/Scene.hpp"

Scene *Scene::instance = nullptr;

Scene::Scene()
{
    configureGrid(GLOBAL::particle_size, &this->grid);
}

Scene::~Scene()
{
    delete instance;
}

Scene *Scene::getInstance()
{
    if (!instance)
        instance = new Scene();

    return instance;
}

void Scene::update(float dt)
{
    // solver
    this->lines.clear();
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (i == GLOBAL::row - 1 && j == GLOBAL::col - 1)
            {
                continue;
            }

            if (j != GLOBAL::col - 1 && i == GLOBAL::row - 1)
            {
                Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i][j + 1].property.getPosition());
                this->lines.push_back(line);
                this->solve(&this->grid[i][j], &this->grid[i][j + 1]);
            }
            else if (j == GLOBAL::col - 1 && i < GLOBAL::row - 1)
            {
                Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i + 1][j].property.getPosition());
                this->lines.push_back(line);
                this->solve(&this->grid[i][j], &this->grid[i + 1][j]);
            }
            else
            {
                Line line1 = Line(this->grid[i][j].property.getPosition(), this->grid[i][j + 1].property.getPosition());
                this->lines.push_back(line1);
                Line line2 = Line(this->grid[i][j].property.getPosition(), this->grid[i + 1][j].property.getPosition());
                this->lines.push_back(line2);
                this->solve(&this->grid[i][j], &this->grid[i][j + 1], &this->grid[i + 1][j]);
            }
        }
    }

    // update
    for (uint i = 0; i < grid.size(); i++)
    {
        for (uint j = 0; j < grid[i].size(); j++)
        {
            this->grid[i][j].update(dt);
        }
    }
}

void Scene::render(sf::RenderTarget *target)
{
    if (GLOBAL::display_particle)
    {
        for (uint i = 0; i < grid.size(); i++)
        {
            for (uint j = 0; j < grid[i].size(); j++)
            {
                target->draw(grid[i][j].property);
            }
        }
    }

    for (Line &line : this->lines)
        line.render(target);

    range.render(target);
}

void Scene::solve(Circle *a, Circle *b)
{
    sf::Vector2f displace = a->property.getPosition() - b->property.getPosition();
    sf::Vector2f unit = Math::_normalize(displace);
    float distance = Math::_length(displace);

    sf::Vector2f force = (stiffness * (distance - GLOBAL::rest_length)) * unit;

    a->force += -(force);
    b->force += force;
}

void Scene::solve(Circle *a, Circle *b, Circle *c)
{
    // a -> b
    sf::Vector2f displace = a->property.getPosition() - b->property.getPosition();
    sf::Vector2f unit = Math::_normalize(displace);
    float distance = Math::_length(displace);

    sf::Vector2f force = (stiffness * (distance - GLOBAL::rest_length)) * unit;

    a->force += -(force);
    b->force += force;

    // a -> c
    displace = a->property.getPosition() - c->property.getPosition();
    unit = Math::_normalize(displace);
    distance = Math::_length(displace);

    force = (stiffness * (distance - GLOBAL::rest_length)) * unit;
    a->force += -(force);
    c->force += force;
}

void Scene::move(const sf::Vector2f &position)
{
    for (uint i = 0; i < grid.size(); i++)
    {
        for (uint j = 0; j < grid[i].size(); j++)
        {
            float d = Math::_length(position - grid[i][j].property.getPosition());
            if (d < 20.f)
            {
                grid[i][j].force += sf::Vector2f(2.f, 2.f);
            }
        }
    }
}