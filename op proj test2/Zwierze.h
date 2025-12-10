#pragma once
#include <iostream>
#include "Organizm.h"
#include <utility>  
using namespace std;
class Zwierze : public Organizm {
public:
    Zwierze(int sila, int inicjatywa, Swiat* swiat, int x, int y);
    virtual ~Zwierze();

    void akcja() override;
	void kolizja(Organizm* inny) override;
    char rysowanie() const override = 0;
    virtual Zwierze* stworzDziecko(int x, int y) = 0;
	virtual bool czyOdbilAtak(Organizm& atakujacy) = 0;


protected:


    void rozmnoz(Zwierze* partner);

    void walcz(Organizm* przeciwnik);
    void raport(const std::string& tekst) const;
};
