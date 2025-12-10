#include "Guarana.h"
#include "Swiat.h"
#include <cstdlib> 

Guarana::Guarana(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Roœlina(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void Guarana::akcja() {
    if (czyWykonanoAkcje()) {
        return; 
    }

    Roœlina::akcja();

    ustawWykonanoAkcje(true);
}

Roœlina* Guarana::stworzDziecko(int x, int y) {
    return new Guarana(0, 0, x, y, *swiat, "G");
}

char Guarana::rysowanie() const {
    return znak[0]; 
}

std::string Guarana::getNazwa() const {
    return "Guarana";
}

void Guarana::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return; 
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {


        if (this->getSila() > inny->getSila()) {
            std::string log = "GUARANA ZABILA" + inny->getNazwa();
            swiat->dodajDoDziennika(log);
            swiat->usunOrganizm(*inny);
        }
        else {
            std::string log = inny->getNazwa() + " ZJADL GUARANE";
            inny->setSila(getSila() + 3); 
            swiat->dodajDoDziennika(log);
            swiat->usunOrganizm(*this);
        }

    }
}
