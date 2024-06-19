#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15

typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Contact;

Contact phone_directory[MAX_CONTACTS];
int contact_count = 0;

void add_contact(const char *name, const char *phone) {
    if (contact_count < MAX_CONTACTS) {
        strncpy(phone_directory[contact_count].name, name, NAME_LENGTH);
        strncpy(phone_directory[contact_count].phone, phone, PHONE_LENGTH);
        contact_count++;
        printf("Contact added: %s, %s\n", name, phone);
    } else {
        printf("Phone directory is full!\n");
    }
}

void search_contact(const char *name) {
    for (int i = 0; i < contact_count; i++) {
        if (strncmp(phone_directory[i].name, name, NAME_LENGTH) == 0) {
            printf("Found contact: %s, %s\n", phone_directory[i].name, phone_directory[i].phone);
            return;
        }
    }
    printf("Contact not found: %s\n", name);
}

void display_contacts() {
    printf("Phone Directory:\n");
    for (int i = 0; i < contact_count; i++) {
        printf("%s, %s\n", phone_directory[i].name, phone_directory[i].phone);
    }
}

int main() {
    int choice;
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];

    while (1) {
        printf("\nPhone Directory\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone: ");
                scanf("%s", phone);
                add_contact(name, phone);
                break;
            case 2:
                printf("Enter name to search: ");
                scanf("%s", name);
                search_contact(name);
                break;
            case 3:
                display_contacts();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
