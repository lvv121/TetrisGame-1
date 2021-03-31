#include "plansza.h"

#include <iostream>
#include <string>
#include "klocek.h"
using namespace std;

plansza::plansza(int x, int y)
{
	width_ = x;
	height_ = y;
	wymiary = new int* [width_];
	for (int i = 0; i < width_; i++)
	{
		wymiary[i] = new int[height_];
		for (int j = 0; j < height_; j++)
		{
			wymiary[i][j] = 0;
		}
	}
}

int plansza::get_height() const
{
	return height_;
}

int plansza::get_width() const
{
	return width_;
}

void plansza::drukuj() const
{
	int x = get_width();
	int y = get_height();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (wymiary[i][j] == 0)
			{
				cout << '-';
			}
			else
			{
				cout << wymiary[i][j];
			}
		}
		cout << "#\n";
	}
	for (int i = 0; i < y + 1; i++)
	{
		cout << "#";
	}

	cout << "\n\n";
}

void plansza::wpisywanie_klocka(klocek& k) const
{
	int rozmiar = k.get_size();
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (k.shape[i][j] != 0)
			{
				wymiary[k.get_x() + i][k.get_y() + j] = k.shape[i][j];
			}
		}
	}
}

void plansza::zamroz(klocek& k) const
{
	int rozmiar = k.get_size();
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (k.shape[i][j] != 0)
			{
				wymiary[k.get_x() + i][k.get_y() + j] = 2;
			}
		}
	}
}

void plansza::glebokie_czyszczenie() const
{
	int x = get_width();
	int y = get_height();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			wymiary[i][j] = 0;
		}
	}
}

void plansza::plytkie_czyszczenie() const
{
	int x = get_width();
	int y = get_height();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (wymiary[i][j] == 1)
			{
				wymiary[i][j] = 0;
			}
		}
	}
}

bool plansza::kolizja(klocek& k, int x, int y) const
{
	int rozmiar = k.get_size();
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (k.shape[i][j] == 1)
			{
				if (x + i < 0 ||
					x + i >= get_width() ||
					y + j < 0 ||
					y + j >= get_height() ||
					wymiary[x + i][y + j] == 2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int plansza::sprawdz_plansze() const
{
	int licznik = 0;
	int x = get_width();
	int y = get_height();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (wymiary[i][j] == 2)
			{
				licznik++;
			}
		}
		if (licznik == y)
		{
			return i;
		}

		licznik = 0;
	}
	return -1;
}

int plansza::przesuwanie(int linia) const
{
	int level = sprawdz_plansze();
	int wynik = 1;
	int y = get_height();
	while (level != -1)
	{
		for (int i = linia - 1; i >= 0; i--)
		{
			for (int j = 0; j < y; j++)
			{
				wymiary[i + 1][j] = wymiary[i][j];
			}
		}
		level = sprawdz_plansze();
		wynik *= linia;
		linia++;
	}
	return wynik;
}