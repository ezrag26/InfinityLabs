#ifndef __OL73_DS_BIT_ARRAY_H__
#define __OL73_DS_BIT_ARRAY_H__

#include <stddef.h> /* size_t */

#include "utils.h"

typedef unsigned long bit_arr_t;

/*
 * Set all the bits in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 */
bit_arr_t BitArrSetAllOn(bit_arr_t b);

/*
 * Unset all the bits in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 */
bit_arr_t BitArrSetAllOff(bit_arr_t b);

/*
 * Set a specific bit in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 */
bit_arr_t BitArrSetOn(bit_arr_t b, size_t index);

/*
 * Unset a specific bit in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 */
bit_arr_t BitArrSetOff(bit_arr_t b, size_t index);

/*
 * Set or unset a specific bit in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 * Values for value: 0 represents to unset, 1 represents to set
 */
bit_arr_t BitArrSetBit(bit_arr_t b, size_t index, int value);

/*
 * Flip a specific bit in the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 */
bit_arr_t BitArrFlipBit(bit_arr_t b, size_t index);

/*
 * Mirror the bit array
 * Return Value: new bit array
 * Complexity: O(1)
 */
bit_arr_t BitArrMirror(bit_arr_t b);

bit_arr_t BitArrMirrorLUT(bit_arr_t b);

/*
 * Check if a specific bit is set
 * Return Value: 1 if bit is set, 0 if bit is unset
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 */
int BitArrIsOn(bit_arr_t b, size_t index);

/*
 * Check if a specific bit is unset
 * Return Value: 1 if bit is unset, 1 if bit is unset
 * Complexity: O(1)
 * Values for index: 0 through size of size_t in bits -1
 */
int BitArrIsOff(bit_arr_t b, size_t index);

/*
 * Count total bits set in the bit array
 * Return Value: Total number of set bits in the bit array
 * Complexity: O(1)
 */
size_t BitArrCountOn(bit_arr_t b);

size_t BitArrCountOnLUT(bit_arr_t b);

/*
 * Count total bits unset in the bit array
 * Return Value: Total number of unset bits in the bit array
 * Complexity: O(1)
 */
size_t BitArrCountOff(bit_arr_t b);

/*
 * Rotate bit array n times to the right
 * Return Value: new bit array
 * Complexity: O(1)
 * n: number of rotations
 * Value for n: any positive value. Any number above size of size_t in bits -1
 * 				will take remainder of n divided by size of size_t in bits
 */
bit_arr_t BitArrRotateRight(bit_arr_t b, size_t n);

/*
 * Rotate bit array n times to the left
 * Return Value: new bit array
 * Complexity: O(1)
 * Value for n: any positive value. Any number above size of size_t in bits -1
 * 				will take remainder of n divided by size of size_t in bits
 */
bit_arr_t BitArrRotateLeft(bit_arr_t b, size_t n);

/*
 * Print the bit array as a string of the binary number to dest
 * Return Value: Pointer to string
 * Complexity: O(n)
 * dest should be large enough to fit size of size_t * 8 bytes
 */
char *BitArrToString(bit_arr_t b, char *dest);

#endif /* __OL73_DS_BIT_ARRAY_H__ */
