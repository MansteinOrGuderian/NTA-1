#include "Header.h"

bool is_number_prime(long long int number) {
    if (number <= 1)
        return false;
    if (number == 2 || number == 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    for (long long int i = 5; i <= sqrt(number); i = i + 6)
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    return true;
}


int main() {
	//long long int number_to_factorise_n = 323324583518541583; // 10001111100101011011111111011100011110001100001011100001111

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
	
	std::cout << quadratic_sieve_algorithm(9893350372343);

	//long long int* array_of_bees = new long long int[101] {-318760582, -312469943, -306179302, -299888659, -293598014, -287307367, -281016718, -274726067, -268435414, -262144759, -255854102, -249563443, -243272782, -236982119, -230691454, -224400787, -218110118, -211819447, -205528774, -199238099, -192947422, -186656743, -180366062, -174075379, -167784694, -161494007, -155203318, -148912627, -142621934, -136331239, -130040542, -123749843, -117459142, -111168439, -104877734, -98587027, -92296318, -86005607, -79714894, -73424179, -67133462, -60842743, -54552022, -48261299, -41970574, -35679847, -29389118, -23098387, -16807654, -10516919, -4226182, 2064557, 8355298, 14646041, 20936786, 27227533, 33518282, 39809033, 46099786, 52390541, 58681298, 64972057, 71262818, 77553581, 83844346, 90135113, 96425882, 102716653, 109007426, 115298201, 121588978, 127879757, 134170538, 140461321, 146752106, 153042893, 159333682, 165624473, 171915266, 178206061, 184496858, 190787657, 197078458, 203369261, 209660066, 215950873, 222241682, 228532493, 234823306, 241114121, 247404938, 253695757, 259986578, 266277401, 272568226, 278859053, 285149882, 291440713, 297731546, 304022381, 310313218};
	//for (long long int i = 0, step = -50; i < 101; i++) {
	//	long long int current_number = (array_of_bees[i] < 0) ? (-array_of_bees[i]) : array_of_bees[i];
	//	std::cout << (step + i) << " step.  Current number is: " << current_number << '\n' << "It's divisor is: \t";
	//	if (array_of_bees[i] < 0)
	//		std::cout << -1 << " * ";
	//	long long int bound_to_search = (long long int)(sqrt(current_number));
	//	for (long long int current_divisor = 1; current_divisor <= bound_to_search; current_divisor++) {
	//		if (is_number_prime(current_divisor)) {
	//			if (current_number % current_divisor == 0) {
	//				std::cout << current_divisor << " * ";
	//				current_number /= current_divisor;
	//				while (current_number % current_divisor == 0) {
	//					std::cout << current_divisor << " * ";
	//					current_number /= current_divisor;
	//				}
	//				//bound_to_search = (long long int)(sqrt(current_number));
	//			}
	//		}
	//		if (current_divisor == bound_to_search) {
	//			if (is_number_prime(current_number))
	//				std::cout << current_number << " * ";
	//			else
	//				std::cout << "Err!";
	//		}
	//	}
	//	std::cout << '\n';
	//}

	std::cout << "\n\n";
}

