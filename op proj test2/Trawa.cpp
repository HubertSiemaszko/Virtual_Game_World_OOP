#include "Trawa.h"
#include "Swiat.h"
#include <cstdlib> 

Trawa::Trawa(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Roœlina(sila, inicjatywa, &swiat, x, y), znak(znak) {
}


Roœlina* Trawa::stworzDziecko(int x, int y) {
    return new Trawa(0, 0, x, y, *swiat, "T");
}
void Trawa::akcja() {
    if (czyWykonanoAkcje()) {
        return; 
    }

    Roœlina::akcja();

    ustawWykonanoAkcje(true);
}


char Trawa::rysowanie() const {
    return znak[0];
}

std::string Trawa::getNazwa() const {
    return "Trawa";
}

void Trawa::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return; 
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {
        if (this->getSila() > inny->getSila()) {
            std::string log = "TRAWA ZABILA " + inny->getNazwa();
            swiat->dodajDoDziennika(log);
            inny->setZyje(false);
            swiat->usunOrganizm(*inny);
        }
        else {
            std::string log = inny->getNazwa() + " ZJADL TRAWE";
            swiat->dodajDoDziennika(log);
            this->setZyje(false);
            swiat->usunOrganizm(*this);
        }
    }
}
