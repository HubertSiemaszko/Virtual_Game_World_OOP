#pragma once
#include "Zwierze.h"
#include <string>

class ¯ó³w : public Zwierze {
public:
    ¯ó³w(int sila, int inicjatywa, int x, int y, Swiat& swiat, std::string znak);
	bool czyOdbilAtak(Organizm& atakujacy) override;
    void akcja() override;
    Zwierze* stworzDziecko(int x, int y) override;
    char rysowanie() const override;
    void kolizja(Organizm* inny) override;
    std::string getNazwa() const override; 


private:
    std::string znak; 
};
