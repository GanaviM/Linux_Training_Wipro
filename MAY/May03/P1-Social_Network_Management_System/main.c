#include "graph.h" // Including the header file for the graph.h 
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    SocialNetwork* network = createSocialNetwork(); // Creating a new social network

    // Measure the time taken by the addUserProfile function
    start = clock();

    // Adding user profiles
    addUserProfile(network, "Ganavi", "Art, Music"); // Adding user profile for Ganavi with interests
    addUserProfile(network, "Bhavya", "Sports, Movies"); // Adding user profile for Bhavya with interests
    addUserProfile(network, "Akhila", "Technology, Reading"); // Adding user profile for Akhila with interests
    addUserProfile(network, "Prasanna", "Gaming, Cooking"); // Adding user profile for Prasanna with interests
    addUserProfile(network, "Ishani", "Travel, Photography"); // Adding user profile for Ishani with interests

    // Adding friendships
    addFriend(network, "Ganavi", "Bhavya"); // Ganavi becomes friends with Bhavya
    addFriend(network, "Ganavi", "Akhila"); // Ganavi becomes friends with Akhila
    addFriend(network, "Ganavi", "Prasanna"); // Ganavi becomes friends with Prasanna
    addFriend(network, "Ganavi", "Ishani"); // Ganavi becomes friends with Ishani
    addFriend(network, "Bhavya", "Akhila"); // Bhavya becomes friends with Akhila
    addFriend(network, "Bhavya", "Prasanna"); // Bhavya becomes friends with Prasanna
    addFriend(network, "Bhavya", "Ishani"); // Bhavya becomes friends with Ishani
    addFriend(network, "Akhila", "Prasanna"); // Akhila becomes friends with Prasanna

    // Displaying friend list
    displayFriendList(network, "Ganavi"); // Displaying Ganavi's friend list
    displayFriendList(network, "Bhavya"); // Displaying Bhavya's friend list
    displayFriendList(network, "Akhila"); // Displaying Akhila's friend list
    displayFriendList(network, "Prasanna"); // Displaying Prasanna's friend list
    displayFriendList(network, "Ishani"); // Displaying Ishani's friend list

    // Recommending friends
    recommendFriends(network, "Ganavi"); // Recommending friends for Ganavi
    recommendFriends(network, "Bhavya"); // Recommending friends for Bhavya
    recommendFriends(network, "Akhila"); // Recommending friends for Akhila
    recommendFriends(network, "Prasanna"); // Recommending friends for Prasanna
    recommendFriends(network, "Ishani"); // Recommending friends for Ishani

    // More functionality testing...
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Total time taken %f seconds to execute.\n", cpu_time_used);

    return 0; // Returning 0 to indicate successful execution.
}
