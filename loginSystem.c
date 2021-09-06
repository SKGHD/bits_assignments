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
#include <time.h>

struct user //struct user defined with name, password and balance in account
{
    char name[10], password[10];
    float balance;
    int lock;
};

struct user user_arr[] = {
    {"admin", "admin", 2000, 0},
    {"aka", "aka", 2002, 1},
    {"sangram", "pass", 2222, 0}};
int unauthAccess = 0;

// function prototypes
void authenticate(char[], int);
void userFunctions(int);
int numOfUsers();
void adminFunctions();
int date();
// Prog start
void authenticate(char username[], int index) //authentication procedure for a user
{
    int maxtry = 3, attempts = 1;
    // char ch, currentUserName[10],
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
            printf("Enter Your Password  : ");
            gets(password);
            if (strcmp(user_arr[index].password, password) == 0) // user authenticated
            {
                if (strcmp(username, "admin") == 0) //Loading Admin Screen
                    adminFunctions();
                else //Load user Screen
                    userFunctions(index);
            }
            else
            {
                attempts++; // wrong password entered
                printf("Wrong password entered.\nNumber of tries left before account gets locked: %d", maxtry - attempts);
                getchar();
            }
        }
        if (attempts == 3 && strcmp(username, "admin") != 0) // no of attempts exceeded, account locked if not admin
        {
            printf("Maximum tries for wrong attempt reached. Your account is now locked!");
            user_arr[index].lock == 1;
            unauthAccess++; //Increment unauthorised access count
        }
    }
}
int date() // Checking current date for monthly reports
{

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int day = local->tm_mday;

    return day;
}
void userFunctions(int index) // user functions
{
    system("CLS");
    int a;
    float update;
    printf("Welcome %s \n", user_arr[index].name);
    printf("Choose option\n 1 = View Account Balance \n 2 = Balance Transfer \n 3 = Update account balance\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        printf("Account balance is : %d", user_arr[index].balance);
        break;
    case 2:
        printf("Balance transfer initiated");
        printf("Updated balance :%s", user_arr[index].balance);
        break;
    case 3:
        printf("Enter new balance");
        scanf("%f", &update);
        user_arr[index].balance = update;
        printf("Updated balance : %s", user_arr[index].balance);
        break;
    default:
        printf("Invalid option entered.\nPlease try again.");
        userFunctions(index); //Recalling method to display options to user once again
    }
}

void adminFunctions() //admin functions, make admin user_arr[0]
{

    char username[10], password[10];
    int usercount = 0, temp, i, bal, pos = 0;
    // Reset Monlthy report on 1st day of Month
    if (date() == 1)
    {

        /* code */
        unauthAccess = 0;
    }
rerun: //Label to re display options
    printf("\nEnter your choice : \n1 - Account unlock\n2 - View Monthly Unauthorised Access Report \n3 - Reset Monthly Unauthorised Access Report\n");
    scanf("%d", &temp);

    switch (temp)
    {

    case 1: // unlock user
            printf("\n");
		    for (i = 0; i < numOfUsers(); i++)
		        {
		        printf("%d - %s \n",i,user_arr[i]);
		    	}
		    	
		        printf ("Enter user id - ");
		        scanf("%d",&pos);
		                    
		        if (pos > 3) 
		        {
					printf("Invalid option");
		            goto rerun;
		        }
		        else
		        {
		        user_arr[pos].lock = 0;
		        printf("Account of User : %s unlocked successfully! \n", user_arr[pos].name);
				}
				goto rerun; 
    case 2:
        printf("Total Unauthorised Access Count :%d", unauthAccess);

        break;
    case 3:
        unauthAccess = 0;
        printf("Reset Monthly Unauthorised Access Report Successful!\nCurrent Count : %d", unauthAccess);
        break;
    default:
        printf("Invalid option entered.\nPlease try again.");
        goto rerun;
    }
}
int numOfUsers()
{
    return (sizeof(user_arr) / sizeof(user_arr[0]));
}
int main()
{
    char currentUserName[10];
    char password[10];

    int i, invalid = 0, flag = 0;
    system("cls");
    printf("Welcome to Account Management System.\n");
    while (1) //infinite times
    {
        printf("Enter the username: "); //username requested
        gets(currentUserName);
        for (i = 0; i < numOfUsers(); i++) //user is client, check USER struct for client name
        {
            if (strcmp(user_arr[i].name, currentUserName) == 0) //user matched to client list, send for authentication.
            {
                authenticate(currentUserName, i);
                flag = 1;
            }
        }
        if (flag != 1)
        {
            printf("%s not found! Press ENTER to try again!", currentUserName);
            invalid++;
            getchar();
            system("CLS");
        }
    }
    return 0;
}
