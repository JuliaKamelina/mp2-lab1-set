#include "tbitfield.h"
#include "tset.h"

#include <gtest.h>

TEST(JK_TBitField, double_bit_clearing)
{
	TBitField bf(10);
	
	int bitIdx = 3;
	
	bf.SetBit(bitIdx);
	EXPECT_NE(0, bf.GetBit(bitIdx));
	
	bf.ClrBit(bitIdx);
	bf.ClrBit(bitIdx);
	EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(JK_TBitField, or_operator_applied_to_bitfields_of_equal_size_two_times)
{
	const int size = 4;
  TBitField bf1(size), bf2(size), bf3(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);
  // bf3 = 1100
  bf3.SetBit(0);
  bf3.SetBit(1);

  // expBf = 1111
  expBf.SetBit(0);
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(JK_TBitField, or_operator_applied_to_bitfields_of_non_equal_size_two_times)
{
  const int size1 = 4, size2 = 5;
  TBitField bf1(size1), bf2(size2), bf3(size1), expBf(size2);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 01010
  bf2.SetBit(1);
  bf2.SetBit(3);
  // bf3 = 1011;
  bf3.SetBit(0);
  bf3.SetBit(2);
  bf3.SetBit(3);

  // expBf = 11110
  expBf.SetBit(0);
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(JK_TSet, can_combine_three_sets_of_equal_size)
{
  const int size = 6;
  TSet set1(size), set2(size), set3(size), set4(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  // set3 = {3, 4, 5}
  set3.InsElem(3);
  set3.InsElem(4);
  set3.InsElem(5);
  set4 = set1 + set2 + set3;
  // expSet = {0, 1, 2, 3, 4, 5}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(3);
  expSet.InsElem(4);
  expSet.InsElem(5);

  EXPECT_EQ(expSet, set4);
}

TEST(TSet, can_combine_three_sets_of_non_equal_size)
{
  const int size1 = 6, size2 = 8, size3=7;
  TSet set1(size1), set2(size2), set3(size3), set4(size2), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(6);
  // set3 = {2, 3, 4, 5, 6}
  set3.InsElem(2);
  set3.InsElem(3);
  set3.InsElem(4);
  set3.InsElem(5);
  set3.InsElem(6);

  set4 = set1 + set2 + set3;
  // expSet = {0, 1, 2, 3, 4, 5, 6}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(3);
  expSet.InsElem(4);
  expSet.InsElem(5);
  expSet.InsElem(6);

  EXPECT_EQ(expSet, set4);
}