#ifndef KNX_INTERPRETER
#define KNX_INTERPRETER

#include "State.h"
#include "KNX.h"
#include <string.h>
#include "Node.h"

typedef struct state _state_;
typedef struct node _node_;

typedef enum {
noLogic,
ifFailure//allows immediate 'else' if set
}logicState;

typedef struct
{
_state_*st;
_node_*nd;
database*local;
database*global;


//states
bool pending;
bool waitExprss;//
bool waitLn;// backslash
bool litOp;//"
int listOp;//()
int blockOp;//{}
int brackOp;//[]
//buffers
char*buffer;//block buffer
unsigned buffSize;
//tokenized sequence
//Persists until cleared or executed
token**stream;
unsigned streamLength;

}interpreter;

interpreter*genInterpreter(_state_ *,_node_ *);

//simply allows multiple returns from the execute function
typedef struct
{
token**substream;
unsigned length;
} tokenList;

//raw input, input length, system state, current node, interpreter instance
void interpret(char*,unsigned,interpreter*);
void reset(interpreter*);
tokenList * execute(interpreter*);

#endif
