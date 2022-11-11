#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <windows.h>

using std::cout; using std::cin; using std::string; using std::vector; using std::to_string;

/*
* written by chapel1337
* made on 11/11/2022
* took awhile to make, i experienced multiple delays because i had a friend visit
* icon of executable is leo (requested by sam)
* probably one of the hardest programs i have ever made
* not much else to say about this
*/

vector<vector<char>> presetMap
{
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
    { '-', '-', '-', '-', '-', '-', '|', '-', '-', '-', '-', '-', '-', '|', '-', '-', '-', '-', '-', '-', },
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
    { '-', '-', '-', '-', '-', '-', '|', '-', '-', '-', '-', '-', '-', '|', '-', '-', '-', '-', '-', '-', },
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
    { ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', },
};

vector<vector<char>> map{ presetMap };
vector<vector<char>> currentMap{ map };

vector<vector<bool>> markersPlaced
{
    { false, false, false, },
    { false, false, false, },
    { false, false, false, },
};

// was originally a bool vector, but changed to integer so i could add default indices
// 0 and 1 evaluate as true and false, so the code might look ugly
vector<vector<int>> markersPlacedPlayer
{
    { 3, 3, 3, },
    { 3, 3, 3, },
    { 3, 3, 3, },
};

vector<vector<bool>> outcomeMapHighlight
{
    { false, false, false, },
    { false, false, false, },
    { false, false, false, },
};

int markerY{ 1 };
int markerX{ 1 };

int mapY{ static_cast<int>(map.size()) };
int mapX{ static_cast<int>(map[0].size()) };

// player1 = true, player2 = false
// X = false, O = true
bool player{ false };

void clear()
{
    system("cls");
}

void title(string title)
{
    SetConsoleTitleA(("tic tac toe - " + title).c_str());
}

void title()
{
    SetConsoleTitleA("tic tac toe");
}

void title(string title, int i)
{
    SetConsoleTitleA(("tic tac toe - " + title + to_string(i)).c_str()); // many paranthesis
}

void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void getInput();
void menu();
void start();

void winTie(bool outcome, bool player) // true = win, false = tie
{
    clear();

    string response{};

    for (int i{ 0 }; i < markersPlacedPlayer.size(); ++i)
    {
        for (int o{ 0 }; o < markersPlacedPlayer[i].size(); ++o)
        {
            if (outcomeMapHighlight[i][o] == true)
            {
                setTextColor(2);
                if (markersPlacedPlayer[i][o] == 0)
                {
                    cout << 'X';
                }
                else if (markersPlacedPlayer[i][o] == 1)
                {
                    cout << 'O';
                }
                else
                {
                    cout << ' ';
                }
                resetTextColor();
            }
            else
            {
                if (markersPlacedPlayer[i][o] == 0)
                {
                    cout << 'X';
                }
                else if (markersPlacedPlayer[i][o] == 1)
                {
                    cout << 'O';
                }
                else
                {
                    cout << ' ';
                }
            }

            if (o != 2)
            {
                cout << " | ";
            }
        }

        cout << '\n';

        if (i != 2)
        {
            cout << "--|---|--\n";
        }
    }
    cout << "\n\n";

    if (outcome && player)
    {
        title("player 1 wins!");

        cout << "player 1 wins!\n\n";
    }
    else if (outcome && !player)
    {
        title("player 2 wins!");

        cout << "player 2 wins!\n\n";
    }
    else if (!outcome)
    {
        title("tie!");

        cout << "tie!\n\n";
    }

    for (int i{ 0 }; i < markersPlaced.size(); ++i)
    {
        for (int o{ 0 }; o < markersPlaced[i].size(); ++o)
        {
            markersPlaced[i][o] = false;
            markersPlacedPlayer[i][o] = 3;
            outcomeMapHighlight[i][o] = false;
        }
    }

    markerY = 1;
    markerX = 1;
    player = false;

    map.clear();
    map = presetMap;
    currentMap.clear();
    currentMap = map;

    cin.get();
    cin.ignore();

    clear();
    
    cout << "would you like to play again?\n\n";
    
    cout << "> ";
    cin >> response;

    if (response == "yes" || response == "y")
    {
        start();
    }
    else if (response == "no" || response == "n")
    {
        menu();
    }
    else
    {
        winTie(outcome, player);
    }
}

// you are now entering: the first layer of hell
void decideOutcome(bool filled)
{
    // false = X, true = O
    if (markersPlacedPlayer[0][0] == 1 && markersPlacedPlayer[1][1] == 1 && markersPlacedPlayer[2][2] == 1)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][0] == 1 && markersPlacedPlayer[1][1] == 1 && markersPlacedPlayer[2][2] == 1)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[0][2] = true;

        winTie(true, true);
    }
    
    else if (markersPlacedPlayer[0][0] == 1 && markersPlacedPlayer[1][0] == 1 && markersPlacedPlayer[2][0] == 1)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[1][0] = true;
        outcomeMapHighlight[2][0] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][1] == 1 && markersPlacedPlayer[1][1] == 1 && markersPlacedPlayer[2][1] == 1)
    {
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[2][1] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][2] == 1 && markersPlacedPlayer[1][2] == 1 && markersPlacedPlayer[2][2] == 1)
    {
        outcomeMapHighlight[0][2] = true;
        outcomeMapHighlight[1][2] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }

    else if (markersPlacedPlayer[0][0] == 1 && markersPlacedPlayer[0][1] == 1 && markersPlacedPlayer[0][2] == 1)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[0][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[1][0] == 1 && markersPlacedPlayer[1][1] == 1 && markersPlacedPlayer[1][2] == 1)
    {
        outcomeMapHighlight[1][0] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[1][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[2][0] == 1 && markersPlacedPlayer[2][1] == 1 && markersPlacedPlayer[2][2] == 1)
    {
        outcomeMapHighlight[2][0] = true;
        outcomeMapHighlight[2][1] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }


    if (markersPlacedPlayer[0][0] == 0 && markersPlacedPlayer[1][1] == 0 && markersPlacedPlayer[2][2] == 0)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][0] == 0 && markersPlacedPlayer[1][1] == 0 && markersPlacedPlayer[2][2] == 0)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[0][2] = true;

        winTie(true, true);
    }

    else if (markersPlacedPlayer[0][0] == 0 && markersPlacedPlayer[1][0] == 0 && markersPlacedPlayer[2][0] == 0)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[1][0] = true;
        outcomeMapHighlight[2][0] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][1] == 0 && markersPlacedPlayer[1][1] == 0 && markersPlacedPlayer[2][1] == 0)
    {
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[2][1] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[0][2] == 0 && markersPlacedPlayer[1][2] == 0 && markersPlacedPlayer[2][2] == 0)
    {
        outcomeMapHighlight[0][2] = true;
        outcomeMapHighlight[1][2] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }

    else if (markersPlacedPlayer[0][0] == 0 && markersPlacedPlayer[0][1] == 0 && markersPlacedPlayer[0][2] == 0)
    {
        outcomeMapHighlight[0][0] = true;
        outcomeMapHighlight[0][1] = true;
        outcomeMapHighlight[0][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[1][0] == 0 && markersPlacedPlayer[1][1] == 0 && markersPlacedPlayer[1][2] == 0)
    {
        outcomeMapHighlight[1][0] = true;
        outcomeMapHighlight[1][1] = true;
        outcomeMapHighlight[1][2] = true;

        winTie(true, true);
    }
    else if (markersPlacedPlayer[2][0] == 0 && markersPlacedPlayer[2][1] == 0 && markersPlacedPlayer[2][2] == 0)
    {
        outcomeMapHighlight[2][0] = true;
        outcomeMapHighlight[2][1] = true;
        outcomeMapHighlight[2][2] = true;

        winTie(true, true);
    }

    else if (filled)
    {
        winTie(false, true);
    }
    else
    {
        return;
    }
}
// you are now exiting: the first layer of hell

