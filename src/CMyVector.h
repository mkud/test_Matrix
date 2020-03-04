/*
 * CMyVector.h
 *
 *  Created on: 2 мар. 2020 г.
 *      Author: maxx
 */

#ifndef CMYVECTOR_H_
#define CMYVECTOR_H_

#include <string.h>
#include <vector>
#include <stdexcept>
#include <cmath>

class CMyMatrix;

class CMyVector {
private:
	double *m_pVector;
	unsigned m_uiLength;
	CMyVector() :
			m_pVector(0), m_uiLength(0) {
	}
	//used for fast access to Matrix
	friend CMyMatrix;
public:

	CMyVector(unsigned uiLength);
	CMyVector(std::initializer_list<double> in_list);

	CMyVector(const CMyVector &inVector);
	virtual ~CMyVector();

	//Compare operators
	bool operator==(const CMyVector &inVector) const;
	bool Near(const CMyVector &inVector, double delta);

	// Operator overloading, for "standard" mathematical vector operations
	CMyVector& operator=(const CMyVector &inVector);

	// Vector mathematical operations
	CMyVector operator+(const CMyVector &inVector);
	CMyVector& operator+=(const CMyVector &inVector);
	CMyVector operator-(const CMyVector &inVector);
	CMyVector& operator-=(const CMyVector &inVector);
	double operator*(const CMyVector &inVector);

	// Vector/scalar operations
	CMyVector operator+(const double &dParam);
	CMyVector operator-(const double &dParam);
	CMyVector operator*(const double &dParam);
	CMyVector operator/(const double &dParam);

	// Access the individual elements
	double& operator()(const unsigned &pos);
	const double& operator()(const unsigned &pos) const;

	// Access the size
	unsigned get_length() const;

};
#endif /* CMYVECTOR_H_ */
