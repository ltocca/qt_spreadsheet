#include "Max.h"

double Max::calc() {
    if (getElements().empty())
        return 0;
    double max = getElements().front();
    for (auto element : elements) {
        if (max < element)
            max = element;
    }
    return max;
}