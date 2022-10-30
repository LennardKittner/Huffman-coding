//
// Created by Lennard on 30.10.22.
//

#include <cmath>
#include "utils.h"

std::shared_ptr<std::string> toBinary(int number, int padding) {
    auto  result = std::make_shared<std::string>();
    while (number != 0) {
        *result = (number % 2 == 0 ? "0" : "1") + *result;
        number/=2;
    }

    while (result->size() < padding)
        *result = "0" + *result;
    return result;
}

std::shared_ptr<int> toDecimal(std::string binary) {
    auto result = std::make_shared<int>();
    for (int i = binary.size()-1;i >= 0;i--) {
        *result += (binary[i] == '1' ? pow(2, (binary.size()-1)-i) : 0);
    }
    return result;
}