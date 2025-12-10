#include "Cyberowca.h"
#include "Swiat.h"
#include "BarszczSosnowskiego.h"
#include <cstdlib> 

Cyberowca::Cyberowca(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}
bool Cyberowca::czyOdbilAtak(Organizm& atakujacy) {
    return false; 
}
void Cyberowca::akcja() {
    zapiszPozycje();

    int minDist = swiat->getPlanszaX();
    Organizm* target = nullptr;
    for (Organizm* o : swiat->getOrganizmy()) {
        BarszczSosnowskiego* b = dynamic_cast<BarszczSosnowskiego*>(o);
        if (b && b->czyZyje()) {
            int dist = abs(b->getX() - x) + abs(b->getY() - y);
            if (dist < minDist) {
                minDist = dist;
                target = b;
            }
        }
    }

    if (target) {
        int dx = target->getX() - x;
        int dy = target->getY() - y;
        if (abs(dx) > abs(dy)) {
            x += (dx > 0 ? 1 : -1);
        }
        else if (dy != 0) {
            y += (dy > 0 ? 1 : -1);
        }
    }
    else {
        Zwierze::akcja();
    }

    std::string log = "CYBEROWCA PRZESUNAL SIE Z (" + std::to_string(prevX) + "," +
        std::to_string(prevY) + ") NA (" + std::to_string(x) + "," +
        std::to_string(y) + ")";
    swiat->dodajDoDziennika(log);
}

Zwierze* Cyberowca::stworzDziecko(int x, int y) {
    return new Cyberowca(10, 4, x, y, *swiat, "C");
}

std::string Cyberowca::getNazwa() const {
    return "Cyberowca";
}

char Cyberowca::rysowanie() const {
    return znak[0]; 
}

void Cyberowca::kolizja(Organizm* inny) {
    if (inny == nullptr) {
        cout << "B³¹d: wskaŸnik 'inny' jest nullptr.\n";
        return; 
    }

    if (inny->getX() == this->getX() && inny->getY() == this->getY()) {
        if (dynamic_cast<Cyberowca*>(inny)) {

            auto wolnePole = swiat->znajdzPusteObok(this->getX(), this->getY());
            if (wolnePole.first != -1 && wolnePole.second != -1) {
                Zwierze* dziecko = this->stworzDziecko(wolnePole.first, wolnePole.second);
                swiat->dodajOrganizm(dziecko);
                std::string log = "Rodzi sie nowa Cyberowca rozmnozyla sie na (" +
                    std::to_string(wolnePole.first) + "," +
                    std::to_string(wolnePole.second) + ")";
                swiat->dodajDoDziennika(log);
                this->ustawWykonanoAkcje(true);
                inny->ustawWykonanoAkcje(true);
            }
            else {
                cout << "Brak miejsca na nowego wilka.\n";
            }
        }
        else {
            if (this->getSila() > inny->getSila()) {
                std::string log = "CYBEROWCA ZJADLA" + inny->getNazwa();
                swiat->dodajDoDziennika(log);
                swiat->usunOrganizm(*inny);
            }
			else if (dynamic_cast<BarszczSosnowskiego*>(inny)) {
				std::string log = "CYBEROWCA ZJADLA BARSZCZ";
				swiat->dodajDoDziennika(log);
				swiat->usunOrganizm(*inny);
			}

            else {
                std::string log = inny->getNazwa() + " ZJADL CYBEROWCE";
                swiat->dodajDoDziennika(log);


                swiat->usunOrganizm(*this);
            }
        }
    }
}
