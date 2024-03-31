#pragma once

#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "../Util/Gizmo.hpp"
#include "../Util/Grid.hpp"
#include "../Globals.hpp"
#include "../Util/Collision.hpp"
#include "../Util/Quadtree.hpp"

class Scene : public GameObject
{
private:
    static Scene *instance;
    std::vector<std::vector<Circle>> grid;
    std::vector<Line> lines;
    Box windRange = Box(sf::Vector2f(100.f, 60.f), sf::Vector2f(GLOBAL::window_width/2.f, GLOBAL::window_height/2.f));
    float amplitude = 100.f;
    float frequency = 1.f;
    int wind_count = 0;
    bool aligned = false;
    float stiffness = 0.3f;

private:
    Scene();
    ~Scene();

private:
    void solve(Circle *a, Circle *b);
    void solve(Circle *a, Circle *b, Circle *c);

public:
    // Delete copy constructor and assignment operator to prevent cloning
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    static Scene *getInstance();

    void update(float dt) override;
    void update(float dt, const sf::Vector2f &position);
    void render(sf::RenderTarget *target) override;

    void move(const sf::Vector2f &position);
    void tear(const sf::Vector2f &position);
};