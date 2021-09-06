// Rewritten

// •	The system should accept the user’s credentials and check if the user is legitimate.
// •	In case the user is legitimate it should ask the user whether he wants to know the account balance, make fund transfer and update balance.
// •	In case user is not legitimate inform the admin about unauthorized access
// •	If more than 3 wrong login attempts are made for the user then lock the account and do not allow access for that account
// •	Secured password based account unlock by legitimate user
// •	Get monthly reports of unauthorized access

#include <stdio.h>
#include <direct.h>
#include <string.h>
#include <stdlib.h>

struct users //struct user defined with name, password and balance in account
{
    char name[10], password[10];
    float balance;
    int lock;
    int invalidAttempts;
};

struct users user[4] = {
    {"admin", "admin", 2000, 0, 0},
    {"aka", "aka", 2002, 0, 1},
    {"sangram", "pass", 2222, 0, 0}};
int unauthAccess = 0;

// function prototypes
int authenticate(char[], int);
int userFunctions(int);
int numOfUsers();
int adminFunctions();
// Prog start
int authenticate(char username[], int index) //authentication procedure for a user
{
    int maxtry = 3, attempts = 1;
    // char ch, currentUserName[10],
    char password[10];
    if (user[index].lock == 1) //account check for lock status
    {
        printf("Account Locked. Contact Admin to unlock your account!");
    }

    else
    {

        while (attempts <= maxtry) //no of incorrect attempts checked
        {

            system("CLS");
            printf("User Name : %s \n", username);
            printf("Enter Your Password  : ");
            gets(password);
            if (strcmp(user[index].password, password) == 0) // user authenticated
            {
                if (strcmp(username, "admin") == 0) //Loading Admin Screen
                    adminFunctions();
                else //Load user Screen
                    userFunctions(index);
            }
            else
                attempts++; // wrong password entered
        }
        if (attempts == 3 && username != "admin") // no of attempts exceeded, account locked if not admin
        {
            printf("Maximum tries for wrong attempt reached. Your account is now locked!");
            user[index].lock == 1;
            unauthAccess++; //Increment unauthorised access count
        }
    }
}

int userFunctions(int index) // user functions
{
    int a;
    float update;
    printf("Welcome %s", user[index].name);
    printf("Choose option \n 1=View Account Balance \t2=Balance Transfer \t3=Update account balance");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        printf("Account balance is : %d", user[index].balance);
        break;
    case 2:
        printf("Balance transfer initiated");
        printf("Updated balance :%s", user[index].balance);
        break;
    case 3:
        printf("Enter new balance");
        scanf("%f", &update);
        user[index].balance = update;
        printf("Updated balance : %s", user[index].balance);
        break;
    default:
        printf("Invalid option entered.\nPlease try again.");
        userFunctions(index); //Recalling method to display options to user once again
    }
}

int adminFunctions() //admin functions, make admin user[0]
{

    char username[10], password[10];
    int usercount = 0, temp, i, bal, flag = 0;
rerun: //Label to re display options
    printf("Enter your choice : \n1 - User Addition  \n2 - Account unlock\n3 - View Total Unauthorised Access Count \n 4 - Reset Unauthoried Access Count");
    scanf("%d", temp);
    switch (temp)
    {
    case 1:

        system("CLS");

        printf("Enter Username");
        gets(username);
        printf("Enter Password");
        gets(password);
        printf("Enter initial balance");
        scanf("%d", &bal);
        // TODO#1:		struct users user[numOfUsers() + 1] = {username, password, bal, 0, 0}; //default lock and invalidAttempts = 0
        break;

    case 2: // unlock user

        printf("Enter username");
        gets(username);
        for (i = 0; i < numOfUsers(); i++)
        {
            if (strcmp(username, user[i].name) == 0)
            {
                flag = 1;

                break;
            }
        }
        if (flag == 1)
        {

            user[i].lock = 0;
            printf("Account of User : %s unlocked successfully!", username);
        }
        else
        {
            printf("Account of User : %s not found in user list! \nTry again!", username);
            goto rerun;
        }
        break;
    case 3:
        printf("Total Unauthorised Access Count :%d", unauthAccess);

        break;
    case 4:
        printf("Reset Unauthoried Access Count Successful!\nCurrent Count : %d", unauthAccess);
        break;
    default:
        printf("Invalid option entered.\nPlease try again.");
        goto rerun;
    }
}
int numOfUsers()
{
    return (sizeof(user) / sizeof(user[0]));
}
int main()
{
    char currentUserName[10];
    char password[10];

    int i, invalid = 0;
    system("cls");
    printf("Welcome to Account Management System.\n");
    while (1) //infinite times
    {
        printf("Enter the username: "); //username requested
        gets(currentUserName);
        for (i = 0; i < numOfUsers(); i++) //user is client, check USER struct for client name
        {
            if (strcmp(user[i].name, currentUserName) == 0) //user matched to client list, send for authentication.
            {
                authenticate(currentUserName, i);
            }
            else
            { // user name not found in client list
                printf("Invalid user");
                invalid++;
                system("cls");
            }
        }
    }
    return 0;
}