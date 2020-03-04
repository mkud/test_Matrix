/*
 * CMyMatrix.cpp
 *
 *  Created on: 3 мар. 2020 г.
 *      Author: maxx
 */

#include "CMyMatrix.h"

// Parameter Constructor

CMyMatrix::CMyMatrix(unsigned uiRows, unsigned uiCols) :
		m_pMatrix(new double[uiRows * uiCols]), m_uiRows(uiRows), m_uiCols(uiCols) {
}

CMyMatrix::CMyMatrix(unsigned uiRows, unsigned uiCols, std::initializer_list<double> in_list) :
		CMyMatrix(uiRows, uiCols) {
	if (in_list.size() != uiRows * uiCols)
		throw std::runtime_error("bad init CMyMatrix");
	double *cur_pos = m_pMatrix;
	for (std::initializer_list<double>::iterator iter = in_list.begin(); iter != in_list.end(); iter++, cur_pos++)
		*cur_pos = *iter;
}

// Copy Constructor

CMyMatrix::CMyMatrix(const CMyMatrix &inMatrix) :
		CMyMatrix(inMatrix.m_uiRows, inMatrix.m_uiCols) {
	memcpy(m_pMatrix, inMatrix.m_pMatrix, sizeof(double) * inMatrix.m_uiRows * inMatrix.m_uiCols);
}

// (Virtual) Destructor

CMyMatrix::~CMyMatrix() {
	delete m_pMatrix;
}

// Matrix compare operator

bool CMyMatrix::operator==(const CMyMatrix &inMatrix) const {
	return (m_uiRows == inMatrix.m_uiRows) && (m_uiCols == inMatrix.m_uiCols)
			&& !memcmp(m_pMatrix, inMatrix.m_pMatrix, sizeof(double) * m_uiRows * m_uiCols);
}

// Check near Matrix because we have double valued matrixs

bool CMyMatrix::Near(const CMyMatrix &inMatrix, double delta) {
	if (m_uiCols != inMatrix.m_uiCols || m_uiRows != inMatrix.m_uiRows)
		return false;

	for (unsigned i = 0; i < m_uiCols * m_uiRows; i++)
		if (fabs(m_pMatrix[i] - inMatrix.m_pMatrix[i]) > delta)
			return false;
	return true;
}

// Assignment Operator

CMyMatrix& CMyMatrix::operator=(const CMyMatrix &inMatrix) {
	if (&inMatrix == this)
		return *this;
	if (inMatrix.m_uiRows != m_uiRows || inMatrix.m_uiCols != m_uiCols) {
		delete m_pMatrix;
		m_uiRows = inMatrix.m_uiRows;
		m_uiCols = inMatrix.m_uiCols;
		m_pMatrix = new double[m_uiRows * m_uiCols];
	}
	memcpy(m_pMatrix, inMatrix.m_pMatrix, sizeof(double) * inMatrix.m_uiRows * inMatrix.m_uiCols);
	return *this;
}

// Addition of two matrices

CMyMatrix CMyMatrix::operator+(const CMyMatrix &inMatrix) {
	if (inMatrix.m_uiRows != m_uiRows || inMatrix.m_uiCols != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator+");

	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] + inMatrix.m_pMatrix[i];

	return result;
}

// Cumulative addition of this matrix and another

