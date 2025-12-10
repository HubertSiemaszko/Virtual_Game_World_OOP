#include "Owca.h"
#include "Swiat.h"
#include <cstdlib> 

Owca::Owca(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void Owca::akcja() {
    Zwierze::akcja();
    std::string log = "OWCA PRZESUNAL SIE Z MIEJSCA (" + std::to_string(prevX) + ", " + std::to_string(prevY) +
        ") NA MIEJSCE (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    swiat->dodajDoDziennika(log);
}
bool Owca::czyOdbilAtak(Organizm& atakujacy) {
    return false; 
}

Zwierze* Owca::stworzDziecko(int x, int y) {
    return new Owca(4, 4, x, y, *swiat, "O");
}

char Owca::rysowanie() const {
    return znak[0]; 
}

std::string Owca::getNazwa() const {
    return "Owca";
}

void Owca::kolizja(Organizm* inny) {

    Zwierze::kolizja(inny);
}