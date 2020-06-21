#include <iostream>
using namespace std;
#include "complex.hpp"
using namespace ilrd;

const char *RED = "\033[31m";
const char *DEF = "\033[0m";
const char *GREEN = "\033[32m";

static void BoolTest();
static void IOTest();
static void BasicAritTest();
static void SetAndGetTest();
static void CompoundOpTest();

int main()
{
	BoolTest();
	IOTest();
	BasicAritTest();
	SetAndGetTest();
	CompoundOpTest();
	cout << DEF << endl;
	return 0;
}

static void BasicAritTest()
{
	size_t pass_counter = 0;
	size_t fail_counter = 0;

	cout << RED << "From BasicAritTest(): " << DEF << endl;
	Complex c1(1);
	Complex c2(10,2);
	Complex c3;
	
	c3 = c1+c2;
	(c3.GetReal() == 11 && c3.GetImaginary() == 2)? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in + operator" << DEF << endl;
	}
	
	c3 = (c1 - c2);
	(c3.GetReal() == -9 && c3.GetImaginary() == -2)? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in - operator" << DEF << endl;
	}

	c3 = c1 * c2;
	(c3.GetReal() == 10 && c3.GetImaginary() == 2)? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in * operator" << DEF << endl;
	}

	c3 = c1 / c2;
	(c3.GetReal() == 7 && c3.GetImaginary() == 7)? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		cout << RED << "fail in / operator" << DEF << endl;
		fail_counter = 0;
	}

	(pass_counter == 4)? 
		cout << endl << GREEN << "All pass" << endl : 
		cout << endl << RED << "TEST FAILED" << DEF << endl;
}
static void BoolTest()
{
	size_t pass_counter = 0;
	size_t fail_counter = 0;

	cout << endl << RED << "From BoolTest(): " << DEF << endl;
	Complex c1(10,4);
	Complex c3 = c1;
	Complex c2(1,3);
	
	((c1==c3) == 1)? ++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in == bool" << DEF << endl;
	}
	
	((c2!=c3) == 1)? ++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in != bool" << DEF << endl;
	}

	(pass_counter == 2)? 
		cout << endl << GREEN << "All pass" << endl : 
		cout << endl << RED << "TEST FAILED" << DEF << endl;
}

static void IOTest()
{
	cout << endl << RED << "From IOTest(): " << DEF << endl;
	Complex c1 = 0;
	cin >> c1;
	cout << c1;
	cout << endl<< endl;
}

static void SetAndGetTest()
{
	size_t pass_counter = 0;
	size_t fail_counter = 0;

	cout << endl << RED << "From SetAndGetTest(): "
	<< DEF << endl;

	Complex c(105,12);
	cout << "original c: " << c << endl;
	cout << "Changing c's real number to 15: " << endl;
	c.SetReal(15);
	cout << "Changing c's imaginary number to 60: " <<  endl;
	c.SetImaginary(60);
	
	cout << "checking if new c = 15 + 60i" << endl;
	(c.GetReal() == 15 && c.GetImaginary() == 60)? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in Set/Get" << DEF << endl;
	}

	(pass_counter == 1)? 
		cout << endl << GREEN << "All pass" << endl : 
		cout << endl << RED << "TEST FAILED" << DEF << endl;
}

static void CompoundOpTest()
{
	size_t pass_counter = 0;
	size_t fail_counter = 0;

	cout << endl << RED << "From CompoundOpTest(): " << DEF << endl;
	Complex c1(1);
	Complex c2(10,2);
	
	(c1+=c2);
	((c1.GetReal() == 11) && (c1.GetImaginary() == 2))? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in +=" << DEF << endl;
	}

	(c1 -= c2);
	((c1.GetReal() == 1) && (c1.GetImaginary() == 0))? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in -=" << DEF << endl;
	}

	(c1 *= c2);	
	((c1.GetReal() == 10) && (c1.GetImaginary() == 2))? 
	++pass_counter : ++fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in *=" << DEF << endl;
	}
	
	(c1/=c2);
	((c1.GetReal() == 7) && (c1.GetImaginary() == 7))? 
	++pass_counter : ++ fail_counter;
	if (fail_counter)
	{
		fail_counter = 0;
		cout << RED << "fail in /=" << DEF << endl;
	}

	(pass_counter == 4)? 
		cout << endl << GREEN << "All pass" << endl : 
		cout << endl << RED << "TEST FAILED" << DEF << endl;
}
