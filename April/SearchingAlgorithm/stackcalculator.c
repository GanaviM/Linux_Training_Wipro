#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    int data;
    struct StackNode* next;
};

struct StackNode* createNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(struct StackNode* root) {
    return (root == NULL);
}

void push(struct StackNode** root, int data) {
    struct StackNode* newNode = createNode(data);
    newNode->next = *root;
    *root = newNode;
}

int pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        printf("Stack underflow.\n");
        exit(1);
    }
    struct StackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

int peek(struct StackNode* root) {
    if (isEmpty(root)) {
        printf("Stack is empty.\n");
        exit(1);
    }
    return root->data;
}

int performOperation(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: printf("Invalid operator.\n");
                 exit(1);
    }
}

int evaluateExpression(char* expression) {
    struct StackNode* operandStack = NULL;
    struct StackNode* operatorStack = NULL;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            push(&operatorStack, expression[i]);
        } else if (expression[i] == ')') {
            while (!isEmpty(operatorStack) && peek(operatorStack) != '(') {
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);
                char op = pop(&operatorStack);
                push(&operandStack, performOperation(op, operand1, operand2));
            }
            pop(&operatorStack); 
        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/') {
            while (!isEmpty(operatorStack) && peek(operatorStack) != '(' &&
                   (expression[i] == '*' || expression[i] == '/') &&
                   (peek(operatorStack) == '*' || peek(operatorStack) == '/')) {
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);
                char op = pop(&operatorStack);
                push(&operandStack, performOperation(op, operand1, operand2));
            }
            push(&operatorStack, expression[i]);
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            int operand = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            i--; 
            push(&operandStack, operand);
        }
    }

    while (!isEmpty(operatorStack)) {
        int operand2 = pop(&operandStack);
        int operand1 = pop(&operandStack);
        char op = pop(&operatorStack);
        push(&operandStack, performOperation(op, operand1, operand2));
    }

    return pop(&operandStack);
}

int main() {
    char expression[100];
    printf("Enter the arithmetic expression: ");
    scanf("%[^\n]%*c", expression);

    int result = evaluateExpression(expression);
    printf("Result: %d\n", result);

    return 0;
}
