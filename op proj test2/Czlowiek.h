#pragma once
#include "Zwierze.h"
#include <string>
class Czlowiek : public Zwierze {
private:
    int cooldownLeft;      
    int activeTurnsLeft;   
    std::string znak;
public:
    Czlowiek(int sila, int inicjatywa, int x, int y, Swiat& swiat, const std::string& znak);

    void akcja() override;
    char rysowanie() const override;
    std::string getNazwa() const override; 
    bool tarczaAlzura(Organizm* atakujacy);

    void kolizja(Organizm* inny) override;
    Zwierze* stworzDziecko(int x, int y) override;
    bool czyOdbilAtak(Organizm& atakujacy) override;

    void aktywujUmiejetnosc();
    int getActiveTurns() const;
    int getCooldown() const;
    void setActiveTurns(int t);
    void setCooldown(int t);
};