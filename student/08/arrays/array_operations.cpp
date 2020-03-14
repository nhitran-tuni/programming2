#include "array_operations.hh"
#include <istream>

int greatest_v1(int* itemptr, int size) {
    int max = *itemptr;
    for (int i = 0; i < size; i++) {
        if (max < itemptr[i]) {
            max = itemptr[i];
        }
    }
    return max;
}

int greatest_v2(int* itemptr, int* endptr) {
    int max = *itemptr;
    for (;itemptr < endptr; itemptr++) {
        if (max < *itemptr) {
            max = *itemptr;
        }
    }
    return max;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    while (itemptr != endptr){
        *targetptr++ = *itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr) {
    while (leftptr < rightptr) {
        int end = *(rightptr - 1 );
        *rightptr = *leftptr;
        *leftptr = end;
    leftptr++;
    rightptr--;
    }
}

