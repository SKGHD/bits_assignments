// Rewritten

// •	The system should accept the user’s credentials and check if the user is legitimate.
// •	In case the user is legitimate it should ask the user whether he wants to know the account balance, make fund transfer and update balance.
// •	In case user is not legitimate inform the admin about unauthorized access
// •	If more than 3 wrong login attempts are made for the user then lock the account and do not allow access for that account
// •	Secured password based account unlock by legitimate user
// •	Get monthly reports of unauthorized access

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct user //struct user defined with name, password and balance in account
{
    char name[10], password[10];
    float balance;
    int lock;
};

struct user user_arr[] = {
    {"admin", "admin", 2000, 0},
    {"rupesh", "pass", 2002, 1},
    {"amirul", "pass", 5000, 0},
    {"sangram", "pass", 2222, 0}};
int unauthAccess = 0;

// function prototypes
int authenticate(char[], int);
int userFunctions(int);
int numOfUsers();
int adminFunctions();
int date();
// Prog start
int authenticate(char username[], int index) //authentication procedure for a user
{
    int maxtry = 3, attempts = 1;

    char password[10];
    if (user_arr[index].lock == 1) //account check for lock status
    {
        printf("Account Locked. Contact Admin to unlock your account!");
    }

    else
    {

        while (attempts <= maxtry) //no of incorrect attempts checked
        {

            system("CLS");
            printf("Found User : %s \n", username);
            printf("Enter Your Password  : \n");
            scanf("%s", password);
            if (strcmp(user_arr[index].password, password) == 0) // user authenticated
            {
                printf("Successfully logged in!\n");
                system("CLS");
                if (strcmp(username, "admin") == 0)
                    return 0; //for Admin Screen

                else
                    return 1; //for user Screen
            }
            else
            {
                printf("Wrong password entered.\nNumber of tries left before account gets locked: %d", maxtry - attempts);
                attempts++; // wrong password entered
                printf("\nPress ENTER to try again!");
                getchar();
            }
        }
        if (attempts == 3 && strcmp(username, "admin") != 0) // no of attempts exceeded, account locked if not admin
        {
            printf("Maximum tries for wrong attempt reached. Your account is now locked!");
            user_arr[index].lock = 1;
            unauthAccess++; //Increment unauthorised access count
            return 2;       // for unauthorised access
        }
    }
    return -1; // for error
}
int date() // Checking current date for monthly reports
{

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int day = local->tm_mday;

    return day;
}
int userFunctions(int index) // user functions
{
    system("CLS");
    int a;
    float update;
    printf("Welcome %s ", user_arr[index].name);
    printf("\nChoose option\n 1 = View Account Balance \n 2 = Balance Transfer \n 3 = Update account balance\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        printf("---------------------------------------------------------");
        printf("\nAccount balance is : %.2f ", user_arr[index].balance);
        break;
    case 2:

        printf("\nEnter the amount you wish to transfer :");
        scanf("%f", &update);
        printf("Balance transfer initiated.");
        system("CLS");
        user_arr[index].balance -= update;
        printf("Updated balance :%.2f", user_arr[index].balance);
        break;
    case 3:
        printf("Enter new balance :");
        scanf("%f", &update);
        user_arr[index].balance = update;
        printf("Updated balance : %.2f", user_arr[index].balance);
        break;
    default:
        printf("Invalid option entered.\nPlease ENTER to try again.");
        getchar();
        userFunctions(index); //Recalling method to display options to user once again
    }
    return 0;
}

int adminFunctions() //admin functions, make admin user_arr[0]
{

    char username[10], password[10], lockStatus[10];

    int usercount = 0, temp, i, bal, pos = 0;
    // Reset Monlthy report on 1st day of Month
    if (date() == 1)
    {

        unauthAccess = 0;
    }
rerun: //Label to re display options

    printf("Enter your choice : \n1 - Account unlock\n2 - View Monthly Unauthorised Access Report \n3 - Reset Monthly Unauthorised Access Report\n");
    scanf("%d", &temp);

    switch (temp)
    {

    case 1: // unlock user
        printf("  No. |    Name    |  Lock Status  \n");
        printf("-----------------------------------\n");
        for (i = 1; i < numOfUsers(); i++)
        {
            strcpy(lockStatus, (user_arr[i].lock == 1) ? "Locked" : "Unlocked");
            printf("%5d - %12s - %12s \n", i, user_arr[i], lockStatus);
        }

        printf("\nEnter user id :");
        scanf("%d", &pos);

        if (pos > numOfUsers() || pos == 0)
        {
            printf("Invalid option selected!\nPlease try again!");

            goto rerun;
        }
        else
        {
            user_arr[pos].lock = 0;
            printf("Account of User : %s unlocked successfully! \n", user_arr[pos].name);
        }
        break;
    case 2:
        printf("Total Unauthorised Access Count :%d", unauthAccess);

        break;
    case 3:
        unauthAccess = 0;
        printf("Reset Monthly Unauthorised Access Report Successful!\nCurrent Count : %d", unauthAccess);

        break;
    default:
        printf("Invalid option entered.\n");

        goto rerun;
        break;
    }
    return 0;
}
int numOfUsers()  // Returns number of users in memory
{
    return (sizeof(user_arr) / sizeof(user_arr[0]));
}
int main()
{
    char currentUserName[10];
    char password[10];

    int i, invalid = 0, flag = 0, authStatus;
    system("cls");
    printf("Welcome to Account Management System.\n");
    //    while (1) //infinite times
    //    {
    printf("Enter the username: "); //username requested
    scanf("%s", currentUserName);
    for (i = 0; i < numOfUsers(); i++) //user is client, check USER struct for client name
    {
        if (strcmp(user_arr[i].name, currentUserName) == 0) //user matched to client list, send for authentication.
        {
            authStatus = authenticate(currentUserName, i);
            flag = 1;
            break;
        }
    }
    if (flag != 1)
    {
        printf("\n%s not found! Press ENTER to try again!", currentUserName);
        invalid++;
        getchar();
        system("CLS");
    }
    //    }
    // Handling routing
    switch (authStatus)
    {
    case 0:
        adminFunctions();
        break;
    case 1:
        userFunctions(i);
        break;
    case 2:
        main();
        break;
    case -1:
        printf("Unexpected Error Occured!");
        break;
    }
    return 0;
}