// you are now entering: the second layer hell
void positionMarker()
{
    currentMap.clear();
    currentMap = map;

    int placedCount{};

    for (int i{ 0 }; i < markersPlaced.size(); ++i)
    {
        for (int o{ 0 }; o < markersPlaced[i].size(); ++o)
        {
            if (markersPlaced[i][o] == true)
            {
                placedCount++;
            }
        }
    }

    if (placedCount == 9)
    {
        decideOutcome(true);
    }
    else
    {
        decideOutcome(false);
    }

    if (player)
    {
        if (markerY == 1 && markerX == 1)
        {
            currentMap[0][2] = '/';
            currentMap[0][3] = '\\';

            currentMap[1][2] = '\\';
            currentMap[1][3] = '/';
        }
        else if (markerY == 2 && markerX == 1)
        {
            currentMap[3][2] = '/';
            currentMap[3][3] = '\\';

            currentMap[4][2] = '\\';
            currentMap[4][3] = '/';
        }
        else if (markerY == 3 && markerX == 1)
        {
            currentMap[6][2] = '/';
            currentMap[6][3] = '\\';

            currentMap[7][2] = '\\';
            currentMap[7][3] = '/';
        }


        else if (markerY == 1 && markerX == 2)
        {
            currentMap[0][9] = '/';
            currentMap[0][10] = '\\';

            currentMap[1][9] = '\\';
            currentMap[1][10] = '/';
        }
        else if (markerY == 2 && markerX == 2)
        {
            currentMap[3][9] = '/';
            currentMap[3][10] = '\\';

            currentMap[4][9] = '\\';
            currentMap[4][10] = '/';
        }
        else if (markerY == 3 && markerX == 2)
        {
            currentMap[6][9] = '/';
            currentMap[6][10] = '\\';

            currentMap[7][9] = '\\';
            currentMap[7][10] = '/';
        }


        else if (markerY == 1 && markerX == 3)
        {
            currentMap[0][16] = '/';
            currentMap[0][17] = '\\';

            currentMap[1][16] = '\\';
            currentMap[1][17] = '/';
        }
        else if (markerY == 2 && markerX == 3)
        {
            currentMap[3][16] = '/';
            currentMap[3][17] = '\\';

            currentMap[4][16] = '\\';
            currentMap[4][17] = '/';
        }
        else if (markerY == 3 && markerX == 3)
        {
            currentMap[6][16] = '/';
            currentMap[6][17] = '\\';

            currentMap[7][16] = '\\';
            currentMap[7][17] = '/';
        }
    }
    else
    {
        if (markerY == 1 && markerX == 1)
        {
            currentMap[0][2] = '\\';
            currentMap[0][3] = '/';

            currentMap[1][2] = '/';
            currentMap[1][3] = '\\';
        }
        else if (markerY == 2 && markerX == 1)
        {
            currentMap[3][2] = '\\';
            currentMap[3][3] = '/';

            currentMap[4][2] = '/';
            currentMap[4][3] = '\\';
        }
        else if (markerY == 3 && markerX == 1)
        {
            currentMap[6][2] = '\\';
            currentMap[6][3] = '/';

            currentMap[7][2] = '/';
            currentMap[7][3] = '\\';
        }


        else if (markerY == 1 && markerX == 2)
        {
            currentMap[0][9] = '\\';
            currentMap[0][10] = '/';

            currentMap[1][9] = '/';
            currentMap[1][10] = '\\';
        }
        else if (markerY == 2 && markerX == 2)
        {
            currentMap[3][9] = '\\';
            currentMap[3][10] = '/';

            currentMap[4][9] = '/';
            currentMap[4][10] = '\\';
        }
        else if (markerY == 3 && markerX == 2)
        {
            currentMap[6][9] = '\\';
            currentMap[6][10] = '/';

            currentMap[7][9] = '/';
            currentMap[7][10] = '\\';
        }


        else if (markerY == 1 && markerX == 3)
        {
            currentMap[0][16] = '\\';
            currentMap[0][17] = '/';

            currentMap[1][16] = '/';
            currentMap[1][17] = '\\';
        }
        else if (markerY == 2 && markerX == 3)
        {
            currentMap[3][16] = '\\';
            currentMap[3][17] = '/';

            currentMap[4][16] = '/';
            currentMap[4][17] = '\\';
        }
        else if (markerY == 3 && markerX == 3)
        {
            currentMap[6][16] = '\\';
            currentMap[6][17] = '/';

            currentMap[7][16] = '/';
            currentMap[7][17] = '\\';
        }
    }
}
// you are now exiting: the second layer of hell

