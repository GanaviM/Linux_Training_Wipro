#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<time.h>
#include "tree.h"
#include "stack.h"

// Function to convert infix expression to postfix expression
char* infixToPostfix(char* infix) {
    // Allocate memory for the postfix expression
    char* postfix = (char*)malloc((strlen(infix) + 1) * sizeof(char));
    if (postfix == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize variables
    int index = 0; // Index for postfix expression
    int top = -1; // Top index for the stack
    char stack[100]; // Stack to store operators
    stack[++top] = '('; // Push '(' onto the stack
    infix = strcat(infix, ")"); // Append ')' to the infix expression

    // Traverse the infix expression
    for (int i = 0; infix[i] != '\0'; i++) {
        // If current character is operand, add it to postfix
        if (isdigit(infix[i])) {
            postfix[index++] = infix[i];
        }
        // If current character is '(', push it onto the stack
        else if (infix[i] == '(') {
            stack[++top] = '(';
        }
        // If current character is operator or ')'
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == ')') {
            // Pop operators from the stack and add to postfix until '(' is encountered
            while (stack[top] != '(') {
                postfix[index++] = stack[top--];
            }
            // If current character is ')', pop '(' from stack
            if (infix[i] == ')') {
                top--;
            }
            // Otherwise, push current operator onto the stack
            else {
                stack[++top] = infix[i];
            }
        }
    }

    // Null terminate the postfix expression
    postfix[index] = '\0';

    // Free memory for the postfix expression
    postfix = realloc(postfix, (strlen(postfix) + 1) * sizeof(char));
    if (postfix == NULL) {
        printf("Memory reallocation failed!\n");
        exit(EXIT_FAILURE);
    }

    return postfix;
}

int main() {
    char expression[100];

    printf("Enter an infix mathematical expression: ");
    if(fgets(expression, sizeof(expression), stdin) == NULL)
    {
	    printf("Error reading input");
	    return 1; //Return an errorr coed
	}
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character from input

    //start measuiring CPU time
    clock_t start = clock();

    // Convert infix expression to postfix expression
    char* postfix = infixToPostfix(expression);
    printf("Postfix Expression: %s\n", postfix);

    // Build the expression tree
    struct TreeNode* root = buildTree(postfix);

    // Perform an iterative inorder traversal of the binary expression tree
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Evaluate the expression
    int result = evaluateExpression(root);
    printf("Result: %d\n", result);

    //Stop measuring CPU time
    clock_t end = clock();


    //Calculate CPU Time used
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    //Print the CPu time used
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    // Deallocate memory for the tree nodes
    freeTree(root);
    free(postfix);

    return 0;
}
