#include "Header.h"


int main() {
	long long int number_to_factorise_n = 323324583518541583; // 10001111100101011011111111011100011110001100001011100001111

	srand(time(0));
	//for (int i = 0; i < 19; i++)
	//	std::cout << (rand() % (200 - 7 + 1)) << " ";
	std::cout << primality_Solovay_Strassen_test(323324583518541583, 79);
}