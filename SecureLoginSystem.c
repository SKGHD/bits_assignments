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
#include <conio.h>

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
void displayOptions();
int main();

// Prog start
int authenticate(char username[], int index) //authentication procedure for a user
{
    int maxtry = 3, attempts = 1, ch;

    char password[10];
checkAuth:                         //label for goto
    if (user_arr[index].lock == 1) //account check for lock status
    {
        system("CLS");
        printf("Account Locked. Contact Admin to unlock your account!");
        printf("\nPress Enter to Return to Login Page.\n");
        getch();
        return 2;
    }

    else
    {
        system("CLS");
        printf("Found User : %s \n", username);
        printf("Enter Your Password  : ");
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
            if (strcmp(username, "admin") != 0) // no of attempts exceeded, account locked if not admin
            {
                printf("Wrong password entered.\nNumber of tries left before account gets locked: %d\n", maxtry - attempts);
                if (attempts == maxtry)
                {
                    printf("Maximum tries for wrong attempt reached. Your account is now locked! \n");
                    user_arr[index].lock = 1;
                    unauthAccess++; //Increment unauthorised access count
                    goto checkAuth; // for unauthorised access
                }
                attempts++; // wrong password entered so incrementing by 1
            }
            printf("Try entering password again ?\n 1 - Yes \n 2 - No\n");
            scanf("%d", &ch);
            if (ch == 1)
            {
                system("CLS");
                goto checkAuth;
                ch = 0;
            }
            else
                return 2;
        }
        //        }
    }
    return 2;
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
    int a, ch;
    float update;

    system("CLS");
    printf("Welcome %s ", user_arr[index].name);
    printf("\nChoose option\n 1 = View Account Balance \n 2 = Balance Transfer \n 3 = Update account balance\n");
    scanf("%d", &a); //Options available displayed
    switch (a)       //user input used
    {
    case 1: //Account balance displayed
        printf("---------------------------------------------------------");
        printf("\nAccount balance is : %.2f \n", user_arr[index].balance);
    useroption: //use after user function complete
        printf("\nPress\n 1 - Go to User Menu \n 2 - Go to Login Screen\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            userFunctions(index);
        case 2:
            main();
        default:
            printf("Invalid Option:");
            goto useroption;
        }
    case 2: // Balance transfer

        printf("\nEnter the amount you wish to transfer :");
        scanf("%f", &update);
        printf("Balance transfer initiated.");
        system("CLS");
        user_arr[index].balance -= update;
        printf("Updated balance :%.2f", user_arr[index].balance);
        goto useroption;

    case 3: // Balance update
        printf("Enter new balance : ");
        scanf("%f", &update);
        user_arr[index].balance = update;
        printf("Updated balance : %.2f", user_arr[index].balance);
        goto useroption;
    default: //incorrect option selected
        goto useroption;
    }
    return 0;
}

int adminFunctions() //admin functions,  admin is set to user_arr[0]
{

    char username[10], password[10], lockStatus[10];

    int usercount = 0, temp, i, bal, pos = -1, ch;
    // Reset Monlthy report on 1st day of Month
    if (date() == 1)
    {

        unauthAccess = 0;
    }
rerun: //Label to re display options

    printf("Enter your choice : \n1 - Lock\\Unlock User Account\n2 - View Monthly Unauthorised Access Report \n3 - Reset Monthly Unauthorised Access Report\n");
    scanf("%d", &temp);
    system("CLS");

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

        printf("\nEnter your choice :");
        scanf("%d", &pos);

        if (pos >= numOfUsers() || pos == 0) // check if the entered  position is invalid
        {
            printf("\n Invalid option selected!\nPlease try again! \n");

            goto rerun;
        }
        else
        {
            user_arr[pos].lock = (user_arr[pos].lock == 1) ? 0 : 1; // locked account unlocked and vice versa

            printf("Account of User : %s %s successfully! \n", user_arr[pos].name, (user_arr[pos].lock == 1) ? "Locked" : "Unlocked");
        }
        goto option;

    case 2:
        printf("Total Unauthorised Access Count :%d\n", unauthAccess);
        goto option;
    case 3:
        unauthAccess = 0;
        printf("Reset Monthly Unauthorised Access Report Successful!\nCurrent Count : %d\n", unauthAccess);
    option:
        printf("Display Admin Options again:\n 1 - Yes \n 2 - No (Logout) \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            system("CLS");
            goto rerun;
        case 2:
            printf("Logging out user\n");
            printf("Press any key to Continue\n"); //pause for input
            getchar();
            main();
        default:
            printf("Invalid option entered.\n");
            printf("Press any key to Continue\n"); //pause for input
            getchar();
            //	system("CLS");
            goto option;
        }

    default:
        printf("Invalid option entered.\n");
        printf("Press any key to Continue\n");
        getch();
        system("CLS"); //pause for input
        goto rerun;
    }
    return 0;
}
int numOfUsers() // Returns number of users in memory
{
    return (sizeof(user_arr) / sizeof(user_arr[0]));
}
void displayOptions() // helper method to display options to STDOUT
{
    int ch;
    printf("Return to Login Screen?\n 1 - Yes\n 2 - No\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        main();
        break;
    case 2:
        exit(0); //exiting the program

    default:
        printf("\nInvalid Input!");
        printf("Press any key to Continue\n"); //pause for input
        getch();
        break;
    }
}

// Main Method
int main()
{

    char currentUserName[10];
    char password[10], a;
    int i, flag, authStatus;
homepage:
    flag = 0;
    system("cls");
    printf("Welcome to Account Management System.\n");

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
    if (flag != 1) //unknown user , send to unauthorised access attempt
    {
        printf("\n%s not found! \n", currentUserName);
        unauthAccess++;
        printf("Press any key to Continue\n"); //pause for input
        getch();
        goto homepage;
    }

    // Handling routing
    switch (authStatus)
    {

    case 0:

        adminFunctions();
        displayOptions();

        break;
    case 1:
        userFunctions(i);
        displayOptions();
        break;
    case 2:
        goto homepage;
        break;
    }
    return 0;
}
