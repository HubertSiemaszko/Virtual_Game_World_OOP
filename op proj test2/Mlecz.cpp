#include "Mlecz.h"
#include "Swiat.h"
#include <cstdlib> 

Mlecz::Mlecz(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Roœlina(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void Mlecz::akcja() {
    
    if (czyWykonanoAkcje()) {
        return; 
    }

    for (int i = 0; i < 3; i++) {
        Roœlina::akcja();
    }

    ustawWykonanoAkcje(true);

}

Roœlina* Mlecz::stworzDziecko(int x, int y) {
    return new Mlecz(0, 0, x, y, *swiat, "M");
}

char Mlecz::rysowanie() const {
    return znak[0]; 
}

std::string Mlecz::getNazwa() const {
    return "Mlecz";
}

void Mlecz::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return;
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {


        if (this->getSila() > inny->getSila()) {
            std::string log = "MLECZ ZABIL" + inny->getNazwa();
            swiat->dodajDoDziennika(log);
            swiat->usunOrganizm(*inny);
        }
        else {
            std::string log = inny->getNazwa() + " ZJADL MLECZA";
            swiat->dodajDoDziennika(log);
            swiat->usunOrganizm(*this);
        }

    }
}