#include "Matrix.h"
#include <iostream>
#include <math.h>
#include <cstring>

// compile with: cl /c /EHsc Matrix.cpp
// post-build command: lib Matrix.obj

//using namespace MatrixNamespace;
//#define loop(x, n) for(int x=0; x < n; x++)

namespace MatrixNamespace {

	const double Matrix<float>::eps = 0.0000001;
	const double Matrix<int>::eps = 0.0000001;
	const double Matrix<double>::eps = 0.0000001;

	template<class T>
	Matrix<T> Matrix<T>::operator=(const Matrix<T>& other_mat) {
		if (this == &other_mat) {
			//dereference
			return(*this);
		}
		else {
			delete[] elements; // Just in case there was any memory
							  // already allocated
			no_rows = other_mat.no_rows;
			no_cols = other_mat.no_cols;
			elements = new T[other_mat.no_rows * other_mat.no_cols];

			memcpy(elements, other_mat.elements, sizeof(T) * no_rows * no_cols);
			/*
			loop(elements_counter, no_rows * no_cols) {
				elements[elements_counter] = other_mat[elements_counter];
			}
			*/
			return(*this);
		}
	}
	//sets the matrix's entries to zero
	template<class T>
	void Matrix<T>::zeros()
	{
		memset(elements, 0, sizeof(T) * no_rows * no_cols);
	}

	template<class T>
	void Matrix<T>::identity()
	{
		set_diag(1);
	}



	template<class T>
	void Matrix<T>::set_diag(T element)
	{
		zeros();
		for (int counter = 0; counter < no_rows; counter++) {
			set_element(counter, counter, element);
		}
	}


	template<class T>
	T* Matrix<T>::get_elements()
	{
		return elements;
	}


	template<class T>
	Matrix<T> Matrix<T>::operator-(const Matrix<T>& other_mat)
	{
		if (verify_dims_add(other_mat)) {
			Matrix<T> return_matrix = Matrix(no_rows, no_cols);
			for (int element = 0; element < no_rows * no_cols; element++) {
				return_matrix.elements[element] = elements[element] + (other_mat.elements[element] * -1);
			}
			//loop(element, no_rows * no_cols) {

			//}
			return return_matrix;
		}
		else {
			throw(dimension_mismatch);
		}
	}

	template<class T>
	Matrix<T> Matrix<T>::transpose() {
		Matrix<T> return_mat = Matrix<T>(no_cols, no_rows);
		for (int row_counter = 0; row_counter < no_rows; row_counter++) {
			//loop(row_counter, no_rows) {
			for (int col_counter = 0; col_counter < no_cols; col_counter++) {
				//loop(col_counter, no_cols) {
				return_mat.elements[(col_counter * no_rows) + row_counter] = elements[(row_counter * no_cols) + col_counter];
			}
		}
		return return_mat;
	}

	template<class T>
	//FMatrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2){
	Matrix<T> Matrix<T>::operator*(const Matrix<T>& other_mat) {
		if (verify_dims_mult(other_mat)) {
			Matrix<T> return_matrix = Matrix<T>(no_rows, other_mat.no_cols);
			for (int mat1RowCounter = 0; mat1RowCounter < no_rows; mat1RowCounter++) {
				//loop(row_counter, no_rows) {
				for (int col_counter = 0; col_counter < other_mat.no_cols; col_counter++) {
					//loop(col_counter, other_mat.no_cols) {
					T s = 0;
					//k records the kth column of the first matrix and the kth row of the second matrix
					//loop(k, no_cols) {
					for (int k = 0; k < no_cols; k++) {
						s += get_element(mat1RowCounter, k) * other_mat.get_element(k, col_counter);
					}
					return_matrix.set_element(mat1RowCounter, col_counter, s);
				}
			}
			return return_matrix;
		}
		else {
			throw(dimension_mismatch);
		}
	}

	template<class T>
	Matrix<T> Matrix<T>::operator*(const T& scalar) {
		Matrix<T> return_matrix(no_rows, no_cols);
		for (int counter = 0; counter < no_rows * no_cols; counter++) {
			//loop(counter, no_rows * no_cols) {
			return_matrix[counter] = return_matrix[counter] * scalar;
		}
		return return_matrix;

	}




	template<class T>
	Matrix<T> Matrix<T>::get_row(int row_index) const
	{
		Matrix<T> return_mat = Matrix(1, no_cols);
		for (int col_counter = 0; col_counter < no_cols; col_counter++) {
			//loop(col_counter, no_cols) {
			return_mat.set_element(0, col_counter, get_element(0, col_counter));
		}
		//}
		//T* return_array = new T[no_cols];
		//memcpy(&return_array, &elements[row*no_cols], no_cols * sizeof(T));
		/*
		loop(col_counter, no_cols) {
			return_mat.set_element(1, col_counter, get_element(1, col_counter));
		}

		*/
		return return_mat;
		//return return_array;
	}

	template<class T>
	void Matrix<T>::multiply_row(int row_index, T coefficient)
	{
		int start_pos = row_index * no_cols;
		for (int counter = start_pos; counter < start_pos + no_cols; counter++) {
			elements[counter] *= coefficient;
		}
	}