void displayStatistics()
{
    cout << "marker y: " << markerY << '\n';
    cout << "marker x: " << markerX << "\n\n";

    // :scream:
    if (player) cout << "player 1's turn\n\n";
    else cout << "player 2's turn\n\n";

    // cout << "map y: " << mapY << '\n';
    // cout << "map x: " << mapX << '\n';
}

void refresh()
{
    system("cls");
    positionMarker();
    displayStatistics();

    for (int i{ 0 }; i < 5; ++i)
    {
        cout << '\n';
    }

    for (int i{ 0 }; i < currentMap.size(); ++i)
    {
        for (int i{ 0 }; i < 45; ++i)
        {
            cout << ' ';
        }

        for (int o{ 0 }; o < currentMap[i].size(); ++o)
        {
            /*
            if (currentMap[i][o] == '/' && !player || currentMap[i][o] == '\\' && !player)
            {
                setTextColor(4);
                cout << currentMap[i][o];
                resetTextColor();
            }
            else if (currentMap[i][o] == '/' && player || currentMap[i][o] == '\\' && player)
            {
                setTextColor(2);
                cout << currentMap[i][o];
                resetTextColor();
            }
            else
            {
                cout << currentMap[i][o];
            }
            */

            cout << currentMap[i][o];
        }

        cout << '\n';
    }

    getInput();
}

