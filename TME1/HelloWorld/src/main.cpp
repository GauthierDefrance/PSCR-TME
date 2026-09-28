#include <iostream>


int main(){

    std::cout << "Hello World !" << std::endl;

    int *tab = new int[10];
    
    for (int i = 0; i < 10; i++) {
        tab[i] = i;
    }

    for (int i=9; i > 0 ; i--) {
        if (tab[i] - tab[i-1] != 1) {
            std::cout << "probleme !" << std::endl;
        }
    }

    return 0;
}