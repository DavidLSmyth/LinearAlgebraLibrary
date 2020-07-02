#pragma comment(lib,"LinearAlgebraLibrary.lib")
#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MatrixNamespace;

namespace LinearAlgebraLibraryTests
{
	TEST_CLASS(LinearAlgebraLibraryTests)
	{
	public:
		TEST_METHOD(TestStandardConstructor)
		{
			MatrixNamespace::Matrix<int> mat_1 = MatrixNamespace::Matrix<int>(2, 2);
			Assert::AreEqual(2, mat_1.get_dimensions()[0]);
			Assert::AreEqual(2, mat_1.get_dimensions()[1]);
			mat_1.set_element(0, 0, 0);
			Assert::AreEqual(0, mat_1.get_element(0, 0));
		}
		TEST_METHOD(TestArrayConstructor)
		{
			int element_array[] = { 10,20,30,40 };
			Matrix<int> mat_1 = Matrix<int>(2, 2, *element_array);
			Assert::AreEqual(2, mat_1.get_dimensions()[0]);
			Assert::AreEqual(2, mat_1.get_dimensions()[1]);
			//mat_1.set_element(0, 0, 0);
			Assert::AreEqual(10, mat_1.get_element(0, 0));
			Assert::AreEqual(20, mat_1.get_element(0, 1));
			Assert::AreEqual(30, mat_1.get_element(1, 0));
		}


		TEST_METHOD(TestCopyConstructor)
		{
			// TODO: Your test code here
			Matrix<int> mat_1 = Matrix<int>(2, 2);
			for (int row_counter = 0; row_counter < mat_1.get_dimensions()[0]; row_counter++) {
				for (int col_counter = 0; col_counter < mat_1.get_dimensions()[1]; col_counter++) {
					mat_1.set_element(row_counter, col_counter, 2);
				}
			}
			Matrix<int> mat_2 = mat_1;
			Assert::AreEqual(2, mat_2.get_element(0, 0));
			Assert::AreEqual(2, mat_2.get_element(0, 1));
			Assert::AreEqual(2, mat_2.get_element(1, 0));
			Assert::AreEqual(2, mat_2.get_element(1, 1));
		}

		TEST_METHOD(TestAssignmentOverload)
		{
			// TODO: Your test code here
			Matrix<int> mat_1 = Matrix<int>(2, 2);
			for (int row_counter = 0; row_counter < mat_1.get_dimensions()[0]; row_counter++) {
				for (int col_counter = 0; col_counter < mat_1.get_dimensions()[1]; col_counter++) {
					mat_1.set_element(row_counter, col_counter, 2);
				}
			}
			Matrix<int> mat_2 = Matrix<int>(2,2);
			mat_2 = mat_1;
			Assert::AreEqual(2, mat_2.get_element(0, 0));
			Assert::AreEqual(2, mat_2.get_element(0, 1));
			Assert::AreEqual(2, mat_2.get_element(1, 0));
			Assert::AreEqual(2, mat_2.get_element(1, 1));
		}

		TEST_METHOD(TestMultiplyRow)
		{
			// TODO: Your test code here
			Matrix<int> mat_1 = Matrix<int>(2, 2);
			for (int row_counter = 0; row_counter < mat_1.get_dimensions()[0]; row_counter++) {
				for (int col_counter = 0; col_counter < mat_1.get_dimensions()[1]; col_counter++) {
					mat_1.set_element(row_counter, col_counter, 2);
				}
			}
			mat_1.multiply_row(1, 3);
			Assert::AreEqual(2, mat_1.get_element(0, 0));
			Assert::AreEqual(2, mat_1.get_element(0, 1));
			Assert::AreEqual(6, mat_1.get_element(1, 0));
			Assert::AreEqual(6, mat_1.get_element(1, 1));
		}

		TEST_METHOD(TestSetElement)
		{
			// TODO: Your test code here
			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 10);
			Assert::AreEqual(10, my_matrix.get_element(0, 0));

			//check exception is thrown for out of bounds
			bool exceptionThrown = false;
			try
			{
				my_matrix.set_element(5, 5, 10);
			}
			catch (...) // or any exception at all
			{
				exceptionThrown = true;
			}

			Assert::IsTrue(exceptionThrown); // or whatever else you want to do
		}

		TEST_METHOD(TestGetRow)
		{
			// TODO: Your test code here

			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 10);
			my_matrix.set_element(0, 1, 20);
			my_matrix.set_element(1, 0, 30);
			my_matrix.set_element(1, 1, 40);
			Assert::AreEqual(40, my_matrix.get_element(1, 1));

