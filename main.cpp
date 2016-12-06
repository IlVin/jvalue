#include <iostream>
#include <string>
#include "include/jvalue.h"

using namespace NJValue;
using namespace std;

int main() {

    TJValue<JSON_INTEGER> a = 0;
    TJValue<JSON_DOUBLE> b = (JSON_DOUBLE)7.17;
    TJValue<JSON_STRING> c = (JSON_STRING)"";
    TJValue<JSON_BOOL> d = (JSON_BOOL)true;


    cout << "a = " << a.ToString() << endl;
    cout << "b = " << b.ToString() << endl;
    cout << "c = " << c.ToString() << endl;
    cout << "d = " << d.ToString() << endl;

    cout << "a is " << a.ToBool() << endl;
    cout << "b is " << (JSON_BOOL)b << endl;
    cout << "c is " << c.ToBool() << endl;
    cout << "d is " << d.ToBool() << endl;

    return 0;
}
