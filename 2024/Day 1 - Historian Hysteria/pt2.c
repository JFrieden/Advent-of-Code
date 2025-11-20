#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Test Comment
#define MAX_LINES 1000
#define MAX_LINE_LEN 50

/* ----------------------------- Input Helpers ----------------------------- */
/**
 * @brief Reads in a file a returns a pointer to the addresses of the arrays.
 * 
 * @param filename 
 * @return int** a pointer to the pointer that holds the first list, colocated next to the pointer for the pointer that has the second list.
*/
void read_input(char* filename, int *arr1, int *arr2, int *i){
    FILE* file = fopen(filename, "r");
    char line[MAX_LINE_LEN];

    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    i[0] = 0;
    while(fgets(line, MAX_LINE_LEN, file) != NULL){
        // printf("%s", line);  
        // put the first number of the line in arr1, put the second number of the line in arr2
        sscanf(line, "%d %d", &arr1[i[0]], &arr2[i[0]]);
        i[0]++; 
    }

    fclose(file);
}

/* ------------------------------------------------------------------------- */
/* ------------------------------- Solution -------------------------------- */
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int* element_wise_abs_diff(int* arr1, int* arr2, const int n){
    int *ret_arr = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        ret_arr[i] = abs(arr1[i] - arr2[i]);
    }
    return ret_arr;
}

/* ------------------------------------------------------------------------- */
/* --------------------------------- Tests --------------------------------- */



/* ------------------------------------------------------------------------- */
/* --------------------------------- Main ---------------------------------- */
int main() {
    int arr1[MAX_LINES];
    int arr2[MAX_LINES];
    int N[1] = {0};

    read_input("input.txt", arr1, arr2, N);

    // printf("N: %d\n", N[0]);
    // printf("Arr 1: ");
    // for(int i = 0; i < N[0]; i++){
    //     printf("%d ", arr1[i]);
    // }
    // printf("\n");
    // printf("Arr 2: ");
    // for(int i = 0; i < N[0]; i++){
    //     printf("%d ", arr2[i]);
    // }
    // printf("\n");

    int arrLen = N[0]-1;
    merge_sort(arr1, 0, arrLen);
    merge_sort(arr2, 0, arrLen);

    // printf("Sorted Arr 1: ");
    // for(int i = 0; i < N[0]; i++){
    //     printf("%d ", arr1[i]);
    //     }
    // printf("\n");
    // printf("Sorted Arr 2: ");
    // for(int i = 0; i < N[0]; i++){
    //     printf("%d ", arr2[i]);
    //     }
    // printf("\n");


    int *dists = element_wise_abs_diff(arr1, arr2, N[0]);
    int total_dist = 0;
    for (int i = 0; i < N[0]; i++) {
        total_dist += dists[i];
    }

    printf("Pt 1 Answer: %d", total_dist);

    
    return 0;
}
