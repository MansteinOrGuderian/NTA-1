#include "Header.h"


int main() {
	long long int number_to_factorise_n = 323324583518541583; // 10001111100101011011111111011100011110001100001011100001111

	//std::cout << "1-step: Checking if number is prime:\n";
	//if (primality_Miller_Rabin_test(number_to_factorise_n, 100) == 1) 	//primality_Solovay_Strassen_test(323324583518541583, 100);
	//	std::cout << "Number is maybe prime\n";
	//else
	//	std::cout << "Number is composite\n";
	//std::cout << "2-step: Bruteforce:\n"; // add case for (-1) - not divide
	//long long int bruteforce_factorization_result = bruteforce_factorization(number_to_factorise_n);
	//std::cout << bruteforce_factorization_result << '\n';
	//number_to_factorise_n /= bruteforce_factorization_result;
	//std::cout << "3-step: rho-Pollard:\n";
	//long long int ro_pollard_factorization_result = rho_pollard_factorization(number_to_factorise_n);
	//std::cout << ro_pollard_factorization_result << '\n';
	//number_to_factorise_n /= ro_pollard_factorization_result;  // 9893350372343 = 236723 * 41792942

	//number_to_factorise_n = 9893350372343;
	//std::cout << "4-step: Quadratic sieve algorithm\n";
	//std::cout << quadratic_sieve_algorithm(number_to_factorise_n) << '\n';
	
	//std::cout << quadratic_sieve_algorithm(9893350372343);
	/*int a = 5, b = a;
	std::cout << a << ' ' << b;*/

	std::set<int> a{8, 2, 4 , 1};
	std::cout << *a.begin() << ' ' << (*a.begin() + 1);
}

