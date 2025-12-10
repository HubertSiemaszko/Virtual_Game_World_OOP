#pragma once
#include <iostream>
#include "Organizm.h"
#include <utility>  
using namespace std;
class Roślina : public Organizm {
public:
    Roślina(int sila, int inicjatywa, Swiat* swiat, int x, int y);
    virtual ~Roślina();

    void akcja() override;

    char rysowanie() const override = 0;
    virtual Roślina* stworzDziecko(int x, int y) = 0;


protected:



    void raport(const std::string& tekst) const;
};
