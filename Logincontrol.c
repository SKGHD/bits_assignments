#include< conio.h >
#include< stdio.h >
#include< dos.h >
#include< string.h >


struct user				//struct user defined with name, password and balance in account 
{
	char *name,*password;
	float balance;
	int lock = 0 ;
	int invalidattempts=0;
};
struct user[10];



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
	   if(strcmp(user[position].password,password==0)			// user authenticated
	   {
	   	attempts=1;
	   }
	   else
		attempts++;												// wrong password entered
	}
	if(attempts==3)										// no of attempts exceeded, account locked
		user[position].lock==1;
	}
	
}


int userfunctions(int position)										// user functions
{
	int a,update;
	printf('Choose option \n 1=Account Balance \t2=Balance Transfer \t3=Update account balance');
	scanf(a);
	switch(a)
	{
		case 1 : 	printf('Account balance is : %d',user[position].balance);
		case 2 : 	printf('Balance transfer initiated');
		case 3 : 	printf('Enter new balance');
					scanf('update');
					user[position].balance=update;

					
	}	
	
int adminfunctions()									//admin functions, make admin user[0]
{
	char choice;
	char *username,*password;
	int usercount=0, temp; 
	printf("Enter  1 - User Addition  2 - Account unclock");
	scanf(temp);
	switch(temp)
	{ case 1 :  while (temp==1)									//user addition
				{
					clrscr();
					if(usercount==10)
					{
						printf(" No more users can be added ") ;
						break;
					}
					printf(" Continuing to add user, If not required press - n ");  // input if admin wants to continue user addition
					scanf(%c,&choice);
					if(choice=='n')					// admin choice
						break;
					usercount++;
					printf(" Enter Username");
					gets(username);
					printf("Enter Password");
					gets(password);
					user.name[usercount]=username;
					user.password[usercount]=password;
				}
		
		case 2:          	// unlock user
							printf("Enter username");
							gets(username)
							for(i=1;i<=10;i++)
							{
								if(strcmp(username,user[i]==0))
									{user[i].lock=0; break ; }
							}

	}	
	
	
void main()
{
	char *currentUserName;			
	char *password;
	//struct user[10];
	user[0].user='admin';			//admin created
	user[0].password='admin';
	int i,invalid=0;
	clrscr();
	while(1)				//infinite times
	{
		printf("Enter the username: ");					//username requested		
		gets(currentUserName);
		for(i=0;i<=10;i++)									//user is client, check USER struct for client name
		{
			if(strcmp(user[i].name,currentUserName)==0)		//user matched to client list, send for authentication.
				authenticate(currentUsername,i);				
			else
			{											// user name not found in client list
				printf ("Invalid user"); invalid++;
				clrscr();
			}
		}
	}
}