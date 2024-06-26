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
    if (old_decimal_number == 0) { // to work correctly
        std::vector<long long int> array_where_number_in_new_scale_will_be_stored;
        array_where_number_in_new_scale_will_be_stored.push_back(0);
        return array_where_number_in_new_scale_will_be_stored;
    }
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
    for (long long int i = 0; i < binary_record_of_number.size(); i++)
        binary_record_of_number[i] -= '0';
    /*for (auto& place : binary_record_of_number) {
    place -= '0';
    //std::cout << place << ' ';    // typeid(place).name() is __int64
    }*/
    return binary_record_of_number;
}

long long int int_number_to_int_degree_with_mod(long long int number, long long int power, long long int modulo) {
    if (power == 0)
        return 1;
    long long int original_number = number;
    while (power > 1) {
        number = ((number % modulo) * (original_number % modulo) % modulo);
        power--;
    }
    return number;
}

long long int legendre_symbol(long long int numerator_a, long long int denominator_p) {  // denominator_p should be prime, or will recieve wrong answer!
    if (denominator_p == 1 || numerator_a == 1)
        return 1;
    //if (denominator_p == -1)
    //    return int_number_to_int_degree(-1, (denominator_p - 1) / 2); // (-1 / p) = (-1)^(p-1)/2
    if (denominator_p % numerator_a == 0) // a == p * k (
        return 0;
    long long int degree = (denominator_p - 1) / 2; // using Euler's criterion (a/p) == a ^ ((p - 1) / 2) mod p
    long long int result_by_Euler_criterion = int_number_to_int_degree_with_mod(numerator_a, degree, denominator_p);// Barret_Gorner(numerator_a, denominator_p, 10, return_number_in_binary_numeral_system(degree));
    if (result_by_Euler_criterion == 1) 
        return 1;
    else
        return -1;
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
    for (long long int i = 0; i <= e_binary_power.size() - 1; i++) { //int i = e.size()-1; i >= 0; i--
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
    long long int hard_division_niu = int_number_to_int_degree(base_scale, k_digit_number) / (2 * n_mod_number);
    long long int q1, q2, q3, result;
    q1 = (long long int)(x_number / int_number_to_int_degree(base_scale, k_digit_number - 1));
    q2 = q1 * hard_division_niu;
    q3 = (long long int)(q2 / int_number_to_int_degree(base_scale, k_digit_number + 1));
    result = x_number - q3 * n_mod_number;
    while (result >= n_mod_number)
        result -= n_mod_number;
    return result;
}

long long int Barret_Gorner(long long int X_base_to_power, long long int n_mod_number, long long int base_scale, std::vector<long long int> e_binary_power) {
    long long Y_answer = 1;
    //std::reverse(e.begin(), e.end());
    for (long long int i = 0; i <= e_binary_power.size() - 1; i++) { //int i = e.size()-1; i >= 0; i--
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
    //std::cout << "Enter the biggest degree of polynomial\n";
    int biggest_degree;
    //std::cin >> biggest_degree;
    //biggest_degree += 1;
    biggest_degree = 3;
    //std::cout << "Enter the coef of polymon f(x)\n";
    //int* coef_polynomial_array = new int[biggest_degree]; // (a_n * x^n + ... + a_0 * x^0 )
    //for (int i = 0; i < biggest_degree; i++) {
    //    int number_coef;
    //    std::cin >> number_coef;
    //    /*if (i == 0) {
    //        coef_polynomial_array[i] = 1;
    //        continue;
    //    }*/
    //    coef_polynomial_array[i] = number_coef;
    //}
    int* coef_polynomial_array = new int[biggest_degree] {1, 0, 1}; // 1* x^2 + 0 * x + 1
    /*std::cout << "Coef of polynomial f(x) are\n";
    for (int i = 0; i < biggest_degree; i++)
        std::cout << coef_polynomial_array[i] << ' ';*/

    //std::cout << "\nEnter the beginning position x0\n";
    long long int x_null = 2; // From task
    //std::cin >> x_null;
    //std::cout << "\nStart position of x0 is: " << x_null;
    long long int approximate_size_of_array_of_subsequence = 5000; // ((long long int)sqrt(n_mod_number)) + 1;  // approximate decide to do so size
    long long int* array_of_function_values = new long long int[approximate_size_of_array_of_subsequence];
    array_of_function_values[0] = x_null;
    for (int i = 1; i < approximate_size_of_array_of_subsequence; i++) {
        long long int function_value = 0;
        for (int current_coef = 0, current_degree = biggest_degree - 1; current_coef < biggest_degree; current_coef++, current_degree--) {
            long long int temp_value = 0;
            temp_value = clear_Barret(int_number_to_int_degree(array_of_function_values[i - 1], current_degree), n_mod_number, 10); // ((x_i) ^ j ) % n_mod
            temp_value = clear_Barret(coef_polynomial_array[current_coef] * temp_value, n_mod_number, 10); //  (a_j * value) % n_mod
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
            // std::cout << " i = " << i << " j = " << i / 2 << '\n';
            //std::cout << "gcd( " << array_of_function_values[i] << " - " << array_of_function_values[i / 2] << " , " << n_mod_number << " ) = " << temp_difference << '\n';
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

long long int* return_number_as_array_of_its_digit(long long int number) {
    long long int digits_in_number = return_countDigit_in_number(number);
    long long int* number_as_array = new long long int[digits_in_number];
    while (digits_in_number) {
        int temp = number % 10; // decimal base scale
        number_as_array[digits_in_number - 1] = temp;
        number /= 10;
        digits_in_number--;
    }
    return number_as_array;
}

long long int bruteforce_factorization(long long int n_mod_number) {
    long long int base_scale = 10;
    long long int digits_in_number = return_countDigit_in_number(n_mod_number);
    long long int* number_as_array = return_number_as_array_of_its_digit(n_mod_number);
    Pair_of_elements<long long int*, long long int> data_about_prime_numbers = Sieve_of_Eratosthenes(100); // in task asked less then 47
    bool is_divisor = 0;
    long long int one_of_multiplier = 0;
    for (long long int index_of_current_prime_number = 0; index_of_current_prime_number < data_about_prime_numbers.variable_two; index_of_current_prime_number++) {
        long long int remainder = 0; // using Pascal divisibility rule
        long long int current_prime = data_about_prime_numbers.variable_one[index_of_current_prime_number];
        for (long long int current_digit = digits_in_number - 1, current_degree = 0; current_digit >= 0; current_digit--, current_degree++) {
            remainder = remainder + ((number_as_array[current_digit] * (int_number_to_int_degree(10, current_degree) % current_prime)) % current_prime);
            remainder %= current_prime;
        }
        if (remainder == 0)
            return current_prime;
    }
    return -1; // input number don't have any divisors less than 48
}

long long int quadratic_sieve_algorithm(long long int number_to_factorise_n) {
    Pair_of_elements<long long int*, long long int> factor_base_data = formatting_factor_base(number_to_factorise_n);
    long long int* factor_base_in_array = factor_base_data.variable_one;
    long long int size_of_factor_base = factor_base_data.variable_two;
    //long long int size_of_factor_base = 4;
    //long long int* factor_base_in_array = new long long int[size_of_factor_base] { -1, 2, 5, 7};
    for (long long int index = 0; index < size_of_factor_base; index++)
        std::cout << factor_base_in_array[index] << ' ';
    std::cout << "\n\n\n";
   
    long long int sieving_interval_parameter_M = 7500; 
    //long long int sieving_interval_parameter_M = 7;
    long long int size_of_sieving_interval = 2 * sieving_interval_parameter_M + 1;
    long long int* interval_as_array = new long long int[size_of_sieving_interval];
    long long int* array_of_a = new long long int[size_of_sieving_interval];
    long long int* array_of_b = new long long int[size_of_sieving_interval];
    long long int* array_of_logarithms_b = new long long int[size_of_sieving_interval]; 
    //double* array_of_logarithms_b = new double[size_of_sieving_interval]; 
    long long int* array_of_sum_of_logaritms = new long long int[size_of_sieving_interval] {0}; // With small numbers use instead long long int, double type (better without rounding) 
    //double* array_of_sum_of_logaritms = new double[size_of_sieving_interval] {0};
    for (long long int current_index = 0; current_index < size_of_sieving_interval; current_index++) {
        interval_as_array[current_index] = (-1) * sieving_interval_parameter_M + current_index;
        array_of_a[current_index] = interval_as_array[current_index] + (long long int)sqrt(number_to_factorise_n); // a = X + (int)sqrt(n)
        array_of_b[current_index] = int_number_to_int_degree(array_of_a[current_index], 2) - number_to_factorise_n; // b = a^2 - n
        array_of_logarithms_b[current_index] = log10((array_of_b[current_index] < 0) ? ((-1) * array_of_b[current_index]) : array_of_b[current_index]); // lg |b|
    }
    for (long long int current_prime_index = 1; current_prime_index < size_of_factor_base; current_prime_index++) {
        long long int current_modulo_p = factor_base_in_array[current_prime_index];
        long long int first_term = (2 * (long long int)sqrt(number_to_factorise_n)) % current_modulo_p; // x^2 + 2 * (int)sqrt(n) * x + [(int)sqrt(n)]^2 = n mod p
        long long int constant_term = int_number_to_int_degree_with_mod((long long int)sqrt(number_to_factorise_n), 2, current_modulo_p);
        long long int right_part = number_to_factorise_n % current_modulo_p;
        right_part = ((right_part - constant_term) < 0) ? ((right_part - constant_term + current_modulo_p) % current_modulo_p) : ((right_part - constant_term) % current_modulo_p);
        if (first_term == 0 && right_part == 0) { // x^2 = 0 mod p
            long long int result_x = 0;
            bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
            while (result_x <= sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, result_x);
                //if (index_to_add_logarithm == -1) // can it exactly be?? - No, contidition in "while" permit this
                //    continue; 
                array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                array_if_log_value_was_added[index_to_add_logarithm] = 1;
                result_x += current_modulo_p;
            }
            result_x = 0; // OR  result_x = -current_modulo_p
            while (result_x >= (-1) * sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, result_x);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice to zero value 
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                result_x -= current_modulo_p;
            }
        }
        else if (right_part == 0) { // x^2 + ax = 0 mod p -> x(x+a) = 0 mod p
            bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
            long long int x1_result = 0;
            long long int x2_result = (-1) * first_term, x2_temp = x2_result;
            while (x1_result <= sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                array_if_log_value_was_added[index_to_add_logarithm] = 1;
                //std::cout << x1_result << ' ';
                x1_result += current_modulo_p;
            }
            x1_result = 0; // OR  result_x = -current_modulo_p
            while (x1_result >= (-1) * sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice to zero value 
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x1_result << ' ';
                x1_result -= current_modulo_p;
            }
            while (x2_result <= sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x2_result << ' ';
                x2_result += current_modulo_p;
            }
            x2_result = x2_temp;
            while (x2_result >= (-1) * sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x2_result << ' ';
                x2_result -= current_modulo_p;
            }
        }
        else if (first_term == 0 && right_part != 0) { // x^2 = b mod p
            if (legendre_symbol(right_part, current_modulo_p) != 1)  // no solutions of congruence
                continue;
            Pair_of_elements<long long int, long long int> solve_of_congruence = squaring_root_per_prime_modulo_p(right_part, current_modulo_p);
            long long int x1_result = solve_of_congruence.variable_one, x1_temp = x1_result;
            long long int x2_result = solve_of_congruence.variable_two, x2_temp = x2_result;
            bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
            while (x1_result <= sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                array_if_log_value_was_added[index_to_add_logarithm] = 1;
                //std::cout << x1_result << ' ';
                x1_result += current_modulo_p;
            }
            x1_result = x1_temp;
            while (x1_result >= (-1) * sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x1_result << ' ';
                x1_result -= current_modulo_p;
            }
            while (x2_result <= sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x1_result << ' ';
                x2_result += current_modulo_p;
            }
            x2_result = x2_temp;
            while (x2_result >= (-1) * sieving_interval_parameter_M) {
                long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                }
                //std::cout << x2_result << ' ';
                x2_result -= current_modulo_p;
            }
        }
        else if (first_term != 0 && right_part != 0) { // x^2 + a * x + b = 0 mod p -> x^2 + 2 * (int)sqrt(n) * x + [(int)sqrt(n)]^2  - n = 0 mod p
            long long int first_term = (2 * (long long int)sqrt(number_to_factorise_n)) % current_modulo_p;
            long long int constant_term = int_number_to_int_degree_with_mod((long long int)sqrt(number_to_factorise_n), 2, current_modulo_p);
            long long int right_part = number_to_factorise_n % current_modulo_p;
            constant_term = ((constant_term - right_part) < 0 ? ((constant_term - right_part + current_modulo_p) % current_modulo_p) : (constant_term - right_part));
            int max_counts_of_roots = 2;
            int amount_of_founded_roots = 0;
            long long int x1_result = 0, x2_result = 0; // 0 can't be answer of this case (x^2 + a * x + b = 0 mod p)
            for (long long int current_number = 1; current_number < current_modulo_p; current_number++) {
                if ((current_number * current_number + first_term * current_number + constant_term) % current_modulo_p == 0) { // bruteforce to find roots
                    (x1_result == 0 ? (x1_result = current_number) : (x2_result = current_number));
                    amount_of_founded_roots++;
                }
                if (max_counts_of_roots == amount_of_founded_roots)
                    break;
            }  //std::cout << x1_result << ' ' << x2_result;
            //Pair_of_elements<long long int, long long int> sqrt_D = Tonelli_Shanks_algorithm((first_term * first_term - 4 * 1 * constant_term) % current_modulo_p, current_modulo_p); // DIDN'T work, but is better to solve this case
            //long long int reverse_to_2a = reverse_element_using_Euclidean_algorithm(vector_of_q_from_Euclidean_algorithm(2, current_modulo_p), 2, current_modulo_p);
            //long long int sqrt_D_plus, sqrt_D_minus;
            //(sqrt_D.variable_one > sqrt_D.variable_two) ? (sqrt_D_plus = sqrt_D.variable_one, sqrt_D_minus = sqrt_D.variable_two) : (sqrt_D_plus = sqrt_D.variable_two, sqrt_D_minus = sqrt_D.variable_one);
            //long long int x1_result = ((-1) * first_term + sqrt_D_plus) * reverse_to_2a, x2_result = ((-1) * first_term - sqrt_D_minus) * reverse_to_2a;
            //std::cout << x1_result << ' ' << x2_result;

            if (x1_result == 0 && x2_result == 0)
                continue; // no integer solutions exict
            else if (x1_result != 0 && x2_result == 0) {
                long long int x1_temp = x1_result;
                bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
                while (x1_result <= sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    //std::cout << x1_result << ' ';
                    x1_result += current_modulo_p;
                }
                x1_result = x1_temp;
                while (x1_result >= (-1) * sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                    if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell 
                        array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                        array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    }
                    //std::cout << x1_result << ' ';
                    x1_result -= current_modulo_p;
                }
                //std::cout << '\n';
            }
            //else if (x1_result == 0 && x2_result != 0) {
            //    long long int x2_temp = x2_result;
            //    bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
            //    while (x2_result <= sieving_interval_parameter_M) {
            //        long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
            //        array_of_sum_of_logaritms[index_to_add_logarithm] += log(current_modulo_p);
            //        array_if_log_value_was_added[index_to_add_logarithm] = 1;
            //        //std::cout << x1_result << ' ';
            //        x2_result += current_modulo_p;
            //    }
            //    x2_result = x2_temp;
            //    while (x2_result >= (-1) * sieving_interval_parameter_M) {
            //        long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
            //        if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell 
            //            array_of_sum_of_logaritms[index_to_add_logarithm] += log(current_modulo_p);
            //            array_if_log_value_was_added[index_to_add_logarithm] = 1;
            //        }
            //        //std::cout << x1_result << ' ';
            //        x2_result -= current_modulo_p;
            //    }
            //    //std::cout << '\n';
            //}
            else if (x1_result != 0 && x2_result != 0) {
                long long int x1_temp = x1_result, x2_temp = x2_result;
                bool* array_if_log_value_was_added = new bool[size_of_sieving_interval] {0};
                while (x1_result <= sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                    array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                    array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    //std::cout << x1_result << ' ';
                    x1_result += current_modulo_p;
                }
                x1_result = x1_temp;
                while (x1_result >= (-1) * sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x1_result);
                    if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                        array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                        array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    }
                    //std::cout << x1_result << ' ';
                    x1_result -= current_modulo_p;
                }
                while (x2_result <= sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                    if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                        array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                        array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    }
                    //std::cout << x1_result << ' ';
                    x2_result += current_modulo_p;
                }
                x2_result = x2_temp;
                while (x2_result >= (-1) * sieving_interval_parameter_M) {
                    long long int index_to_add_logarithm = iterative_binary_search(interval_as_array, size_of_sieving_interval, x2_result);
                    if (array_if_log_value_was_added[index_to_add_logarithm] == 0) { // we didn't need add twice log(p_i) to cell
                        array_of_sum_of_logaritms[index_to_add_logarithm] += log10(current_modulo_p);
                        array_if_log_value_was_added[index_to_add_logarithm] = 1;
                    }
                    //std::cout << x2_result << ' ';
                    x2_result -= current_modulo_p;
                }
                //std::cout << '\n';
            }
            else
                continue; // are there any more cases...?
        }
    }
    long long int* array_of_differences = new long long int[size_of_sieving_interval] {0}; // double
    //double* array_of_differences = new double[size_of_sieving_interval] {0}; // double
    std::cout << "X" << "\t" << "a = X - sqrt(n)" << "\t" << "b = a^2 - n" "\t\t" << "lg(|b|)" << "\t\t" << "sum(lg(p))"  << "\t\t" << "lg(|b|) - sum(lg(p))" << '\n';
    for (long long int current_index = 0; current_index < size_of_sieving_interval; current_index++) {
        array_of_differences[current_index] = array_of_logarithms_b[current_index] - array_of_sum_of_logaritms[current_index];
        std::cout << interval_as_array[current_index] << "\t" << array_of_a[current_index] << "\t\t" << array_of_b[current_index] << "\t\t" << array_of_logarithms_b[current_index] << "\t\t" << array_of_sum_of_logaritms[current_index] << "\t\t" << array_of_differences[current_index] << '\n';
    }
    std::cout << "\n\n";

    long long int bound_to_decide_if_can_be_B_number = array_of_differences[0]; // for small numbers can use only first
    for (long long current_index = 1; current_index < size_of_sieving_interval; current_index++)
        if (array_of_differences[current_index] < bound_to_decide_if_can_be_B_number)
            bound_to_decide_if_can_be_B_number = array_of_differences[current_index];
    bound_to_decide_if_can_be_B_number += 2; // setting bound value, if has potential to be B-number 

    //double bound_to_decide_if_can_be_B_number = 1.7;
    //double bound_to_decide_if_can_be_B_number = 1.0;
    std::vector<long long int> candidates_to_B_numbers_vector;
    std::vector<long long int> a_number_from_candidates_in_B_numbers_vector;
    for (long long int current_index = 0; current_index < size_of_sieving_interval; current_index++) {
        if (array_of_differences[current_index] <= bound_to_decide_if_can_be_B_number) {
            candidates_to_B_numbers_vector.push_back(array_of_b[current_index]);
            a_number_from_candidates_in_B_numbers_vector.push_back(array_of_a[current_index]);
        }
    }
    long long int amount_of_potential_B_numbers = candidates_to_B_numbers_vector.size();
    long long int* candidates_to_B_numbers_array = new long long int[amount_of_potential_B_numbers] {0};
    long long int* array_of_a_to_candidates_in_B_numbers = new long long int[amount_of_potential_B_numbers] {0};
    for (long long int current_index = 0; current_index < amount_of_potential_B_numbers; current_index++) {
        candidates_to_B_numbers_array[current_index] = candidates_to_B_numbers_vector[current_index]; // array of potential B-numbers 
        array_of_a_to_candidates_in_B_numbers[current_index] = a_number_from_candidates_in_B_numbers_vector[current_index];
        std::cout << candidates_to_B_numbers_array[current_index] << ' ';
    } std::cout << '\n';


    long long int* array_of_a_of_B_numbers = new long long int[amount_of_potential_B_numbers];
    long long int amount_of_B_numbers = 0, amount_of_false_detected_B_numbers = 0; 
    long long int* array_of_B_numbers = new long long int[amount_of_potential_B_numbers];
    long long int** decomposition_of_B_numbers_with_mod = new long long int* [amount_of_potential_B_numbers];
    long long int** degree_decomposition_of_B_numbers = new long long int* [amount_of_potential_B_numbers];
    for (long long int index = 0; index < amount_of_potential_B_numbers; index++) { 
        decomposition_of_B_numbers_with_mod[index] = new long long int[size_of_factor_base] {0}; // amount of occurrences of each factor_base_number in decomposition by mod 2
        degree_decomposition_of_B_numbers[index] = new long long int[size_of_factor_base] {0}; // amount of occurrences of each factor_base_number in decomposition
    }

    for (long long int index_of_current_potential_B_number = 0; index_of_current_potential_B_number < amount_of_potential_B_numbers; index_of_current_potential_B_number++) {
        long long int current_candidate = candidates_to_B_numbers_array[index_of_current_potential_B_number];
        std::cout << "Decomposition of " << current_candidate << " on multipliers by factor base:\n";
        if (current_candidate < 0) {
            decomposition_of_B_numbers_with_mod[index_of_current_potential_B_number][0]++;
            degree_decomposition_of_B_numbers[index_of_current_potential_B_number][0]++;
            current_candidate = (-1) * current_candidate;
            std::cout << factor_base_in_array[0] << ' ';
        }
        for (long long int current_index_prime = 1; current_index_prime < size_of_factor_base; current_index_prime++) {
            //std::cout << "Current factor " << factor_base_in_array[current_index_prime] << '\n';
            while (current_candidate % factor_base_in_array[current_index_prime] == 0) { // number could divide more than ones on current prime number
                current_candidate = current_candidate / factor_base_in_array[current_index_prime];
                std::cout << factor_base_in_array[current_index_prime] << ' ';
                decomposition_of_B_numbers_with_mod[index_of_current_potential_B_number][current_index_prime]++;
                degree_decomposition_of_B_numbers[index_of_current_potential_B_number][current_index_prime]++;
                decomposition_of_B_numbers_with_mod[index_of_current_potential_B_number][current_index_prime] %= 2; // adding by mod 2
            }
            if (current_candidate == 1)
                break; // no sence to continue checking through factor base
        }
        if (current_candidate != 1) {
            std::cout << current_candidate << '\n';
            std::cout << candidates_to_B_numbers_array[index_of_current_potential_B_number] << " isn't B-number\n\n";
            array_of_B_numbers[index_of_current_potential_B_number] = 0; // flag, that not B-number will be deleted from array of B-numbers
            array_of_a_of_B_numbers[index_of_current_potential_B_number] = 0;
            decomposition_of_B_numbers_with_mod[index_of_current_potential_B_number][0] = -1; // flag, that not B-number will be deleted from array of decomposition
            degree_decomposition_of_B_numbers[index_of_current_potential_B_number][0] = -1;
            amount_of_false_detected_B_numbers++;
        }
        else { // current_candidate decomposed by multipliers by factor base
            array_of_B_numbers[index_of_current_potential_B_number] = candidates_to_B_numbers_array[index_of_current_potential_B_number]; // add to array of B-numbers
            array_of_a_of_B_numbers[index_of_current_potential_B_number] = array_of_a_to_candidates_in_B_numbers[index_of_current_potential_B_number];
            //temp_copy_array_of_a[index_of_current_potential_B_number] = copy_array_of_a[]
            std::cout << '\n' << candidates_to_B_numbers_array[index_of_current_potential_B_number] << " is B-number\n\n";
            amount_of_B_numbers++;
        }
    }
    std::cout << "\n\n";

    long long int new_size = amount_of_potential_B_numbers - amount_of_false_detected_B_numbers; // reshaping - delete rows that contain not B-numbers
    long long int** temp_decomposition_with_mod = new long long int* [new_size];
    long long int** temp_degree_decomposition = new long long int* [new_size];
    for (long long int row_index = 0; row_index < new_size; row_index++) {
        temp_decomposition_with_mod[row_index] = new long long int[size_of_factor_base] {0};
        temp_degree_decomposition[row_index] = new long long int[size_of_factor_base] {0};
    }
    for (long long int current_old_row_index = 0, current_new_row_index = 0; current_old_row_index < amount_of_potential_B_numbers; current_old_row_index++) {
        if (decomposition_of_B_numbers_with_mod[current_old_row_index][0] == -1)
            continue; // skip row where not B-numbers and the last one
        for (long long int current_collumn = 0; current_collumn < size_of_factor_base; current_collumn++) {
            temp_decomposition_with_mod[current_new_row_index][current_collumn] = decomposition_of_B_numbers_with_mod[current_old_row_index][current_collumn]; // copying old data
            temp_degree_decomposition[current_new_row_index][current_collumn] = degree_decomposition_of_B_numbers[current_old_row_index][current_collumn];
        }
        current_new_row_index++;
    }
    for (long long int current_old_row_index = 0; current_old_row_index < amount_of_potential_B_numbers; current_old_row_index++) { // old value of amount_of_B_numbers used
        delete[] decomposition_of_B_numbers_with_mod[current_old_row_index];
        delete[] degree_decomposition_of_B_numbers[current_old_row_index];
    }
    delete[] decomposition_of_B_numbers_with_mod; // clear old memory
    delete[] degree_decomposition_of_B_numbers;
    decomposition_of_B_numbers_with_mod = temp_decomposition_with_mod;
    degree_decomposition_of_B_numbers = temp_degree_decomposition;
    amount_of_B_numbers = new_size;

    long long int* temp_array_of_a_of_B_numbers = new long long int[amount_of_B_numbers];
    long long int* temp_array_of_B_numbers = new long long int[amount_of_B_numbers];
    for (long long int old_array_index = 0, new_array_index = 0; old_array_index < amount_of_potential_B_numbers; old_array_index++) {
        if (array_of_B_numbers[old_array_index] == 0)
            continue; // skip where not B-numbers  
        temp_array_of_B_numbers[new_array_index] = array_of_B_numbers[old_array_index];
        temp_array_of_a_of_B_numbers[new_array_index] = array_of_a_of_B_numbers[old_array_index];
        new_array_index++;
    }
    delete[] array_of_a_of_B_numbers;
    delete[] array_of_B_numbers; // clear old memory
    array_of_a_of_B_numbers = temp_array_of_a_of_B_numbers;
    array_of_B_numbers = temp_array_of_B_numbers;

    std::cout << "\nB-numbers is:\n";
    for (long long int index = 0; index < amount_of_B_numbers; index++)
        std::cout << array_of_B_numbers[index] << "\t\t" << (index) << " number\n";
    std::cout << "\n";
    

    std::cout << "Need to solve following system of equations by modulo 2:\n";
    for (long long int current_row = 0; current_row < amount_of_B_numbers; current_row++) {
        //std::cout << "Decomposition of " << array_of_B_numbers[current_row] << " on multipliers by factor base:\n";
        for (long long int current_collumn = 0; current_collumn < size_of_factor_base; current_collumn++)
            std::cout << decomposition_of_B_numbers_with_mod[current_row][current_collumn] << ' ';
        std::cout << '\n';
    }

    char* marks_of_row = new char[amount_of_B_numbers] {0};
    std::cout << "\n\n";
    for (long long int current_column = 0; current_column < size_of_factor_base; current_column++) {
        for (long long int current_row = 0; current_row < amount_of_B_numbers; current_row++) {
            if (decomposition_of_B_numbers_with_mod[current_row][current_column] == 1) {
                marks_of_row[current_row] = '*'; // mark row
                //long long int index_of_column_to_right_side = current_column + 1, index_of_column_to_left_side = current_column - 1;
                //    if (index_of_column_to_right_side < size_of_factor_base) {
                //        for (long long int column = index_of_column_to_right_side; column < size_of_factor_base; column++)
                //            if (decomposition_of_B_numbers[current_row][column] == 1)
                //                for (long long int row = current_row; row < amount_of_B_numbers; row++) {
                //                    decomposition_of_B_numbers[row][column] ^= decomposition_of_B_numbers[row][current_column]; // XOR values in highlighted segment of matrix
                //                }
                //       index_of_column_to_right_side = size_of_factor_base;
                //    }
                //    if (index_of_column_to_left_side >= 0) {
                //        for (long long int column = index_of_column_to_left_side; column >= 0; column--)
                //            if (decomposition_of_B_numbers[current_row][column] == 1)
                //                for (long long int row = current_row; row < amount_of_B_numbers; row++) {
                //                    decomposition_of_B_numbers[row][column] ^= decomposition_of_B_numbers[row][current_column];
                //                }
                //        index_of_column_to_left_side = -1;
                //    }                
                for (long long int column = 0; column < size_of_factor_base; column++)
                    if (column != current_column && decomposition_of_B_numbers_with_mod[current_row][column] == 1)
                        for (long long int row = current_row; row < amount_of_B_numbers; row++) 
                            decomposition_of_B_numbers_with_mod[row][column] ^= decomposition_of_B_numbers_with_mod[row][current_column];  // XOR values in highlighted segment of matrix             
                break; // column is considered only once
            }
        }
    }

   std::cout << "Reduced System of equations by modulo 2:\n";
   for (long long int current_row = 0; current_row < amount_of_B_numbers; current_row++) {
       //std::cout << "Decomposition of " << array_of_B_numbers[current_row] << " on multipliers by factor base:\n";
       for (long long int current_collumn = 0; current_collumn < size_of_factor_base; current_collumn++)
           std::cout << decomposition_of_B_numbers_with_mod[current_row][current_collumn] << ' ';
       std::cout << ' ' << marks_of_row[current_row] << '\t' << current_row << " line\n";
   }

   long long int** decomposition_to_solve = new long long int* [amount_of_B_numbers];
   for (long long int row_index = 0; row_index < new_size; row_index++)
       decomposition_to_solve[row_index] = new long long int[size_of_factor_base] {0};

   std::vector<long long int> vector_of_numbers_of_lines_that_can_use_as_possible_solution;
   std::cout << "\nFounding line, that can be used as solution...\n";
   long long int amount_of_rows_that_can_use_as_possible_solution = 0;
   for (long long int row_index = 0; row_index < amount_of_B_numbers; row_index++) {
       long long int amount_of_ones_in_row = 0;
       for (long long int current_collumn = 0; current_collumn < size_of_factor_base; current_collumn++)
           amount_of_ones_in_row += decomposition_of_B_numbers_with_mod[row_index][current_collumn];
       if (marks_of_row[row_index] != '*' || amount_of_ones_in_row == 0) {
           std::cout << row_index << " line:  ";
           for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
               std::cout << decomposition_of_B_numbers_with_mod[row_index][current_column] << ' ';
           std::cout << '\n';
           if (amount_of_ones_in_row == 0) { // save row, which contains only 0
               decomposition_to_solve[amount_of_rows_that_can_use_as_possible_solution][0] = -1; // all other cells are null by default (see definition of decomposition_to_solve)
           }
           else {
               for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
                   decomposition_to_solve[amount_of_rows_that_can_use_as_possible_solution][current_column] = decomposition_of_B_numbers_with_mod[row_index][current_column];
           }
           vector_of_numbers_of_lines_that_can_use_as_possible_solution.push_back(row_index);
           amount_of_rows_that_can_use_as_possible_solution++;
       }
       if ((row_index == amount_of_B_numbers - 1) && amount_of_rows_that_can_use_as_possible_solution == 0) {
           std::cout << "Cannot solve system of equations\n";
           //throw std::exception("No solutions, make sieving interval bigger");
           std::cout << "No solutions, make sieving interval bigger\n";
           return -1;
       }
   }

   if (amount_of_rows_that_can_use_as_possible_solution != 0) { // If solutions exist, try to find it
       long long int** decomposition_to_solve_temp = new long long int* [amount_of_rows_that_can_use_as_possible_solution]; // reshaping - delete rows that cannot use as solution  
       for (long long int row_index = 0; row_index < amount_of_rows_that_can_use_as_possible_solution; row_index++)
           decomposition_to_solve_temp[row_index] = new long long int[size_of_factor_base] {0};
       for (long long int current_old_row_index = 0, current_new_row_index = 0; current_old_row_index < amount_of_B_numbers; current_old_row_index++) {
           long long int amount_of_ones_in_row = 0;
           for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
               amount_of_ones_in_row += abs(decomposition_to_solve[current_old_row_index][current_column]);
           if (amount_of_ones_in_row == 0) // skip full empty lines
               continue;
           if (amount_of_ones_in_row == 1 && decomposition_to_solve[current_old_row_index][0] == -1) { // lines of nulls, which is solution
               decomposition_to_solve_temp[current_new_row_index][0] = 0;
               current_new_row_index++;
           }
           else { // if not linearly independent row, than save it
               for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
                   decomposition_to_solve_temp[current_new_row_index][current_column] = decomposition_to_solve[current_old_row_index][current_column]; // copying old data
               current_new_row_index++;
           }
       }
       for (long long int current_old_row_index = 0; current_old_row_index < amount_of_B_numbers; current_old_row_index++)
           delete[] decomposition_to_solve[current_old_row_index];
       delete[] decomposition_to_solve; // clear old memory
       decomposition_to_solve = decomposition_to_solve_temp;

       //std::cout << "\n\n";
       //for (long long int current_row = 0; current_row < amount_of_rows_that_can_use_as_possible_solution; current_row++) {
       //    for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
       //        std::cout << decomposition_to_solve[current_row][current_column] << ' ';
       //    std::cout << '\t' << vector_of_numbers_of_lines_that_can_use_as_possible_solution[current_row] << " line\n";
       //}
       
       for (long long int current_possible_solution = 0; current_possible_solution < amount_of_rows_that_can_use_as_possible_solution; current_possible_solution++) {
           long long int amount_of_ones_in_row = 0; 
           for (long long int current_column = 0; current_column < size_of_factor_base; current_column++)
               amount_of_ones_in_row += decomposition_to_solve[current_possible_solution][current_column];
           if (amount_of_ones_in_row == 0) { // decide, which variant we have simple(all nulls) or not
               long long int row_index = vector_of_numbers_of_lines_that_can_use_as_possible_solution[current_possible_solution];
               
               unsigned long long int result_x = 1;
               for (long long int factor_base_index = 0; factor_base_index < size_of_factor_base; factor_base_index++) {
                   if (degree_decomposition_of_B_numbers[row_index][factor_base_index] != 0) {
                       result_x *= array_of_a_of_B_numbers[row_index];
                       result_x = result_x % number_to_factorise_n;
                   }
               }
               std::cout << '\n' << "X: " << result_x << '\n';
               unsigned long long int result_y = 1;
               for (long long int factor_base_index = 0; factor_base_index < size_of_factor_base; factor_base_index++) {
                   unsigned long long int degree = 0;
                   degree += degree_decomposition_of_B_numbers[row_index][factor_base_index];
                   result_y = (result_y * int_number_to_int_degree(factor_base_in_array[factor_base_index], degree / 2)) % number_to_factorise_n;
               }
               std::cout << '\n' << "Y: " << result_y << '\n';

               long long int inverse_y = ((-1) * result_y + number_to_factorise_n);
               if (result_x == result_y || result_x == inverse_y) {
                       std::cout << "\nX = +- Y mod n, trivial solution. Try other possible solution.\n";
                       continue;
               }
               long long int first_multiplier = ((result_x - result_y < 0) ? (result_x - result_y + number_to_factorise_n) : (result_x - result_y));
               long long int second_multiplier = ((result_x + result_y > number_to_factorise_n) ? ((result_x + result_y) % number_to_factorise_n) : (result_x + result_y));
               first_multiplier = greater_common_divisor(first_multiplier, number_to_factorise_n);
               second_multiplier = greater_common_divisor(second_multiplier, number_to_factorise_n);
               std::cout << first_multiplier << ' ' << second_multiplier << '\n';
               //Pair_of_elements <long long int, long long int> result(first_multiplier, second_multiplier);
               //return result;
               if (first_multiplier != 1 || second_multiplier != 1)
                    return (first_multiplier > second_multiplier ? first_multiplier : second_multiplier);
           }
           else {
               std::vector<long long int> vectors_positions_of_terms_for_current_solution;
               long long int current_row = 0;
               while (current_row < amount_of_B_numbers) {
                   if (marks_of_row[current_row] == '*') { // marked with '*' lines, contains only one unit in line
                       std::vector<long long int>::iterator iterator_if_present = std::find(vector_of_numbers_of_lines_that_can_use_as_possible_solution.begin(), vector_of_numbers_of_lines_that_can_use_as_possible_solution.end(), current_row);
                       if (iterator_if_present != vector_of_numbers_of_lines_that_can_use_as_possible_solution.end()) { // check, if is one of depended row (or row, that currently in use)
                           current_row++;
                           continue; // skip linery depend lines
                       }
                       for (long long int current_column = 0; current_column < size_of_factor_base; current_column++) {
                           if (decomposition_to_solve[current_possible_solution][current_column] && decomposition_of_B_numbers_with_mod[current_row][current_column]) { // only than, 
                               vectors_positions_of_terms_for_current_solution.push_back(current_row);
                               break;
                           }
                       }
                   }
                   current_row++;
               }

               unsigned long long int result_x = 1;
               for (long long int index_of_used_row : vectors_positions_of_terms_for_current_solution) {
                   result_x *= array_of_a_of_B_numbers[index_of_used_row];
                   result_x %= number_to_factorise_n;
               }
               result_x *= array_of_a_of_B_numbers[vector_of_numbers_of_lines_that_can_use_as_possible_solution[current_possible_solution]];
               result_x %= number_to_factorise_n;
               std::cout << '\n' << "X: " << result_x << '\n';

               unsigned long long int result_y = 1;
               for (long long int factor_base_index = 0; factor_base_index < size_of_factor_base; factor_base_index++) {
                   unsigned long long int degree = 0;
                   for (long long int index_of_used_row : vectors_positions_of_terms_for_current_solution)
                       degree += degree_decomposition_of_B_numbers[index_of_used_row][factor_base_index];
                   degree += degree_decomposition_of_B_numbers[vector_of_numbers_of_lines_that_can_use_as_possible_solution[current_possible_solution]][factor_base_index];
                   //std::cout << factor_base_in_array[factor_base_index] << ' ' <<  degree << '\n';
                   if (factor_base_in_array[factor_base_index] == -1)
                       continue; // as multiplier doesn't influence, so skip
                   result_y = (result_y * int_number_to_int_degree(factor_base_in_array[factor_base_index], degree / 2)) % number_to_factorise_n;
               }
               std::cout << '\n' << "Y: " << result_y << '\n';

               long long int inverse_y = ((-1) * result_y + number_to_factorise_n);
               if (result_x == result_y || result_x == inverse_y) {
                   std::cout << "\nX = +- Y mod n, trivial solution. Try other possible solution.\n";
                   continue;
               }

               long long int first_multiplier = ((result_x - result_y < 0) ? (result_x - result_y + number_to_factorise_n) : (result_x - result_y));
               long long int second_multiplier = ((result_x + result_y > number_to_factorise_n) ? ((result_x + result_y) % number_to_factorise_n) : (result_x + result_y));
               first_multiplier = greater_common_divisor(first_multiplier, number_to_factorise_n);
               second_multiplier = greater_common_divisor(second_multiplier, number_to_factorise_n);
               std::cout << first_multiplier << ' ' << second_multiplier << '\n';
               //Pair_of_elements <long long int, long long int> result(first_multiplier, second_multiplier);
               //return result;
               if (first_multiplier != 1 || second_multiplier != 1)
                   return (first_multiplier > second_multiplier ? first_multiplier : second_multiplier);
           }
       }
   }
   else { // amount_of_rows_that_can_use_as_possible_solution == 0
       std::cout << "There are no solutions exists\n";
       return -1;
   }
   return -1;
}

