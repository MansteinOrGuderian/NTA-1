#include "Header.h"


int main() {
	long long int number_to_factorise_n = 323324583518541583; // 10001111100101011011111111011100011110001100001011100001111

	std::cout << "1-step: Checking if number is prime:\n";
	if (primality_Miller_Rabin_test(number_to_factorise_n, 100) == 1) 	//std::cout << primality_Solovay_Strassen_test(323324583518541583, 100);
		std::cout << "Number is maybe prime\n";
	else
		std::cout << "Number is composite\n";
	std::cout << "2-step: Bruteforce:\n";


	std::cout << "3-step: rho-Pollard:\n";
	long long int ro_pollard_factorization_result = rho_pollard_factorization(number_to_factorise_n);
	std::cout << ro_pollard_factorization_result << '\n';
	number_to_factorise_n /= ro_pollard_factorization_result;
}

