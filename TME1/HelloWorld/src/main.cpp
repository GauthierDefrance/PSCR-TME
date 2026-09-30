#include <iostream>


int main(){

    std::cout << "Hello World !" << std::endl;

    int *tab = new int[10];
    
    for (int i = 0; i < 10; i++) {
        tab[i] = i;
    }

    bool check = true;

    for (int i=9; i > 0 ; i--) {
        if (tab[i] - tab[i-1] != 1) {
            std::cout << "probleme !" << std::endl;
            check = false;
        }
    }

    if (check)
    {
        std::cout << "La liste est superbe !" << std::endl;
    } else
    {
        std::cout << "La liste est problématique !" << std::endl;
    }

    return 0;
}