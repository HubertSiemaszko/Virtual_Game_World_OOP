#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>

Czlowiek::Czlowiek(int sila, int inicjatywa, int x, int y, Swiat& swiat, const std::string& znak)
    : Zwierze(sila, inicjatywa, &swiat, x, y), cooldownLeft(0), activeTurnsLeft(0), znak(znak) {
}

void Czlowiek::akcja() {
    zapiszPozycje();
    char input = swiat->getLastInput();

    if (input == 'u') {
        aktywujUmiejetnosc();
    }

    switch (input) {
    case 'a': if (x > 0) y--; break;
    case 'd': if (x < swiat->getPlanszaX() - 1) y++; break;
    case 'w': if (y > 0) x--; break;
    case 's': if (y < swiat->getPlanszaY() - 1) x++; break;
    default: break;
    }

    swiat->dodajDoDziennika("Czlowiek przesunal sie na (" + std::to_string(x) + "," + std::to_string(y) + ")");

    if (activeTurnsLeft > 0) {
        swiat->dodajDoDziennika("Tarcza Alzura aktywna, pozostalo tur: " + std::to_string(activeTurnsLeft));
        --activeTurnsLeft;
        if (activeTurnsLeft == 0) {
            cooldownLeft = 5;
            swiat->dodajDoDziennika("Tarcza Alzura wygasla, cooldown: " + std::to_string(cooldownLeft));
        }
    }
    else if (cooldownLeft > 0) {
        --cooldownLeft;
        swiat->dodajDoDziennika("Cooldown Tarczy Alzura, pozostalo tur: " + std::to_string(cooldownLeft));
    }
}
bool Czlowiek::tarczaAlzura(Organizm* atakujacy) {
    if (activeTurnsLeft > 0 && dynamic_cast<Zwierze*>(atakujacy)) {
        static const int DX[8] = { -1,-1,-1,0,0,1,1,1 };
        static const int DY[8] = { -1, 0, 1,-1,1,-1,0,1 };
        std::vector<std::pair<int, int>> wolne;
        for (int k = 0; k < 8; ++k) {
            int nx = x + DX[k];
            int ny = y + DY[k];
            if (nx >= 0 && nx < swiat->getPlanszaX() && ny >= 0 && ny < swiat->getPlanszaY()
                && !swiat->getOrganizmNaPolu(nx, ny)) {
                wolne.emplace_back(nx, ny);
            }
        }
        if (!wolne.empty()) {
            std::pair<int, int> selected = wolne[rand() % wolne.size()];
            int nx = selected.first;
            int ny = selected.second;
            atakujacy->setPozycja(nx, ny);
            swiat->dodajDoDziennika("Tarcza Alzura odparla " + atakujacy->getNazwa() +
                " na (" + std::to_string(nx) + "," + std::to_string(ny) + ")");
        }
        return true;
    }
    return false;
}
void Czlowiek::kolizja(Organizm* inny) {
    if (!inny) return;
    if (inny->getX() == x && inny->getY() == y) {
        if (tarczaAlzura(inny)) return;

        if (getSila() >= inny->getSila()) {
            swiat->dodajDoDziennika("Czlowiek zabil " + inny->getNazwa());
            swiat->usunOrganizm(*inny);
        } else {
            swiat->dodajDoDziennika(inny->getNazwa() + " zabil Czlowieka");
            swiat->usunOrganizm(*this);
        }
    }
}

std::string Czlowiek::getNazwa() const {
    return "Czlowiek";
}

char Czlowiek::rysowanie() const {
    return znak[0]; 
}

void Czlowiek::aktywujUmiejetnosc() {
    if (activeTurnsLeft == 0 && cooldownLeft == 0) {
        activeTurnsLeft = 5;
        swiat->dodajDoDziennika("Czlowiek aktywowal Tarcze Alzura! Pozostalo tur: " + std::to_string(activeTurnsLeft));
    }
}

Zwierze* Czlowiek::stworzDziecko(int x, int y) {
    return new Czlowiek(5, 5, x, y, *swiat, "H");
}

bool Czlowiek::czyOdbilAtak(Organizm& atakujacy) {
    return false; 
}

int Czlowiek::getActiveTurns() const { return activeTurnsLeft; }
int Czlowiek::getCooldown() const { return cooldownLeft; }
void Czlowiek::setActiveTurns(int t) { activeTurnsLeft = t; }
void Czlowiek::setCooldown(int t) { cooldownLeft = t; }