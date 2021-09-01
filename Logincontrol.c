#include< conio.h >
#include< stdio.h >
#include< dos.h >
#include< string.h >


struct user				//struct user defined with name, password and balance in account 
{
	char *name,*password;
	float balance;
	int lock = 0 ;
}



int authenticate(char username,int position)			//authentication procedure for a user
{
	int maxtry = 3 , attempts = 1 ;
	char ch;
	if(user[position].lock==1)							//account check for lock status
	{
		printf ("Account Locked"); break;				
	}
	
	else
	{
	
	while(attempts < = maxtry)							//no of incorrect attempts checked
	{
	   userNameCorrect = 0;
	   clrscr();
	   printf("User Name : %s\n",currentUserName);
	   printf("Password  : ");
	   gets(password);
	   if(strcmp(user[position].password,password==0)
	   {
	   	attempts=1;
	   }
	}
	if(attempts==3)										// no of attempts exceeded, account locked
		user[position].lock==1;
	}
	
	
int userfunctions()										// user functions
{
	}	
	
int adminfunctions()									//admin functions, make admin user[0]
{
	char choice;
	char *username,*password;
	int usercount=0, temp=0; 
	
	while (temp=0)									//user addition
	{
		clrscr();
		if(usercount==10)
		{
			printf(" No more users can be added ") ;
			break;
		}
		printf(" Continuing to add user, If not required press - n ");
		scanf(%c,&choice);
		if(choice=='n')
			break;
		usercount++;
		printf(" Enter Username");
		gets(username);
		printf("Enter Password");
		gets(password);
		user.name[usercount]=username;
		user.password[usercount]=password;
	}
	
	}	
	
	
void main()
{
	char *currentUserName;			
	char *password;
	struct user[10];
	int i,invalid=0;
	clrscr();
 
	/*printf("Enter the username: ");					//username requested		
	gets(currentUserName);
	
	if(strcmp(currentUserName,"admin")==0)				//check if user is admin or client
	{
	clrscr();
	   printf("User Name : %s\n",currentUserName);				//user is admin
	   printf("Password  : ");
	   gets(password);	
	}
	else*/
	{
		for(i=0;i<=10;i++)									//user is client, check USER struct for client name
		{
			if(strcmp(user[i].name,currentUserName)==0)		//user matched to client list, send for authentication.
				authenticate(currentUsername,i);				
			else											// user name not found in client list
			 printf ("Invalid user"); invalid++;
		}

	}
	
	
}