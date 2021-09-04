#include "vm.h"

#include <stdbool.h>
#include <stdio.h>

#include "debug.h"
#include "memory.h"

#define CSKARD_READ_BYTE() (*vm->ip++)
#define CSKARD_READ_CONSTANT() (vm->chunk->constants.values[CSKARD_READ_BYTE()])
#define CSKARD_READ_CONSTANT_LONG() \
    (vm->chunk->constants.values[(vm->ip += 3, (vm->ip[-3]) | (vm->ip[-2]) << 8 | (vm->ip[-1]) << 16)])


void initStack(Stack *stack)
{
    stack->capacity = CSKARD_STACK_MIN_SIZE;
    stack->count = 0;
    stack->stack = CSKARD_GROW_ARRAY(Value, NULL, 0, CSKARD_STACK_MIN_SIZE);
    stack->stackTop = stack->stack;
}

void freeStack(Stack *stack)
{

}

void resetStack(Stack *stack)
{
    stack->stackTop = stack->stack;
}

void initVM(VM *vm)
{

}

void freeVM(VM *vm)
{

}

static InterpreterResult run(VM *vm)
{
    while (true)
    {
#ifdef CSKARD_DEBUG_TRACE_EXECUTION
        disassembleInstruction(vm->chunk, vm->ip - vm->chunk->code);
#endif

        uint8_t instruction;
        Value constant;
        switch (instruction = CSKARD_READ_BYTE())
        {
            case OP_RETURN:
                return INTERPRETER_OK;
            case OP_CONSTANT:
                constant = CSKARD_READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            case OP_CONSTANT_LONG:
                constant = CSKARD_READ_CONSTANT_LONG();
                printValue(constant);
                printf("\n");
                break;
        }
    }
}

InterpreterResult interpret(VM *vm, Chunk *chunk)
{
    vm->chunk = chunk;
    vm->ip = vm->chunk->code;
    return run(vm);
}
