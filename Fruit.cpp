#include "Fruit.h"

Fruit::Fruit(Board& game_board)      // default c'tor
{
    //srand(time(NULL));
    int newVal, newRow, newCol, goodPos = 0;

    newVal = (rand() % (4)) + 5;     //// 5-9
    this->val = newVal;

    while (goodPos == 0)
    {
        newRow = (rand() % (22)) + 1;     ////   1-22
        newCol = (rand() % (82)) + 1;     //// 1-82
        if(game_board.getCellItem(newRow, newCol) == BREADCRUMB)
            goodPos = 1;
    }

    /// set starting position at
    this->current_position.setRow(newRow);
    this->current_position.setCol(newCol);
}


void Fruit::printFruit()   /// print fruit
{
    gotoxy(this->current_position.getCol(), this->current_position.getRow());
    switch (this->val)
    {
    case 5:
        cout << 'S';
        break;
    case 6:
        cout << 'B';
        break;
    case 7:
        cout << 'M';
        break;
    case 8:
        cout << 'A';
        break;
    case 9:
        cout << 'W';
        break;
    default:
        break;
    }
}

// places the ghost at random place on the board
void Fruit::fruitMovement(Board& game_board, vector<Fruit>& other_array, int num_fruits)   ///random movement
{
    //srand(time(NULL));
    int moved = 0;

    while (moved == 0)
    {
        int moveDir = (rand() % (4)) + 1;
        int curRow = this->current_position.getRow();
        int curCol = this->current_position.getCol();

        switch (moveDir)
        {
        case FRUIT_UP:   /////make fruit_dir = ghost dir in oprations
            this->move(game_board, other_array, num_fruits, curRow - 1, curCol, &moved);
            break;
        case FRUIT_DOWN:
            this->move(game_board, other_array, num_fruits, curRow + 1, curCol, &moved);
            break;
        case FRUIT_RIGHT:
            this->move(game_board, other_array, num_fruits, curRow, curCol + 1, &moved);
            break;
        case FRUIT_LEFT:
            this->move(game_board, other_array, num_fruits, curRow, curCol - 1, &moved);
            break;
        }
    }
}

void Fruit::move(Board& game_board, vector<Fruit>& other_array, int num_fruits, int new_row, int new_col, int* moved)     /// the actual movement
{
    Position new_pos(new_row, new_col);

    // check if the next position is available
    char new_position_on_board = game_board.getCellItem(new_row, new_col);
    bool collision = false; /// check if fruits are collisioning 🙂

    for (int i = 0; i < num_fruits; i++)
    {
        if (new_pos == other_array[i].current_position)
            collision = true;
    }

    if (new_position_on_board != WALL && new_position_on_board != SIDE_TUNNEL && new_position_on_board != UP_DOWN_TUNNEL && collision == false)
    {
        this->reservePreviousItem(game_board);
        this->current_position.setRow(new_row);
        this->current_position.setCol(new_col);
        this->printFruit();
        *moved = 1;
    }
}

void Fruit::reservePreviousItem(Board& game_board)
{
    this->prev_pos = this->current_position; // save the current position so that we can go back to it
    int prevRow = this->prev_pos.getRow();
    int prevCol = this->prev_pos.getCol();
    char prev_item_on_board = game_board.getCellItem(prevRow, prevCol);

    // print the previous item that was on the board
    if (prev_item_on_board == BREADCRUMB)
    {
        gotoxy(prevCol, prevRow);
        cout << (char)BREADCRUMB;
    }
    else if (prev_item_on_board == EATEN || prev_item_on_board == EMPTY_CELL_BOARD)
    {
        gotoxy(prevCol, prevRow);
        cout << (char)EATEN;
    }
}