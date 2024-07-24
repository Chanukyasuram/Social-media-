#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <ctime>  // For timestamp

using namespace std;

// Utility function to get the current timestamp
string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
             ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    return string(buffer);
}

// Convert string to lowercase
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Message class
class Message {
public:
    string sender;         // Sender of the message
    string receiver;       // Receiver of the message
    string content;        // Content of the message
    bool isGroupMessage;   // True if the message is a group message, false if personal
    string timestamp;      // Timestamp of the message

    Message() {}

    Message(string sender, string receiver, string content, bool isGroupMessage = false)
        : sender(toLowerCase(sender)), receiver(toLowerCase(receiver)), content(content), isGroupMessage(isGroupMessage), timestamp(getCurrentTimestamp()) {}

    // Function to display the message details
    void displayMessage() const {
        string type = isGroupMessage ? "Group" : "Personal";
        cout << type << " Message - Sender: " << sender
             << ", Receiver: " << receiver
             << ", Content: " << content
             << ", Timestamp: " << timestamp << endl;
    }
};

// SocialGroup class to manage group functionalities
class SocialGroup {
private:
    string groupName;             // Name of the group
    vector<string> members;       // Members of the group
    vector<Message> messages;     // Messages in the group

public:
    SocialGroup() {}

    SocialGroup(string groupName) : groupName(groupName) {}

    // Add a member to the group
    void addMember(const string& userName) {
        string lowerUserName = toLowerCase(userName);
        if (!isMember(lowerUserName)) {
            members.push_back(lowerUserName);
            cout << userName << " added to the group." << endl;
        } else {
            cout << userName << " is already a member of the group." << endl;
        }
    }

    // Remove a member from the group
    void removeMember(const string& userName) {
        string lowerUserName = toLowerCase(userName);
        auto it = find(members.begin(), members.end(), lowerUserName);
        if (it != members.end()) {
            members.erase(it);
            cout << userName << " removed from the group." << endl;
        } else {
            cout << userName << " is not a member of the group." << endl;
        }
    }

    // Add a message to the group or personal message
    void addMessage(const Message& message) {
        if (message.isGroupMessage) {
            if (isMember(message.receiver)) {
                messages.push_back(message);
            } else {
                cout << "Group message cannot be sent because the receiver is not a member of the group." << endl;
            }
        } else {
            // Personal messages are allowed regardless of user registration
            messages.push_back(message);
        }
    }

    // Display group information
    void displayGroupInfo() const {
        cout << "Group: " << groupName << endl;
        cout << "Members: ";
        for (const auto& member : members) {
            cout << member << " ";
        }
        cout << endl;

        cout << "Messages: " << endl;
        for (const auto& message : messages) {
            message.displayMessage();
        }
    }

    // Check if a user is a member of the group
    bool isMember(const string& userName) const {
        return find(members.begin(), members.end(), toLowerCase(userName)) != members.end();
    }
};

// User class to manage user information
class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {}

    User(string firstName, string lastName, int age, string gender)
        : firstName(firstName), lastName(lastName), age(age), gender(gender) {}
};

// Global maps for users and friendships
map<string, User> mapUserName;
map<string, set<string>> Friends;

// Function to add a user
void addUser(const string& userName, const User& user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "UserName Already Taken" << endl;
    }
}

// Function to make friends
void makeThemFriend(const string& userName1, const string& userName2) {
    Friends[userName1].insert(userName2);
    Friends[userName2].insert(userName1);
}

// Function to display all users
void displayAllUsers() {
    for (const auto& user : mapUserName) {
        if (user.first != "register") {
            cout << "UserName: " << user.first << ", Name: " << user.second.firstName << " " << user.second.lastName << endl;
        }
    }
}

// Function to display all friendships
void displayAllFriendships() {
    for (const auto& pair : Friends) {
        cout << pair.first << ": ";
        for (const auto& friendName : pair.second) {
            cout << friendName << " ";
        }
        cout << endl;
    }
}

