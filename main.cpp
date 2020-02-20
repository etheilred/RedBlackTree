#include <iostream>
#include <random>
#include "RBTree.h"

using namespace std;

int main() {
    RBTree rbt;
    for (int i = 1; i < 11; ++i) rbt.add(i);
    rbt.print();
    while (!rbt.empty()) {
        int c;
        cin >> c;
        rbt.remove(c);
        rbt.print();
    }
    cout << "OK" << endl;
    return 0;
}
