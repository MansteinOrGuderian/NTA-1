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

bool primality_Solovay_Strassen_test(long long int number_to_test, long long int amount_of_tries) { // detect not prime numbers, with probability 1 / 2 ^ amount_of_tries, for all prime numbers, exept 2, will return 0
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

bool primality_Miller_Rabin_test(long long int number_to_test, long long int amount_of_tries) { // detect not prime numbers, with probability 1 / 4 ^ amount_of_tries, for all prime numbers, exept 2, will return 0
    if (number_to_test < 2)
        return false;
    if (number_to_test == 2)
        return true; // is prime
    if (number_to_test % 2 == 0)
        return false; // isn't prime
    long long int multiplier_d = number_to_test - 1;
    long long int power_of_two = 0;
    while (multiplier_d % 2 == 0) { // factoring number: (number_to_test - 1) == d * 2^n
        power_of_two++;
        multiplier_d /= 2;
    }
    long long int lower_bound = 2, upper_bound = number_to_test - 1;
    for (int current_iteration = 0; current_iteration < amount_of_tries; current_iteration++) {
        long long int randomly_generated_number = rand() % upper_bound + lower_bound;
        if (greater_common_divisor(randomly_generated_number, number_to_test) > 1)
            return false;
        long long int number_x = Barret_Gorner(randomly_generated_number, number_to_test, 10, return_number_in_binary_numeral_system(multiplier_d));
        if (number_x == 1 || number_x == (number_to_test - 1))
            continue;
        bool flag_to_continue = 0;
        for (int current_degree = 0; current_degree < power_of_two - 1; current_degree++) {
            number_x = Barret_Gorner(number_x, number_to_test, 10, return_number_in_binary_numeral_system(2));
            if (number_x == number_to_test - 1) {
                flag_to_continue = 1;
                break;
            }
        }
        if (!flag_to_continue)
            return false;
    }
    return true;
}


long long int rho_pollard_factorization(long long int n_mod_number) {
    //long long int n_mod_number;
    //std::cout << "Enter the mod number n\n"; // number to factorize
    //std::cin >> n_mod_number;
    std::cout << "Enter the biggest degree of polynom\n";
    int biggest_degree;
    std::cin >> biggest_degree; //5
    biggest_degree += 1;
    std::cout << "Enter the coef of polymon f(x)\n";
    int* coef_polynom_array = new int[biggest_degree]; // 6 places (a_n * x^n + ... + a_0 * x^0 )
    for (int i = 0; i < biggest_degree; i++) {
        int number_coef;
        std::cin >> number_coef;
        /*if (i == 0) {
            coef_polynom_array[i] = 1;
            continue;
        }*/
        coef_polynom_array[i] = number_coef;
    }
    std::cout << "Coef of polynom f(x) are\n";
    for (int i = 0; i < biggest_degree; i++)
        std::cout << coef_polynom_array[i] << ' ';
    // std::cout << "\nEnter the beginning position x0\n";
    long long int x_null = 2; // From task
    std::cout << "Start position of x0 is: " << x_null;
    //std::cin >> x_null;
    long long int approximate_size_of_array_of_subsequence = 5000; //((long long int)sqrt(n_mod_number)) + 1;  // approximate decide to do so size
    long long int* array_of_function_values = new long long int[approximate_size_of_array_of_subsequence];
    array_of_function_values[0] = x_null;
    for (int i = 1; i < approximate_size_of_array_of_subsequence; i++) {
        long long int function_value = 0;
        for (int current_coef = 0, current_degree = biggest_degree - 1; current_coef < biggest_degree; current_coef++, current_degree--) {
            long long int temp_value = 0;
            temp_value = clear_Barret(int_number_to_int_degree(array_of_function_values[i - 1], current_degree), n_mod_number, 10); // ((x_i) ^ j ) % n_mod
            temp_value = clear_Barret(coef_polynom_array[current_coef] * temp_value, n_mod_number, 10); //  (a_j * value) % n_mod
            function_value = clear_Barret(function_value + temp_value, n_mod_number, 10); // (a_n * x^n + ... a_0 * x^0) % n_mod
        }
        array_of_function_values[i] = function_value;
    }
    bool break_point = 0;
    long long int one_of_multiplier = 0;
    while (!break_point) { //ro-pollard with Floyd modification
        for (long long int i = 2; i < approximate_size_of_array_of_subsequence; i += 2) { // pairs form (x_2k, x_k)
            long long int temp_difference = array_of_function_values[i] - array_of_function_values[i / 2];
            temp_difference = temp_difference > 0 ? temp_difference : (-1) * temp_difference;
            temp_difference = greater_common_divisor(temp_difference, n_mod_number);
            std::cout << " i = " << i << " j = " << i / 2 << '\n';
            std::cout << "gcd( " << array_of_function_values[i] << " - " << array_of_function_values[i / 2] << " , " << n_mod_number << " ) = " << temp_difference << '\n';
            if (temp_difference != 1) {
                break_point = 1;
                one_of_multiplier = temp_difference;
                break;
            }
        }
    }
    return one_of_multiplier;
}

Pair_of_elements<long long int*, long long int> Sieve_of_Eratosthenes(long long int number_to_which_count_primes) {
    if (number_to_which_count_primes < 1) {
        Pair_of_elements<long long int*, long long int> Data(NULL, 0);
        return Data; // There are no prime values
    }
    switch (number_to_which_count_primes)
    {
    case 2: {
        long long int* array_of_primes = new long long int[1]{ 2 };
        Pair_of_elements<long long int*, long long int> Data(array_of_primes, 1);
        return Data;
        break;
    }
    case 3: {
        long long int* array_of_primes = new long long int[2]{ 2, 3 };
        Pair_of_elements<long long int*, long long int> Data(array_of_primes, 2);
        return Data;
        break;
    }
    default:
        long long int array_of_numbers_size = number_to_which_count_primes + 1;
        long long int* array_number = new long long int[array_of_numbers_size] {};
        bool* if_number_is_prime_array = new bool[array_of_numbers_size] {};
        long long int amount_of_prime_numbers = array_of_numbers_size;
        for (long long int i = 0; i < array_of_numbers_size; i++) {
            array_number[i] = i;
            if_number_is_prime_array[i] = 1;
            //std::cout << array_number[i] << ' ';
        }
        if_number_is_prime_array[0] = 0; // 0 isn't prime
        if_number_is_prime_array[1] = 0; // 1 isn't prime
        for (long long int i = 0; i <= (int)sqrt(number_to_which_count_primes); i++) { // 2 3 4
            if (if_number_is_prime_array[i]) // 0 0 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0(!)
                for (long long j = i * i; j <= number_to_which_count_primes; j += i) {
                    if (if_number_is_prime_array[j] == 0)
                        continue;
                    else {
                        if_number_is_prime_array[j] = 0;
                        amount_of_prime_numbers--;
                    }
                }
            /*std::cout << '\n';
            for (int k = 0; k < array_of_numbers_size; k++)
                std::cout << if_number_is_prime_array[k] << ' ';*/
        }
        amount_of_prime_numbers -= 2; // minus two places, because 0 and 1 are not primes
        long long int* array_of_primes = new long long int[amount_of_prime_numbers] {};
        for (long long int i = 0, j = 0; i < array_of_numbers_size; i++) {
            if (if_number_is_prime_array[i]) {
                array_of_primes[j] = array_number[i];
                j++;
            }
        }
        //for (int i = 0; i < amount_of_prime_numbers; i++) {
        //    std::cout << array_of_primes[i] << ' ';
        //}
        Pair_of_elements<long long int*, long long int> Data(array_of_primes, amount_of_prime_numbers);
        return Data;
        break;
    }
}