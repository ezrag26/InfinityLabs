#ifndef __WS9_LIB_H__
#define __WS9_LIB_H__

char *ItoaBase10(int value, char *str, int base);

int AtoiBase10(const char *str);

char *Itoa(int value, char *str, int base);

int Atoi(const char *str, int base);

void CharInFirst2(char *arr1, char *arr2, char *arr3);

int IsLittleEndian();

#endif /* __WS9_LIB_H__ */
