#include <iostream>
#include <conio.h>
#include <cstdlib>

struct Hero {
    char nom;
    int vie = 5;
    int pos_x;
    int pos_y;
};

struct Ennemies {
    char nom;
    int pos_x;
    int pos_y;
};


int main() {
    bool game = true;

    const int map_size_x = 20;
    const int map_size_y = 10;

    Hero H{ 'H', 0, 0 };



    char map[map_size_x * map_size_y];


    for (int i = 0; i < map_size_x * map_size_y; i++) {
        map[i] = '.';
    }


    map[6 + 2 * map_size_x] = '~';
    map[7 + 2 * map_size_x] = '~';
    map[5 + 2 * map_size_x] = '~';

    map[9 + 4 * map_size_x] = '~';
    map[10 + 4 * map_size_x] = '~';

    map[5 + 4 * map_size_x] = '~';
    map[6 + 4 * map_size_x] = '~';
    map[7+ 4 * map_size_x] = '~';
    map[8 + 4 * map_size_x] = '~';


    map[3 + 1 * map_size_x] = 'A';
    map[3 + 2 * map_size_x] = 'A';
    map[3 + 3 * map_size_x] = 'A';

    map[15 + 6 * map_size_x] = 'A';
    map[16 + 6 * map_size_x] = 'A';
    map[17 + 6 * map_size_x] = 'A';
    map[18 + 6 * map_size_x] = 'A';

    map[18 + 6 * map_size_x] = 'x';
    map[18 + 6 * map_size_x] = 'x';


    while (game) {


        system("cls");


        for (int j = 0; j < map_size_y; j++) {
            for (int i = 0; i < map_size_x; i++) {

                if (i == H.pos_x && j == H.pos_y) {
                    std::cout << H.nom << ' ';
                }
                else {
                    std::cout << map[i + j * map_size_x] << ' ';
                }
            }
            std::cout << '\n';
        }

        std::cout << "\nZ = Haut | S = Bas"
            << "\nQ = Gauche | D = Droite"
            << "\nX = Quitter\n";


        char direction = _getch();


        if (direction >= 'A' && direction <= 'Z') {
            direction = direction + ('a' - 'A');
        }


        if (direction == 'x') {
            game = false;
            continue;
        }


        int next_x = H.pos_x;
        int next_y = H.pos_y;

        if (direction == 'z') {
            next_y--;
        }
        else if (direction == 's') {
            next_y++;
        }
        else if (direction == 'q') {
            next_x--;
        }
        else if (direction == 'd') {
            next_x++;
        }
        else {
            continue;
        }


        next_x = (next_x + map_size_x) % map_size_x;
        next_y = (next_y + map_size_y) % map_size_y;


        int next_index = next_x + next_y * map_size_x;

        if (map[next_index] == '~') {

            continue;
        }

        if (map[next_index] == 'A') {

            continue;
        }
        if (map[next_index] == 'x') {
            
            H.vie -= 1;

            if (H.vie == 0)
            {
                game = false;
           }
        }


        H.pos_x = next_x;
        H.pos_y = next_y;
    }

    system("cls");
    std::cout << "Fin du jeu !\n";

    return 0;
}