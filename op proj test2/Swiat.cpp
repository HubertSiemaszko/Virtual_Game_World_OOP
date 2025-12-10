#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Czlowiek.h"
#include "Wilk.h"
#include "Owca.h"
#include "¯ó³w.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"
#include "Cyberowca.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>

using namespace std;
char Swiat::getLastInput()  {
    return lastInput;
}
void Swiat::wykonajTure(char input) {
    clearScreen();

    lastInput = input; 

    for (auto* org : organizmy) org->ustawWykonanoAkcje(false);

    for (auto* org : organizmy) org->zapiszPozycje();

    std::sort(organizmy.begin(), organizmy.end(),
        [](Organizm* a, Organizm* b) {
            if (a->getInicjatywa() == b->getInicjatywa())
                return a->getWiek() > b->getWiek();
            return a->getInicjatywa() > b->getInicjatywa();
        }
    );

    size_t poczRozmiar = organizmy.size();
    for (size_t i = 0; i < poczRozmiar; ++i) {
        Organizm* org = organizmy[i];
        if (!org->czyZyje() || org->czyWykonanoAkcje()) continue;

        org->akcja();
        org->ustawWykonanoAkcje(true);

        for (size_t j = 0; j < organizmy.size(); ++j) {
            if (i == j) continue;
            Organizm* inny = organizmy[j];
            if (!inny->czyZyje()) continue;
            if (inny->getX() == org->getX() && inny->getY() == org->getY()) {
                inny->kolizja(org);
                break;
            }
        }
    }

    usunMartweOrganizmy();

    for (auto* org : organizmy) if (org->czyZyje()) org->zwiekszWiek();
    ++licznikTur;
    rysujSwiat();
}

bool Swiat::zapiszDoPliku(const std::string& nazwa) {
    std::ofstream out(nazwa);
    if (!out) return false;

    out << "SWIAT;" << planszaX << ";" << planszaY << ";" << licznikTur << "\n";

    for (Organizm* o : organizmy) {
        out << o->getNazwa() << ";"
            << o->getSila() << ";"
            << o->getInicjatywa() << ";"
            << o->getWiek() << ";"
            << o->getX() << ";"
            << o->getY();

        if (Czlowiek* cz = dynamic_cast<Czlowiek*>(o)) {
            out << ";" << cz->getActiveTurns() << ";" << cz->getCooldown();
        }

        out << "\n";
    }
    return true;
}


