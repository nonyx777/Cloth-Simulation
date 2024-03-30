#pragma once

#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "../Util/Gizmo.hpp"
#include "../Util/Grid.hpp"
#include "../Globals.hpp"
#include "../Util/Collision.hpp"

class Scene : public GameObject
{
private:
    static Scene *instance;
    std::vector<std::vector<Circle>> grid;
    std::vector<Line> lines;
    bool aligned = false;
    float rest_length = 20.f;
    float stiffness = 0.2f;

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
    void update(sf::Vector2f &vec, float dt);
    void render(sf::RenderTarget *target) override;
};