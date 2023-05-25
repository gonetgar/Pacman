#ifndef FRUIT
#define FRUIT

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Position.h"
#include "Operation.h"
#include "Board.h"
#include "Creature.h"

class Fruit : public Creature
{
    int val; // 5-9
public:
    Fruit(Board& game_board);
    int getVal() { return val; }
    void printFruit();
    void fruitMovement(Board& game_board, vector<Fruit>& other_array, int num_fruits);
    void move(Board& game_board, vector<Fruit>& other_array, int num_fruits, int new_row, int new_col, int* moved);
    void reservePreviousItem(Board& game_board);
};

#endif