	template<class T>
	void Matrix<T>::swap_rows(int row_index_1, int row_index_2)
	{

		if (0 <= row_index_1 && row_index_1 < no_rows && 0 <= row_index_2 && row_index_2 < no_rows) {
			T* row1_copy = new T[sizeof(T) * no_cols];
			T* start_index = &elements[no_cols * row_index_1];
			//copy row 1 of matrix to row1_copy
			memcpy(row1_copy, &elements[no_cols * row_index_1], sizeof(T) * no_cols);
			//copy the elements from row 2 to row 1
			memcpy(&elements[no_cols * row_index_1], &elements[no_cols * row_index_2], sizeof(T) * no_cols);
			memcpy(&elements[no_cols * row_index_2], row1_copy, sizeof(T) * no_cols);
			//get rid of temp files
			delete[] row1_copy;
		}
		else {
			std::cerr << "Out of bounds error" << std::endl;
			throw(dimension_mismatch);
		}
	}



	template<class T>
	Matrix<T> Matrix<T>::get_col(int col)
	{
		Matrix<T> return_mat = Matrix(no_rows, 1);
		for (int row_counter = 0; row_counter < no_cols; row_counter++) {
			//loop(row_counter, no_cols) {
			return_mat.set_element(row_counter, 1, get_element(row_counter, 1));
		}
		return return_mat;
	}

	template<class T>
	bool Matrix<T>::operator==(const Matrix<T>& other_mat) const
	{
		if (no_rows == other_mat.no_rows && no_cols == other_mat.no_cols) {
			for (int element_index = 0; element_index < no_rows * no_cols; element_index++) {
				//loop(element_index, no_rows * no_cols) {
				if (elements[element_index] - other_mat.elements[element_index] > eps) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}



	template<class T>
	Matrix<T> Matrix<T>::operator+(const Matrix<T>& other_mat)
	{
		if (verify_dims_add(other_mat)) {
			Matrix<T> return_matrix(no_rows, no_cols);
			for (int row_counter = 0; row_counter < no_rows; row_counter++) {
				for (int col_counter = 0; col_counter < no_cols; col_counter++) {
					return_matrix.set_element(row_counter, col_counter, get_element(row_counter, col_counter) + other_mat.get_element(row_counter, col_counter));
				}
			}
			return return_matrix;
		}
		else {
			throw(dimension_mismatch);
		}
	}

	template<class T>
	bool Matrix<T>::operator!=(Matrix other_mat)
	{
		return false;
	}

	template<class T>
	bool Matrix<T>::set_row(int row_index, T* rowArray) {
		if (sizeof(rowArray) / sizeof(T) != no_cols) {
			throw(dimension_mismatch);
			return false;
		}
		else {
			memcpy(this->elements[row_index * no_cols], rowArray, no_cols);
			return true;
		}
	}

	template<class T>
	bool Matrix<T>::set_element(int row_index, int col_index, T element)
	{
		if (verify_valid_index(row_index, col_index)) {
			elements[(row_index * no_cols) + col_index] = element;
			return true;
		}
		else {
			std::cerr << "Dimensions do not match. Rows: " << row_index << "Cols" << col_index << "No rows" << no_rows << "No cols" << no_cols << std::endl;
			throw(dimension_mismatch);
			return false;
		}
	}

	template<class T>
	T Matrix<T>::two_norm()
	{
		//matrix norms can be defined in a number of different ways
		//must define a function |.| : K^Mxn -> R satisfying: 
		/*
		1). ||c*A|| = |c| * ||A||
		2). ||A+B|| <= ||A|| + ||B||
		3). ||A|| >= 0
		4). ||A|| = 0 iff A = 0_m,n
		return T();
		*/
		T sum = 0;
		for (int element = 0; element < no_rows * no_cols; element++) {
		//loop(element, no_rows * no_cols) {
			sum += elements[element] * elements[element];
		}
		return sqrt(sum);
	}



	template<class T>
	float Matrix<T>::determinant()
	{
		return 0.0f;
	}

	template<class T>
	int* Matrix<T>::get_dimensions()
	{
		int* return_array = new int[2];
		return_array[0] = no_rows;
		return_array[1] = no_cols;
		return return_array;
	}

	template<class T>
	Matrix<T> Matrix<T>::get_inverse()
	{
		return Matrix();
	}

	template<class T>
	int Matrix<T>::get_no_rows()
	{
		return no_rows;
	}

	template<class T>
	int Matrix<T>::get_no_cols()
	{
		return no_cols;
	}

	template<class T>
	void Matrix<T>::print_matrix()
	{
		//std::cout << "Printing matrix" << std::endl;
		for (int row_counter = 0; row_counter < no_rows; row_counter++) {
			for (int col_counter = 0; col_counter < no_cols; col_counter++) {
				std::cout << get_element(row_counter, col_counter);
				std::cout << ", ";
			}
			std::cout << std::endl;
		}
	}
}