#include<iostream>
#include<functional>
#include<ctime>

const unsigned int MAXVALUE = 32;

namespace FactorialGenerator
{
	// Method A for run-time number generation
	constexpr unsigned int Factorial_RunTime_Recursive(unsigned int Num) {
		return !!Num ? Num * Factorial_RunTime_Recursive(Num - 1) : 1;
	}

	// Method B for run-time number generation
	unsigned int Factorial_RunTime_Non_Recursive(unsigned int Num) {

		auto FactorialLambda = [](unsigned int Num)-> unsigned int {

			unsigned int CurrNum = 1;

			for (unsigned int FactNum = 1; FactNum <= Num; ++FactNum) {
				CurrNum *= FactNum;
			}

			return CurrNum;
		};

		return !!Num ? FactorialLambda(Num) : 1;
	}

	// Method A for compile-time factorial generation
	template<unsigned int N>
	class Factorial_CompileTime_Recursive_A {
	public:
		enum {
			Value = N * (unsigned)Factorial_CompileTime_Recursive_A<N - 1>::Value // cast to unsigned to supress error C4308
		};
	};

	template <>
	class Factorial_CompileTime_Recursive_A<1> {
	public:
		enum {
			Value = 1
		};
	};

	template <>
	class Factorial_CompileTime_Recursive_A<0> {
	public:
		enum {
			Value = 1
		};
	};

	// Method B for compile-time factorial generation
	template<unsigned int N>
	struct Factorial_CompileTime_Recursive_B: std::integral_constant<unsigned int, (N*Factorial_CompileTime_Recursive_B<N - 1>{}) > {};

	template<>
	struct Factorial_CompileTime_Recursive_B<0>: std::integral_constant<unsigned int, 1> {};
}

int main() {

	clock_t
		Clk_Begin,
		Clk_End;

	unsigned int FactorialNumber = 0;
	double FactNumCalc_ElapsedTime = 0.f;


	// Compile-Time Method A
	{
		Clk_Begin = clock();

		FactorialNumber = FactorialGenerator::Factorial_CompileTime_Recursive_A<MAXVALUE>::Value;

		Clk_End = clock();
	}

	FactNumCalc_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Compile time recursive factorial generator A for number " << MAXVALUE << " is " << FactorialNumber << "\n Time: " << FactNumCalc_ElapsedTime << " seconds" << "\n";

	// Compile-Time Method B
	{
		Clk_Begin = clock();

		FactorialNumber = FactorialGenerator::Factorial_CompileTime_Recursive_B<MAXVALUE>();

		Clk_End = clock();
	}

	FactNumCalc_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Compile time recursive factorial generator B for number " << MAXVALUE << " is " << FactorialNumber << "\n Time: " << FactNumCalc_ElapsedTime << " seconds" << "\n";

	// Run-Time Non-Recursive Method
	{
		Clk_Begin = clock();

		FactorialNumber = FactorialGenerator::Factorial_RunTime_Non_Recursive(MAXVALUE);

		Clk_End = clock();
	}

	FactNumCalc_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Run-time non-recursive factorial generator for number " << MAXVALUE << " is " << FactorialNumber << "\n Time: " << FactNumCalc_ElapsedTime << " seconds" << "\n";

	// Run-Time Recursive Method
	{
		Clk_Begin = clock();

		FactorialNumber = FactorialGenerator::Factorial_RunTime_Recursive(MAXVALUE);

		Clk_End = clock();
	}

	FactNumCalc_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Run-time recursive factorial generator for number " << MAXVALUE << " is " << FactorialNumber << "\n Time: " << FactNumCalc_ElapsedTime << " seconds" << "\n";

	getchar();
	return 0;
}