#include <stdio.h>

extern void bubble_sort(int *numbers, int lines, FILE *fptr);

extern void selection_sort(int *numbers, int lines, FILE *fptr);

extern void merge_sort(int *numbers, int lines, FILE *fptr);
extern void merge_sort_recursion(int a[], int left, int right);
extern void merge_sorted_arrays(int a[], int left, int middle, int right);