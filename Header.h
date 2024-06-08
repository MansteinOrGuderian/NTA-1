#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib> 

long long int int_number_to_int_degree(long long int number, long long int power);

long long int greater_common_divisor(long long int number_one, long long int number_two);

long long int return_countDigit_in_number(long long int number_to_found_digits);
std::vector<long long int> from_decimal_number_to_new_numeral_scale_of_notation(long long int old_decimal_number, long long int new_scale);
std::vector<long long int> return_number_in_binary_numeral_system(unsigned long long int decimal_number);
long long int clear_Gorner(long long int X_base_to_power, std::vector<long long int> e_binary_power);
long long int clear_Barret(long long int x_number, long long int n_mod_number, long long int base_scale);
long long int Barret_Gorner(long long int X_base_to_power, long long int n_mod_number, long long int base_scale, std::vector<long long int> e_binary_power);
const char array_to_work_with_16_scale_notation[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

long long int legendre_symbol(long long int numerator_a, long long int denominator_p);
bool if_pseudo_prime_number_by_Euler(long long int odd_number_p, long long int base_number);
bool primality_Solovay_Strassen_test(long long int number_to_test, long long int amount_of_iterations);
bool primality_Miller_Rabin_test(long long int number_to_test, long long int amount_of_iterations);

long long int rho_pollard_factorization(long long n_mod_number);

template <typename First_type, typename Second_type>
struct Pair_of_elements {
    First_type variable_one;
    Second_type variable_two;
    Pair_of_elements() : variable_one{}, variable_two{} {}
    Pair_of_elements(First_type object_first, Second_type object_second) : variable_one(object_first), variable_two(object_second) {}
    friend std::ostream& operator<<(std::ostream& out, const Pair_of_elements& Object_Data) {
        out << '\n' << Object_Data.variable_one << ' ' << Object_Data.variable_two << '\n';
        return out;
    }
};

Pair_of_elements<long long int*, long long int> Sieve_of_Eratosthenes(long long int number_to_which_count_primes);
long long int* return_number_as_array_of_its_digit(long long int number);
long long int bruteforce_factorization(long long int n_mod_number);
long long int quadratic_sieve_algorithm(long long int number_to_factorise_n);
Pair_of_elements<long long int*, long long int> formatting_factor_base(long long int number_n);
long long int int_number_to_int_degree_with_mod(long long int number, long long int power, long long int modulo);
long long int iterative_binary_search(long long int* array_of_numbers, long long int size_of_array, long long int number_to_search);