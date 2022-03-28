/**
 * implementation for the stack
 */

#include <stdio.h>
#include "../lib/kstack.h"

typedef enum boolean
{
    False,
    True
} bool;

struct mmy
{
    int data;
};

bool Test_MakeUpStack(struct __StackHeaders **ptr)
{
    struct mmy **arr = (struct mmy **)malloc(sizeof(struct mmy *) * 2);
    for (int i = 0; i < 2; i++)
        arr[i] = (struct mmy *)malloc(sizeof(struct mmy) * 5);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++)
            arr[i][j].data = (i + 1) * (j + 1);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++)
            printf("%d ", arr[i][j].data);
        printf("\n");
    }

    // adding cargo
    for (int i = 0; i < 2; i++) {
        int rc = __push_top(ptr, arr[i]);
        if (rc != 1) {
            fprintf(stderr, "Error!!\n");
            free(arr);
            return False;
        }
    }

    for (int i = 0; i < 2; i++) {
        struct mmy *rc = (struct mmy *)__pop_top(ptr);

        for (int j = 0; j < 5; j++) {
            if (rc[j].data == arr[2 - 1 - i][j].data) {
                printf("%d ?= %d\n", rc[j].data, arr[2 - 1 - i][j].data);
                //  for the verbose
            } else {
                free(arr);
                *ptr = remKStack((*ptr));
                return False;
            }
        }
    }

    *ptr = remKStack(*ptr);
    return True;
}

int main(int argc, char const *argv[])
{
    struct __StackHeaders *mainStkPtr = initKStack();
    Test_MakeUpStack(&mainStkPtr);

    return 0;
}
