#include <stdio.h>
#include <assert.h>

#define NON_REC 0

#ifdef NON_REC 
    #define MAX_HEAPIFY(ARR, LEN, INDEX) max_heapify_nonrec(ARR, LEN, INDEX)
#else 
    #define MAX_HEAPIFY(ARR, LEN, INDEX) max_heapify(ARR, LEN, INDEX)
#endif

void
max_heapify_nonrec(int arr[], int length, int index) {

    int l, r, temp, largest, isSwapped = 1;


    while(index < length && isSwapped) {

        isSwapped = 0;
        l = index * 2;
        r = l + 1;
        
        largest = index;
        if(l <= length && arr[l] > arr[largest]) {
            largest = l;
        }

        if(r <= length && arr[r] > arr[largest]) {
            largest = r;
        }

        if(largest != index) {
            temp = arr[largest];
            arr[largest] = arr[index];
            arr[index] = temp;
            index = largest;
            isSwapped = 1;
        }
    }
}

void
max_heapify(int arr[], int length, int index) {
    int l, r, largest, temp;
    
    if(index >= length) return;

    l = 2*index;
    r = l + 1;

//find largest element
    largest = index; //assume
    if(l <= length && arr[l] > arr[largest]) {
        largest = l;
    }
    
    if(r <= length && arr[r] > arr[largest]) {
        largest = r;
    }

    if(largest != index) {

        temp = arr[largest];
        arr[largest] = arr[index];
        arr[index] = temp;
        max_heapify(arr, length, largest);
        //element at 'index' position is now at 'largest' position.
        //call heapify on that element.
    }

}

void
build_max_heap(int arr[], int length) {
    int i;

    for(i = length /2; i >= 1; i--) {
        MAX_HEAPIFY(arr, length, i);
    }
}

void
print_heap(int arr[], int length, int iter) {
    
    int i;
    printf("\n iter = %d | ", iter);
    for(i = 1; i <= length; i++) {
        printf(" %d,", arr[i]);
    }
}

/*
 Arr is 1-indexed array
*/
void
heapsort(int arr[], int length) {
    int i, temp;
//build max-heap
    build_max_heap(arr, length);

    print_heap(arr, length, 0);
    for(i = length; i > 1; i--) {
        //replace root with last element.
        temp = arr[1];
        arr[1] = arr[i];
        arr[i] = temp;
        
        MAX_HEAPIFY(arr, i - 1, 1);
        print_heap(arr, length, i);
    } 

}

void
test_order_ascending(int arr[], int length) {

    int i;
    for(i = 1; i < length; i++) {
        assert(arr[i] <= arr[i+1]);
    }
}

int
main(int argc, char **argv) {
    int arr[] = {0, 2, 1, 3, 0};
    int size  = 4;
    int i;
    heapsort(arr, size);
    test_order_ascending(arr, size);
    printf("\n Heapsort =");
    print_heap(arr, size, 0);
    
    int arr1[] = {0, 5, 2, 5, 1, 6, 1, 89 , 44 , -1};
    size= (sizeof arr1 / sizeof *arr1) - 1;
    heapsort(arr1, size);
    test_order_ascending(arr1, size); 
    printf("\n Heapsort =");
    print_heap(arr1, size, 0);
    
    int arr2[] = {0, 100, -999, 0, 12, 4323, -3254, 3, 53, 45, 23, 324, 324, 54};
    size= (sizeof arr2 / sizeof *arr2) - 1;
    heapsort(arr2, size);
    test_order_ascending(arr2, size); 
    printf("\n Heapsort =");
    print_heap(arr2, size, 0);
}

