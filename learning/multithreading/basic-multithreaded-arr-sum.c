#include <windows.h>
#include <wchar.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 6

struct ThreadData {
    int localThreadNum;
    int totalArrLen;
    int totalNumThreads;
    int** ptrToPartialSumArr;
};

void initNumArr(int** numArray, int* arrSize);
void determineNumThreads(int numArrSize, int* numThreads);
void prepThreads(HANDLE** threadArray, struct ThreadData** dataStructs);
DWORD WINAPI sumFunction(LPVOID lpParam);

int main(void) {

    //int finalSum = 0;
    int* numArray;
    int numArrSize = 0;

    int* partialSums;
    int partialSumArrSize = 0;

    int numThreads = 0;
    HANDLE* threadArray;
    struct ThreadData* dataStructs;

    initNumArr(&numArray, &numArrSize);
    
    determineNumThreads(numArrSize, &numThreads);

    partialSumArrSize = numThreads;
    partialSums = malloc(partialSumArrSize * sizeof(int));

    dataStructs = malloc(numThreads * sizeof(*dataStructs));

    for (int i=0; i < numThreads; i++) {
        dataStructs[i].totalArrLen = numArrSize;
        dataStructs[i].totalNumThreads = numThreads;
        dataStructs[i].ptrToPartialSumArr = &partialSums;
    }

    prepThreads(&threadArray, &dataStructs);

    WaitForMultipleObjects(numThreads, threadArray, TRUE, INFINITE);

    for (int i=0; i < numThreads; i++) {
        CloseHandle(threadArray[i]);
    }

    free(numArray);
    free(partialSums);
    free(threadArray);
    free(dataStructs);

    return 0;
}

void initNumArr(int** numArray, int* arrSize) {
    char input[MAX_INPUT_LEN];
    int numToAdd = 0;

    printf("Please enter how many elements you'd like the array to contain.\n"
        "Please note that the number you input can be up to 5 numbers in length: "
    );
    fgets(input, MAX_INPUT_LEN, stdin);
    sscanf(input, "%d", arrSize);
    *numArray = malloc(*arrSize * sizeof(**numArray));

    printf("\nPlease now enter the numbers for your array.\n"
        "Please note that the numbers you input can be up to 5 digits in length.\n"
    );

    for (int i=0; i < *arrSize; i++) {
        printf("Number %d: ", i+1);
        fgets(input, MAX_INPUT_LEN, stdin);
        sscanf(input, "%d", &numToAdd);
        (*numArray)[i] = numToAdd;
    }
}

void determineNumThreads(int numArrSize, int* numThreads) {
    char input[MAX_INPUT_LEN];
    if (numArrSize < 11) {
        printf("Array is small so no threads will be created.\n");
        return;
    }

    printf("How many threads would you like to create?\n"
        "Please note that, because the array is %d elements long, "
        "the maximum allowable input will be %d and the minimum is 2.\n", numArrSize, (numArrSize-1)
    );
    while (*numThreads <= 1 || *numThreads >= numArrSize) {
        fgets(input, MAX_INPUT_LEN, stdin);
        sscanf(input, "%d", numThreads);
    }
}

void prepThreads(HANDLE** threadArray, struct ThreadData** dataStructs) {
    int numThreads = dataStructs[0]->totalNumThreads;
    *threadArray = malloc(numThreads * sizeof(**threadArray));

    for (int i=0; i < numThreads; i++) {
        dataStructs[i]->localThreadNum = i;
        (*threadArray)[i] = CreateThread(NULL, 0, sumFunction, dataStructs[i], 0, NULL);
    }
}

DWORD WINAPI sumFunction(LPVOID lpParam) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    TCHAR strBuf[64];
    size_t strSize;
    DWORD chars;

    if (out == INVALID_HANDLE_VALUE) return 1;

    struct ThreadData localData = *(struct ThreadData*)lpParam;
    StringCchPrintf(strBuf, 64, TEXT("Local thread ID: %d\n"
                                     "Total num threads: %d\n"
                                     "Arr length: %d\n"), localData.localThreadNum, localData.totalNumThreads, localData.totalArrLen);
    StringCchLength(strBuf, 64, &strSize);
    WriteConsole(out, strBuf, (DWORD)strSize, &chars, NULL);

    return 0;
}