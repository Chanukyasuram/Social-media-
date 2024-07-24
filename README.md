# Social Media online using c++

This project is a simulation of a social network where users can be added, create friendships, join social groups, and send personal or group messages. The program is written in C++ and includes functionalities for user management, group management, and messaging.

## Features

- **User Management**
  - Add new users with first name, last name, age, and gender.
  - Display all registered users.
  - Manage friendships between users.

- **Group Management**
  - Create social groups.
  - Add or remove members from groups.
  - Display group information including members and messages.

- **Messaging**
  - Send personal messages between users.
  - Send group messages within a social group.
  - Chat between two users with an option to send another message or let the receiver send a message.

## Classes and Functions

### Classes

- `Message`
  - Represents a message with sender, receiver, content, timestamp, and message type (personal or group).
  
- `SocialGroup`
  - Manages group functionalities including adding/removing members and storing messages.

- `User`
  - Represents a user with first name, last name, age, and gender.

### Functions

- `string getCurrentTimestamp()`
  - Returns the current timestamp as a string.
  
- `string toLowerCase(const string& str)`
  - Converts a string to lowercase.
  
- `void addUser(const string& userName, const User& user)`
  - Adds a new user to the global user map.
  
- `void makeThemFriend(const string& userName1, const string& userName2)`
  - Establishes a friendship between two users.
  
- `void displayAllUsers()`
  - Displays all registered users.
  
- `void displayAllFriendships()`
  - Displays all friendships.

- `void ensureUserRegistered(string& username)`
  - Ensures that a username is registered, prompting the user to register if not.

## How to Use

1. **Compile the program** using a C++ compiler. For example:
   ```sh
   g++ -o social_network social_network.cpp
Run the program:

sh
Copy code
./social_network
Interactive Menu:

Choose an option from the menu to add members, send messages, display group info, display users, display friendships, or start a chat between two users.
Follow the prompts to enter necessary information like usernames, message content, etc.
End the Program:

Select option 8 to exit the program.
Example Usage
Add Users:
Add initial users (Alice, Bob, Charlie) to the system.
Create a Group:
Create a group "Goa trip" and add Alice and Bob as members.
Send Messages:
Send personal and group messages between users.
Chat:
Start a chat session between two users with the option to send multiple messages.
Future Improvements
Implement case-sensitive handling for usernames.
Enhance user registration with validation.
Add more interactive features and user-friendly prompts.
