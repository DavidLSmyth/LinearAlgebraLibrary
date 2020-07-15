// LinearAlgebraRunner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../LinearAlgebraLibrary/Matrix.cpp"
#include "../LinearAlgebraLibrary/MatrixFunctions.cpp"
//using namespace MatrixNamespace;
int main()
{
	
	//const float elements[9] = { 1,1,1,1,2,2,1,2,3 };
	//Matrix<float> mat_1 = Matrix<float>(3,3,*elements);
	const float elements[9] = { 0,1,0, -8,8,1, 2,-2,0};
	Matrix<float> mat_1 = Matrix<float>(3,3, *elements);
	mat_1.print_matrix();
	std::cout << std::endl;
	/*
	const float elements1[9] = { 1,0,0,-1,1,0,-1,0,1 };
	Matrix<float> mat_2 = Matrix<float>(3, 3, *elements1);
	Matrix<float> mat_3 = Matrix<float>(3,3);
	mat_3 = (mat_2 * mat_1);
	//const float elements1[9] = { 1,0,0,-1,1,0,-1,0,1 };
	//Matrix<float> mat_2 = Matrix<float>(3, 3, *elements);
	mat_3.print_matrix();
	*/

	MatrixFns::PLUFactorisation<float> factorisation = MatrixFns::MatrixFunctions::getPLUFactors(mat_1, 0.00001);
	std::cout << "Factorisation results: "<< std::endl;
	std::cout << "P: " << std::endl;
	factorisation.P.print_matrix();
	std::cout << "L: " << std::endl;
	factorisation.L.print_matrix();
	std::cout << "U: " << std::endl;
	factorisation.U.print_matrix();
	Matrix<float> res = factorisation.P * factorisation.L * factorisation.U;
	std::cout << "Result: " << std::endl;
	res.print_matrix();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
