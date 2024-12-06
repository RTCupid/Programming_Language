#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Language.h"

const char* s = "(520-20)/10$";
int         p = 0;

/*
{ G ::= E '&'
{ E ::= T {['+' '-'] T}*
{ T ::= P {['*' '/'] P}*
{ P ::= '(' E ')' | N
{ N ::= ['0'-'9']+

*/

int GetG ()
{
    printf ("Start\n");
    int val = GetE ();
    if (s[p] != '$')
    {
        assert (0);
    }
    p++;
    return val;
}

int GetE ()
{
    int val = GetT ();
    while (s[p] == '+' || s[p] == '-')
    {
        int op = s[p];
        p++;
        int val2 = GetT ();
        if (op == '+')
        {
            val += val2;
        }
        if (op == '-')
        {
            val -= val2;
        }
    }
    return val;
}

int GetT ()
{
    int val = GetP ();
    while (s[p] == '*' || s[p] == '/')
    {
        int op = s[p];
        p++;
        int val2 = GetP ();
        if (op == '*')
        {
            val *= val2;
        }
        if (op == '/')
        {
            val /= val2;
        }
    }
    return val;
}

int GetP ()
{
    if (s[p] == '(')
    {
        p++;
        int val = GetE ();
        if (s[p] != ')')
        {
            assert (0);
        }
        p++;
        return val;
    }
    else
    {
        return GetN ();
    }
}

int GetN ()
{
    int val = 0;
    while ('0' <= s[p] && s[p] <= '9')
    {
        val = val * 10 + s[p] - '0';
        p++;
    }
    return val;
}