CMyMatrix& CMyMatrix::operator+=(const CMyMatrix &inMatrix) {
	if (inMatrix.m_uiRows != m_uiRows || inMatrix.m_uiCols != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator+=");

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		m_pMatrix[i] += inMatrix.m_pMatrix[i];

	return *this;
}

// Subtraction of this matrix and another

CMyMatrix CMyMatrix::operator-(const CMyMatrix &inMatrix) {
	if (inMatrix.m_uiRows != m_uiRows || inMatrix.m_uiCols != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator+=");
	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] - inMatrix.m_pMatrix[i];

	return result;
}

// Cumulative subtraction of this matrix and another

CMyMatrix& CMyMatrix::operator-=(const CMyMatrix &inMatrix) {
	if (inMatrix.m_uiRows != m_uiRows || inMatrix.m_uiCols != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator+=");

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		m_pMatrix[i] -= inMatrix.m_pMatrix[i];

	return *this;
}

// Left multiplication of this matrix and another

CMyMatrix CMyMatrix::operator*(const CMyMatrix &inMatrix) {
	if (inMatrix.m_uiRows != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator* CMyMatrix");
	CMyMatrix result(m_uiRows, inMatrix.m_uiCols);
	memset(result.m_pMatrix, 0, sizeof(double) * m_uiRows * inMatrix.m_uiCols);

	double *c, *b, a;
	for (unsigned i = 0; i < m_uiRows; ++i) {
		c = result.m_pMatrix + i * inMatrix.m_uiCols;
		for (unsigned k = 0; k < m_uiCols; ++k) {
			b = inMatrix.m_pMatrix + k * inMatrix.m_uiCols;
			a = m_pMatrix[i * m_uiCols + k];
			for (unsigned j = 0; j < inMatrix.m_uiCols; ++j)
				c[j] += a * b[j];
		}
	}
	return result;
}

// Cumulative left multiplication of this matrix and another

CMyMatrix& CMyMatrix::operator*=(const CMyMatrix &inMatrix) {
	CMyMatrix result = (*this) * inMatrix;
	(*this) = result;
	return *this;
}

// Calculate a transpose of this matrix

CMyMatrix CMyMatrix::transpose() {
	CMyMatrix result(m_uiCols, m_uiRows);

	for (unsigned i = 0; i < m_uiRows; i++) {
		for (unsigned j = 0; j < m_uiCols; j++) {
			result.m_pMatrix[j * m_uiRows + i] = m_pMatrix[i * m_uiCols + j];
		}
	}

	return result;
}

// Matrix/scalar addition

CMyMatrix CMyMatrix::operator+(const double &dParam) {
	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] + dParam;

	return result;
}

// Matrix/scalar subtraction

CMyMatrix CMyMatrix::operator-(const double &dParam) {
	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] - dParam;

	return result;
}

// Matrix/scalar multiplication

CMyMatrix CMyMatrix::operator*(const double &dParam) {
	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] * dParam;

	return result;
}

// Matrix/scalar division

CMyMatrix CMyMatrix::operator/(const double &dParam) {
	CMyMatrix result(m_uiRows, m_uiCols);

	for (unsigned i = 0; i < m_uiRows * m_uiCols; i++)
		result.m_pMatrix[i] = m_pMatrix[i] / dParam;

	return result;
}

// Multiply a matrix with a vector

CMyVector CMyMatrix::operator*(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiCols)
		throw std::overflow_error("CMyMatrix::operator* CMyVector");

	CMyVector result(inVector.m_uiLength);
	memset(result.m_pVector, 0, sizeof(double) * inVector.m_uiLength);

	double *cur_pos = m_pMatrix;
	for (unsigned i = 0; i < m_uiRows; i++) {
		for (unsigned j = 0; j < m_uiCols; j++, cur_pos++) {
			result.m_pVector[i] += (*cur_pos) * inVector.m_pVector[j];
		}
	}

	return result;
}

// Obtain a vector of the diagonal elements

CMyVector CMyMatrix::diag_vec() {
	if (m_uiRows != m_uiCols)
		throw std::overflow_error("CMyMatrix::diag_vec");
	CMyVector result(m_uiRows);
	double *cur_pos = m_pMatrix;
	for (unsigned i = 0; i < m_uiRows; i++, cur_pos += m_uiRows + 1) {
		result.m_pVector[i] = *cur_pos;
	}

	return result;
}

// Access the individual elements

double& CMyMatrix::operator()(const unsigned &row, const unsigned &col) {
	if (row >= m_uiRows || col >= m_uiCols)
		throw std::overflow_error("CMyMatrix::operator()");
	return m_pMatrix[row * m_uiCols + col];
}

