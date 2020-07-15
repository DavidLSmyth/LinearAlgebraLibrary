#pragma comment(lib,"LinearAlgebraLibrary.lib")
#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix.cpp"
#include "MatrixFunctions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MatrixNamespace;

namespace LinearAlgebraLibraryTests
{
	TEST_CLASS(LinearAlgebraLibraryTests)
	{
	public:

		
		
		TEST_METHOD(TestPLUFactorisation)
		{
			//for test case 1
			
			const float* mat_1_elements;

			const float* l_mat_1_elements;

			const float* u_mat_1_elements;

			const float* p_mat_1_elements;

			mat_1_elements = new float[4]{ 1,2,3,8 };
			l_mat_1_elements = new float[4]{ 1,0, 1 / 3.0,1 };
			u_mat_1_elements = new float[4]{ 3,8,0, -2 / 3.0 };
			p_mat_1_elements = new float[4]{ 0,1,1,0 };

			Matrix<float> mat_1(2, 2, *mat_1_elements);
			Matrix<float> l_mat_1(2, 2, *l_mat_1_elements);
			Matrix<float> p_mat_1(2, 2, *p_mat_1_elements);
			Matrix<float> u_mat_1(2, 2, *u_mat_1_elements);

			MatrixFns::PLUFactorisation<float> factorisation = MatrixFns::MatrixFunctions::getPLUFactors(mat_1, 0.00001);
			
			Assert::IsTrue(factorisation.P == p_mat_1);
			Assert::IsTrue(factorisation.U == u_mat_1);
			Assert::IsTrue(factorisation.L == l_mat_1);

			mat_1_elements = new float[9]{ 0,1,0, -8,8,1, 2,-2,0 };
			l_mat_1_elements = new float[9]{ 1,0,0, 0,1,0, -1/4.0,0,1 };
			u_mat_1_elements = new float[9]{ -8,8,1, 0,1,0, 0,0,1/4.0};
			p_mat_1_elements = new float[9]{0,1,0, 1,0,0, 0,0,1 };

			mat_1 = Matrix<float>(3, 3, *mat_1_elements);
			l_mat_1 = Matrix<float>(3, 3, *l_mat_1_elements);
			p_mat_1 = Matrix<float>(3, 3, *p_mat_1_elements);
			u_mat_1 = Matrix<float>(3, 3, *u_mat_1_elements);

			factorisation = MatrixFns::MatrixFunctions::getPLUFactors(mat_1, 0.00001);

			Assert::IsTrue(factorisation.P == p_mat_1);
			Assert::IsTrue(factorisation.U == u_mat_1);
			Assert::IsTrue(factorisation.L == l_mat_1);
			Assert::IsTrue(factorisation.P * factorisation.L * factorisation.U == mat_1);
		}


	};

}