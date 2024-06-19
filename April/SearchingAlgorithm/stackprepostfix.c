#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}


void infixToPostfix(char *infix, char *postfix) {
    char stack[MAX_SIZE];
    int top = -1; 

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            postfix[strlen(postfix)] = ch;
        }
        else if (isOperator(ch)) {
              while (top >= 0 && precedence(stack[top]) >= precedence(ch)) {
                postfix[strlen(postfix)] = stack[top--];
            }
            stack[++top] = ch;
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[strlen(postfix)] = stack[top--];
            }
            top--;
        }
    }

    while (top >= 0) {
        postfix[strlen(postfix)] = stack[top--];
    }
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
