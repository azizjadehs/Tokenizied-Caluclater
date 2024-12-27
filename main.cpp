#include <iostream>
#include <string>
using namespace std;

#include "DList.h"
#include "TwoStackAlgo.h"

int main() {

string str;

while (true) {
    
    cout << "input (Abbruch: stop):";
    cin >> str;

    if (str == "stop")
        break;

    cout << "=" << calc(str) << endl;
}

}