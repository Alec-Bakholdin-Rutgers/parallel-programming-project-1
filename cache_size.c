#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MB 1024 * 1024

int doSomething(int dataSizeMb, long numLoops, int cacheSize){
    long bufferSize = dataSizeMb * MB;
    volatile int * buffer;
    buffer = (int*) malloc (bufferSize);
    for(long k = 0; k < numLoops; k++){
        for  (long i = 0; i < bufferSize/sizeof(int); i += cacheSize) {
            buffer[i] = buffer[i];
        }
    }
}

int main(int argc, char** argv) {
    if(argc < 4) {
        printf("Invalid number of arguments: %d\n", argc);
        return 0;
    }

    int dataSizeMb = atoi(argv[1]);
    int numLoops = atoi(argv[2]);
    int cacheSize = atoi(argv[3]);

    clock_t start, end;
    start = clock();
    doSomething(dataSizeMb, numLoops, cacheSize);
    end = clock();
    printf("Time taken: %f seconds\n", ((double)(end - start))/CLOCKS_PER_SEC);
}