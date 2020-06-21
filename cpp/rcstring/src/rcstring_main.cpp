#include <iostream>

#include "rcstring.hpp"

using namespace std;
using namespace ilrd;

bool TestLength(size_t actual, size_t exp)
{
    return actual == exp;
}

bool TestEqualCopy(RCString rcs[], const char *strings[])
{
    bool success = true;

    for (size_t i = 0; i < 3; ++i)
    {
        if (strcmp(rcs[i].RCStr(), strings[0]) != 0)
        {
            cout << "Failed. i = " << i << endl;
            cout << "Returned: " << rcs[i].RCStr() << endl;
            cout << "Expected: " << strings[0] << endl;
            success = false;
        }
    }
    return success;
}

bool TestEqualOp(RCString rcs[])
{
    bool success = true;

    for (size_t i = 0; i < 2; ++i)
    {
        if (!(rcs[i] == rcs[i + 1]))
        {
            cout << "Failed. i = " << i << endl;
            cout << "Returned: " << (rcs[i] == rcs[i + 1]) << endl;
            cout << "Expected: " << 1 << endl;
            success = false;
        }
    }
    return success;
}

bool TestLessThanOp(const RCString& s1, const RCString& s2)
{
    bool success = true;

    for (size_t i = 0; i < 1; ++i)
    {
        if (!(s1 < s2))
        {
            // cout << "Failed. i = " << i << endl;
            // cout << "Returned: " << (s1 < s2) << endl;
            // cout << "Expected: " << 1 << endl;
            success = false;
        }
    }
    return success;
}

bool TestGreaterThanOp(const RCString& s1, const RCString& s2)
{
    bool success = true;

    for (size_t i = 0; i < 1; ++i)
    {
        if (!(s1 > s2))
        {
            // cout << "Failed. i = " << i << endl;
            // cout << "Returned: " << (s1 > s2) << endl;
            // cout << "Expected: " << 1 << endl;
            success = false;
        }
    }
    return success;
}

bool TestSubscriptOpConst(const RCString& rc, const char *string)
{
    if (rc.Length() != strlen(string)) return false;

    for (size_t i = 0; i < rc.Length(); ++i)
    {
        if (rc[i] != string[i]) return false;
    }

    return true;
}

bool TestSubscriptOp(RCString& rc1, RCString& rc2)
{
    assert(rc1 == rc2);
    assert(rc1.RCStr() == rc2);
    assert(rc1 == rc2.RCStr());
    
    rc1[0] = 'a';

    assert(!(rc1 == rc2));

    rc1[rc1.Length() - 1] = 'b';

    return true;
}

bool TestLength(const RCString& s, const char *string)
{
    if (!(s.Length() == strlen(string))) return false;
    
    return true;
}

void TestIStream()
{
    RCString s4;
    cin >> s4;
    cout << "Entered input: " << s4 << endl;
}

void PrintPassFail(bool result)
{
    const char *message = result ? "passed." : "failed.";
    cout << message << endl;
}

int main()
{
    const char *strings[] = {"", "2 another", "3rd", "4th"};
    RCString s1 = strings[0];
    RCString s2(s1);
    RCString s3 = s1;

    RCString rcs[] = {s1, s2, s3};

    PrintPassFail(TestLength(s1.Length(), strlen(strings[0])));
    PrintPassFail(TestLength(s2.Length(), strlen(strings[0])));
    PrintPassFail(TestLength(s3.Length(), strlen(strings[0])));

    PrintPassFail(TestLength(s1, strings[0]));
    PrintPassFail(TestLength(s2, strings[0]));
    PrintPassFail(TestLength(s3, strings[0]));

    PrintPassFail(TestSubscriptOpConst(s1, strings[0]));
    PrintPassFail(TestSubscriptOpConst(s2, strings[0]));
    PrintPassFail(TestSubscriptOpConst(s3, strings[0]));

    PrintPassFail(TestEqualCopy(rcs, strings));
    PrintPassFail(TestEqualOp(rcs));

    s1 = strings[1];
    PrintPassFail(TestLength(s1.Length(), strlen(strings[1])));

    PrintPassFail(TestLength(s1, strings[1]));
    PrintPassFail(TestSubscriptOpConst(s1, strings[1]));

    RCString rcs1[] = {s1, s2};
    PrintPassFail(TestGreaterThanOp(s1, s2));
    PrintPassFail(TestGreaterThanOp(s1, s3));
    PrintPassFail(!TestGreaterThanOp(s3, s1));
    PrintPassFail(!TestGreaterThanOp(s2, s1));

    s3 = s1;
    PrintPassFail(TestLength(s3.Length(), strlen(strings[1])));

    PrintPassFail(TestLength(s3, strings[1]));
    PrintPassFail(TestSubscriptOpConst(s3, strings[1]));

    PrintPassFail(TestGreaterThanOp(s1, s2));
    PrintPassFail(!TestLessThanOp(s1, s2));

    PrintPassFail(TestGreaterThanOp(s3, s2));
    PrintPassFail(!TestLessThanOp(s3, s2));

    PrintPassFail(!TestGreaterThanOp(s1, s3));

    PrintPassFail(TestLessThanOp(s2, s1));
    PrintPassFail(!TestGreaterThanOp(s2, s1));

    PrintPassFail(TestLessThanOp(s2, s3));
    PrintPassFail(!TestGreaterThanOp(s2, s3));

    s2 = strings[2];
    PrintPassFail(TestLength(s2.Length(), strlen(strings[2])));
    
    PrintPassFail(TestLength(s2, strings[2]));
    PrintPassFail(TestSubscriptOpConst(s2, strings[2]));

    PrintPassFail(TestLessThanOp(s1, s2));
    PrintPassFail(TestLessThanOp(s3, s2));

    PrintPassFail(TestGreaterThanOp(s2, s1));
    PrintPassFail(TestGreaterThanOp(s2, s3));
    
    // cout << s1 << endl;
    // cout << s3 << endl;
    
    TestSubscriptOp(s1, s3);
    
    // cout << s1 << endl;
    // cout << s3 << endl;

    TestIStream();

}
