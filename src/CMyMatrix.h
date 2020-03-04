/*
 * CMyMatrix.h
 *
 *  Created on: 3 мар. 2020 г.
 *      Author: maxx
 */

#ifndef CMYMATRIX_H_
#define CMYMATRIX_H_

#include <string.h>
#include <vector>
#include <stdexcept>
#include "CMyVector.h"

class CMyMatrix {
private:
	double *m_pMatrix;
	unsigned m_uiRows;
	unsigned m_uiCols;

	CMyMatrix() :
			m_pMatrix(0), m_uiRows(0), m_uiCols(0) {
	}
	double internalDeterminant(double *matrix, int n);
public:
	CMyMatrix(unsigned uiRows, unsigned uiCols);
	CMyMatrix(unsigned uiRows, unsigned uiCols, std::initializer_list<double> in_list);

	CMyMatrix(const CMyMatrix &inMatrix);
	virtual ~CMyMatrix();

	//Compare operators
	bool operator==(const CMyMatrix &inMatrix) const;
	bool Near(const CMyMatrix &inMatrix, double delta);

	// Operator overloading, for "standard" mathematical matrix operations
	CMyMatrix& operator=(const CMyMatrix &inMatrix);

	// Matrix mathematical operations
	CMyMatrix operator+(const CMyMatrix &inMatrix);
	CMyMatrix& operator+=(const CMyMatrix &inMatrix);
	CMyMatrix operator-(const CMyMatrix &inMatrix);
	CMyMatrix& operator-=(const CMyMatrix &inMatrix);
	CMyMatrix operator*(const CMyMatrix &inMatrix);
	CMyMatrix& operator*=(const CMyMatrix &inMatrix);
	CMyMatrix transpose();

	// Matrix/scalar operations
	CMyMatrix operator+(const double &dParam);
	CMyMatrix operator-(const double &dParam);
	CMyMatrix operator*(const double &dParam);
	CMyMatrix operator/(const double &dParam);

	// Matrix/vector operations
	CMyVector operator*(const CMyVector &inVector);
	CMyVector diag_vec();

	// Access the individual elements
	double& operator()(const unsigned &row, const unsigned &col);
	const double& operator()(const unsigned &row, const unsigned &col) const;

	// Access the row and column sizes
	unsigned get_rows() const;
	unsigned get_cols() const;

	// Get determinant of the matrix
	double Determinant();
	//Getting Inverse Matrix by Gauss-Jordan Method
	CMyMatrix GetInverseMatrix();
};

#endif /* CMYMATRIX_H_ */
