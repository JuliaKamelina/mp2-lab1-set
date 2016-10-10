// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len>=0)
	{
		BitLen=len;
		MemLen=(len-1)/(sizeof(TELEM)*8)+1;
		pMem=new TELEM[MemLen];
		for(int i=0;i<MemLen;i++) pMem[i]=0;
	}
	else
	{
		std::cout<<"wrong value";
		exit(1);
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
	{
		pMem[i]=bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1<<(n&sizeof(TELEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n>-1 && n<BitLen)
		pMem[GetMemIndex(n)]|=GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n>-1 && n<BitLen)
		pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n>-1 && n<BitLen)
		return pMem[GetMemIndex(n)]&GetMemMask(n);
	else
	{
		cout<<"index is out of range";
		exit(1);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen=bf.BitLen;
	if(MemLen!=bf.MemLen)
	{
		MemLen=bf.MemLen;
		delete []pMem;
		pMem=new TELEM[MemLen];
	}
	for(int i=0;i<MemLen;++i)
		pMem[i]=bf.MemLen;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool res=true;
	if(BitLen!=bf.BitLen)
		res=false;
	else
	{
		for(int i=0;i<MemLen;++i)
			if(pMem[i]!=bf.pMem[i])
			{
				res=false;
				break;
			}
	}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ~((*this)==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int n;
	TBitField tmp(0);
	if(BitLen<bf.BitLen)
	{
		n=MemLen;
		tmp=bf;
	}
	else
	{
		n=bf.MemLen;
		tmp=*this;
	}
		for(int i=0;i<n;i++)
		{
			tmp.pMem[i]=pMem[i]|bf.pMem[i];
		}
		return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n;
	TBitField tmp(0);
	if(BitLen<bf.BitLen)
	{
		n=MemLen;
		tmp=bf;
	}
	else
	{
		n=bf.MemLen;
		tmp=*this;
	}
		for(int i=0;i<n;i++)
		{
			tmp.pMem[i]=pMem[i]&bf.pMem[i];
		}
		return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int l=BitLen;
	TBitField tmp(l);
	for(int i=0;i<MemLen;++i)
		tmp.pMem[i]=~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char ch;
	do
	{
		istr >> ch;
	}while(ch!=' ');
	while (1)
	{
		istr >> ch;
		if (ch=='0') 
			bf.ClrBit(i++);
		else
			if(ch=='1')
				bf.SetBit(i++);
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i))
			ostr << '1';
		else ostr << '0';
	return ostr;
}
