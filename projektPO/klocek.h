#pragma once
#include <iostream>
using namespace std;

class klocek
{
private:
	int size_;
	int pos_x_, pos_y_;
	int** rotate(bool clock_direction);

public:
	int** shape;
	klocek(int size = 1);
	~klocek();
	int get_size() const;
	int get_x();
	int get_y();
	void move_down();
	void move_right();
	void move_left();
	void pokaz_nastepny_klocek();
	void obrot_w_prawo(bool right);
	void klocek_start(int start);
	klocek& operator=(klocek&);
};

class kwadrat : public klocek
{
public:
	kwadrat(int size = 2);
};

class litera_l : public klocek
{
public:
	litera_l(int size = 3);
};

class podluzny : public klocek
{
public:
	explicit podluzny(int size = 5) : klocek(size)
	{
		for (int i = 0; i < size; i++)
		{
			shape[size / 2][i] = 1;
		}
	}
};

class trojnik : public klocek
{
public:
	trojnik(int size = 3) : klocek(size)
	{
		for (int i = 0; i < size; i++)
		{
			shape[0][i] = 1;
			shape[size / 2][size / 2] = 1;
		}
	}
};

class zygzak : public klocek
{
public:
	zygzak(int size = 3) : klocek(size)
	{
		for (int i = 0; i < size - 1; i++)
		{
			shape[0][i] = 1;
			shape[size / 2][size / 2] = 1;
			shape[size / 2][2] = 1;
		}
	}
};