			//int* int_array = new int[2];
			Matrix<int> row_one = my_matrix.get_row(0);
			Assert::AreEqual(row_one.get_element(0, 0), 10);
			Assert::AreEqual(row_one.get_element(0, 1), 20);
		}

		TEST_METHOD(TestIdentity) {
			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 10);
			my_matrix.set_element(0, 1, 20);
			my_matrix.set_element(1, 0, 30);
			my_matrix.set_element(1, 1, 40);
			my_matrix.identity();
			Assert::AreEqual(1, my_matrix.get_element(0, 0));
			Assert::AreEqual(0, my_matrix.get_element(0, 1));
			Assert::AreEqual(0, my_matrix.get_element(1, 0));
			Assert::AreEqual(1, my_matrix.get_element(1, 1));
		}


		TEST_METHOD(TestAddition)
		{
			// TODO: Your test code here

			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 10);
			my_matrix.set_element(0, 1, 10);
			my_matrix.set_element(1, 0, 20);
			my_matrix.set_element(1, 1, 20);
			Matrix<int> other_matrix = my_matrix;
			other_matrix.set_element(1, 1, 30);
			Matrix<int> return_matrix = my_matrix + other_matrix;
			Assert::AreEqual(20, return_matrix.get_element(0, 0));
			Assert::AreEqual(20, return_matrix.get_element(0, 1));
			Assert::AreEqual(40, return_matrix.get_element(1, 0));
			Assert::AreEqual(50, return_matrix.get_element(1, 1));
		}

		TEST_METHOD(TestSubtraction)
		{
			// TODO: Your test code here

			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 10);
			my_matrix.set_element(0, 1, 10);
			my_matrix.set_element(1, 0, 20);
			my_matrix.set_element(1, 1, 20);
			Matrix<int> other_matrix = my_matrix;
			other_matrix.set_element(1, 1, 30);
			other_matrix.set_element(1, 0, 5);
			Matrix<int> return_matrix = my_matrix - other_matrix;
			Assert::AreEqual(0, return_matrix.get_element(0, 0));
			Assert::AreEqual(0, return_matrix.get_element(0, 1));
			Assert::AreEqual(15, return_matrix.get_element(1, 0));
			Assert::AreEqual(-10, return_matrix.get_element(1, 1));
		}

		TEST_METHOD(TestMultiplication)
		{
			// TODO: Your test code here

			Matrix<int> my_matrix = Matrix<int>(2, 2);
			my_matrix.set_element(0, 0, 2);
			my_matrix.set_element(0, 1, 0);
			my_matrix.set_element(1, 0, 0);
			my_matrix.set_element(1, 1, 2);
			int elements[4] = { 2,3,4,5 };
			Matrix<int> other_matrix = Matrix<int>(2, 2, *elements);

			Matrix<int> return_matrix = Matrix<int>(2,2);
			return_matrix = (my_matrix * other_matrix);
			Assert::AreEqual(4, return_matrix.get_element(0, 0));
			Assert::AreEqual(6, return_matrix.get_element(0, 1));
			Assert::AreEqual(8, return_matrix.get_element(1, 0));
			Assert::AreEqual(10, return_matrix.get_element(1, 1));

			return_matrix = my_matrix * other_matrix;
			Assert::AreEqual(4, return_matrix.get_element(0, 0));
			Assert::AreEqual(6, return_matrix.get_element(0, 1));
			Assert::AreEqual(8, return_matrix.get_element(1, 0));
			Assert::AreEqual(10, return_matrix.get_element(1, 1));
		}
		TEST_METHOD(TestTranspose)
		{
			// TODO: Your test code here

			Matrix<int> my_matrix = Matrix<int>(2, 3);
			my_matrix.set_element(0, 0, 2);
			my_matrix.set_element(0, 1, 0);
			my_matrix.set_element(0, 2, 1);
			my_matrix.set_element(1, 0, 0);
			my_matrix.set_element(1, 1, 2);
			my_matrix.set_element(1, 2, 5);

			Matrix<int> return_matrix = my_matrix.transpose();

			Assert::AreEqual(2, return_matrix.get_element(0, 0));
			Assert::AreEqual(0, return_matrix.get_element(0, 1));
			Assert::AreEqual(0, return_matrix.get_element(1, 0));
			Assert::AreEqual(2, return_matrix.get_element(1, 1));
			Assert::AreEqual(1, return_matrix.get_element(2, 0));
			Assert::AreEqual(5, return_matrix.get_element(2, 1));
		}

		TEST_METHOD(TestSwap)
		{
			Matrix<int> my_matrix = Matrix<int>(2, 3);
			my_matrix.set_element(0, 0, 2);
			my_matrix.set_element(0, 1, 0);
			my_matrix.set_element(0, 2, 1);
			my_matrix.set_element(1, 0, 0);
			my_matrix.set_element(1, 1, 2);
			my_matrix.set_element(1, 2, 5);

			my_matrix.swap_rows(0, 1);

			Assert::AreEqual(0, my_matrix.get_element(0, 0));
			Assert::AreEqual(2, my_matrix.get_element(0, 1));
			Assert::AreEqual(5, my_matrix.get_element(0, 2));
			Assert::AreEqual(2, my_matrix.get_element(1, 0));
			Assert::AreEqual(0, my_matrix.get_element(1, 1));
			Assert::AreEqual(1, my_matrix.get_element(1, 2));
		}

		TEST_METHOD(TestEquality)
		{
			Matrix<int> my_matrix = Matrix<int>(2, 3);
			my_matrix.set_element(0, 0, 2);
			my_matrix.set_element(0, 1, 0);
			my_matrix.set_element(0, 2, 1);
			my_matrix.set_element(1, 0, 0);
			my_matrix.set_element(1, 1, 2);
			my_matrix.set_element(1, 2, 5);

			Matrix<int> my_matrix1 = Matrix<int>(2, 3);
			my_matrix1.set_element(0, 0, 2);
			my_matrix1.set_element(0, 1, 0);
			my_matrix1.set_element(0, 2, 1);
			my_matrix1.set_element(1, 0, 0);
			my_matrix1.set_element(1, 1, 2);
			my_matrix1.set_element(1, 2, 5);

			Assert::IsTrue(my_matrix == my_matrix1);
		}



	};
}
