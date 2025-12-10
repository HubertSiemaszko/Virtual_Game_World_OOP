#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Żółw.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Cyberowca.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"
#include <tuple> 
#define MAXWILK 5
#define MAXOWCA 5
#define MAXZOLW 5
#define MAXLIS 5
#define MAXANTYLOPA 5
#define MAXCYBEROWCA 5
#define MAXTRAWA 3
#define MAXMLECZ 3
#define MAXGUARANA 3
#define MAXWILECZJAGODY 3
#define MAXBARSZCZ 10
#define MAXHUMAN 1
using namespace std;

int main() {
    srand(time(nullptr));
    Swiat swiat;

	const int initCountAnimals = MAXWILK + MAXOWCA + MAXZOLW + MAXLIS + MAXANTYLOPA + MAXCYBEROWCA;
	const int initCountPlants = MAXTRAWA + MAXMLECZ + MAXGUARANA + MAXWILECZJAGODY + MAXBARSZCZ;

    int maxX = swiat.getPlanszaX();
    int maxY = swiat.getPlanszaY();
	if (maxX < 1 || maxY < 1) {
		cout << "Niepoprawne wymiary planszy.\n";
		return 1;
	}
	if (maxX*maxY < initCountAnimals) {
		cout << "Niepoprawna liczba organizmow.\n";
		return 1;
	}
	if (maxX*maxY < initCountPlants) {
		cout << "Niepoprawna liczba roslin.\n";
		return 1;
	}


		for (int j = 0; j < MAXWILK; ++j) {
			int x, y;
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Wilk(9, 5, x, y, swiat, "W"));
		}
       
		for (int j = 0; j < MAXOWCA; ++j) {
			int x, y;
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Owca(4, 4, x, y, swiat, "O"));
		}

		for (int j = 0; j < MAXZOLW; ++j) {
			int x, y; 
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Żółw(2, 1, x, y, swiat, "Z"));
		}
       
		for (int j = 0; j < MAXLIS; ++j) {
			int x, y;
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Lis(3, 7, x, y, swiat, "L"));
		}

        for (int j = 0; j < MAXANTYLOPA; ++j) {
            int x, y; 
            x = swiat.getFreeX();
            y = swiat.getFreeY(x);
            swiat.dodajOrganizm(new Antylopa(4, 4, x, y, swiat, "A"));
        }

        for (int j = 0; j < MAXCYBEROWCA; ++j) {
            int x, y; 
            x = swiat.getFreeX();
            y = swiat.getFreeY(x);
            swiat.dodajOrganizm(new Cyberowca(10, 4, x, y, swiat, "C"));
        }
    

		for (int j = 0; j < MAXTRAWA; ++j) {
			int x, y; 
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Trawa(0, 0, x, y, swiat, "T"));
		}

		for (int j = 0; j < MAXMLECZ; ++j) {
			int x, y; 
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Mlecz(0, 0, x, y, swiat, "M"));
		}
       
		for (int j = 0; j < MAXGUARANA; ++j) {
			int x, y; 
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new Guarana(0, 0, x, y, swiat, "G"));
		}

		for (int j = 0; j < MAXWILECZJAGODY; ++j) {
			int x, y; 
			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new WilczeJagody(99, 0, x, y, swiat, "J"));
		}

		for (int j = 0; j < MAXBARSZCZ; ++j) {
			int x, y; 

			x = swiat.getFreeX();
			y = swiat.getFreeY(x);
			swiat.dodajOrganizm(new BarszczSosnowskiego(10, 0, x, y, swiat, "B"));
		}
    
		if(MAXHUMAN)
    {
        int x, y; 

        x = swiat.getFreeX();
        y = swiat.getFreeY(x);
        swiat.dodajOrganizm(new Czlowiek(5, 4, x, y, swiat, "H"));
    }


    swiat.rysujSwiat();

    while (true) {
        char input = _getch();
        if (input == 'q') break;
        else if (input == 'z') {
            if (swiat.zapiszDoPliku("savegame.txt"))
                cout << "Zapisano stan do savegame.txt\n";
            else
                cout << "Błąd zapisu!\n";
            continue;
        }
        else if (input == 'l') {
            if (swiat.wczytajZPliku("savegame.txt"))
                cout << "Wczytano stan z savegame.txt\n";
            else
                cout << "Błąd wczytywania!\n";
            continue;
        }
		else if (input == 'r'||input=='w' || input == 'a' || input == 's' || input == 'd'||input=='u') {
			swiat.wykonajTure(input);
		}
    }

    return 0;
}