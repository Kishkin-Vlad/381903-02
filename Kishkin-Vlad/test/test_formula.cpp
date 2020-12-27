#include <gtest.h>

#include "Formula.h"


TEST(Formula, can_create_form)
{
	ASSERT_NO_THROW(Formula form);
}

TEST(Formula, example1)
{
	Formula form("2^3");
	form.conversToRevPolNot();
	double res = form.calculateExpression();
	cout << res;

	ASSERT_EQ((double)8, res);
}

TEST(Formula, example2)
{
	Formula form("2+ -3");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)-1, res);
}

TEST(Formula, example3)
{
	Formula form("2- -3");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)5, res);
}

TEST(Formula, example4)
{
	Formula form("(4 + 3)");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)7, res);
}

TEST(Formula, example5)
{
	Formula form("1 + (4 + 3)");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)8, res);
}

TEST(Formula, example6)
{
	Formula form("1 + (4 + 3) + 2");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)10, res);
}

TEST(Formula, example7)
{
	Formula form("1 +(4+ 3)/ 2");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)4, res);
}

TEST(Formula, example8)
{
	Formula form("(6+ 2)3");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)24, res);
}

TEST(Formula, example9)
{
	Formula form("(4 + 2)(3+1)");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)24, res);
}

TEST(Formula, example10)
{
	Formula form("2*(10+-2)/(3+1)");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)4, res);
}

TEST(Formula, example11)
{
	Formula form("       2^   2^    2          ");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)16, res);
}

TEST(Formula, example12)
{
	Formula form("11");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)11, res);
}

TEST(Formula, example13)
{
	Formula form("11 - ---11");
	form.conversToRevPolNot();
	double res = form.calculateExpression();

	ASSERT_EQ((double)22, res);
}