// you are now entering: the second layer of hell
void placeMarker()
{
    if (player)
    {
        if (markerY == 1 && markerX == 1 && markersPlaced[0][0] == false)
        {
            markersPlaced[0][0] = true;
            markersPlacedPlayer[0][0] = true;

            map[0][2] = '/';
            map[0][3] = '\\';

            map[1][2] = '\\';
            map[1][3] = '/';
        }
        else if (markerY == 2 && markerX == 1 && markersPlaced[1][0] == false)
        {
            markersPlaced[1][0] = true;
            markersPlacedPlayer[1][0] = true;

            map[3][2] = '/';
            map[3][3] = '\\';

            map[4][2] = '\\';
            map[4][3] = '/';
        }
        else if (markerY == 3 && markerX == 1 && markersPlaced[2][0] == false)
        {
            markersPlaced[2][0] = true;
            markersPlacedPlayer[2][0] = true;

            map[6][2] = '/';
            map[6][3] = '\\';

            map[7][2] = '\\';
            map[7][3] = '/';
        }


        else if (markerY == 1 && markerX == 2 && markersPlaced[0][1] == false)
        {
            markersPlaced[0][1] = true;
            markersPlacedPlayer[0][1] = true;

            map[0][9] = '/';
            map[0][10] = '\\';

            map[1][9] = '\\';
            map[1][10] = '/';
        }
        else if (markerY == 1 && markerX == 3 && markersPlaced[0][2] == false)
        {
            markersPlaced[0][2] = true;
            markersPlacedPlayer[0][2] = true;

            map[0][16] = '/';
            map[0][17] = '\\';

            map[1][16] = '\\';
            map[1][17] = '/';
        }

        else if (markerY == 2 && markerX == 2 && markersPlaced[1][1] == false)
        {
            markersPlaced[1][1] = true;
            markersPlacedPlayer[1][1] = true;

            map[3][9] = '/';
            map[3][10] = '\\';

            map[4][9] = '\\';
            map[4][10] = '/';
        }
        else if (markerY == 2 && markerX == 3 && markersPlaced[1][2] == false)
        {
            markersPlaced[1][2] = true;
            markersPlacedPlayer[1][2] = true;

            map[3][16] = '/';
            map[3][17] = '\\';

            map[4][16] = '\\';
            map[4][17] = '/';
        }

        else if (markerY == 3 && markerX == 2 && markersPlaced[2][1] == false)
        {
            markersPlaced[2][1] = true;
            markersPlacedPlayer[2][1] = true;

            map[6][9] = '/';
            map[6][10] = '\\';

            map[7][9] = '\\';
            map[7][10] = '/';
        }
        else if (markerY == 3 && markerX == 3 && markersPlaced[2][2] == false)
        {
            markersPlaced[2][2] = true;
            markersPlacedPlayer[2][2] = true;

            map[6][16] = '/';
            map[6][17] = '\\';

            map[7][16] = '\\';
            map[7][17] = '/';
        }
        else
        {
            return;
        }

        player = false;
    }

    else
    {
        if (markerY == 1 && markerX == 1 && markersPlaced[0][0] == false)
        {
            markersPlaced[0][0] = true;
            markersPlacedPlayer[0][0] = false;

            map[0][2] = '\\';
            map[0][3] = '/';

            map[1][2] = '/';
            map[1][3] = '\\';
        }
        else if (markerY == 2 && markerX == 1 && markersPlaced[1][0] == false)
        {
            markersPlaced[1][0] = true;
            markersPlacedPlayer[1][0] = false;

            map[3][2] = '\\';
            map[3][3] = '/';

            map[4][2] = '/';
            map[4][3] = '\\';
        }
        else if (markerY == 3 && markerX == 1 && markersPlaced[2][0] == false)
        {
            markersPlaced[2][0] = true;
            markersPlacedPlayer[2][0] = false;

            map[6][2] = '\\';
            map[6][3] = '/';

            map[7][2] = '/';
            map[7][3] = '\\';
        }


        else if (markerY == 1 && markerX == 2 && markersPlaced[0][1] == false)
        {
            markersPlaced[0][1] = true;
            markersPlacedPlayer[0][1] = false;

            map[0][9] = '\\';
            map[0][10] = '/';

            map[1][9] = '/';
            map[1][10] = '\\';
        }
        else if (markerY == 1 && markerX == 3 && markersPlaced[0][2] == false)
        {
            markersPlaced[0][2] = true;
            markersPlacedPlayer[0][2] = false;

            map[0][16] = '\\';
            map[0][17] = '/';

            map[1][16] = '/';
            map[1][17] = '\\';
        }
        
        else if (markerY == 2 && markerX == 2 && markersPlaced[1][1] == false)
        {
            markersPlaced[1][1] = true;
            markersPlacedPlayer[1][1] = false;

            map[3][9] = '\\';
            map[3][10] = '/';

            map[4][9] = '/';
            map[4][10] = '\\';
        }
        else if (markerY == 2 && markerX == 3 && markersPlaced[1][2] == false)
        {
            markersPlaced[1][2] = true;
            markersPlacedPlayer[1][2] = false;

            map[3][16] = '\\';
            map[3][17] = '/';

            map[4][16] = '/';
            map[4][17] = '\\';
        }

        else if (markerY == 3 && markerX == 2 && markersPlaced[2][1] == false)
        {
            markersPlaced[2][1] = true;
            markersPlacedPlayer[2][1] = false;

            map[6][9] = '\\';
            map[6][10] = '/';

            map[7][9] = '/';
            map[7][10] = '\\';
        }
        else if (markerY == 3 && markerX == 3 && markersPlaced[2][2] == false)
        {
            markersPlaced[2][2] = true;
            markersPlacedPlayer[2][2] = false;

            map[6][16] = '\\';
            map[6][17] = '/';

            map[7][16] = '/';
            map[7][17] = '\\';
        }

        else
        {
            return;
        }

        player = true;
    }
}
// you are now exiting: the second layer of hell

