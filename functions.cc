#include "functions.hh"

void add_to_all(int *data, int length, int value)
{
    for (int i = 0; i < length; i++) {
        data[i] += value;
    }
}
