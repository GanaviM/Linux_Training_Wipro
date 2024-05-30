#include "graph.h"  // Including the header file for the Social Network Management System

FriendNode* createFriendNode(int userId) {  // Function to create a new friend node for a given user ID
    FriendNode* node = (FriendNode*)malloc(sizeof(FriendNode));  // Allocating memory for the new friend node
    if (node == NULL) {  // Checking if memory allocation failed
        printf("Memory allocation failed.\n");  // Printing an error message
        exit(EXIT_FAILURE);  // Exiting the program with an error code
    }
    node->userId = userId;  // Setting the user ID for the new friend node
    node->next = NULL;  // Initializing the next pointer to NULL
    return node;  // Returning the newly created friend node
}

SocialNetwork* createSocialNetwork() {  // Function to create a new social network
    SocialNetwork* network = (SocialNetwork*)malloc(sizeof(SocialNetwork));  // Allocating memory for the new social network
    if (network == NULL) {  // Checking if memory allocation failed
        printf("Memory allocation failed.\n");  // Printing an error message
        exit(EXIT_FAILURE);  // Exiting the program with an error code
    }
    network->totalUsers = 0;  // Initializing the total number of users to 0
    return network;  // Returning the newly created social network
}

void addUserProfile(SocialNetwork* network, char* name, char* interests) {  // Function to add a new user profile to the social network
    if (network->totalUsers >= MAX_USERS) {  // Checking if the maximum user limit has been reached
        printf("Max user limit reached.\n");  // Printing a message indicating the limit has been reached
        return;  // Returning without adding the user profile
    }
    strcpy(network->profiles[network->totalUsers].name, name);  // Copying the name to the new user profile
    strcpy(network->profiles[network->totalUsers].interests, interests);  // Copying the interests to the new user profile
    network->friends[network->totalUsers] = NULL;  // Initializing the friends list for the new user profile to NULL
    network->totalUsers++;  // Incrementing the total number of users in the social network
}

int findUserByName(SocialNetwork* network, char* name) {  // Function to find a user in the social network by name
    for (int i = 0; i < network->totalUsers; i++) {  // Looping through all user profiles in the network
        if (strcmp(network->profiles[i].name, name) == 0) {  // Checking if the name matches
            return i;  // Returning the index of the user profile
        }
    }
    return -1;  // Returning -1 if the user was not found
}

void addFriend(SocialNetwork* network, char* userName1, char* userName2) {  // Function to add a friend connection between two users
    int user1Index = findUserByName(network, userName1);  // Finding the index of the first user
    int user2Index = findUserByName(network, userName2);  // Finding the index of the second user
    if (user1Index == -1 || user2Index == -1) {  // Checking if either user was not found
        printf("User not found.\n");  // Printing an error message
        return;  // Returning without adding the friend connection
    }

    FriendNode* friend1 = createFriendNode(user2Index);  // Creating a new friend node for the second user
    friend1->next = network->friends[user1Index];  // Adding the new friend node to the list of friends for the first user
    network->friends[user1Index] = friend1;  // Updating the list of friends for the first user

    FriendNode* friend2 = createFriendNode(user1Index);  // Creating a new friend node for the first user
    friend2->next = network->friends[user2Index];  // Adding the new friend node to the list of friends for the second user
    network->friends[user2Index] = friend2;  // Updating the list of friends for the second user
}

void recommendFriends(SocialNetwork* network, char* userName) {  // Function to recommend friends for a user
    int userIndex = findUserByName(network, userName);  // Finding the index of the user
    if (userIndex == -1) {  // Checking if the user was not found
        printf("User not found.\n");  // Printing an error message
        return;  // Returning without recommending friends
    }

    for (int i = 0; i < network->totalUsers; i++) {  // Looping through all user profiles in the network
        if (i != userIndex) {  // Checking if the user is not the same as the current user
            FriendNode* current = network->friends[userIndex];  // Getting the list of friends for the current user
            int isFriend = 0;  // Flag to indicate if the current user is already a friend
            while (current != NULL) {  // Looping through the list of friends
                if (current->userId == i) {  // Checking if the current user is already a friend
                    isFriend = 1;  // Setting the flag to true
                    break;  // Exiting the loop
                }
                current = current->next;  // Moving to the next friend in the list
            }
            if (!isFriend) {  // Checking if the current user is not already a friend
                printf("Recommendation: %s\n", network->profiles[i].name);  // Printing the recommendation
            }
        }
    }
}

void displayFriendList(SocialNetwork* network, char* userName) {  // Function to display the friend list for a user
    int userIndex = findUserByName(network, userName);  // Finding the index of the user
    if (userIndex == -1) {  // Checking if the user was not found
        printf("User not found.\n");  // Printing an error message
        return;  // Returning without displaying the friend list
    }

    FriendNode* current = network->friends[userIndex];  // Getting the list of friends for the user
    printf("Friend List of %s:\n", userName);  // Printing the heading for the friend list
    while (current != NULL) {  // Looping through the list of friends
        printf("- %s\n", network->profiles[current->userId].name);  // Printing the name of each friend
        current = current->next;  // Moving to the next friend in the list
    }
}

void displayNewsFeed() {  // Function to display the news feed (placeholder)
    // Placeholder for displaying news feed
    printf("Displaying news feed...\n");
}

