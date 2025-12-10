#include "Organizm.h"
#include "Swiat.h"    

Organizm::Organizm(int sila, int inicjatywa, Swiat* swiat, int x, int y)
    : sila(sila),
    inicjatywa(inicjatywa),
    x(x),
    y(y),
    wiek(0),
    zyje(true),
    swiat(swiat),
    prevX(x), 
    prevY(y),  
    wykonanoAkcje(false)  


{
}


Organizm::~Organizm() = default;

int Organizm::getSila() const {
    return sila;
}

int Organizm::getInicjatywa() const {
    return inicjatywa;
}

int Organizm::getX() const {
    return x;
}

int Organizm::getY() const {
    return y;
}

int Organizm::getWiek() const {
    return wiek;
}

bool Organizm::czyZyje() const {
    return zyje;
}

Swiat* Organizm::getSwiat() const {
    return swiat;
}

void Organizm::setSwiat(Swiat* swiat) {
    this->swiat = swiat;
}

void Organizm::setPozycja(int noweX, int noweY) {
    x = noweX;
    y = noweY;
}

void Organizm::setZyje(bool stan) {
    zyje = stan;
}

void Organizm::setSila(int nowasila) {
    sila = nowasila;
}

void Organizm::zapiszPozycje() {
    prevX = x;
    prevY = y;
}

void Organizm::przywrocPoprzedniaPozycje() {
    x = prevX;
    y = prevY;
}

void Organizm::zwiekszWiek() {
    wiek++;
}

void Organizm::setWiek(int nowyWiek) {
    wiek = nowyWiek;
}




void Organizm::ustawWykonanoAkcje(bool stan) {
    wykonanoAkcje = stan;
}

bool Organizm::czyWykonanoAkcje() const {
    return wykonanoAkcje;
}