Pair_of_elements<long long int*, long long int> formatting_factor_base(long long int number_n) {
    long long int upper_bound_of_base = (long long int)(pow(exp(pow(log(number_n) * log(log(number_n)), 0.5)), (1 / sqrt(2)))); // (exp{ [ln(x) * ln(ln(x))] ^ 1/2} ) ^ \{alpha}, where \{alpha} = 1 / sqrt(2)
    Pair_of_elements<long long int*, long long int> data_about_prime_numbers = Sieve_of_Eratosthenes(upper_bound_of_base); 
    //long long int size_of_factor_base = 31; // (-1) + 30 primes, let's try so
    //long long int* factor_base_in_array = new long long int[size_of_factor_base]; 
    //factor_base_in_array[0] = -1; // -1 always need to be
    //for (long long int factor_base_index = 1, data_prime_index = 0; (factor_base_index < size_of_factor_base) && (data_prime_index < data_about_prime_numbers.variable_two); data_prime_index++)
    //    if (legendre_symbol(number_n, data_about_prime_numbers.variable_one[data_prime_index]) == 1) {
    //        factor_base_in_array[factor_base_index] = data_about_prime_numbers.variable_one[data_prime_index];
    //        factor_base_index++;
    //    }
    std::vector<long long int> factor_base_in_vector;
    factor_base_in_vector.push_back(-1); // -1 always need to be
    for (long long int data_prime_index = 0; data_prime_index < data_about_prime_numbers.variable_two; data_prime_index++)
        if (legendre_symbol(number_n, data_about_prime_numbers.variable_one[data_prime_index]) == 1)
            factor_base_in_vector.push_back(data_about_prime_numbers.variable_one[data_prime_index]);
    long long int size_of_factor_base = factor_base_in_vector.size();
    long long int* factor_base_in_array = new long long int[size_of_factor_base]; 
    for (long long int current_index = 0; current_index < size_of_factor_base; current_index++)
        factor_base_in_array[current_index] = factor_base_in_vector[current_index];
    Pair_of_elements<long long int*, long long int> factor_base_data(factor_base_in_array, size_of_factor_base);
    return factor_base_data;
}