// Ensure username is registered, otherwise prompt user to register or enter a valid username
void ensureUserRegistered(string& username) {
    while (mapUserName.find(toLowerCase(username)) == mapUserName.end()) {
        cout << "User not registered. Please enter a valid username or type 'register' to add a new user: ";
        cin >> username;
        if (toLowerCase(username) == "register") {
            string firstName, lastName, gender, newUserName;
            int age;
            cout << "Enter username: ";
            cin >> newUserName;
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender: ";
            cin >> gender;
            newUserName = toLowerCase(newUserName);
            if (mapUserName.find(newUserName) == mapUserName.end()) {
                addUser(newUserName, User(firstName, lastName, age, gender));
                cout << "User registered successfully." << endl;
                username = newUserName;
            } else {
                cout << "Username already taken, please choose another username." << endl;
            }
        }
    }
}

// Main function
int main() {
    // Creating and adding initial users
    User alice("Alice", "Mishra", 30, "Female");
    User bob("Bob", "Ali", 27, "Male");
    User charlie("Charlie", "Smith", 25, "Non-Binary");

    addUser("alice", alice);
    addUser("bob", bob);
    addUser("charlie", charlie);

    // Creating a social group
    SocialGroup group1("Goa trip");

    // Adding initial members to the group
    group1.addMember("alice");
    group1.addMember("bob");

    // Interactive loop
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Add member to group" << endl;
        cout << "2. Remove member from group" << endl;
        cout << "3. Send message" << endl;
        cout << "4. Display group info" << endl;
        cout << "5. Display all users" << endl;
        cout << "6. Display all friendships" << endl;
        cout << "7. Chat between two users" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string userName;
            cout << "Enter the username to add to the group: ";
            cin >> userName;
            ensureUserRegistered(userName);
            group1.addMember(userName);
        } else if (choice == 2) {
            string userName;
            cout << "Enter the username to remove from the group: ";
            cin >> userName;
            ensureUserRegistered(userName);
            group1.removeMember(userName);
            // Remove the user from the global map if they are not in the group
            if (!group1.isMember(userName)) {
                mapUserName.erase(toLowerCase(userName));
                cout << "User " << userName << " removed from the user list." << endl;
            }
        } else if (choice == 3) {
            int messageType;
            cout << "Enter 1 for personal message or 2 for group message: ";
            cin >> messageType;
            string sender, receiver, content;
            cout << "Enter the sender username: ";
            cin >> sender;
            ensureUserRegistered(sender);
            cout << "Enter the receiver username: ";
            cin >> receiver;
            ensureUserRegistered(receiver);
            cout << "Enter message content: ";
            cin.ignore();  // Ignore newline left in the buffer
            getline(cin, content);

            if (messageType == 1) {
                Message message(sender, receiver, content);
                group1.addMessage(message);
            } else if (messageType == 2) {
                Message message(sender, receiver, content, true);
                group1.addMessage(message);
            }
        } else if (choice == 4) {
            group1.displayGroupInfo();
        } else if (choice == 5) {
            displayAllUsers();
        } else if (choice == 6) {
            displayAllFriendships();
        } else if (choice == 7) {
            string user1, user2;
            cout << "Enter the username of the first user: ";
            cin >> user1;
            ensureUserRegistered(user1);
            cout << "Enter the username of the second user: ";
            cin >> user2;
            ensureUserRegistered(user2);

            cout << "Chat between " << user1 << " and " << user2 << endl;
            cin.ignore();  // Ignore newline left in the buffer before starting the chat loop
            string messageContent;
            while (true) {
                cout << "Enter message content (or type 'exit' to end chat): ";
                getline(cin, messageContent);
                if (toLowerCase(messageContent) == "exit") {
                    break;
                }
                Message message(user1, user2, messageContent);
                group1.addMessage(message);
                cout << "Message sent." << endl;

                // Ask if the user wants to send another message or let the receiver send one
                cout << "Enter '1' to send another message or '2' to let the receiver send a message: ";
                int option;
                cin >> option;
                cin.ignore();  // Ignore newline left in the buffer
                if (option == 2) {
                    string receiverMessage;
                    cout << "Enter the message content from " << user2 << ": ";
                    getline(cin, receiverMessage);
                    Message receiverMsg(user2, user1, receiverMessage);
                    group1.addMessage(receiverMsg);
                    cout << "Message received and sent." << endl;
                }
            }
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
