#include "Header.h"


long long int int_number_to_int_degree(long long int number, long long int power) {
    if (power == 0)
        return 1;
    long long int original_number = number;
    while (power > 1) {
        number *= original_number;
        power--;
    }
    return number;
}

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

std::vector<long long int> from_decimal_number_to_new_numeral_scale_of_notation(long long int old_decimal_number, long long int new_scale) {
    long long int number_output = 0;
    std::vector<long long int> array_where_number_in_new_scale_will_be_stored;
    while (old_decimal_number != 0) {
        number_output = old_decimal_number % new_scale; // take and remember a remainder
        old_decimal_number /= new_scale; // divide by new scale (from 2 up to 16)
        array_where_number_in_new_scale_will_be_stored.insert(array_where_number_in_new_scale_will_be_stored.begin(), array_to_work_with_16_scale_notation[number_output]);
        //printf("%c ", array_to_work_with_16_scale_notation[number_output]);
    }
    return array_where_number_in_new_scale_will_be_stored;
} // int number -> to int array partition (could be interpret as integer-numerical char codes)

std::vector<long long int> return_number_in_binary_numeral_system(unsigned long long int decimal_number) {
    std::vector<long long int> binary_record_of_number = from_decimal_number_to_new_numeral_scale_of_notation(decimal_number, 2);
    for (int i = 0; i < binary_record_of_number.size(); i++)
        binary_record_of_number[i] -= '0';
    /*for (auto& place : binary_record_of_number) {
    place -= '0';
    //std::cout << place << ' ';    // typeid(place).name() is __int64
    }*/
    return binary_record_of_number;
}

long long int legendre_symbol(long long int numerator_a, long long int denominator_p) { // denominator_p should be prime, or will recieve wrong answer!
    long long int legendre_symbol_value = Barret_Gorner(numerator_a, denominator_p, 10, return_number_in_binary_numeral_system( (denominator_p - 1) / 2) ); // Computing a ^ ((p - 1) / 2),  Euler's criterion a ^ ((p - 1) / 2) == 1 mod p 
    return (legendre_symbol_value == (denominator_p - 1) ? -1 : legendre_symbol_value);
}

bool if_pseudo_prime_number_by_Euler(long long int odd_number_p, long long int base_number) { // if gcd(a, p) == 1 and (a/p) == a ^ ((p - 1) / 2) mod p
    return (Barret_Gorner(base_number, odd_number_p, 10, return_number_in_binary_numeral_system((odd_number_p - 1) / 2)) == (legendre_symbol(base_number, odd_number_p) % odd_number_p)) ? true : false;
}

long long int return_countDigit_in_number(long long int number_to_found_digits) {
    if (number_to_found_digits == 0)
        return 1;
    long long int countDigit = 0;
    while (number_to_found_digits != 0) {
        number_to_found_digits = number_to_found_digits / 10;
        ++countDigit;
    }
    return countDigit;
}

long long int clear_Gorner(long long int X_base_to_power, std::vector<long long int> e_binary_power) {
    long long Y_answer = 1;
    //std::reverse(e.begin(), e.end());
    for (int i = 0; i <= e_binary_power.size() - 1; i++) { //int i = e.size()-1; i >= 0; i--
        Y_answer = Y_answer * Y_answer;
        if (e_binary_power[i] == 1)
            Y_answer = Y_answer * X_base_to_power;
    }
    return Y_answer;
}

long long int clear_Barret(long long int x_number, long long int n_mod_number, long long int base_scale) {
    long long int k_digit_number = return_countDigit_in_number(n_mod_number);
    if (!n_mod_number)
        return -1;
    long long int hard_division_niu = (int)pow(base_scale, k_digit_number) / (2 * n_mod_number);
    long long int q1, q2, q3, result;
    q1 = x_number / pow(base_scale, k_digit_number - 1);
    q2 = q1 * hard_division_niu;
    q3 = q2 / pow(base_scale, k_digit_number + 1);
    result = x_number - q3 * n_mod_number;
    while (result >= n_mod_number)
        result -= n_mod_number;
    return result;
}

long long int Barret_Gorner(long long int X_base_to_power, long long int n_mod_number, long long int base_scale, std::vector<long long int> e_binary_power) {
    long long Y_answer = 1;
    //std::reverse(e.begin(), e.end());
    for (int i = 0; i <= e_binary_power.size() - 1; i++) { //int i = e.size()-1; i >= 0; i--
        Y_answer = clear_Barret(Y_answer * Y_answer, n_mod_number, base_scale);
        if (e_binary_power[i] == 1)
            Y_answer = clear_Barret(Y_answer * X_base_to_power, n_mod_number, base_scale);
    }
    return Y_answer;
}

bool primality_Solovay_Strassen_test(long long int number_to_test, long long int amount_of_tries) { // detect not prime numbers, with probapility 1 / 2 ^ amount_of_tries, for all prime numbers, exept 2, will return 0
    if (number_to_test == 2) 
        return true; // is prime
    if (number_to_test % 2 == 0 || number_to_test == 1)
        return false; // isn't prime
    srand((unsigned)time(0));
    long long int lower_bound = 2, upper_bound = number_to_test - 2;
    for (int current_iteration = 0; current_iteration < amount_of_tries; current_iteration++) {
        long long int randomly_generated_number = rand() % upper_bound + lower_bound;
        if (greater_common_divisor(randomly_generated_number, number_to_test) != 1)
            return false;
        if (!if_pseudo_prime_number_by_Euler(number_to_test, randomly_generated_number))
            return false;
    }
    return true; 
}

