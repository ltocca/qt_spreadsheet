#include "Min.h"

double Min::calc() {
    if (getElements().empty())
        return 0;
    double min = getElements().front();
    for (auto element : elements) {
        if (element < min)
            min = element;
    }
    return min;
}