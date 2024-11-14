#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cfunctions.h"

clock_t t;

int main(int argc, char *argv[])
{
    // Check if we enter 2 arrgs
    if (argc != 2)
    {
        printf("Format: \"./program filename.txt\"\n");
        return 1;
    }

    // Create File pointer and asign the the value of our filename.txt arguement
    FILE *fptr;
    fptr = fopen(argv[1], "r");

    // Copy the file values to the array (keeping track of the amount of elements we entered with the lines value) of numbers then close the file
    int numbers[50000]; // Max value of 50000
    int fnum = 0;
    int lines = 0;
    while (fscanf(fptr, "%d", &fnum) != EOF)
    {
        numbers[lines] = fnum;
        lines++;
    }
    fclose(fptr);

    // Choose sorting method
    int userChoice = 0;
    printf("Sorting method to use... \n1 - Bubble Sort\n2 - Selection Sort\n3 - Merge Sort\n");
    scanf("%d", &userChoice);
    switch (userChoice)
    {
    case 1:
        t = clock();
        bubble_sort(numbers, lines, fptr);
        t = clock() - t;
        printf("Time taken with Bubble Sort method: %f seconds\n", ((double)t) / CLOCKS_PER_SEC);
        break;
    case 2:
        t = clock();
        selection_sort(numbers, lines, fptr);
        t = clock() - t;
        printf("Time taken with Selection Sort method: %f seconds\n", ((double)t) / CLOCKS_PER_SEC);
        break;
    case 3:
        t = clock();
        merge_sort(numbers, lines, fptr);
        t = clock() - t;
        printf("Time taken with Selection Sort method: %f seconds\n", ((double)t) / CLOCKS_PER_SEC);
        break;
    default:
        printf("Pick and option\n");
        return 2;
    }

    return 0;
}

void merge_sort(int *numbers, int lines, FILE *fptr)
{
    
    merge_sort_recursion(numbers, 0, lines - 1);

    fptr = fopen("/home/mochi/Dropbox/Code/new/_sortingalgorthims/outputs/merge_sort_output.txt", "w");
    for (int i = 0; i < lines; i++)
        fprintf(fptr, "%d\n", numbers[i]);
    fclose(fptr);
}

void merge_sorted_arrays(int a[], int left, int middle, int right)
{
    int left_length = middle - left + 1; // Gathers the length of the left, left = START of the left of the array, right = END of the right of the array, middle = the MIDDLE of the array
    int right_length = right - middle; // Gathers the length of the right of the array. Remember that right is the END of the right side of the array.

    int temp_left[left_length];
    int temp_right[right_length];

    int i, j, k;

    for (int i = 0; i < left_length; i++) // copying the values of the left side into a temporary array
        temp_left[i] = a[left + i]; // only gathering the left portion

    for (int i = 0; i < right_length; i++) // copying the values of the right side into a temporary array
        temp_right[i] = a[middle + 1 + i]; // only gathering from right portion (which starts at middle)

    // k is used to index the ACTUAL array were sorting a[]. Were starting k at left most side and up until right most side
    // i keeps track of index of the temporary left array, and j keeps track of the index of temporary right array
    for (i = 0, j = 0, k = left; k <= right; k++) 
    {
        if ((i < left_length) &&  // this means the left array is all used so the remaining right array can be added to the final array
            (j >= right_length || // this means we've reached the end of the temp right array (meaning the final arrray HAS to be sorted)
            temp_left[i] <= temp_right[j])) // OR this is checking which element is the smaller one of the right and left temporary arrays
        {
            a[k] = temp_left[i]; // this case if the ith element of the left array is SMALLER OR EQUAL to the jth element of the right array
            i++;
        }
        else
        {
            a[k] = temp_right[j]; // this case if the ith element of the left array is larger to the jth element of the right array
            j++;
        }
    }
}

void merge_sort_recursion(int a[], int left, int right)
{
    if (left < right) // Base case of the recursion. As long as left is less or equal, continue to divide and use recursion
    {
        int middle = left + (right - left) / 2; // gather the middle value (remember left starts at 0)

        merge_sort_recursion(a, left, middle); // Call recursion with indexes defining the left portion of the array
        merge_sort_recursion(a, middle + 1, right); // Call recursion with indexes defining the right portion of the array

        merge_sorted_arrays(a, left, middle, right);
    }
}



void selection_sort(int *numbers, int lines, FILE *fptr)
{
    int small;
    int indexCopy;
    for (int i = 0; i < lines - 1; i++)
    {
        small = 0;
        for (int j = i; j < lines; j++)
        {
            if (small == 0)
                small = numbers[j];
            if (small > numbers[j])
            {
                small = numbers[j];
                indexCopy = j;
            }
        }
        numbers[indexCopy] = numbers[i];
        numbers[i] = small;
    }

    fptr = fopen("/home/mochi/Dropbox/Code/new/_sortingalgorthims/outputs/selection_sort_output.txt", "w");
    for (int i = 0; i < lines; i++)
        fprintf(fptr, "%d\n", numbers[i]);
    fclose(fptr);
}


void bubble_sort(int *numbers, int lines, FILE *fptr)
{
    int swap = -1;           // Swap number allows to keep track of the amount of times we had to swap two elements
    int compare = lines - 1; // compare will allow us to later lessen the amount of comparison loops.

    for (int i = 0; i < lines - 1; i++) // Iterate through the length of the number array (lines - 1 because those are the indices of the array)
    {
        int x = 0; // x and y will represent the positions of the elements being compared
        int y = 1;

        if (swap == 0) // If we reach this point and made 0 swaps we can exit knowing each element is sorted
            break;

        swap = 0; // Reset swap to 0
        for (int j = 0; j < compare; j++)
        {
            if (numbers[x] > numbers[y]) // If the the element on the left is greater then swap them, else dont and continue
            {
                int tempX = numbers[x];
                numbers[x] = numbers[y];
                numbers[y] = tempX;
                swap++;
            }
            x++; // ++ x and y to check the next 2 elements in the number array
            y++;
        }
        compare--; // After bubbling the first element to the top, subtract the amount of elements we iterate by 1
    }

    fptr = fopen("/home/mochi/Dropbox/Code/new/_sortingalgorthims/outputs/bubble_sort_output.txt", "w");
    for (int i = 0; i < lines; i++)
        fprintf(fptr, "%d\n", numbers[i]);
    fclose(fptr);
}
