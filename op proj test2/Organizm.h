#pragma once
#include <string> 
class Swiat;

class Organizm {
protected:
    int sila;            
    int inicjatywa;     
    int x, y;           
    int wiek;            
    bool zyje;          
    Swiat* swiat;       
    int prevX, prevY;
    bool wykonanoAkcje; 

public:
    Organizm(int sila, int inicjatywa, Swiat* swiat, int x, int y);

    virtual ~Organizm();
    void setSwiat(Swiat* swiat);

    int getSila() const;
    int getInicjatywa() const;
    int getX() const;
    int getY() const;
    int getWiek() const;
    bool czyZyje() const;
    Swiat* getSwiat() const;
    virtual std::string getNazwa() const = 0;
    void ustawWykonanoAkcje(bool stan);
    bool czyWykonanoAkcje() const;
    void setPozycja(int noweX, int noweY);
    void setZyje(bool stan);
    void setSila(int nowasila);
    void setWiek(int nowyWiek);


    void zapiszPozycje(); 
    void przywrocPoprzedniaPozycje();
    void zwiekszWiek(); 


    virtual void akcja() = 0;
    virtual void kolizja(Organizm* intruz) = 0;
    virtual char rysowanie() const = 0;
};
