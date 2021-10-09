#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KB (1 << 10)
#define MB (1 << 20)
#define GB (1 << 30)
#define ARR_SIZE (256 * MB)
#define ARR_LENGTH (ARR_SIZE/sizeof(int))
#define NUM_STEPS (64 * 1024 * 1024)
#define NUM_LOOPS 20
#define STEP_SIZE 16

void testCacheLineSize();
void testCacheSize();
double cacheLineSizeLoopTimeInMs(int *arr, long arrLength, int stepSize);
double cacheSizeLoopTimeInMs(int *arr, long arrLength);


int main() {
    printf("Determining Cache Line Size...\n");
    testCacheLineSize();

    printf("\n\nDetermining Cache Size...\n");
    testCacheSize();
}

// varying step size
void testCacheLineSize() {
    int *arr = malloc(ARR_SIZE);

    printf("Step Size | Time Taken (ms)\n");
    for(int i = 1; i <= 1 << 10; i <<= 1) {
        double timeTotal = 0;
        for(int j = 0; j < NUM_LOOPS; j++) {
            timeTotal += cacheLineSizeLoopTimeInMs(arr, ARR_LENGTH, i);
        }
        printf("%9d | %10.2f\n", i, timeTotal/NUM_LOOPS);
    }
}

// varying array size
void testCacheSize() {
    printf("Array Size (Bytes) | Time Taken (ms)\n");
    for(int arrSize = KB; arrSize <= 4 * MB; arrSize <<= 1) {
        int *arr = malloc(arrSize);
        int arrLength = arrSize/sizeof(int);

        double totalTime = 0;
        for(int i = 0; i < NUM_LOOPS; i++) {
            totalTime += cacheSizeLoopTimeInMs(arr, arrLength);
        }
        printf("%11d        | %10.3f\n", arrSize, totalTime/NUM_LOOPS);

        free(arr);
    }
}

double cacheLineSizeLoopTimeInMs(int *arr, long arrLength, int stepSize) {
    clock_t start, end;

    start = clock();
    for(int i = 0; i < arrLength; i += stepSize) {
        arr[i]++;
    }
    end = clock();

    return ((double) end - start)/CLOCKS_PER_SEC * 1000;
}

double cacheSizeLoopTimeInMs(int *arr, long arrLength) {
    clock_t start, end;
    int lengthMod = arrLength - 1;

    start = clock();
    for(int j = 0; j < NUM_STEPS; j++) {
        // optimized way to say arr[(j * STEP_SIZE) % arrLength]++
        arr[(j * STEP_SIZE) & lengthMod]++;
    }
    end = clock();
    return ((double)(end - start))/CLOCKS_PER_SEC * 1e3;
}

