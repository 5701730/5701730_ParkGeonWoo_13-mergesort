#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 

int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수
int totalComparisons = 0;
int totalMoves = 0;
int isFirst = 0;         // 첫 번째 출력 여부 확인

// 랜덤생성
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 범위의 난수 생성
    }
}
//출력함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n"); // 10개씩 출력
    }
    printf("\n");
}

// 합병함수
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // 왼쪽 배열크기
    int n2 = right - mid;    // 오른쪽 배열크기

    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        moveCount++; 
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        moveCount++; 
    }

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        comparisonCount++; 
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        moveCount++;
        k++;
    }

    // 남은 원소 처리하는 반복문
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        moveCount++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        moveCount++;
    }

    
    free(L);
    free(R);
}

//반복적으로 구현(보너스)
void doMergeSort(int arr[], int size) {
    int rounds = 0; // 병합 호출 횟수

    for (int curr_size = 1; curr_size <= size - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < size - 1) ? (left_start + 2 * curr_size - 1) : (size - 1);

            merge(arr, left_start, mid, right_end);
            rounds++;

            if (rounds % 10 == 0&&isFirst==0) {
                
                for (int i = 0; i < 10; i++) {
                    printf("%3d ", arr[i]);
                }
                printf("| ");
                for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
                    printf("%3d ", arr[i]);
                }
                printf("\n\n");
            }
        }
    }
}



int main() {
    int array[SIZE];
    srand(time(NULL)); // 난수 초기화

    for (int i = 0; i < 20; i++) { // 20번 반복
        generateRandomArray(array); 
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) { // 첫 번째 실행부터 정렬과정을 보여주기위해
            printf("Merge Sort Run\n");
            doMergeSort(array,SIZE);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
