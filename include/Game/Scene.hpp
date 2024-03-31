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
    Box range;

    bool aligned = false;
    float stiffness = 0.5f;

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
    void render(sf::RenderTarget *target) override;

    void move(const sf::Vector2f &position);
};