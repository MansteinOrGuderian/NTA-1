#include <iostream>
#include <vector>

long long int greater_common_divisor(long long int number_one, long long int number_two) {
    long long int temp;
    if (number_one < 0)
        number_one = -number_one;
    if (number_two < 0)
        number_two = -number_two;
    while (number_two != 0) {
        temp = number_one % number_two;
        number_one = number_two;
        number_two = temp;
    }
    return number_one;
}