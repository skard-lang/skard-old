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
    stack->stack = CSKARD_GROW_ARRAY(Value, NULL, 0, CSKARD_STACK_MIN_SIZE);
    stack->stackTop = stack->stack;
}

void freeStack(Stack *stack)
{
    CSKARD_FREE_ARRAY(Value, stack->stack, stack->capacity);
    stack->capacity = 0;
    stack->stack = NULL;
    stack->stackTop = NULL;
}

void pushStack(Stack *stack, Value value)
{
    size_t offset = stack->stackTop - stack->stack;
    if (offset == stack->capacity)
    {
        size_t oldCapacity = stack->capacity;
        stack->capacity = CSKARD_GROW_CAPACITY(oldCapacity);
        stack->stack = CSKARD_GROW_ARRAY(Value, stack->stack, oldCapacity, stack->capacity);
        stack->stackTop = stack->stack + offset;
    }

    *stack->stackTop = value;
    stack->stackTop++;
}

Value popStack(Stack *stack)
{
    stack->stackTop--;
    return *stack->stackTop;
}


void initVM(VM *vm)
{
    initStack(&vm->stack);
}

void freeVM(VM *vm)
{
    freeStack(&vm->stack);
}

static InterpreterResult run(VM *vm)
{
    while (true)
    {
#ifdef CSKARD_DEBUG_TRACE_EXECUTION
        printSpaces(16);
        printf("STACK CAPACITY: %zu\n", vm->stack.capacity);
        printSpaces(16);
        printf("STACK OFFSET: %zu\n", vm->stack.stackTop - vm->stack.stack);
        printSpaces(16);
        for (Value *slot = vm->stack.stack; slot < vm->stack.stackTop; slot++)
        {
            printValue(*slot);
        }
        printf("\n");
        disassembleInstruction(vm->chunk, vm->ip - vm->chunk->code);
#endif

        uint8_t instruction;
        Value constant;
        Value operand;
        switch (instruction = CSKARD_READ_BYTE())
        {
            case OP_RETURN:
                printValue(popStack(&vm->stack));
                printf("\n");
                return INTERPRETER_OK;
            case OP_CONSTANT:
                constant = CSKARD_READ_CONSTANT();
                pushStack(&vm->stack, constant);
                break;
            case OP_CONSTANT_LONG:
                constant = CSKARD_READ_CONSTANT_LONG();
                pushStack(&vm->stack, constant);
                break;

            case OP_NEGATE_INT:
                (vm->stack.stackTop - 1)->as.sk_int = -((vm->stack.stackTop - 1)->as.sk_int);
                break;
            case OP_ADD_INT:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_int = (vm->stack.stackTop - 1)->as.sk_int + operand.as.sk_int;
                break;
            case OP_SUBTRACT_INT:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_int = (vm->stack.stackTop - 1)->as.sk_int - operand.as.sk_int;
                break;
            case OP_MULTIPLY_INT:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_int = (vm->stack.stackTop - 1)->as.sk_int * operand.as.sk_int;
                break;
            case OP_DIVIDE_INT:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_int = (vm->stack.stackTop - 1)->as.sk_int / operand.as.sk_int;
                break;

            case OP_NEGATE_REAL:
                (vm->stack.stackTop - 1)->as.sk_real = -((vm->stack.stackTop - 1)->as.sk_real);
                break;
            case OP_ADD_REAL:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_real = (vm->stack.stackTop - 1)->as.sk_real + operand.as.sk_real;
                break;
            case OP_SUBTRACT_REAL:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_real = (vm->stack.stackTop - 1)->as.sk_real - operand.as.sk_real;
                break;
            case OP_MULTIPLY_REAL:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_real = (vm->stack.stackTop - 1)->as.sk_real * operand.as.sk_real;
                break;
            case OP_DIVIDE_REAL:
                operand = popStack(&vm->stack);
                (vm->stack.stackTop - 1)->as.sk_real = (vm->stack.stackTop - 1)->as.sk_real / operand.as.sk_real;
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
