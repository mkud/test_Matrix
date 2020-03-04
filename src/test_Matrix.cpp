//============================================================================
// Name        : test_Matrix.cpp
// Author      : Maksim Kudimov
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CMyVector.h"
#include "CMyMatrix.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE( "CMyMatrix base", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test(3, 2, 	{1, 2,
							 4, 5,
							 7, 8}
	);
	// @formatter:on
	REQUIRE(test(2, 0) == 7);
}

TEST_CASE( "CMyMatrix transpose", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test(3, 2, 	{1, 2,
							 4, 5,
							 7, 8}
	);
	CMyMatrix goal(2, 3, 	{1, 4, 7,
							 2, 5, 8}
	);
	// @formatter:on
	REQUIRE(test.transpose() == goal);
}

TEST_CASE( "CMyMatrix::diag_vec", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test(3, 3, 	{1, 2, 3,
							 4, 5, 6,
							 7, 8, 9}
	);
	// @formatter:on
	CMyVector test1_vector = test.diag_vec();
	CMyVector test1_goal( { 1, 5, 9 });
	REQUIRE(test1_vector == test1_goal);
}

TEST_CASE( "Matrix multiplication", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test1(3, 3, 	{1, 2, -2,
							 4, 5, -1,
							-5, -3, 4}
	);
	CMyMatrix test2(3, 3, 	{4, 3, -2,
							 1, 2, -3,
							-1, -2, 4}
	);
	CMyMatrix test_goal(3, 3, 	{8, 11, -16,
								22, 24, -27,
								-27, -29, 35}
	);
	// @formatter:on
	REQUIRE(test_goal == (test1 * test2));
}

TEST_CASE( "Vector multiplication", "[CMyVector]" ) {
	CMyVector test1( { 1, 2, -3 });
	CMyVector test2( { 4, -5, 6 });
	REQUIRE(-24 == (test1 * test2));
}

TEST_CASE( "Matrix Vector multiplication", "[CMyMatrix*CMyVector]" ) {
	// @formatter:off
	CMyMatrix test1(3, 3, 	{1, 2, -2,
							 4, 5, -1,
							-5, -3, 4}
	);
	// @formatter:on
	CMyVector test2( { 4, 2, 1 });
	CMyVector test_goal( { 6, 25, -22 });
	REQUIRE(test_goal == (test1 * test2));
}

TEST_CASE( "Matrix determinant 2X2", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test1(2, 2, 	{1, 2,
							 4, 5}
	);
	// @formatter:on
	REQUIRE(-3 == test1.Determinant());
}

TEST_CASE( "Matrix determinant", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test1(3, 3, 	{1, 2, -2,
							 4, 5, -1,
							-5, -3, 4}
	);
	// @formatter:on
	REQUIRE(-31 == test1.Determinant());
}

TEST_CASE( "Matrix inversion", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test1(3, 3, 	{2, 5, 7,
							 6, 3, 4,
							 5, -2, -3}
	);
	CMyMatrix test_goal(3, 3, 	{1, -1, 1,
							 	 -38, 41, -34,
								 27, -29, 24}
	);
	// @formatter:on
	REQUIRE(test1.GetInverseMatrix().Near(test_goal, 0.0001));
}

TEST_CASE( "Matrix inversion2", "[CMyMatrix]" ) {
	// @formatter:off
	CMyMatrix test1(3, 3, 	{1, 2, -2,
							 4, 5, -1,
							-5, -3, 4}
	);
	CMyMatrix test_goal(3, 3, 	{-0.5484, 0.0645, -0.2581,
							 	 0.3548, 0.1935, 0.2258,
								 -0.4194, 0.2258, 0.0968}
	);
	// @formatter:on
	REQUIRE(test1.GetInverseMatrix().Near(test_goal, 0.0001));
}

