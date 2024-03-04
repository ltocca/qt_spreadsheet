#include "Sum.h"

double Sum::calc() {
    if (getElements().empty())
        return 0;
    double sum = 0;
    for (auto element : elements) {
        sum += element;
    }
    return sum;
}

