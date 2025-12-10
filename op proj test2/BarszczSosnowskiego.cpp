#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include "Cyberowca.h"
#include <cstdlib>

BarszczSosnowskiego::BarszczSosnowskiego(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Roœlina(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void BarszczSosnowskiego::akcja() {
    if (czyWykonanoAkcje()) return;
    zapiszPozycje();

    static const int DX[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
    static const int DY[8] = { -1,  0,  1, -1, 1,-1, 0, 1 };
    for (int k = 0; k < 8; ++k) {
        int nx = getX() + DX[k];
        int ny = getY() + DY[k];
        if (nx < 0 || nx >= swiat->getPlanszaX() || ny < 0 || ny >= swiat->getPlanszaX())
            continue;
        Organizm* o = swiat->getOrganizmNaPolu(nx, ny);
        if (o && dynamic_cast<Zwierze*>(o) && !dynamic_cast<Cyberowca*>(o)) {
            swiat->dodajDoDziennika(getNazwa() + " zabil(a) " + o->getNazwa() +
                " na (" + std::to_string(nx) + "," + std::to_string(ny) + ")");
            swiat->usunOrganizm(*o);
        }
    }

    Roœlina::akcja();
    ustawWykonanoAkcje(true);
}

Roœlina* BarszczSosnowskiego::stworzDziecko(int x, int y) {
    return new BarszczSosnowskiego(10, 0, x, y, *swiat, "B");
}

char BarszczSosnowskiego::rysowanie() const {
    return znak[0];
}

std::string BarszczSosnowskiego::getNazwa() const {
    return "BarszczSosnowskiego";
}

void BarszczSosnowskiego::kolizja(Organizm* inny) {
    if (inny != nullptr) {
		if (!dynamic_cast<Cyberowca*>(inny)) {
			inny->setZyje(false);
			
		}
        else {
            std::string log = "CYBEROWCA ZJADLA BARSZCZ";
            swiat->dodajDoDziennika(log);
        }

        this->setZyje(false); 
    }
}