long long int iterative_binary_search(long long int* array_of_numbers, long long int size_of_array, long long int number_to_search) {
    long long low_bound = 0, high_bound = size_of_array;
    while (low_bound <= high_bound) {
        long long int middle = low_bound + (high_bound - low_bound) / 2;
        if (array_of_numbers[middle] == number_to_search)
            return middle;
        if (array_of_numbers[middle] < number_to_search)
            low_bound = middle + 1;
        else
            high_bound = middle - 1;
    }
    return -1; // element is not in array
}

Pair_of_elements<long long int, long long int> squaring_root_per_prime_modulo_p(long long int number_a, long long int prime_number_p) { // number_a > 0
        if (legendre_symbol(number_a, prime_number_p) == 1) {  
            if (prime_number_p == 2) { // (1/2) = 1
                Pair_of_elements<long long int, long long int> result(-1, 1); // just one solution
                return result;
            } 
            if (prime_number_p == 3) { // (1/3) = 1
                    Pair_of_elements<long long int, long long int> result(-1, 1); // case only for 1, cause (2/3) = -1
                    return result;
            }
            if (prime_number_p == 5) {
                if (number_a == 1) { // (1/5) = 1
                    Pair_of_elements<long long int, long long int> result(-1, 1); 
                    return result;
                } 
                else { // (4/5) = 1
                    Pair_of_elements<long long int, long long int> result(-2, 2); 
                    return result;
                } // only this 2 cases, beacause (2/5) = -1, and (3/5) = -1
            }
            if (number_a == 1) {
                Pair_of_elements<long long int, long long int> result(-1, 1); 
                return result;
            }
            if ((prime_number_p - 3) % 4 == 0) {// p = 4k + 3
                long long int k = (prime_number_p - 3) / 4;
                long long int result_x = Barret_Gorner(number_a, prime_number_p, 10, return_number_in_binary_numeral_system((k + 1))); // x = +- a ^ (k + 1) mod p
                long long int result_x2 = (result_x < 0 ? (-result_x + prime_number_p) : (result_x - prime_number_p));
                // ??
                Pair_of_elements<long long int, long long int> result(result_x, result_x2);
                return result;
            }
            else if ((prime_number_p - 5) % 8 == 0) { // p = 8k + 5
                long long int k = (prime_number_p - 5) / 8;
                long long int result_x = Barret_Gorner(number_a, prime_number_p, 10, return_number_in_binary_numeral_system((k + 1))); // a^(k + 1)
                if (legendre_symbol(number_a, prime_number_p) == -1)
                    result_x = (result_x * Barret_Gorner(2, prime_number_p, 10, return_number_in_binary_numeral_system((2 * k + 1)))) % prime_number_p; // x = +- a^(k + 1) * 2^(2k + 1)  mod p
               
                long long int result_x2 = (result_x < 0 ? (-result_x + prime_number_p) : (result_x - prime_number_p) );
                Pair_of_elements<long long int, long long int> result(result_x, result_x2);
                return result;
            }
            else if ((prime_number_p - 1) % 8 == 0) { // p = 8k + 1
                Pair_of_elements<long long int, long long int> result = Tonelli_Shanks_algorithm(number_a, prime_number_p);
                return result;
            }
        }
        else {
            std::cout << "\nError!\n" << number_a << " isn't quadratic residues to " << prime_number_p << '\n';
            return { 0, 0};
        }
}

