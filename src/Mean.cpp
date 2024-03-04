
#include "Mean.h"

double Mean::calc() {
    double result;
    for (auto element : elements) {
        result += element;
    }
    if (getElements().empty())
        return 0;
    return result / getElements().size();
}
