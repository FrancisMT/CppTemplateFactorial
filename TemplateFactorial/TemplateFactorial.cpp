#include <iostream>

#define MAXNUM 10

template<unsigned int N>
class Factorial {
public:
	enum {
		Value = N * Factorial<N - 1>::Value
	};
};

template <>
class Factorial<0> {
public:
	enum {
		Value = 1
	};
};

int main() {

	// Number mus be known at compile time.
	auto FactorialResult_A = Factorial<3>::Value;
	auto FactorialResult_B = Factorial<4>::Value;
	auto FactorialResult_C = Factorial<5>::Value;

	std::cout
		<< "Factorial for 3: " << FactorialResult_A << "\n"
		<< "Factorial for 4: " << FactorialResult_B << "\n"
		<< "Factorial for 5: " << FactorialResult_C << "\n";
	getchar();
}