#include <stdio.h>
#include <stdlib.h>

void getArray(int*, size_t);
void printArray(const int*, size_t);
void insertionSort(int*, int);
void intError(char*, int*, size_t);

int main(void) {
    char buffer[10];
    int size;

    fprintf(stdout, "Enter the size of the array: ");
    intError(buffer, &size, 10);

    if (size <= 0) {
        errno = 1;
        perror("size can't be negative or zero");
        return 1;
    }
    int* arr = malloc(size * sizeof(int));

    if (!arr) {
        perror("Memory Allocation Failed");
        return 1;
    }

    getArray(arr, size);
    insertionSort(arr, size);
    printArray(arr, size);

    free(arr);

    return 0;
}

void getArray(int* arr, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        fprintf(stdout, "arr[%zu] = ", i);
        char buffer[10];
        intError(buffer, &arr[i], 10);
    }
}

void printArray(const int* arr, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        fprintf(stdout,"%d ", *(arr + i));
    }
}

void insertionSort(int* arr,const int n) {
    for (size_t i = 1; i < n; i++) {
        int const key = arr[i];
        int j = (int)i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void intError(char* buffer, int* temp, const size_t n) {
    char* endPointer;

    if (!fgets(buffer, (int)n, stdin)) {
        perror("Input Error");
        exit(1);
    }

    errno = 0;
    const long temp_val = strtol(buffer, &endPointer, 10);

    if (buffer == endPointer) {
        fprintf(stderr, "Invalid input: No digits found\n");
        exit(1);
    }

    if (*endPointer == '.' || *endPointer == 'e' || *endPointer == 'E') {
        fprintf(stderr, "Invalid input: Float detected\n");
        exit(1);
    }

    *temp = (int)temp_val;
}
