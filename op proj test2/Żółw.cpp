#include "¯ó³w.h"
#include "Swiat.h"
#include <cstdlib> 

¯ó³w::¯ó³w(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

bool ¯ó³w::czyOdbilAtak(Organizm& atakujacy) {
    if (atakujacy.getSila() < 5) {
        atakujacy.przywrocPoprzedniaPozycje();
        std::string log= "Atakujacy nie zadal obrazen zolwiowi";
		swiat->dodajDoDziennika(log);
        return true;
    }
    return false;
}

void ¯ó³w::akcja() {
   
    int szansa = rand() % 4;
    if (szansa == 1) {
        Zwierze::akcja();
    }
    std::string log = "ZOLW PRZESUNAL SIE Z MIEJSCA (" + std::to_string(prevX) + ", " + std::to_string(prevY) +
        ") NA MIEJSCE (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    swiat->dodajDoDziennika(log);
}

Zwierze* ¯ó³w::stworzDziecko(int x, int y) {
    return new ¯ó³w(2, 1, x, y, *swiat, "Z");
}

char ¯ó³w::rysowanie() const {
    return znak[0]; 
}

std::string ¯ó³w::getNazwa() const {
    return "Zolw";
}

void ¯ó³w::kolizja(Organizm* inny) {
    if (!inny) return;

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {
        if (dynamic_cast<Zwierze*>(inny)) {
            if (czyOdbilAtak(*inny)) {
                return;
            }
        }

        if (dynamic_cast<¯ó³w*>(inny)) {
            auto wolnePole = swiat->znajdzPusteObok(getX(), getY());
            if (wolnePole.first != -1) {
                auto* dziecko = stworzDziecko(wolnePole.first, wolnePole.second);
                dziecko->ustawWykonanoAkcje(true);
                swiat->dodajOrganizm(dziecko);
                swiat->dodajDoDziennika("Zolw rozmnozyl sie na (" +
                    std::to_string(wolnePole.first) + "," +
                    std::to_string(wolnePole.second) + ")");
                this->ustawWykonanoAkcje(true);
                inny->ustawWykonanoAkcje(true);
            }
            return;
        }

        if (this->getSila() > inny->getSila()) {
            swiat->dodajDoDziennika("Zolw zjadl " + inny->getNazwa());
            swiat->usunOrganizm(*inny);
        }
        else {
            swiat->dodajDoDziennika(inny->getNazwa() + " zjadl Zolwia");
            swiat->usunOrganizm(*this);
        }
    }
}

