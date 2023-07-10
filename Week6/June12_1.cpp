#include <iostream>
using namespace std;
void recursiveFunction (int n) {
    int local_var = 0;

    if (n > 0) {
        recursiveFunction(n - 1);
        
        
    }

    cout << "local variable at address: " << &local_var << endl;
}

int main () {
    recursiveFunction(5);
}

/* outputs as follows:
local variable at address: 0xc58a3ff4ec
local variable at address: 0xc58a3ff52c
local variable at address: 0xc58a3ff56c
local variable at address: 0xc58a3ff5ac
local variable at address: 0xc58a3ff5ec
since each function call allocates its local variables in smaller memory addresses than the last, the stack grows downwards with each call.*/