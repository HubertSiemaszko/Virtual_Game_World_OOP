#include "Wilk.h"
#include "Swiat.h"
#include <cstdlib> 

Wilk::Wilk(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), znak(znak) {
}

void Wilk::akcja() {
    Zwierze::akcja();
    std::string log = "WILK PRZESUNAL SIE Z MIEJSCA (" + std::to_string(prevX) + ", " + std::to_string(prevY) +
        ") NA MIEJSCE (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    swiat->dodajDoDziennika(log);
}

Zwierze* Wilk::stworzDziecko(int x, int y) {
    return new Wilk(9, 5, x, y, *swiat, "W");
}

std::string Wilk::getNazwa() const {
    return "Wilk";
}

char Wilk::rysowanie() const {
    return znak[0]; 
}

bool Wilk::czyOdbilAtak(Organizm& atakujacy) {
    return false; 
}

void Wilk::kolizja(Organizm* inny) {
    
    if (czyOdbilAtak(*inny)) return;

    Zwierze::kolizja(inny);
}
