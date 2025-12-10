#include "Antylopa.h"
#include "Swiat.h"
#include <cstdlib> 

Antylopa::Antylopa(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}
bool Antylopa::czyOdbilAtak(Organizm& atakujacy) {
    
    return false; 
}

void Antylopa::akcja() {
    static const int DX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    static const int DY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    int ruch = rand() % 8;
    int nx = x + 2*DX[ruch];
    int ny = y + 2*DY[ruch];

    if (nx >= 0 && nx < swiat->getPlanszaX() && ny >= 0 && ny < swiat->getPlanszaY()) {
        x = nx;
        y = ny;
    }
    std::string log = "ANTYLOPA PRZESUNELA SIE Z MIEJSCA (" + std::to_string(prevX) + ", " + std::to_string(prevY) +
        ") NA MIEJSCE (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    swiat->dodajDoDziennika(log);
}

Zwierze* Antylopa::stworzDziecko(int x, int y) {
    return new Antylopa(4, 4, x, y, *swiat, "A");
}

char Antylopa::rysowanie() const {
    return znak[0]; 
}

std::string Antylopa::getNazwa() const {
    return "Antylopa";
}

void Antylopa::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return;
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {
        if (dynamic_cast<Antylopa*>(inny)) {
            

            auto wolnePole = swiat->znajdzPusteObok(this->getX(), this->getY());
            if (wolnePole.first != -1 && wolnePole.second != -1) {
                Zwierze* dziecko = this->stworzDziecko(wolnePole.first, wolnePole.second);
                swiat->dodajOrganizm(dziecko);
                std::string log = "Rodzi sie nowy organizm: Antylopa.\n";
                swiat->dodajDoDziennika(log);
                this->ustawWykonanoAkcje(true);
                inny->ustawWykonanoAkcje(true);
            }
      
        }
        else {
            int szansa = rand() % 2;
            if (szansa == 1) {
                auto wolnePole = swiat->znajdzPusteObok(this->getX(), this->getY());
                if (wolnePole.first != -1 && wolnePole.second != -1) {
                    this->setPozycja(wolnePole.first, wolnePole.second);

                    std::string log = "ANTYLOPA UCIEKLA NA POLE (" + std::to_string(wolnePole.first) + ", " + std::to_string(wolnePole.second) + ")";
                    swiat->dodajDoDziennika(log);
                }
                else {
                    std::string log = "ANTYLOPA NIE MOGLA UCIEC, BRAK WOLNEGO POLA.";
                    swiat->dodajDoDziennika(log);
                    if (this->getSila() > inny->getSila()) {
                        std::string log = "ANTYLOPA ZJADLA" + inny->getNazwa();
                        swiat->dodajDoDziennika(log);
                        swiat->usunOrganizm(*inny);
                    }
                    else {
                        std::string log = inny->getNazwa() + " ZJADL ANTYLOPE";
                        swiat->dodajDoDziennika(log);


                        swiat->usunOrganizm(*this);
                    }
                }
            }

        }
    }
}
