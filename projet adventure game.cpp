
#include <iostream>
#include <conio.h>
#include <cstdlib>

//CONSTANTES
const int Map_size_x = 20;
const int Map_size_y = 10;
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
void initialiserCarte(int* pMap) {

        // Terrain par défaut
        for (int i = 0; i < Map_size_x * Map_size_y; i++) {
            pMap[i] = GROUND;
        }

        // Montagnes
        for (int x = 0; x < 5; x++) {
            for (int y = 1; y < 3; y++) {
                pMap[y * Map_size_x + x] = MOUNTAIN;
            }
        }
        for (int x = 10; x < 15; x++) {
            for (int y = 6; y < 8; y++) {
                pMap[y * Map_size_x + x] = MOUNTAIN;
            }
        }

        // Eau
        for (int x = 2; x < 5; x++) {
            for (int y = 6; y < 9; y++) {
                pMap[y * Map_size_x + x] = WATER;
            }
        }

}

void initialiserNewLevel(int* pMap) {


    
        // Terrain par défaut
        for (int i = 0; i < Map_size_x * Map_size_y; i++) {
            pMap[i] = GROUND;
        }

        // Montagnes
        for (int x = 6; x < 10; x++) {
            for (int y = 3; y < 6; y++) {
                pMap[y * Map_size_x + x] = MOUNTAIN;
            }
        }
        for (int x = 10; x < 15; x++) {
            for (int y = 6; y < 8; y++) {
                pMap[y * Map_size_x + x] = MOUNTAIN;
            }
        }

        // Eau
        for (int x = 3; x < 9; x++) {
            for (int y = 4; y < 7; y++) {
                pMap[y * Map_size_x + x] = WATER;
            }
        }


}

//AFFICHAGE
void afficherCarte(
    const int* pMap,
    const Hero& H,
    const Finish& E,
    const Enemy enemies[]
) {
    for (int y = 0; y < Map_size_y; y++) {
        for (int x = 0; x < Map_size_x; x++) {

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
                    int terrain = pMap[y * Map_size_x + x];

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

//HUD
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
bool estDansLaCarte(const int* pMap, int x, int y) {
    return x >= 0 && x < Map_size_x &&
        y >= 0 && y < Map_size_y;
}

bool terrainAccessible(const int* pMap, int x, int y) {
    int index = y * Map_size_x + x;

    return pMap[index] != MOUNTAIN &&
        pMap[index] != WATER;
}

void deplacerHero(Hero& H, const int* pMap, char touche) {

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
    if (!estDansLaCarte(pMap, pos_x, pos_y)) {
        return;
    }


    //Vérifier le terrain
    if (!terrainAccessible(pMap, pos_x, pos_y)) {
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

void afficherVictory() {
    system("cls");
    std::cout << "       VICTOIRE !           \n";
    std::cout << "Bravo ! Tu as atteint la fin !\n";

}

void deplacerEnnemi(Enemy& E, const int* pMap) {

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
    if (!estDansLaCarte(pMap, pos_x, pos_y)) {
        return;
    }

    if (!terrainAccessible(pMap, pos_x, pos_y)) {
        return;
    }

    //deplacement valide
    E.pos_x = pos_x;
    E.pos_y = pos_y;
}



//PROGRAMME PRINCIPAL
int main() {
    int niveau = 1;
    bool game = true;

    Hero H{ 'H', 10, 0, 3, 'd' };
    Finish F{ 'F', 19, 9 };

    int Map[Map_size_x * Map_size_y];
    int* pMap = Map;

    if (niveau == 1) {
        initialiserCarte(pMap);

        Enemy enemies[enemy_count] = {

            { 'X', 6, 2, true },
            { 'X', 12, 2, true },
            { 'X', 11, 5, true },
            { 'X', 8, 8, true },
            { 'X', 16, 8, true }
        };



        while (game) {

            system("cls");

            afficherCarte(pMap, H, F, enemies);
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

            deplacerHero(H, Map, touche);

            //Deplacer les ennemis vivants
            for (int i = 0; i < enemy_count; i++) {
                if (enemies[i].vivant) {
                    deplacerEnnemi(enemies[i], Map);
                }

            }

            gererCollision(H, enemies);

            if (H.life <= 0) {
                afficherGameOver;
                break;
            }

            //Verifier si le heros atteint la fin
            if (H.pos_x == F.pos_x && H.pos_y == F.pos_y) {

                niveau += 1;
                initialiserNewLevel(pMap);

            }
            if (niveau == 2)
            {
                H.pos_x = 10;
                H.pos_y = 0;

                

            }
            
            if (H.pos_x == F.pos_x && H.pos_y == F.pos_y)
            {
                niveau += 1;
                afficherVictory();  
            }
        }

        return 0;
    }
    
}

    
