#pragma once
#include "plansza.h"
#include "utilities.h"
#include "klocek.h"
class gra
{
private:
	int cols_ = 12, rows_ = 10;
	int millisec;
	bool test;
	klocek klocek_ = NULL;
	klocek nastepny_klocek_ = NULL;
	static klocek* random_brick();
	bool zyje_ = true;
	int wynik_ = 0;
	void nowy_klocek();
	plansza plansza1_;
	void game_over();
	void manual();
	void restart_gry();
	void klatka(keys key, bool wDol);
public:
	gra();
	void play();
};
