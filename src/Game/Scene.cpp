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
    this->lines.clear();

    sf::Vector2f wind_mov = sf::Vector2f(amplitude * Math::_cos(wind_count * frequency), amplitude * Math::_sin(wind_count * frequency)) + sf::Vector2f(GLOBAL::window_width / 2.f, GLOBAL::window_height / 4.f);
    windRange.property.setPosition(wind_mov);

    for (uint i = 0; i < grid.size(); i++)
    {
        for (uint j = 0; j < grid[i].size(); j++)
        {
            float d = Math::_length(windRange.property.getPosition() - grid[i][j].property.getPosition());
            if (d < 70.f)
            {
                grid[i][j].force += sf::Vector2f(0.05f, 0.05f);
            }
        }
    }

    // solver
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (i == GLOBAL::row - 1 && j == GLOBAL::col - 1)
            {
                continue;
            }

            if (grid[i][j].teared)
            {
                continue;
            }

            if (j != GLOBAL::col - 1 && i == GLOBAL::row - 1)
            {
                if (grid[i][j + 1].teared)
                    continue;

                Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i][j + 1].property.getPosition());
                this->lines.push_back(line);
                this->solve(&this->grid[i][j], &this->grid[i][j + 1]);
            }
            else if (j == GLOBAL::col - 1 && i < GLOBAL::row - 1)
            {
                if (grid[i + 1][j].teared)
                    continue;

                Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i + 1][j].property.getPosition());
                this->lines.push_back(line);
                this->solve(&this->grid[i][j], &this->grid[i + 1][j]);
            }
            else
            {
                if (grid[i][j + 1].teared == false && grid[i + 1][j].teared == false)
                {
                    Line line1 = Line(this->grid[i][j].property.getPosition(), this->grid[i][j + 1].property.getPosition());
                    this->lines.push_back(line1);
                    Line line2 = Line(this->grid[i][j].property.getPosition(), this->grid[i + 1][j].property.getPosition());
                    this->lines.push_back(line2);
                    this->solve(&this->grid[i][j], &this->grid[i][j + 1], &this->grid[i + 1][j]);
                    continue;
                }
                if (grid[i][j + 1].teared == false && grid[i + 1][j].teared == true)
                {
                    Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i][j + 1].property.getPosition());
                    this->lines.push_back(line);
                    this->solve(&this->grid[i][j], &this->grid[i][j + 1]);
                    continue;
                }

                if (grid[i][j + 1].teared == true && grid[i + 1][j].teared == false)
                {
                    Line line = Line(this->grid[i][j].property.getPosition(), this->grid[i+1][j].property.getPosition());
                    this->lines.push_back(line);
                    this->solve(&this->grid[i][j], &this->grid[i+1][j]);
                    continue;
                }
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

    if (wind_count < 360)
        wind_count++;
    else
        wind_count = 0;
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

void Scene::tear(const sf::Vector2f &position)
{
    for (uint i = 0; i < grid.size(); i++)
    {
        for (uint j = 0; j < grid[i].size(); j++)
        {
            float d = Math::_length(position - grid[i][j].property.getPosition());
            if (d < 5.f)
            {
                grid[i][j].teared = true;
            }
        }
    }
}