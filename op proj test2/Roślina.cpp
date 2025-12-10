#include "Roœlina.h"
#include "Swiat.h"
#include <cstdlib>   
#include <ctime>
#include <utility>
#include <typeinfo>


Roœlina::Roœlina(int sila, int inicjatywa, Swiat* swiat, int x, int y)
    : Organizm(sila, inicjatywa, swiat, x, y) {
}

Roœlina::~Roœlina() {}

void Roœlina::akcja() {
    if (rand() % 3 == 1) {
        static const int DX[8] = { -1,-1,-1,0,0,1,1,1 };
        static const int DY[8] = { -1, 0, 1,-1,1,-1,0,1 };
        int emptyCount = 0;
        int emptyX[8], emptyY[8];

        for (int k = 0; k < 8; ++k) {
            int nx = getX() + DX[k];
            int ny = getY() + DY[k];
            if (nx >= 0 && nx < swiat->getPlanszaX() && ny >= 0 && ny < swiat->getPlanszaY()
                && !swiat->getOrganizmNaPolu(nx, ny)) {
                emptyX[emptyCount] = nx;
                emptyY[emptyCount] = ny;
                ++emptyCount;
            }
        }

        if (emptyCount > 0) {
            int choice = rand() % emptyCount;
            int sx = emptyX[choice], sy = emptyY[choice];
            Organizm* dziecko = stworzDziecko(sx, sy);
            dziecko->ustawWykonanoAkcje(true);
            swiat->dodajOrganizm(dziecko);
            swiat->dodajDoDziennika(getNazwa() + " rozmnozyla sie na (" +
                std::to_string(sx) + "," +
                std::to_string(sy) + ")");
        }
    }
}




void Roœlina::raport(const std::string& tekst) const {
    swiat->dodajDoDziennika(tekst);
}