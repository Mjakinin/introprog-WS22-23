#include <stdio.h>
// Gibt die Zahl x^x für alle Zahlen zwischen 1 und n aus
//
// 1^1 = 1 = 1
// 2^2 = 2*2 = 4
// 3^3 = 3*3*3 = 27
// 4^4 = 4*4*4*4 = 256
// ...
// n^n
int multi(int x){

    int result=1;

    for(int i=0; i<x; i++){

        result = result * x;
    }

    return result;
}

int main()
{
for(int i=1; i<10; i++){

    printf("%d \n", multi(i));
}
}