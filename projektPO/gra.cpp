#include "gra.h"
#include <chrono>
#include <conio.h>
#include <stdio.h>
using namespace std;

void gra::game_over()
{
	cout << "Gratulacje, uzyskales " << wynik_ << " punktow!" << endl;
	cout << "Czy chcesz zagrac jeszcze raz?" << endl;
	cout << "Y / n" << endl;;
	const int cho = _getch();
	if (cho == 121 || cho == 89)
	{
		restart_gry();
	}
}

void gra::manual()
{
	string man = "Instrukcja";
	cout << string((man.length() + 2), '#') << endl;
	cout << "#" << man << "#" << endl;
	cout << string((man.length() + 2), '#') << endl;
	cout << "Krok w lewo => D\n";
	cout << "Krok w prawo => A\n";
	cout << "Obrot do gory => W\n";
	cout << "Obrot w dol => S\n";
	cout << "Przyspieszenie klocka => space\n\n";
}

gra::gra()
{
	plansza1_ = plansza(cols_, rows_);
	klocek_ = *random_brick();
	nastepny_klocek_ = *random_brick();
}

klocek* gra::random_brick()
{
	srand(static_cast<unsigned>(time(0)));
	const int randomNumber = (rand() % 5) + 1;
	klocek k = NULL;
	switch (randomNumber)
	{
	case 1:
		return new kwadrat();

	case 2:
		return new litera_l();

	case 3:
		return new podluzny();

	case 4:
		return new trojnik();

	case 5:
		return new zygzak();

	default: throw exception("<gra::random_brick>");
	}
}

void gra::nowy_klocek()
{
	klocek_ = nastepny_klocek_;
	nastepny_klocek_ = *random_brick();
	if (plansza1_.kolizja(klocek_, 0, 0))
		zyje_ = false;
}

void gra::klatka(keys key, bool wDol)
{
	if (!zyje_)
	{
		return;
	}
	if (test || wDol)
	{
		plansza1_.plytkie_czyszczenie();
		test = false;
	}
	if (wDol)
	{
		if (!plansza1_.kolizja(klocek_, klocek_.get_x() + 1, klocek_.get_y()))
		{
			klocek_.move_down();
			wynik_++;
			plansza1_.wpisywanie_klocka(klocek_);
		}
		else
		{
			plansza1_.zamroz(klocek_);
			wynik_ += plansza1_.przesuwanie(plansza1_.get_height());
			plansza1_.przesuwanie(plansza1_.sprawdz_plansze());
			nowy_klocek();
		}
	}
	switch (key)
	{
	case keys::a:
		if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y() - 1))
		{
			klocek_.move_left();
			test = true;
		}
		break;

	case keys::d:
		if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y() + 1))
		{
			klocek_.move_right();
			test = true;
		}
		break;

	case keys::w:
		klocek_.obrot_w_prawo(false);
		if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y()))
		{
			test = true;
		}
		else
		{
			klocek_.obrot_w_prawo(true);
		}

		break;

	case keys::s:
		if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y()))
		{
			test = true;
		}
		else
		{
			klocek_.obrot_w_prawo(false);
		}

		break;
	}
}

void gra::restart_gry()
{
	wynik_ = 0;
	zyje_ = true;
	plansza1_.glebokie_czyszczenie();
}

void gra::play()
{
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	chrono::steady_clock::time_point measure;
	millisec = 1000;
	while (zyje_)
	{
		while (zyje_)
		{
			measure = chrono::steady_clock::now();
			if (chrono::duration_cast<chrono::milliseconds>(measure - start).count() > millisec)
			{
				system("CLS");
				start = measure;
				plansza1_.plytkie_czyszczenie();
				if (!plansza1_.kolizja(klocek_, klocek_.get_x() + 1, klocek_.get_y()))
				{
					klocek_.move_down();
					plansza1_.wpisywanie_klocka(klocek_);
				}
				else
				{
					plansza1_.zamroz(klocek_);
					wynik_ += plansza1_.przesuwanie(plansza1_.sprawdz_plansze());
					millisec = 1000;
					nowy_klocek();
				}
				plansza1_.drukuj();
				gra::manual();
				nastepny_klocek_.pokaz_nastepny_klocek();
			}
			if (_kbhit())
			{
				test = false;
				auto k = _getch();
				switch (k)
				{
					case static_cast<int>(keys::d) :
						if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y() + 1))
						{
							klocek_.move_right();
							test = true;
						}
					break;

					case static_cast<int>(keys::w) :
						klocek_.obrot_w_prawo(false);
						if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y()))
						{
							test = true;
						}
						else
						{
							klocek_.obrot_w_prawo(true);
						}

						break;

						case static_cast<int>(keys::s) :
							klocek_.obrot_w_prawo(true);
							if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y()))
							{
								test = true;
							}
							else
							{
								klocek_.obrot_w_prawo(false);
							}

							break;

							case static_cast<int>(keys::spacebar) :
								millisec /= 2;
								break;

							default:
								if (!plansza1_.kolizja(klocek_, klocek_.get_x(), klocek_.get_y() - 1))
								{
									klocek_.move_left();
									test = true;
								}
								break;
				}
				if (test == false)
				{
				}
			}
		}
		game_over();
	}
}