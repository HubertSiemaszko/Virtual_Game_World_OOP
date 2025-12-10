#pragma once
#include "Roœlina.h"
#include <string>

class Trawa : public Roœlina {
public:
    Trawa(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak);

    void akcja() override;
    Roœlina* stworzDziecko(int x, int y) override;
    char rysowanie() const override;
    void kolizja(Organizm* inny) override;
    std::string getNazwa() const override; 


private:
    std::string znak; 
};