#pragma once
#include <iostream>
#include <vector>
#include "Organizm.h"

class Swiat {
private:
    int planszaX = 20;
    int planszaY = 20;
    int licznikTur = 0;
    std::vector<Organizm*> organizmy;
    char lastInput;            



public:
    
    void wykonajTure(char charTurowy);
    char getLastInput(); 
    int getFreeX() ;
    int getFreeY(int x) ;

    void rysujSwiat();
    void clearScreen();
    void dodajOrganizm(Organizm* org);
    std::vector<Organizm*>& getOrganizmy();
    void usunOrganizm(Organizm& org);
    Organizm* getOrganizmNaPolu(int x, int y);
    std::pair<int, int> znajdzPusteObok(int x, int y);
    void dodajDoDziennika(const std::string& tekst);
    void usunMartweOrganizmy(); 
    bool zapiszDoPliku(const std::string& nazwaPliku);
    bool wczytajZPliku(const std::string& nazwaPliku);
    int getPlanszaX() const { return planszaX; }
    int getPlanszaY() const {
        return planszaY;
    }
}; 
