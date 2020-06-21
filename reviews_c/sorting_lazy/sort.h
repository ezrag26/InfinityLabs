/*******************************************************************************
*																			   *
*	DataStructures - Sorting Algorithms - Header							   *
*	Developer: Lazy Frid						  							   *
*	Reviewer: Ezra															   *
*	Status: S 15.10.2019													   *
*	Date: 07.10.2019														   *
*																			   *
*******************************************************************************/
#include <stddef.h>				/* size_t */

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

int *CountingSort(int *dest, const int *src, size_t size, int min, int max);

unsigned int *RadixSortFlex(unsigned int *dest, const unsigned int *src,
														size_t size, int base);

unsigned int *RadixSort2Powers(unsigned int *dest, const unsigned int *src,
											size_t size, unsigned int base_exp);

void MergeSort(int *dest, int *src, size_t size);

/**
 * @brief sort by heapifying array and picking the tops.
 * in-place, not-stable
 * 
 * @param arr prt to array start
 * @param size number of elements
 * @complexity O(nlog(n)): heapify in O(n) and sort in (nlog(n)) 
 */
void HeapSort(int *arr, size_t size);