void moveMarker(char direction)
{
    if (direction == 'w' && markerY != 1)
    {
        markerY--;
    }
    else if (direction == 's' && markerY != 3)
    {
        markerY++;
    }
    else if (direction == 'd' && markerX != 3)
    {
        markerX++;
    }
    else if (direction == 'a' && markerX != 1)
    {
        markerX--;
    }
}

void getInput()
{
    int input{ _getch() };

    switch (input)
    {
    case 'W':
    case 'w':
        moveMarker('w');
        break;

    case 'S':
    case 's':
        moveMarker('s');
        break;

    case 'D':
    case 'd':
        moveMarker('d');
        break;

    case 'A':
    case 'a':
        moveMarker('a');
        break;

    case ' ':
        placeMarker();
        break;

    default:
        getInput();
        break;
    }

    refresh();
}

void quit()
{
    clear();

    for (int i{ 3 }; i > 0; --i)
    {
        title("exiting in", i);
        cout << "okay, exiting in " << i;

        Sleep(1000);
        clear();
    }

    Beep(200, 325);
    exit(1);
}

void start()
{
    title();

    refresh();
    getInput();
}

void menu()
{
    clear();
    title("menu");

    char response{};

    cout << "tic tac toe\n\n";

    cout << "1. start\n";
    cout << "2. quit\n\n";

    cout << "> ";
    cin >> response;

    switch (response)
    {
    case '1':
        start();
        break;

    case '2':
        quit();
        break;
    }

    menu();
}

int main()
{
    title("credits");

    setTextColor(6);
    cout << "written by chapel1337\n";
    cout << "made on 11/11/2022\n";
    resetTextColor();

    /*
    for (int i{ 0 }; i < 26; ++i)
    {
        cout << '\n';
    }

    setTextColor(8);
    cout << "a secret is waiting to be triggered : )\n";
    resetTextColor();
    */
    
    Sleep(2000);

    Beep(200, 325);
    menu();
}