Pair_of_elements <long long int, long long int> Tonelli_Shanks_algorithm(long long int number_a, long long int prime_number_p) {
    long long int number_d = (prime_number_p - 1); // h ttps://www.youtube.com/watch?v=C8QGzkKqvUQ
    long long int s_power_of_two = 0;
    while (number_d % 2 == 0) {
        number_d = number_d >> 1; // divide by 2
        s_power_of_two++;
    } // a^(2^s * d) == 1 mod p
    long long int not_quadratic_residues_b = 0;
    for (long long int numerator = 1; numerator < prime_number_p; numerator++) { // better randomly choose it
        if (legendre_symbol(numerator, prime_number_p) == -1) {
            not_quadratic_residues_b = numerator;
            break;
        }
    }
    long long int number_z = Barret_Gorner(not_quadratic_residues_b, prime_number_p, 10, return_number_in_binary_numeral_system(number_d)); // ord z = 2^s
    long long int number_r = s_power_of_two;
    long long int result_x = Barret_Gorner(number_a, prime_number_p, 10, return_number_in_binary_numeral_system((number_d + 1) / 2));
    long long int w = Barret_Gorner(number_a, prime_number_p, 10, return_number_in_binary_numeral_system((number_d))); // ord w | 2^(s - 1)
    while (w % prime_number_p != 1) {
        long long int m = 0;
        for (long long int degree = 1; ; degree++)
            if (int_number_to_int_degree_with_mod(w, int_number_to_int_degree(2, degree), prime_number_p) == 1) { // w^(2^m) = 1 mod p <=> ord w = 2^m
                m = degree;
                break;
            }
        number_z = int_number_to_int_degree_with_mod(number_z, int_number_to_int_degree(2, number_r - m - 1), prime_number_p); // z = z^(2^(r - m - 1))
        result_x = (result_x * number_z) % prime_number_p;
        number_z = int_number_to_int_degree_with_mod(number_z, 2, prime_number_p); //to rhis x^2 still equal to w * a 
        w = (w * number_z) % prime_number_p; // ord z = 2^(r - (r - m)) = 2^m   
        number_r = m; // -> ord w | 2^(m - 1)
    }
    long long int result_x2 = (result_x < 0 ? (result_x + prime_number_p) : (result_x - prime_number_p));
    Pair_of_elements <long long int, long long int> result(result_x, result_x2);
    return result;
}

