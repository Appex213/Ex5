#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    char one;
    long bigNumber;
    float numberWithDot;
    double numberWithDotx2;
    char lots[50];
} Element;


typedef struct {
    Element *content;
    int size;
    int topIndex;
} Stack;

int isFull(Stack* stackPtr);
int isEmpty(Stack* stackPtr);
int isHalfEmpty(Stack* stackPtr);

void Print(Element* content)
{
    printf("\nint is:     %d\n", content->number);
    printf("long is:    %ld\n", content->bigNumber);
    printf("float is:   %f\n", content->numberWithDot);
    printf("double is:  %lf\n", content->numberWithDotx2);
    printf("char is:    %c\n", content->one);
    printf("string is:  %s\n", content->lots);
    printf(" --------\n ");
}

void Scan(Element* content)
{
    printf("Enter int:\n");
    scanf("%d",&content->number);
    printf("Enter long:\n");
    scanf("%ld", &content->bigNumber);
    printf("Enter float:\n");
    scanf("%f", &content->numberWithDot);
    printf("Enter double:\n");
    scanf("%lf", &content->numberWithDotx2);
    printf("Enter char:\n");
    scanf("%c", &content->one);
    /* I don't fully understand why this is necessary, but without it it just skips the char's scanf*/
    scanf("%c", &content->one);
    printf("Enter string: (len<50)\n");
    scanf("%s", content->lots);
    printf("\n\n");
}


void printStack(Stack* stackPtr) {
    int i;
    printf("Size of stack = %d, Size of content = %d\n", stackPtr->size, stackPtr->topIndex + 1);
    printf("Contents: ");
    for (i = 0; i <= stackPtr->topIndex; i++) {
        Element element = stackPtr->content[i];
        printf("\n-->Element no. %d\n",i+1 );
        Print(&element);
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
    /*Put information in array; update topIndex*/
    stackPtr->content[++stackPtr->topIndex] = element;

    if (isFull(stackPtr)) {
        Element* newContent = (Element*) realloc(stackPtr->content,sizeof(Element) * stackPtr->size * 2);
        if (newContent == NULL) {
            free(stackPtr->content);
            printf("Push: Insufficient memory to realloc stack.\n");
            exit(1);  /* Exit, returning error code */
        }
        stackPtr->content = newContent;
        stackPtr->size *= 2;
        printf("---------------------------------> Expanding size of stack to %d\n", stackPtr->size);
    }
}

Element pop(Stack *stackPtr) {
        Element returnVal;
    /* note - before using pop, the user must check that the stack is not empty */
    if (isEmpty(stackPtr)) {
        printf("Can't pop Element from Stack: Stack is empty.\n");
        exit(1);  /* Exit, returning error code */
    }
    /* Get information from the array; update topIndex */
    returnVal = stackPtr->content[stackPtr->topIndex--];

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
    /* note - before using top, the user must check that the stack is not empty */
    if (isEmpty(stackPtr)) {
        printf("Can't top Element from Stack: Stack is empty.\n");
        exit(1);  /* Exit, returning error code */
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

int main() {

    int input;
    Element element;
    Stack stack;
    Element temp;

    init(&stack);
    printf("Welcome to the elements stack!\n");

    do {
        printf("Please choose option from the menu:\n\t1 : push\n\t2 : top\n\t3 : pop\n\t4 : print stack\n\tother : exit\n");
        scanf("%d",&input);
        switch (input) {
            case 1: printf("-->Enter element data to push: \n");
                              Scan(&element);
                    push(&stack, element);
                    break;
            case 2: if (!isEmpty(&stack)) {
                        printf("-->top element is:\n");
                        Print(&stack.content[stack.topIndex]);
                        printf("\n");
                    } else {
                        printf("can't top! stack is empty!\n");
                    }
                    break;
            case 3: if (!isEmpty(&stack)) {
                        printf("-->popped element is:\n");
                        temp = pop(&stack);
                        Print(&temp);
                        printf("\n");
                    } else {
                        printf("can't pop! stack is empty!\n");
                    }
                    break;
            case 4: if (!isEmpty(&stack)) {
                    printStack(&stack);
                    } else {
                        printf("nothing to print! stack is empty!\n");
                    }
        }
    } while (1 <= input && input <= 4);

    destroy(&stack);
    return 0;
}