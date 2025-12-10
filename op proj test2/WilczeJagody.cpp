#include "WilczeJagody.h"
#include "Swiat.h"
#include <cstdlib> 

WilczeJagody::WilczeJagody(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Roœlina(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void WilczeJagody::akcja() {
    if (czyWykonanoAkcje()) {
        return; 
    }

    Roœlina::akcja();

    ustawWykonanoAkcje(true);
}

Roœlina* WilczeJagody::stworzDziecko(int x, int y) {
    return new WilczeJagody(99, 0, x, y, *swiat, "J");
}

char WilczeJagody::rysowanie() const {
    return znak[0]; 
}

std::string WilczeJagody::getNazwa() const {
    return "WilczeJagody";
}

void WilczeJagody::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return; 
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {


        if (this->getSila() > inny->getSila()) {
            std::string log = "WILCZEJAGODY ZABILY" + inny->getNazwa();
            swiat->dodajDoDziennika(log);
            swiat->usunOrganizm(*inny);
        }
        else {
            std::string log = inny->getNazwa() + " ZJADL WILCZE JAGODY I ZMARL";
            swiat->dodajDoDziennika(log);

            swiat->usunOrganizm(*this);
            swiat->usunOrganizm(*inny);
        }

    }
}
