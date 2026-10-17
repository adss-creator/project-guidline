
#include <iostream>
#include <conio.h>
#include <cstdlib>

//CONSTANTES
const int map_size_x = 20;
const int map_size_y = 10;
const int enemy_count = 5;

const int GROUND = 0;
const int MOUNTAIN = 1;
const int WATER = 2;

//STRUCTURES
struct Hero {
    char nom;
    int pos_x;
    int pos_y;
    int life;
    char direction;
};

struct Enemy {
    char nom;
    int pos_x;
    int pos_y;
    bool vivant;
};

struct Finish {
    char nom;
    int pos_x;
    int pos_y;
};

//INITIALISATION
void initialiserCarte(int map[]) {

    //Terrain par défaut
    for (int i = 0; i < map_size_x * map_size_y; i++) {
        map[i] = GROUND;
    }

    //Montagnes
    for (int x = 0; x < 5; x++) {
        for (int y = 1; y < 3; y++) {
            map[y * map_size_x + x] = MOUNTAIN;
        }
    }

    for (int x = 2; x < 6; x++) {
        for (int y = 2; y < 7; y++) {
            map[y * map_size_x + x] = MOUNTAIN;
        }
    }

    for (int x = 12; x < 18; x++) {
        for (int y = 6; y < 7; y++) {
            map[y * map_size_x + x] = MOUNTAIN;
        }
    }

    //Eau
    for (int x = 2; x < 5; x++) {
        for (int y = 6; y < 9; y++) {
            map[y * map_size_x + x] = WATER;
        }
    }

    for (int x = 10; x < 13; x++) {
        for (int y = 4; y < 6; y++) {
            map[y * map_size_x + x] = WATER;
        }
    }
}

//AFFICHAGE
void afficherCarte(
    const int map[],
    const Hero& H,
    const Finish& E,
    const Enemy enemies[]
) {
    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {

            //Héros
            if (x == H.pos_x && y == H.pos_y) {
                std::cout << H.nom << ' ';
            }

            //Arrivée
            else if (x == E.pos_x && y == E.pos_y) {
                std::cout << E.nom << ' ';
            }

            else {
                bool enemy_found = false;

                //Ennemis
                for (int i = 0; i < enemy_count; i++) {
                    if (enemies[i].vivant &&
                        x == enemies[i].pos_x &&
                        y == enemies[i].pos_y) {

                        std::cout << enemies[i].nom << ' ';
                        enemy_found = true;
                        break;
                    }
                }

                //Terrain
                if (!enemy_found) {
                    int terrain = map[y * map_size_x + x];

                    if (terrain == GROUND) {
                        std::cout << ". ";
                    }
                    else if (terrain == MOUNTAIN) {
                        std::cout << "A ";
                    }
                    else if (terrain == WATER) {
                        std::cout << "~ ";
                    }
                }
            }
        }

        std::cout << '\n';
    }
}


int compterEnnemisVivants(const Enemy enemies[]) {
    int compteur = 0;

    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].vivant) {
            compteur++;
        }
    }

    return compteur;
}

void afficherHUD(const Hero& H, const Enemy enemies[]) {
    std::cout << "\nVies : " << H.life << '\n';

    std::cout << "Ennemis restants : "
        << compterEnnemisVivants(enemies) << '\n';

    std::cout << "\nZ = Haut | S = Bas\n";
    std::cout << "Q = Gauche | D = Droite\n";
    std::cout << "Echap = Quitter\n";
}

//DEPLACEMENT
bool estDansLaCarte(int x, int y) {
    return x >= 0 && x < map_size_x &&
        y >= 0 && y < map_size_y;
}

bool terrainAccessible(const int map[], int x, int y) {
    int index = y * map_size_x + x;

    return map[index] != MOUNTAIN &&
        map[index] != WATER;
}

void deplacerHero(Hero& H, const int map[], char touche) {

    int pos_x = H.pos_x;
    int pos_y = H.pos_y;

    //Déterminer la nouvelle position
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
    else {
        return;
    }

    //Vérifier les limites
    if (!estDansLaCarte(pos_x, pos_y)) {
        return;
    }

    //Vérifier le terrain
    if (!terrainAccessible(map, pos_x, pos_y)) {
        return;
    }

    //Valider le déplacement
    H.pos_x = pos_x;
    H.pos_y = pos_y;
}

bool collisionEnnemi(const Hero& H, const Enemy enemies[]) {
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].vivant &&
            H.pos_x == enemies[i].pos_x &&
            H.pos_y == enemies[i].pos_y) {
            return true;
        }
    }

    return false;
}

void gererCollision(Hero& H, const Enemy enemies[]) {
    if (collisionEnnemi(H, enemies)) {
        H.life--;

        if (H.life < 0) {
            H.life = 0;
        }
    }
}

//FIN DE PARTIE
void afficherGameOver(const Hero& H) {

    std::cout << "       GAME OVER        \n";
    std::cout << "Le heros a perdu toutes ses vies !\n";
    std::cout << "life restantes : " << H.life << '\n';
}

void afficherVictoire() {
    system("cls");

    std::cout << "       VICTOIRE !           \n";
    std::cout << "Bravo ! Tu as atteint la fin !\n";

}

void deplacerEnnemi(Enemy& E, const int map[]) {

    int pos_x = E.pos_x;
    int pos_y = E.pos_y;

	//deplacement aleatoire
    int direction = rand() % 4;

    if (direction == 0) {
        pos_y--; 
    }
    else if (direction == 1) {
        pos_y++; 
    }
    else if (direction == 2) {
        pos_x--;
    }
    else {
        pos_x++; 
    }

	//ennemi ne peut pas sortir de la carte
    if (!estDansLaCarte(pos_x, pos_y)) {
        return;
    }

    if (!terrainAccessible(map, pos_x, pos_y)) {
        return;
    }

    //deplacement valide
    E.pos_x = pos_x;
    E.pos_y = pos_y;
}



//PROGRAMME PRINCIPAL
int main() {

    bool game = true;

    Hero H{ 'H', 10, 0, 3, 'd' };
    Finish F{ 'F', 19, 9 };

    int map[map_size_x * map_size_y];
    initialiserCarte(map);

    Enemy enemies[enemy_count] = {
        { 'X', 6, 2, true },
        { 'X', 12, 2, true },
        { 'X', 11, 6, true },
        { 'X', 8, 8, true },
        { 'X', 16, 8, true }
    };

    while (game) {

        system("cls");

        afficherCarte(map, H, F, enemies);
        afficherHUD(H, enemies);

        //Attendre une touche
        char touche = _getch();

        //Convertir les majuscules
        if (touche >= 'A' && touche <= 'Z') {
            touche += 'a' - 'A';
        }

        //Ignorer les touches non reconnues
        if (touche != 'z' && touche != 'q' &&
            touche != 's' && touche != 'd') {
            continue;
        }

        deplacerHero(H, map, touche);

        //Deplacer les ennemis vivants
        for (int i = 0; i < enemy_count; i++) {
            if (enemies[i].vivant) {
                deplacerEnnemi(enemies[i], map);
            }

        }

        //Verifier si le heros atteint la fin
        if (H.pos_x == F.pos_x && H.pos_y == F.pos_y) {
            game = false;
            break;
        }

        gererCollision(H, enemies);

        if (H.life <= 0) {
            game = false;
        }
        else if (H.pos_x == F.pos_x && H.pos_y == F.pos_y) {
            afficherVictoire();
        }
    }

    

    std::cout << "\nAppuie sur une touche pour fermer...";

    return 0;
}
