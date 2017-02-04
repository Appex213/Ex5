#include <stdio.h>
#include <stdlib.h>

//change values here to change the type of the elements in the stack
#define ELEMENT_FORMAT "%c" // "%c"/"%d"/"%f" ...
typedef char Element;       // char/int/float ...

typedef struct {
    Element *content;
    int size;
    int topIndex;
} Stack;

void printStack(Stack* stackPtr) {
    int i;
    printf("Size of stack = %d, Size of content = %d\n", stackPtr->size, stackPtr->topIndex + 1);
    printf("Content: ");
    for (i = 0; i <= stackPtr->topIndex; i++) {
        printf(ELEMENT_FORMAT, stackPtr->content[i]);
        printf(" ");
    }
    printf("\n\n");
}

void init(Stack* stackPtr) {
    Element* newContent = (Element*) malloc(sizeof(Element));
    if (newContent == NULL) {
        printf("Insufficient memory to initialize stack.\n");
        exit(1);  /* Exit, returning error code. */
    }
    stackPtr->content = newContent;
    stackPtr->size = 1;
    stackPtr->topIndex = -1;  /* I.e., empty */
}

void destroy(Stack* stackPtr) {
    free(stackPtr->content);
    stackPtr->content = NULL;
    stackPtr->size = 0;
    stackPtr->topIndex = -1;  /* I.e., empty */
}

void push(Stack* stackPtr, Element element) {
    //Put information in array; update topIndex
    stackPtr->content[++stackPtr->topIndex] = element;

    if (isFull(stackPtr)) {
        Element* newContent = (Element*) realloc(stackPtr->content,sizeof(Element) * stackPtr->size * 2);
        if (newContent == NULL) {
            free(stackPtr->content);
            printf("Push: Insufficient memory to realloc stack.\n");
            exit(1);  // Exit, returning error code
        }
        stackPtr->content = newContent;
        stackPtr->size *= 2;
        printf("---------------------------------> Expanding size of stack to %d\n", stackPtr->size);
    }
}

Element pop(Stack *stackPtr) {
    //note - before using pop, the user must check that the stack is not empty
    if (isEmpty(stackPtr)) {
        printf("Can't pop Element from Stack: Stack is empty.\n");
        exit(1);  // Exit, returning error code
    }
    //Get information from the array; update topIndex
    Element returnVal = stackPtr->content[stackPtr->topIndex--];

    if (isHalfEmpty(stackPtr)) {
        Element* newContent = (Element*) realloc(stackPtr->content,sizeof(Element) * stackPtr->size / 2);
        if (newContent == NULL) {
            printf("Pop: Insufficient memory to realloc stack.\n");
            exit(1);  /* Exit, returning error code. */
        }
        stackPtr->content = newContent;
        stackPtr->size /= 2;
        printf("---------------------------------> Shrinking size of stack to %d\n", stackPtr->size);
    }

    return returnVal;
}

Element top(Stack *stackPtr) {
    //note - before using top, the user must check that the stack is not empty
    if (isEmpty(stackPtr)) {
        printf("Can't top Element from Stack: Stack is empty.\n");
        exit(1);  // Exit, returning error code
    }
    return stackPtr->content[stackPtr->topIndex];
}

int isEmpty(Stack* stackPtr) {
    return stackPtr->topIndex < 0;
}

int isHalfEmpty(Stack* stackPtr) {
    return stackPtr->topIndex < (stackPtr->size / 2) - 1;
}

int isFull(Stack* stackPtr) {
    return stackPtr->topIndex >= stackPtr->size - 1;
}

int main(void) {

    int input;
    Element element;
    Stack stack;

    init(&stack);
    printf("Welcome to the elements stack!\n");

    do {
        printf("Please choose option from the menu:\n\t1 : push\n\t2 : top\n\t3 : pop\n\t4 : print stack\n\tother : exit\n");
        scanf("%d",&input);
        switch (input) {
            case 1: printf("Enter element to push: ");
                    scanf(ELEMENT_FORMAT, &element);
                    push(&stack, element);
                    break;
            case 2: if (!isEmpty(&stack)) {
                        printf("top\n");
                        printf(ELEMENT_FORMAT, top(&stack));
                        printf("\n");
                    } else {
                        printf("can't top! stack is empty!\n");
                    }
                    break;
            case 3: if (!isEmpty(&stack)) {
                        printf("pop\n");
                        printf(ELEMENT_FORMAT, pop(&stack));
                        printf("\n");
                    } else {
                        printf("can't pop! stack is empty!\n");
                    }
                    break;
            case 4: printStack(&stack);
        }
    } while (1 <= input && input <= 4);

    destroy(&stack);
    return 0;
}

