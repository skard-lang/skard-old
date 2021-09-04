#ifndef CSKARD_VM_H
#define CSKARD_VM_H

#include "chunk.h"

#define CSKARD_STACK_MIN_SIZE 256

typedef struct
{
    size_t count;
    size_t capacity;
    Value *stack;
    Value *stackTop;
} Stack;

void initStack(Stack *stack);
void freeStack(Stack *stack);
void resetStack(Stack *stack);

typedef struct
{
    Chunk *chunk;
    uint8_t *ip;
} VM;

typedef enum
{
    INTERPRETER_OK,
    INTERPRETER_NOK_COMPILE,
    INTERPRETER_NOK_RUNTIME
} InterpreterResult;

void initVM(VM *vm);
void freeVM(VM *vm);

InterpreterResult interpret(VM *vm, Chunk *chunk);

#endif //CSKARD_VM_H
