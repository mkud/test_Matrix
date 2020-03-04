/*
 * CMyVector.cpp
 *
 *  Created on: 2 мар. 2020 г.
 *      Author: maxx
 */

#include "CMyVector.h"

// Parameter Constructor

CMyVector::CMyVector(unsigned uiLength) :
		m_pVector(new double[uiLength]), m_uiLength(uiLength) {
}

CMyVector::CMyVector(std::initializer_list<double> in_list) :
		CMyVector(in_list.size()) {
	if (in_list.size() != in_list.size())
		throw std::runtime_error("bad init CMyVector");
	double *cur_pos = m_pVector;
	for (std::initializer_list<double>::iterator iter = in_list.begin(); iter != in_list.end(); iter++, cur_pos++)
		*cur_pos = *iter;
}

// Copy Constructor

CMyVector::CMyVector(const CMyVector &inVector) :
		CMyVector(inVector.m_uiLength) {
	memcpy(m_pVector, inVector.m_pVector, sizeof(double) * inVector.m_uiLength);
}

// (Virtual) Destructor

CMyVector::~CMyVector() {
	delete m_pVector;
}

// Vector compare operator

bool CMyVector::operator==(const CMyVector &inVector) const {
	return (m_uiLength == inVector.m_uiLength) && !memcmp(m_pVector, inVector.m_pVector, sizeof(double) * m_uiLength);
}

// Check near Vector because we have double valued vectors

bool CMyVector::Near(const CMyVector &inVector, double delta) {
	if (m_uiLength != inVector.m_uiLength)
		return false;

	for (unsigned i = 0; i < m_uiLength; i++)
		if (fabs(m_pVector[i] - inVector.m_pVector[i]) > delta)
			return false;
	return true;
}

// Assignment Operator

CMyVector& CMyVector::operator=(const CMyVector &inVector) {
	if (&inVector == this)
		return *this;
	if (inVector.m_uiLength != m_uiLength) {
		delete m_pVector;
		m_uiLength = inVector.m_uiLength;
		m_pVector = new double[m_uiLength];
	}
	memcpy(m_pVector, inVector.m_pVector, sizeof(double) * inVector.m_uiLength);
	return *this;
}

// Addition of two matrices

CMyVector CMyVector::operator+(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiLength)
		throw std::overflow_error("CMyVector::operator+");

	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] + inVector.m_pVector[i];

	return result;
}

// Cumulative addition of this vector and another

CMyVector& CMyVector::operator+=(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiLength)
		throw std::overflow_error("CMyVector::operator+=");

	for (unsigned i = 0; i < m_uiLength; i++)
		m_pVector[i] += inVector.m_pVector[i];

	return *this;
}

// Subtraction of this vector and another

CMyVector CMyVector::operator-(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiLength)
		throw std::overflow_error("CMyVector::operator+=");
	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] - inVector.m_pVector[i];

	return result;
}

// Cumulative subtraction of this vector and another

CMyVector& CMyVector::operator-=(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiLength)
		throw std::overflow_error("CMyVector::operator+=");

	for (unsigned i = 0; i < m_uiLength; i++)
		m_pVector[i] -= inVector.m_pVector[i];

	return *this;
}

// Left multiplication of this vector and another

double CMyVector::operator*(const CMyVector &inVector) {
	if (inVector.m_uiLength != m_uiLength)
		throw std::overflow_error("CMyVector::operator* CMyVector");
	double result = 0;
	for (unsigned i = 0; i < m_uiLength; ++i)
		result += inVector.m_pVector[i] * m_pVector[i];
	return result;
}

// Vector/scalar addition

CMyVector CMyVector::operator+(const double &dParam) {
	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] + dParam;

	return result;
}

// Vector/scalar subtraction

CMyVector CMyVector::operator-(const double &dParam) {
	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] - dParam;

	return result;
}

// Vector/scalar multiplication

CMyVector CMyVector::operator*(const double &dParam) {
	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] * dParam;

	return result;
}

// Vector/scalar division

CMyVector CMyVector::operator/(const double &dParam) {
	CMyVector result(m_uiLength);

	for (unsigned i = 0; i < m_uiLength; i++)
		result.m_pVector[i] = m_pVector[i] / dParam;

	return result;
}

// Access the individual elements

double& CMyVector::operator()(const unsigned &pos) {
	if (pos >= m_uiLength)
		throw std::overflow_error("CMyVector::operator()");
	return m_pVector[pos];
}

// Access the individual elements (const)

const double& CMyVector::operator()(const unsigned &pos) const {
	if (pos >= m_uiLength)
		throw std::overflow_error("CMyVector::operator() const");
	return m_pVector[pos];
}

// Get the number of rows of the vector

unsigned CMyVector::get_length() const {
	return m_uiLength;
}

