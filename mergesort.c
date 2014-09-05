#include <stdio.h>
#include <stdlib.h>

void
merge(unsigned int start, unsigned int mid, unsigned int end, int *arr) {
    int *sorted;
    unsigned int i, j, k, l;
    unsigned int size;
    
    //get sum of sizes of two partitions
    size = end - start + 1;
    sorted = (int*) malloc (sizeof(int) * size);
    if(sorted == NULL) {
        printf("Failed to allocate memory. Exiting");
        exit(1);
    }
    // compare corresponding element of each array and 
    // copy smaller element to sorted array.
    i = start;
    j = mid + 1;
    k = 0;
    while(i <= mid && j <= end) {
         if(arr[i] <= arr[j]) {
             sorted[k++] = arr[i++];
         } else {
             sorted[k++] = arr[j++];
         }
    }

    while(i <= mid) {
        sorted[k++] = arr[i++];
    }

    while(j <= end) {
        sorted[k++] = arr[j++]; 
    }

    //copy sorted array back to original array
    l = 0;
    i = start;
    while(l < size) {
        arr[i++] = sorted[l++];
    }

    free(sorted);
}

void
mergesort(unsigned int start, unsigned int end, int *arr) {
//divide and conquer
    unsigned int mid;
    if(arr == NULL) return;
    if(start < end) {
        mid = ((end - start) / 2 ) + start;
        mergesort(start, mid, arr);
        mergesort(mid + 1, end, arr);
        merge(start, mid, end, arr);
    }
}

void
print_arr(int *arr, int size) {
    int i;
    if(arr == NULL) return;

    printf("\n ");
    for(i = 0; i < size; i++) {
        printf(" %d", arr[i]);
    }
    printf(" \n");
}

int
main(int argc, char *argv[]) {
    unsigned int size;
    int arr[] = {1, 5, 2, 3, 7, 4, 8, 6, 9, 0, -2, -6, -1, -99, 11, 45, -6};
    //int arr[] = {1};
    //int arr[] = {1, 0};
    size = sizeof(arr) / sizeof(int);
    printf("\n Size of arr = %d", size);

    print_arr(arr, size);

    mergesort(0, size - 1, arr);

    print_arr(arr, size);
    return 0;
}
