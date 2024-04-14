#include "../include/ConfigWindow.hpp"

ConfigWindow::ConfigWindow() : Window()
{
    this->initWindow();
    this->initImGui();
}

void ConfigWindow::initWindow()
{
    this->video_mode.width = GLOBAL::config_window_width;
    this->video_mode.height = GLOBAL::config_window_height;
    this->window = new sf::RenderWindow(this->video_mode, "Configuration Window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void ConfigWindow::update(float dt)
{
    this->pollEvent();

    this->updateImGui();
    ImGui::Begin("Parameters");
    ImGui::SetWindowSize(ImVec2(this->window->getSize()));

    // configure engine window size
    ImGui::Text("Window Size");
    ImGui::InputInt("Window Height", &GLOBAL::window_height);
    ImGui::InputInt("Window Width", &GLOBAL::window_width);

    GLOBAL::window_height = Math::_clampOnRange(GLOBAL::window_height, 400, 1000);
    GLOBAL::window_width = Math::_clampOnRange(GLOBAL::window_width, 400, 1000);

    // configure grid
    ImGui::Text("Particle Grid Configuration");
    ImGui::InputInt("Row: ", &GLOBAL::row);
    ImGui::InputInt("Column: ", &GLOBAL::col);
    ImGui::InputInt("Particle Size", &GLOBAL::particle_size);
    if (ImGui::Button("Display Particle"))
        GLOBAL::display_particle = !GLOBAL::display_particle;
    ImGui::Text("Display Grid: %s", GLOBAL::display_particle ? "True" : "False");
    ImGui::InputFloat("Damping Coefficient", &GLOBAL::damping_coefficient);
    ImGui::InputFloat("Resting Length", &GLOBAL::rest_length);
    ImGui::InputFloat("Tear Distance", &GLOBAL::tear_distance);

    ImGui::End();
}

void ConfigWindow::render(sf::RenderTarget *target)
{
    //....
}