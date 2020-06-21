/*******************************************************************************
*																			   *
*	DataStructurs - Fibonacci												   *
*	Developer: Naama Amir												   	   *
*	Reviwer: 																   *
*																			   *
*******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "fibonacci.h"

size_t IterFibonacci(size_t n)
{
	size_t i = 0;
	size_t prev = 1;
	size_t result = 0;

	for (i = 0; i < n; ++i)
	{
		result = prev + result;
		prev = result - prev;
	}

	return result;
}

size_t RecFibonacci(size_t n)
{
	switch (n)
	{
		case (0):
			return 0;
		case (1):
			return 1;
		default:
			return (RecFibonacci(n - 1) + RecFibonacci(n - 2));
	}
}