bool Swiat::wczytajZPliku(const std::string& nazwa) {
    std::ifstream in(nazwa);
    if (!in) return false;
    for (auto* o : organizmy) delete o;
    organizmy.clear();

    std::string line;
    if (!std::getline(in, line)) return false;
    {
        std::istringstream ss(line);
        std::string tag;
        if (!std::getline(ss, tag, ';') || tag != "SWIAT") return false;

        std::string tmp;
        if (!std::getline(ss, tmp, ';')) return false;
        planszaX = std::stoi(tmp);
        if (!std::getline(ss, tmp, ';')) return false;
        planszaY = std::stoi(tmp);
        if (!std::getline(ss, tmp, ';')) return false;
        licznikTur = std::stoi(tmp);
    }
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string typ, tmp;
        std::getline(ss, typ, ';');

        int sila, inicjatywa, wiek, x, y;
        std::getline(ss, tmp, ';'); sila = std::stoi(tmp);
        std::getline(ss, tmp, ';'); inicjatywa = std::stoi(tmp);
        std::getline(ss, tmp, ';'); wiek = std::stoi(tmp);
        std::getline(ss, tmp, ';'); x = std::stoi(tmp);
        std::getline(ss, tmp, ';'); y = std::stoi(tmp);

        Organizm* nowy = nullptr;
        if (typ == "Trawa") {
            nowy = new Trawa(sila, inicjatywa, x, y, *this, "T");
        }
        else if (typ == "Wilk") {
            nowy = new Wilk(sila, inicjatywa, x, y, *this, "W");
        }
        else if (typ == "Owca") {
            nowy = new Owca(sila, inicjatywa, x, y, *this, "O");
        }
        else if (typ == "¯ó³w") {
            nowy = new ¯ó³w(sila, inicjatywa, x, y, *this, "Z");
		}
		else if (typ == "Mlecz") {
			nowy = new Mlecz(sila, inicjatywa, x, y, *this, "M");
		}
		else if (typ == "Guarana") {
			nowy = new Guarana(sila, inicjatywa, x, y, *this, "G");
		}
		else if (typ == "WilczeJagody") {
			nowy = new WilczeJagody(sila, inicjatywa, x, y, *this, "J");
		}
        else if (typ == "Lis") {
			nowy = new Lis(sila, inicjatywa, x, y, *this, "L");

        }
        else if (typ == "Antylopa") {
            nowy = new Antylopa(sila, inicjatywa, x, y, *this, "A");

        }
        else if (typ == "BarszczSosnowskiego") {
            nowy = new BarszczSosnowskiego(sila, inicjatywa, x, y, *this, "B");
        }
        else if (typ == "Cyberowca") {
            nowy = new Cyberowca(sila, inicjatywa, x, y, *this, "O");
        }
        else if (typ == "Czlowiek") {
            std::string tmp;
            int active, cooldown;

            if (!std::getline(ss, tmp, ';')) break;
            active = std::stoi(tmp);

            if (!std::getline(ss, tmp, ';')) break;
            cooldown = std::stoi(tmp);

            auto* cz = new Czlowiek(sila, inicjatywa, x, y, *this, "H");
            cz->setActiveTurns(active);
            cz->setCooldown(cooldown);
            nowy = cz;
        }

        if (nowy) {
            nowy->setWiek(wiek);
            organizmy.push_back(nowy);
        }
    }
    return true;
}



void Swiat::usunOrganizm(Organizm& org) {
    org.setZyje(false);
}

void Swiat::usunMartweOrganizmy() {
    organizmy.erase(
        std::remove_if(organizmy.begin(), organizmy.end(),
            [](Organizm* o) { return !o->czyZyje(); }),
        organizmy.end()
    );
}


Organizm* Swiat::getOrganizmNaPolu(int x, int y) {
    for (Organizm* organizm : organizmy) {
        if (organizm->getX() == x && organizm->getY() == y) {
            return organizm;
        }
    }
    return nullptr; 
}




void Swiat::rysujSwiat() {
    for (int i = 0; i < planszaX; ++i) {
        for (int j = 0; j < planszaY; ++j) {
            Organizm* org = getOrganizmNaPolu(i, j);
            char symbol = org ? org->rysowanie() : ' ';
            std::cout << '[' << symbol << ']';
        }
        std::cout << std::endl;
    }
    std::cout << "Hubert Siemaszko 202413" << std::endl;

}

void Swiat::clearScreen() {
    system("cls");
}


void Swiat::dodajOrganizm(Organizm* org) {
    organizmy.push_back(org);
}

std::pair<int, int> Swiat::znajdzPusteObok(int x, int y) {
    static const int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    static const int dy[8] = { 1, 0, -1, 1,-1,  1,  0, -1 };
    for (int k = 0; k < 8; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < planszaX && ny >= 0 && ny < planszaY
            && !getOrganizmNaPolu(nx, ny)) {
            return { nx, ny };
        }
    }
    return { -1, -1 };
}

void Swiat::dodajDoDziennika(const std::string& tekst) {
    std::cout << tekst << std::endl;
}

std::vector<Organizm*>& Swiat::getOrganizmy() {
    return organizmy;
}


int Swiat::getFreeX()  {
    int x;
    bool hasFree;
    Organizm* organizm;
    do {
        x = rand() % planszaX;
        hasFree = false;
        for (int y = 0; y < planszaY; ++y) {
            if (getOrganizmNaPolu(x, y) == nullptr) {
                hasFree = true;
                break;
            }
        }
    } while (!hasFree);
    return x;
}

int Swiat::getFreeY(int x)  {
    int y;
    do {
        y = rand() % planszaY;
    } while (getOrganizmNaPolu(x, y) != nullptr);
    return y;
}