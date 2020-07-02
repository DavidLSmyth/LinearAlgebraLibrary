#pragma once


#pragma once
//#define loop(x, n) for(int x=0; x < n; x++)
namespace MatrixNamespace {
	//want Matrix to contain elements of type T
	template<class T>
	class Matrix
	{
	public:
		Matrix<T>(const Matrix<T>& other_mat) {
			no_cols = other_mat.no_cols;
			no_rows = other_mat.no_rows;
			elements = new T[no_rows * no_cols];
			memcpy(elements, other_mat.elements, sizeof(T) * no_rows * no_cols);
			//memcpy(elements, other_mat.elements, sizeof(elements)/sizeof(T));
		}

		Matrix<T>(int no_rows, int no_cols) {
			this->no_cols = no_cols;
			this->no_rows = no_rows;
			elements = new T[no_rows * no_cols];
		}

		//maybe change this to utilise constructor chaining
		Matrix<T>(int no_rows, int no_cols, const T &element_array) {
			/*
			if((sizeof(element_array) / sizeof(T)) != no_cols * no_rows) {
				std::cout << "Size pf matrix: "<<sizeof(element_array)<< "size of T"<< sizeof(element_array[0]) << std::endl;
				throw(dimension_mismatch);
			}
			else {
			*/
			this->no_cols = no_cols;
			this->no_rows = no_rows;
			elements = new T[no_rows * no_cols];
			memcpy(elements, &element_array, sizeof(T) * no_rows * no_cols);
			//}
		}

		Matrix<T> operator+(const Matrix<T>& other_mat);
		Matrix<T> operator-(const Matrix<T>& other_mat);
		//Multiply by transpose of other



		//friend Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2);
		Matrix<T> operator*(const Matrix<T>& other_mat);
		Matrix<T> operator*(const T& scalar);
		bool operator==(const Matrix<T>& other_mat) const;
		bool operator!=(Matrix<T> other_mat);


		Matrix<T> operator=(const Matrix<T>& other_mat);
		Matrix<T> transpose();
		Matrix<T> get_row(int row_index) const;
		//multiplies a row by a coefficient in-place
		void multiply_row(int row_index, T coefficient);

		void swap_rows(int row_index_1, int row_index_2);
		Matrix<T> get_col(int col);
		void zeros();
		void identity();
		void set_diag(T element);

		T* get_elements();

		bool set_element(int row_index, int col_index, T element);
		bool set_row(int row_index, T* rowArray);
		T get_element(int row_index, int col_index) { return elements[(row_index * no_cols) + col_index]; };
		//if const, then get_element complains because it is not defined for a const
		//Matrix. So need to define a const method
		T get_element(int row_index, int col_index) const { return elements[(row_index * no_cols) + col_index]; };
		int get_rank() { throw "NotImplementedError"; };
		T two_norm();
		float determinant();
		int* get_dimensions();
		Matrix get_inverse();
		int get_no_rows();
		int get_no_cols();
		void print_matrix();
		~Matrix<T>() {
			delete[] elements;
		}

	private:
		bool verify_dims_add(Matrix<T> other_matrix) { if (no_rows == other_matrix.get_dimensions()[0] && no_cols == other_matrix.get_dimensions()[1]) { return true; } else { return false; } };
		//number of columns of this matrix must equal number of rows of other matrix
		bool verify_dims_mult(Matrix<T> other_matrix) { return (no_cols == other_matrix.no_rows); };
		bool verify_valid_index(int i, int j) {
			if (0 <= i && i < no_rows && 0 <= j && j < no_cols) { return true; }
			else { return false; }
		}
		static const double eps;
		T* elements;
		long int no_rows;
		long int no_cols;
		const char* dimension_mismatch = "Dimensions of matrices are not compatible";
	};
}
