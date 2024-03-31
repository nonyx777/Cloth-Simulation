#include "../../include/Util/Grid.hpp"

void configureGrid(uint size, std::vector<std::vector<Circle>>* grid)
{
    for(uint i = 0; i < GLOBAL::row; i++){
        std::vector<Circle> row_cells;
        for(uint j = 0; j < GLOBAL::col; j++){
            Circle circle = Circle(size, sf::Vector2f((i * 5) + ((GLOBAL::window_width * 27.f)/100.f), (j * 5)));
            circle.row = i;
            circle.col = j;

            if(j == 0)
                circle.pin = true;

            row_cells.push_back(circle);
        }
        grid->push_back(row_cells);
    }
}