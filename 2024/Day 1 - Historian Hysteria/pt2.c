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

struct occurrence_counter{
    int key;
    int arr1_count;
    int arr2_count;
};

struct occurrence_counter *get_counts(int arr1[], int arr2[], int N, int *out_size){
    
    struct occurrence_counter *counter = malloc(N * sizeof(struct occurrence_counter));
    
    merge_sort(arr1, 0, N-1);
    merge_sort(arr2, 0, N-1);
    
    int j = 0;
    // Find occurrences in arr1
    for(int i = 0; i < N; i++){
        if(i == 0 || arr1[i] != arr1[i-1]){
            counter[j].key = arr1[i];
            counter[j].arr1_count = 1;
            counter[j].arr2_count = 0;
            ++j;
        }
        else{
            counter[j-1].arr1_count = counter[j-1].arr1_count + 1;
        }   
    }

    int ctr_size = j;

    // Find occurrences in arr2
    j = 0;
    for(int i = 0; i < N; i++){
        if (arr2[i] == counter[j].key){
            counter[j].arr2_count++;
        }
        // always looking at smallest unseen num in arr2, if bigger, 
        // time to check next counter key against same number
        else if((arr2[i] > counter[j].key) && (j < ctr_size)){
            j++;
            i--;
        // always looking at smallest unseen num in arr2, if smaller, 
        // time to check next against same counter key.
        }else if (arr2[i] < counter[j].key){
            continue;
        }
    }

    *out_size = ctr_size;
    return counter;
}

int compute_and_sum_similarity(struct occurrence_counter *counter, int N){
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum += counter[i].key * counter[i].arr1_count * counter[i].arr2_count;
    }
    return sum;
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
    int arrLen = N[0]-1; //N is modified to the final size of the arrays

    int counter_out_size;
    struct occurrence_counter *counter = get_counts(arr1, arr2, N[0], &counter_out_size);
    int sum = compute_and_sum_similarity(counter, counter_out_size);

    printf("Pt 2 Answer: %d", sum);

    
    return 0;
}
