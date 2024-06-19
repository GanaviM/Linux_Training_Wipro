#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node of the linked list
struct Node {
    char data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to reverse a linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Function to check if a linked list is a palindrome
bool isPalindrome(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return true;

    // Find the middle of the linked list
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list
    struct Node* secondHalf = reverseList(slow->next);

    // Compare the first and second halves
    struct Node* firstHalf = head;
    while (secondHalf != NULL) {
        if (firstHalf->data != secondHalf->data)
            return false;
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return true;
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%c ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Main function
int main() {
    // Create a linked list
    struct Node* head = newNode('a');
    head->next = newNode('b');
    head->next->next = newNode('c');
    head->next->next->next = newNode('b');
    head->next->next->next->next = newNode('a');

    printf("Original linked list: ");
    printList(head);

    // Check if the linked list is a palindrome
    if (isPalindrome(head))
        printf("Linked list is a palindrome.\n");
    else
        printf("Linked list is not a palindrome.\n");

    return 0;
}
