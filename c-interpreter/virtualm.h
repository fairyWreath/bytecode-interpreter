// backend virtual machine to run the code
// a chunk is handed to the virtual machine, and the vm runs the chunk of  code
// vm is stackbased

#ifndef virtualm_h
#define virtualm_h

#include "chunk.h"
#include "hasht.h"
#include "value.h"


#define STACK_MAX 256		

typedef struct
{
	Chunk* chunk;		// array of chunk code
	uint8_t* ip;		// to store location of the instruction currently being executed, a BYTE POINTER
	Value stack[STACK_MAX];			// stack array is 'indirectly' declared inline here
	Value* stackTop;			// pointer to the element just PAST the element containing the top value of the stack

	Obj* objects;		// pointer to the header of the Obj itself/node, start of the list
	Table globals;		// for storing global variables
	Table strings;		// for string interning, to make sure every equal string takes one memory
} VM;

// rseult that responds from the running VM
typedef enum
{
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;


void initVM();
void freeVM();

// interpret/run chunks and return enum
// changed from interpreting chunks to interpreting strings
InterpretResult interpret(const char* source);

extern VM vm;		// use extern, declare as global variable

// stack operations to determine order of value manipulations
void push(Value value);
Value pop();

#endif