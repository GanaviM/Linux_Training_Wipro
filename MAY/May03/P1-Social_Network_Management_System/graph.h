#ifndef GRAPH_H //Header guard to prevent multiple inclusion
#define GRAPH_H //preprocessor directive the deines macro GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define constants for maximum user and friends

#define MAX_USERS 100
#define MAX_FRIENDS 100

//define the structure for a user profile
typedef struct {
    char name[50];//name of the user
    char interests[100];//Interests of the user
} UserProfile;

//define the strucure for a friend node
typedef struct FriendNode {
    int userId;//Id of the friend
    struct FriendNode* next;//pointer to the next friend in the list
} FriendNode;

//Define the structure for the social network
typedef struct {
    int totalUsers;//total number of users in the network
    UserProfile profiles[MAX_USERS];//Array to store user profiles
    FriendNode* friends[MAX_USERS];//Array to store friend lists for each user
} SocialNetwork;

//Function prototypes 
FriendNode* createFriendNode(int userId);//Function to create a new friend node
SocialNetwork* createSocialNetwork();//function to create a new social network
void addUserProfile(SocialNetwork* network, char* name, char* interests);//Function to adddd a new user profile
void addFriend(SocialNetwork* network, char* userName1, char* userName2);//Function to add a friend connection
int findUserByName(SocialNetwork* network, char* name);//function to find a user by name
void recommendFriends(SocialNetwork* network, char* userName);//function to recommend friends for a user
void displayFriendList(SocialNetwork* network, char* userName);//function to display the friend list for a user
void displayNewsFeed();//function to display the news feed


#endif /* GRAPH_H*///end of the header guard

