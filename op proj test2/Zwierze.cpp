#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>   
#include <ctime>
#include <utility>
#include <typeinfo>


Zwierze::Zwierze(int sila, int inicjatywa, Swiat* swiat, int x, int y)
    : Organizm(sila, inicjatywa, swiat, x, y) {
}

Zwierze::~Zwierze() {}


void Zwierze::akcja() {
    static const int DX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    static const int DY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    int ruch = rand() % 8; 
    int nx = x + DX[ruch];
    int ny = y + DY[ruch];

    if (nx >= 0 && nx < swiat->getPlanszaX() && ny >= 0 && ny < swiat->getPlanszaY()) {
        x = nx;
        y = ny;
    }
}

void Zwierze::kolizja(Organizm* inny) {
    if (!inny) return;
    if (inny->getX() != getX() || inny->getY() != getY()) return;

    if (typeid(*inny) == typeid(*this)) {
        rozmnoz(static_cast<Zwierze*>(inny));
        return;
    }

    walcz(inny);
}

void Zwierze::rozmnoz(Zwierze* partner) {
    if (czyWykonanoAkcje() && partner->czyWykonanoAkcje()) return;

    std::pair<int, int> pustePole = getSwiat()->znajdzPusteObok(getX(), getY());
    int nx = pustePole.first;
    int ny = pustePole.second;
    if (nx != -1) {
        Organizm* dziecko = stworzDziecko(nx, ny);
        dziecko->ustawWykonanoAkcje(true);
        getSwiat()->dodajOrganizm(dziecko);
        getSwiat()->dodajDoDziennika(
            getNazwa() + " i " + partner->getNazwa() +
            " rozmnozyli sie na (" + std::to_string(nx) + "," + std::to_string(ny) + ")"
        );
        ustawWykonanoAkcje(true);
        partner->ustawWykonanoAkcje(true);
    }
}

void Zwierze::walcz(Organizm* przeciwnik) {
    if (getSila() >= przeciwnik->getSila()) {
        getSwiat()->dodajDoDziennika(
            getNazwa() + " zabil " + przeciwnik->getNazwa()
            + " na (" + std::to_string(getX()) + "," + std::to_string(getY()) + ")"
        );
        getSwiat()->usunOrganizm(*przeciwnik);
    }
    else {
        getSwiat()->dodajDoDziennika(
            przeciwnik->getNazwa() + " zabil " + getNazwa()
            + " na (" + std::to_string(getX()) + "," + std::to_string(getY()) + ")"
        );
        getSwiat()->usunOrganizm(*this);
    }
}


void Zwierze::raport(const std::string& tekst) const {
    swiat->dodajDoDziennika(tekst);
}