// Access the individual elements (const)

const double& CMyMatrix::operator()(const unsigned &row, const unsigned &col) const {
	if (row >= m_uiRows || col >= m_uiCols)
		throw std::overflow_error("CMyMatrix::operator() const");
	return m_pMatrix[row * m_uiCols + col];
}

// Get the number of rows of the matrix

unsigned CMyMatrix::get_rows() const {
	return m_uiRows;
}

// Get the number of columns of the matrix

unsigned CMyMatrix::get_cols() const {
	return m_uiCols;
}

// Get determinant of the matrix

double CMyMatrix::Determinant() {
	if (m_uiCols != m_uiRows)
		throw std::runtime_error("CMyMatrix::Determinant() - matrix not square");
	return internalDeterminant(m_pMatrix, m_uiCols);
}

//Internal determinant function for recursive calculation

double CMyMatrix::internalDeterminant(double *matrix, int n) {
	switch (n) {
	case 1:
		return matrix[0];
	case 2:
		return ((matrix[0] * matrix[m_uiCols + 1]) - (matrix[m_uiCols] * matrix[1]));
	default: {
		double det = 0;
		double submatrix[m_uiCols * m_uiCols];
		int subi, i, subj, j;
		for (int x = 0; x < n; x++) {
			subi = 0;
			for (i = 1; i < n; i++) {
				subj = 0;
				for (j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi * m_uiCols + subj] = matrix[i * m_uiCols + j];
					subj++;
				}
				subi++;
			}
			det += ((x % 2) ? -1 : 1) * matrix[x] * internalDeterminant(submatrix, n - 1);
		}
		return det;
	}
	}

}

//Getting Inverse Matrix by Gauss-Jordan Method

CMyMatrix CMyMatrix::GetInverseMatrix() {

	if (m_uiCols != m_uiRows)
		throw std::runtime_error("CMyMatrix::GetInverseMatrix() - matrix not square");

	//Work Matrix
	double A[m_uiCols][m_uiCols * 2];
	//temp variables
	double tmp_vector[m_uiCols * 2];
	double temp;
	unsigned i, j, k;
	//Copy date to work matrix and append with one-matrix
	for (i = 0; i < m_uiCols; i++) {
		memcpy(A[i], m_pMatrix + i * m_uiCols, sizeof(double) * m_uiCols);
		memset(A[i] + m_uiCols, 0, sizeof(double) * m_uiCols);
		A[i][m_uiCols + i] = 1;
	}

	// Interchange the row of matrix; by rows
	for (i = m_uiCols - 1; i > 0; i--) {
		if (A[i - 1][0] < A[i][0]) {
			memcpy(tmp_vector, A[i], sizeof(double) * m_uiCols * 2);
			memcpy(A[i], A[i - 1], sizeof(double) * m_uiCols * 2);
			memcpy(A[i - 1], tmp_vector, sizeof(double) * m_uiCols * 2);
		}
	}

	// Replace a row by sum of itself and a
	// constant multiple of another row of the matrix
	for (i = 0; i < m_uiCols; i++) {

		for (j = 0; j < m_uiCols; j++) {

			if (j != i) {

				temp = A[j][i] / A[i][i];
				for (k = 0; k < 2 * m_uiCols; k++) {

					A[j][k] -= A[i][k] * temp;
				}
			}
		}
	}

	// Multiply each row by a nonzero integer.
	// Divide row element by the diagonal element
	for (i = 0; i < m_uiCols; i++) {

		double temp = A[i][i];
		for (j = 0; j < 2 * m_uiCols; j++) {

			A[i][j] = A[i][j] / temp;
		}
	}

	CMyMatrix result(m_uiCols, m_uiCols);

	//Generate result Matrix
	for (i = 0; i < m_uiCols; i++)
		for (j = 0, k = m_uiCols; j < m_uiCols; j++, k++)
			result.m_pMatrix[i * m_uiCols + j] = A[i][k];
	return result;

}
