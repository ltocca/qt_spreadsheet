#include "Mean.h"

double Mean::calc() {
    if (getElements().empty())
        return 0;
    double result = 0;
    for (auto element : elements) {
        result += element;
    }
    return result / static_cast<double>(getElements().size());
}