//std::vector<long long int> vector_of_q_from_Euclidean_algorithm(long long int number_one, long long int number_two) {
//    std::vector<long long int> vector_of_q;
//    if (number_one == 1 || number_two == 1) {
//        if (number_one == 1 && number_two == 1) {
//            vector_of_q.push_back(1);
//            return vector_of_q;
//        }
//        if (number_one == 1 && number_two != 1) {
//            vector_of_q.push_back(number_two);
//            return vector_of_q;
//        }
//        if (number_two == 1 && number_one != 1) {
//            vector_of_q.push_back(number_one);
//            return vector_of_q;
//        }
//    }
//    if (number_one == 0 || number_two == 0) {
//        vector_of_q.push_back(0);
//        return vector_of_q;
//    }
//    long long int temp;
//    if (number_one < number_two) {
//        auto temp_temp = number_one;
//        number_one = number_two;
//        number_two = temp_temp;
//    }
//    while (number_two != 0) {
//        //std::cout << "number_one " << number_one << "\nnumber_two " << number_two << '\n';
//        temp = number_one % number_two;
//        //std::cout << "Temp = " << temp << '\n';
//        //std::cout << "push_back  = " << (number_one / number_two) << '\n';
//        vector_of_q.push_back((number_one / number_two));
//        number_one = number_two;
//        number_two = temp;
//        //std::cout << "number_one " << number_one << "\nnumber_two " << number_two << '\n';
//    }
//    vector_of_q.pop_back(); // remove the last quotient, at which remainder == 0. For ex. : 3 = 3 * 1 + 0, (a = q * b + r)
//    return vector_of_q;
//}
//
//long long int reverse_element_using_Euclidean_algorithm(std::vector<long long int> given_vector_of_q, long long int number_to_reverse, long long int mod_number) {
//    if (greater_common_divisor(number_to_reverse, mod_number) == 1) {
//        long long int start_null = 0, start_one = 1;
//        std::vector<long long int> vector_of_q = given_vector_of_q;
//        long long int reverse = 1;
//        if (number_to_reverse == 1 || mod_number == 1) {
//            if (mod_number == 1) // Process both variants: (number, mod == 1) or (mod == 1)
//                return 0;
//            if (number_to_reverse == 1)
//                return 1;
//        }
//        for (auto quotient : vector_of_q) {
//            reverse = (-1) * quotient * start_one + start_null;
//            start_null = start_one;
//            start_one = reverse;
//        }
//        while (reverse < 0)
//            reverse += mod_number;
//        return reverse;
//    }
//    else {
//        std::cout << "\nCannot find reverse element.\nGCD of number_to_reverse " << number_to_reverse << " and mod_number " << mod_number << " isn't equal to 1\n";
//        return 0;
//    }
//}

double MeasureTime(std::function<void()> operation, unsigned int amount_of_measurements) {
    double* time_for_all_tryes = new double[amount_of_measurements + 1]{};
    int current_measurement = 0;
    while (current_measurement < amount_of_measurements) {
        auto start_time = std::chrono::high_resolution_clock::now();
        operation();  // Executing operation
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;
        time_for_all_tryes[current_measurement] = elapsed_time.count();
        std::cout << time_for_all_tryes[current_measurement] << '\n';
        time_for_all_tryes[amount_of_measurements] += time_for_all_tryes[current_measurement];
        current_measurement++;
        std::cout << "Total:\t" << time_for_all_tryes[amount_of_measurements] << '\n';
    }
    double average_time = (time_for_all_tryes[amount_of_measurements] / amount_of_measurements);
    delete[] time_for_all_tryes;
    return average_time;
}