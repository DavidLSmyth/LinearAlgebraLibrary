#include "MatrixFunctions.h"
#include "Matrix.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>

namespace MatrixFns {
	//A library of functions that act on matrices


	//template <typename T>
	const char MatrixFns::MatrixFunctions::unstablePivot[] = "Pivot is < epsilon, result is unstable";



	template <typename T>
	MatrixFns::PLUFactorisation<T> MatrixFunctions::getPLUFactors(const Matrix<T>& B, float epsilon) {
		Matrix<T>& A = const_cast<Matrix<T>&>(B);
		int no_rows = A.get_no_rows();
		int no_cols = A.get_no_cols();
		Matrix<T> L = Matrix<T>(no_rows, no_rows);
		L.identity();

		Matrix<float> P = Matrix<float>(no_rows, no_rows);
		P.identity();
		Matrix<T> U = Matrix<T>(A);

		//iterate over each row in the matrix, swap if necessary and eliminate all below

		//finds the largest pivot
		int pivotMaxIndex = 0;


		Matrix<float> currentPermutation = Matrix<float>(no_rows, no_rows);
		T maxPivotValue;
		T coefficient;
		Matrix<T> tempL = Matrix<T>(no_rows, no_rows);
		Matrix<T> tempU = Matrix<T>(no_rows, no_rows);
		tempL.identity();
		tempU.identity();
		T nextPossiblePivot;

		//iterate over each row and swap as necessary
		for (int pivotIndex = 0; pivotIndex < A.get_no_rows()-1; pivotIndex++) {
			//get current row
			pivotMaxIndex = pivotIndex;
			maxPivotValue = U.get_element(pivotIndex, pivotIndex);
			for (int counter = pivotIndex + 1; counter < A.get_no_rows(); counter++) {
				//find biggest pivot below rowIndex
				nextPossiblePivot = U.get_element(counter, pivotIndex);
				if (nextPossiblePivot > maxPivotValue) {
					//cout << nextPossiblePivot << " > " << maxPivotValue << endl;
					maxPivotValue = nextPossiblePivot;
					pivotMaxIndex = counter;
				}
			}

			if (pivotMaxIndex != pivotIndex) {
				//update P
				currentPermutation.identity();
				currentPermutation.swap_rows(pivotMaxIndex, pivotIndex);
				U.swap_rows(pivotMaxIndex, pivotIndex);
				P = currentPermutation * P;

			}

			if (maxPivotValue < epsilon) {
				//if 0, continue to next
				//throw(unstablePivot);
				continue;
				//return MatrixFns::PLUFactorisation<T> { P, L, U };
			}
			else {
				tempL.identity();
				tempU.identity();
				//update the row, eliminating below the pivot
				for (int currentRowIndex = pivotIndex + 1; currentRowIndex < A.get_no_rows(); currentRowIndex++) {
					coefficient = -U.get_element(currentRowIndex, pivotIndex)/ maxPivotValue;
					tempL.set_element(currentRowIndex, pivotIndex, -coefficient);
					tempU.set_element(currentRowIndex, pivotIndex, +coefficient);
					//tempL.mul
				}
				std::cout << "tempL: " << std::endl;
				tempL.print_matrix();
				L = L * tempL;				
				std::cout << "L: "<< std::endl;

				L.print_matrix();
				U = tempU * U;
				std::cout << "U: " << std::endl;
				U.print_matrix();
				

			}
			std::cout << "------------- next iteration ----------" << std::endl;
		}
		return MatrixFns::PLUFactorisation<T> { P, L, U };

	}

	template<typename T>
	Matrix<T> MatrixFns::MatrixFunctions::getSubMatrix(Matrix<T>& A, int start_row, int start_col, int end_row, int end_col)
	{
		//Matrix<T>& B = const_cast<Matrix<T&>>(A);
		Matrix<T> returnMatrix = Matrix<T>(end_row - start_row, end_col - start_col);
		for (int row_counter = start_row; row_counter < end_row; row_counter++) {
			for (int col_counter = start_col; col_counter < end_col; col_counter++) {
				returnMatrix.set_element(row_counter - start_row, col_counter - start_col, A.get_element(row_counter, col_counter));
			}

		}
		return returnMatrix;
	}

}