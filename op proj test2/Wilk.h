#pragma once
#include "Zwierze.h"
#include <string>

class Wilk : public Zwierze {
public:
    Wilk(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak);

    void akcja() override;
    Zwierze* stworzDziecko(int x, int y) override;
    char rysowanie() const override;
    void kolizja(Organizm* inny) override;
    std::string getNazwa() const override; 
    bool czyOdbilAtak(Organizm& atakujacy) override;


private:
    std::string znak; 
};
