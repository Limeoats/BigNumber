#include "src/bignumber.h"

#include <iostream>

int main() {
    BigNumber b("35");
    BigNumber c("62");
    std::cout << b * c << std::endl;
}