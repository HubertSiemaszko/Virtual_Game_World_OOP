#include "Lis.h"
#include "Swiat.h"
#include <cstdlib> 

Lis::Lis(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}
bool Lis::czyOdbilAtak(Organizm& atakujacy) {
    return false; 
}
void Lis::akcja() {
    static const int DX[8] = { -1,  0,  1, -1, 1, -1,  0,  1 };
    static const int DY[8] = { -1, -1, -1,  0, 0,  1,  1,  1 };

    int kierunek = rand() % 8;
    int nx = x + DX[kierunek];
    int ny = y + DY[kierunek];

    if (nx < 0 || nx >= swiat->getPlanszaX() ||
        ny < 0 || ny >= swiat->getPlanszaY()) {
        return;
    }

    Organizm* orgNaPolu = swiat->getOrganizmNaPolu(nx, ny);
    if (orgNaPolu == nullptr || orgNaPolu->getSila() <= this->getSila()) {
        x = nx;
        y = ny;
        std::string log = "LIS PRZESUNAL SIE Z MIEJSCA (" + std::to_string(prevX) + ", " + std::to_string(prevY) +
            ") NA MIEJSCE (" + std::to_string(x) + ", " + std::to_string(y) + ")";
        swiat->dodajDoDziennika(log);
    }
}

Zwierze* Lis::stworzDziecko(int x, int y) {
    return new Lis(3, 7, x, y, *swiat, "L");
}

char Lis::rysowanie() const {
    return znak[0]; 
}

std::string Lis::getNazwa() const {
    return "Lis";
}

void Lis::kolizja(Organizm* inny) {

    Zwierze::kolizja(inny);
}
