#include <iostream>
#include <conio.h>
#include <cstdlib>

struct Hero {
    char nom;
    int position_x;
    int position_y;
    int vies;
    char direction;
};

struct Enemy {
    char nom;
    int position_x;
    int position_y;
    bool vivant;
};

int main() {
    bool game = true;

    //taille map
    const int map_size_x = 20;
    const int map_size_y = 10;
    const int enemy_count = 5;

    //type terrain
    const int ground = 0;
    const int mountain = 1;
    const int water = 2;


    Hero H{ 'H', 10, 0, 3, 'd' };


    int map[map_size_x * map_size_y] = {};

    // map initialisé avec "ground"
    for (int i = 0; i < map_size_x * map_size_y; i++) {
        map[i] = ground;
    }

    //mountain
    for (int x = 0; x < 5; x++) {
        for (int y = 1; y < 3; y++) {
            map[y * map_size_x + x] = mountain;
        }
    }

    
    for (int x = 2; x < 6; x++) {
        for (int y = 2; y < 7; y++) {
            map[y * map_size_x + x] = mountain;
        }
    }

    for (int x = 12; x < 18; x++) {
        for (int y = 6; y < 7; y++) {
            map[y * map_size_x + x] = mountain;
        }
    }

    //water
    for (int x = 2; x < 5; x++) {
        for (int y = 6; y < 9; y++) {
            map[y * map_size_x + x] = water;
        }
    }

    for (int x = 10; x < 13; x++) {
        for (int y = 4; y < 6; y++) {
            map[y * map_size_x + x] = water;
        }
    }

    

    Enemy enemies[enemy_count] = {
        { 'X', 6, 2, true },
        { 'X', 12, 2, true },
        { 'X', 11, 6, true },
        { 'X', 8, 8, true },
        { 'X', 16, 8, true }
    };

    //boucle principale
    while (game) {

        system("cls");

        for (int y = 0; y < map_size_y; y++) {
            for (int x = 0; x < map_size_x; x++) {

                if (x == H.position_x &&
                    y == H.position_y) {

                    std::cout << H.nom << ' ';
                }
                else {
                    bool enemy_found = false;

                    for (int i = 0; i < enemy_count; i++) {
                        if (enemies[i].vivant &&
                            x == enemies[i].position_x &&
                            y == enemies[i].position_y) {

                            std::cout << enemies[i].nom << ' ';
                            enemy_found = true;
                            break;
                        }
                    }


                    if (!enemy_found) {
                        int terrain = map[y * map_size_x + x];

                        if (terrain == ground) {
                            std::cout << ". ";
                        }
                        else if (terrain == mountain) {
                            std::cout << "A ";
                        }
                        else if (terrain == water) 
                        {
                            std::cout << "~ ";
                        }
                    }
                }
            }

            std::cout << '\n';
        }

        //hud
        int ennemis_restants = 0;

        for (int i = 0; i < enemy_count; i++) {
            if (enemies[i].vivant) {
                ennemis_restants++;
            }
        }

        std::cout << "\nVies : " << H.vies << '\n';
        std::cout << "Ennemis restants : "
            << ennemis_restants << '\n';

        std::cout << "\nZ = Haut | S = Bas\n";
        std::cout << "Q = Gauche | D = Droite\n";
        std::cout << "Echap = Quitter\n";

        //actualisation apres touche
        char touche = _getch();

        // echap pour quitter
        if (touche == 27) {
            break;
        }


        if (touche >= 'A' && touche <= 'Z') {
            touche = touche + ('a' - 'A');
        }

        //prochaine position
        int pos_x = H.position_x;
        int pos_y = H.position_y;

        bool action_valide = false;

        if (touche == 'z' || touche == 'q' ||
            touche == 's' || touche == 'd') {

            action_valide = true;

            if (touche == 'z') {
                pos_y--;
            }
            else if (touche == 's') {
                pos_y++;
            }
            else if (touche == 'q') {
                pos_x--;
            }
            else if (touche == 'd') {
                pos_x++;
            }



            if (pos_x < 0 || pos_x >= map_size_x ||
                pos_y < 0 || pos_y >= map_size_y) {
                continue;
            }

            int pos_index = pos_y * map_size_x + pos_x;


            if (map[pos_index] != mountain &&
                map[pos_index] != water) {

                H.position_x = pos_x;
                H.position_y = pos_y;
            }


            for (int i = 0; i < enemy_count; i++) {

                if (enemies[i].vivant &&
                    H.position_x == enemies[i].position_x &&
                    H.position_y == enemies[i].position_y) {

                    H.vies--;

                    if (H.vies < 0) {
                        H.vies = 0;
                    }

                    if (H.vies <= 0) {
                        game = false;
                    }

                    break;
                }
            }
        }

        //ignore touche non reconnu
        if (!action_valide) {
            continue;
        }

        //verif nombrre de vie
        if (!game) {
            break;
        }
    }


    if (H.vies <= 0) {
        system("cls");

        std::cout << "       GAME OVER        \n";

        std::cout << "Le heros a perdu toutes ses vies !\n";
        std::cout << "Vies restantes : " << H.vies << '\n';
    }

    std::cout << "\nAppuie sur une touche pour fermer...";

    return 0;
}

