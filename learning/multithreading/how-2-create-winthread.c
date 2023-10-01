#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// The function to be passed to the created thread
DWORD WINAPI thread_body(LPVOID lpParam) {
    printf("Hello from first thread!\n");
    return 0;
}

int main(void) {
    // The thread to be created
    HANDLE thread;
    // A variable, to have the thread ID passed to it
    DWORD threadId;

    thread = CreateThread(NULL, 0, thread_body, (void*)NULL, 0, &threadId);

    if (thread == NULL) {
        printf("Error: thread could not be created.\n");
        exit(EXIT_FAILURE);
    }

    // Waits for the thread to execute
    DWORD waitReturn = WaitForSingleObject(thread, INFINITE);

    if (waitReturn == WAIT_TIMEOUT || waitReturn == WAIT_FAILED) {
        printf("Something went wrong with the thread and it didn't manage to enter signaled state, or the function coming.\n");
        exit(EXIT_FAILURE);
    }

    CloseHandle(thread);

    return 0;
}