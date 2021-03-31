#pragma once
#include "klocek.h"
class plansza
{
private:
	int height_;
	int width_;
public:
	int** wymiary;
	plansza(int x = 12, int y = 10);
	int get_height() const;
	int get_width() const;
	void drukuj() const;
	void wpisywanie_klocka(klocek& k) const;
	void zamroz(klocek& k) const;
	void glebokie_czyszczenie() const;
	void plytkie_czyszczenie() const;
	bool kolizja(klocek& k, int x, int y) const;
	int sprawdz_plansze() const;
	int przesuwanie(int linia = 10) const;
};
