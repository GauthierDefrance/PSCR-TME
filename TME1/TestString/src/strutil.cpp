// strutil.cpp
#include "strutil.h"

#include <algorithm>

namespace pr {

size_t length(const char* s) {
    if (s == nullptr) return 0;
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

char* newcopy(const char* s) {

    char *ns = new char[length(s) + 1];

    for (int i = 0; s[i] != '\0'; i++)
    {
        ns[i] = s[i];
    }

    return ns;
}

int compare(const char* a, const char* b) {

    int lenghtA = length(a);
    int lenghtB = length(b);
    int minLenght = std::min(lenghtA, lenghtB);


    int i = 0;


    return 0;
}

}
