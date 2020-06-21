#include <iostream>     // I/O operations
#include "rcstring.hpp"
#include "utils.hpp"    // ASSERT

using namespace ilrd;

void ConstructorAndAssignmentTest(void);
void AssignmentOpTest(void);
void LengthTest(void);
void AccessTest(void);
void OutPutTest(void);
void InputTest(void);

int main()
{
    ConstructorAndAssignmentTest();
    LengthTest();
    AccessTest();
    OutPutTest();
    InputTest();

    return (0);
}

void ConstructorAndAssignmentTest(void)
{
    RCString strTest("mor");
    RCString strTest2(strTest);
    RCString strTest3 = strTest2;
    RCString strTest4 = "morcohen";
    RCString *strTest5 = new RCString(strTest4);

    assert(strTest.RCCounter() == 3);
    assert(strTest2.RCCounter() == 3);
    assert(strTest3.RCCounter() == 3);
    assert(strTest4.RCCounter() == 2);
    assert(strTest5->RCCounter() == 2);

    delete (strTest5);

    assert(strTest4.RCCounter() == 1);
}

void LengthTest(void)
{
    RCString strTest("mor");
    assert(strTest.Length() == 3);
}

void AccessTest(void)
{
    RCString strTest("mor123");
    assert(strTest[4] == '2');
    strTest[4] = '3';
    assert(strTest[4] == '3');
}

void OutPutTest(void)
{
    RCString strTest = "Hello world! \n";
    std::cout << strTest;
}

void InputTest(void)
{
    RCString strTest;

    std::cin >> strTest;

    std::cout  << "The input was : " << strTest << std::endl ;
}
