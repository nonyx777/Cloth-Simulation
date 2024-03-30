#include "../../include/Util/Grid.hpp"

void configureGrid(uint size, std::vector<std::vector<Circle>>* grid)
{
    std::vector<std::vector<Circle>> cells;
    uint row = 10;
    uint column = 10;

    for(uint i = 0; i < row; i++){
        std::vector<Circle> row_cells;
        for(uint j = 0; j < column; j++){
            Circle circle = Circle(size, sf::Vector2f((i * 30) + 165, (j * 30) + 30));
            circle.row = i;
            circle.col = j;

            if(j == 0)
                circle.pin = true;

            row_cells.push_back(circle);
        }
        grid->push_back(row_cells);
    }
}