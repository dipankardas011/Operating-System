#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>

#define BLACKHOLE NULL // for readable purpose

/**
 * For the header
 */
struct __Stack
{
    void *data_ptr;
    struct __Stack *next;
};

struct __StackHeaders
{
    struct __Stack *topPtr;
};

// Before operating call this function
struct __StackHeaders *initKStack()
{
    struct __StackHeaders *tempK =
        (struct __StackHeaders *)malloc(sizeof(struct __StackHeaders));
    assert(tempK != BLACKHOLE);
    tempK->topPtr = BLACKHOLE;
    return tempK;
}
/**
 * TODO: to be filled
 */
// before forgetting about the pointer
struct __StackHeaders *remKStack(struct __StackHeaders *TOPKPTR)
{
    // using traditional loop for removal
    struct __Stack *temp = TOPKPTR->topPtr;
    struct __Stack *freer = BLACKHOLE;
    while (temp != BLACKHOLE) {
        freer = temp;
        temp = temp->next;
        free(freer);
    }
    TOPKPTR->topPtr = BLACKHOLE;
    temp = BLACKHOLE;
    freer = BLACKHOLE;
    free(TOPKPTR);
    return BLACKHOLE;
}
/**
 * TODO: to be filled
 */
/**
 * @param TOPKPTR it takes pointer for the head of the stack
 * @param iData it takes the insert data to be inserted
 * @return 1 means success 0 means failure
 */
int __push_top(struct __StackHeaders **TOPKPTR, void *iData)
{
    struct __Stack *front = (struct __Stack *)malloc(sizeof(struct __Stack));
    assert(front);
    front->data_ptr = iData;
    // front->next = BLACKHOLE;
    front->next = (*TOPKPTR)->topPtr;
    (*TOPKPTR)->topPtr = front;

    assert((*TOPKPTR)->topPtr->data_ptr == iData);
    return 1;
}
/**
 * TODO: to be filled
 */
void *__pop_top(struct __StackHeaders **TOPKPTR)
{

    if ((*TOPKPTR)->topPtr == BLACKHOLE)
        return BLACKHOLE;

    struct __Stack *freer = (*TOPKPTR)->topPtr;
    (*TOPKPTR)->topPtr = (*TOPKPTR)->topPtr->next;

    void *ret = freer->data_ptr;
    free(freer);
    return ret;
}
/**
 * TODO: to be filled
 */
inline void *__peek_top(struct __StackHeaders **TOPKPTR)
{

    if ((*TOPKPTR)->topPtr == BLACKHOLE)
        return BLACKHOLE;

    return ((*TOPKPTR)->topPtr->data_ptr);
}