// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : 
MaxPower(mp), BitField(mp){}

// конструктор копирования
TSet::TSet(const TSet &s) : 
BitField(s.BitField), MaxPower(s.MaxPower){}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : 
BitField(bf), MaxPower(bf.GetLength()){}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if(Elem<MaxPower)
	{
		return BitField.GetBit(Elem);
	}
	else
		throw logic_error("WRONG_VALUE");
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if(Elem<MaxPower)
	{
		BitField.SetBit(Elem);
	}
	else
		throw logic_error("WRONG_VALUE");
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if(Elem<MaxPower)
	{
		BitField.ClrBit(Elem);
	}
	else
		throw logic_error("WRONG_VALUE");
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField;
	MaxPower=s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int res;
	if(*this==s)
		res=0;
	else res=1;
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return BitField|s.BitField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if(Elem<MaxPower)
	{
		TSet tmp(*this);
		tmp.InsElem(Elem);
		return tmp;
	}
	else
		throw logic_error("WRONG_VALUE");
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if(Elem<MaxPower)
	{
		TSet tmp(*this);
		tmp.DelElem(Elem);
		return tmp;
	}
	else
		throw logic_error("WRONG_VALUE");
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return BitField&s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~(BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmp;
	char ch;
	do
	{
		istr>>ch;
	}while(ch!='{');
	do
	{
		istr>>tmp;
		s.InsElem(tmp);
		do
		{
			istr>>ch;
		}while(ch!=',' && ch!='}');
	}while(ch!='}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int n;
	char ch=' ';
	ostr<<"{";
	n=s.GetMaxPower();
	for(int i=0;i<n;i++)
	{
		if(s.IsMember(i))
		{
			ostr<<ch<<' '<<i;
			ch=',';
		}
	}
	ostr<<"}";
	return ostr;
}
