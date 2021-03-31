#pragma once
#include "klocek.h"

#include <iostream>
#include <string>
using namespace std;

klocek::klocek(int size)
{
	size_ = size;
	pos_x_ = 0;
	pos_y_ = 0;
	shape = new int* [size];
	for (int i = 0; i < size; i++)
	{
		shape[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			shape[i][j] = 0;
		}
	}
}

klocek::~klocek()
{
	for (int i = 0; i < size_; i++)
		delete[] shape[i];
	delete[] shape;
}

int klocek::get_size() const
{
	return size_;
}

int klocek::get_x()
{
	return pos_x_;
}

int klocek::get_y()
{
	return pos_y_;
}

void klocek::move_down()
{
	pos_x_++;
}

void klocek::move_right()
{
	pos_y_++;
}

void klocek::move_left()
{
	pos_y_--;
}

int** klocek::rotate(bool clock_direction)
{
	int rozmiar = get_size();
	int** wynik;
	wynik = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		wynik[i] = new int[rozmiar];
	if (clock_direction)
	{
		for (int i = 0; i < rozmiar; i++)
		{
			for (int j = 0; j < rozmiar; j++)
			{
				wynik[j][rozmiar - 1 - i] = shape[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < rozmiar; i++)
		{
			for (int j = rozmiar - 1; j >= 0; j--)
			{
				wynik[rozmiar - 1 - i][j] = shape[j][i];
			}
		}
	}
	return wynik;
}

void klocek::pokaz_nastepny_klocek()
{
	int rozmiar = get_size();
	string next = "Nastepny klocek";
	cout << string((next.length() + 2), '#') << endl;
	cout << "#" << next << "#" << endl;
	cout << string((next.length() + 2), '#') << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (shape[i][j] == 0)
			{
				cout << '-';
			}
			else
			{
				cout << to_string(shape[i][j]);
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

void klocek::obrot_w_prawo(bool right)
{
	shape = rotate(right);
}

void klocek::klocek_start(int start)
{
	pos_x_ = 0;
	pos_y_ = start;
}

klocek& klocek::operator=(klocek& k)
{
	size_ = k.size_;
	pos_x_ = k.pos_x_;
	pos_y_ = k.pos_y_;
	shape = new int* [k.size_];
	for (int i = 0; i < k.size_; i++)
		shape[i] = new int[k.size_];
	for (int i = 0; i < k.get_size(); i++)
	{
		for (int j = 0; j < k.get_size(); j++)
		{
			shape[i][j] = k.shape[i][j];
		}
	}
	return *this;
}

kwadrat::kwadrat(int size) : klocek(size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			shape[i][j] = 1;
		}
	}
}

litera_l::litera_l(int size) : klocek(size)
{
	for (int i = 0; i < size; i++)
	{
		shape[i][size - 1] = 1;
		shape[0][i] = 1;
	}
}