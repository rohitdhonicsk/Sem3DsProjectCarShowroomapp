
#define BUFFER_SIZE 1000
// declaration of Linklist,stack and queue as a structure
typedef struct node {
  char car_name[2000];
  struct node *next;
} node;

typedef struct {
  char a[MAX][1000];
  int top;
} stack;

typedef struct queue {
  char *car_order[MAX];
  int rear, front;
} queue;
/**************************************************************************************************************************/
// color and Cursur posn and delay function for GUI
COORD xy = {0, 0};
void SetColorAndBackground(int ForgC, int BackC) {
  WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
  ;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
  return;
}
void gotoxy(int x, int y) {
  xy.X = x;
  xy.Y = y;  // X and Y coordinates#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#include <conio.h>
#include <time.h>
#include <windows.h>
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void SetColor(int ForgC) {
  WORD wColor;
  // We will need this handle to get the current background attribute
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  // We use csbi for the wAttributes word.
  if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
    // Mask out all but the background attribute, and add in the forgournd color
    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }
  return;
}

void ClearColor() { SetColor(15); }

void ClearConsoleToColors(int ForgC, int BackC) {
  WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
  // Get the handle to the current output buffer...
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  // This is used to reset the carat/cursor to the top left.
  COORD coord = {0, 0};
  // A return value... indicating how many chars were written
  //   not used but we need to capture this since it will be
  //   written anyway (passing NULL causes an access violation).
  DWORD count;

  // This is a structure containing all of the console info
  // it is used here to find the size of the console.
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  // Here we will set the current color
  SetConsoleTextAttribute(hStdOut, wColor);
  if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
    // This fills the buffer with a given character (in this case 32=space).
    FillConsoleOutputCharacter(hStdOut, (TCHAR)32,
                               csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes,
                               csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    // This will set our cursor position for the next print statement.
    SetConsoleCursorPosition(hStdOut, coord);
  }
  return;
}
void delay(int number_of_seconds) {
  // Converting time into milli_seconds
  int milli_seconds = 1000 * number_of_seconds;

  // Stroing start time
  clock_t start_time = clock();

  // looping till required time is not acheived
  while (clock() < start_time + milli_seconds)
    ;
}
/**********************************************************************************************************************/
// function of stack

void push(stack *s, char *str) {
  if (s->top == MAX - 1)
    printf("overflow");
  else
    strcpy(s->a[++s->top], str);
}

void display(stack *s) {
  int i;

  for (i = s->top; i >= 0; i--) {
    printf("%s ", s->a[i]);
  }
}
/*********************************************************************************************************************/
// function of queue to get order
int Enqueue(queue *q, char *order_name) {
  int c;

  if (q->rear == MAX - 1)
    printf("Sorry,we are currently unavailable for orders\n");  // Queue_Full
  else {
    q->rear = q->rear + 1;

    q->car_order[q->rear] = order_name;

    c = q->rear;
    return c + 1;
  }
  return -1;
}

char *Display_Front(queue *q) {
  return q->car_order[q->front];  // Display_front_Of_Queue
}

void Dequeue(queue *q) {
  if (q->front == q->rear + 1)
    printf("Sorry,We couldn't find any record\n");  // Queue_empty(no order)
  else {
    // top of stack=Display_Front(&q)
    q->front = q->front + 1;
  }
}
void display_order(queue *q) {
  int i;

  for (i = q->front; i <= q->rear; i++) {
    printf("%s ", q->car_order[i]);
  }
}
/**************************************************************************************************************/
// linklist to store car name
node *head = NULL, *last = NULL;
void display_list(node *head) {
  node *temp = head;
  while (temp != NULL) {
    printf("%s ===>", temp->car_name);
    temp = temp->next;
  }
}
//*************************************************************************************************************
//Writing Car Name from linklist To File....
void writefile()
{
    FILE * fptr;
    fptr = fopen("carname.txt", "a");
    node * iterator=head ;

    if(fptr==NULL)
    {
        printf("Error\n");
    }

    else
    {
        while(iterator!= NULL)
        {
            fprintf(fptr, "%s\n", iterator->car_name);
            iterator= iterator->next;
        }
    }

    fclose(fptr);
    }

node create_list(int n) {
  node *temp = NULL, *new_node = NULL;
  int i;
  gotoxy(10,11);
  
  printf("Enter the data you want to insert in the list: \n");
  for (i = 0; i < n; i++) {
    new_node = (node *)malloc(sizeof(node));
    gotoxy(10,13+i);
	printf("Car name (%d): ", i + 1);
    fflush(stdin);
    scanf("%[^\n]%*c", new_node->car_name);

    new_node->next = NULL;

    if (last) last->next = new_node;
    if (!head)
      head = new_node;
    else if (!last)
      temp->next = new_node;
    temp = new_node;
    last = NULL;
  }
  last = temp;
  writefile();
}
int search(char car_name_d[]) {
  int j = 1;
  node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->car_name, car_name_d) == 0) {
      return j;
    } else {
      j++;
    }
    temp = temp->next;
  }

  if (!temp) return 0;
  return j;
}


int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
     
    *line = -1;
    *col  = -1;

    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {     // FAILS when len == 0
  		//buffer[len -1] = '\0';
       
        *line += 1;
		str[strlen(str)-1]='\0';
        // Find first occurrence of word in str
        pos = strstr(str, word);
          
        if (pos !=NULL&&strcmp(str,word)==0)
          {
             // First index of word in str is 
            //fseek(fptr,0,SEEK_CUR-5);
			//fprintf(fptr,"%c",'a');           
            // Memory address of pos - memory
            // address of str.
            
		    *col = (pos - str);
            break;
        }
    }


    // If word is not found then set line to -1
    if (*col == -1)
        *line = -1;

    return *col;
}


void deletec(char car_name_d[]) 
{ 
    // Store head node 
  node* temp = head, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && strcmp(temp->car_name, car_name_d) == 0) 
    { 
        head = temp->next;   // Changed head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL &&strcmp(temp->car_name, car_name_d) != 0) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 
  
    free(temp);  // Free memory 
} 
/***************************************************************************************************************/
/***************************************************************************************************************/
// Function for being admin to get access for car addition and deletion
void admin() {
  int ch, n, i;
   int line, col;
   

  char carname_to_delete[2000];
  char pass[10];
  char username[10];
  char adduser[10];
  char addpass[40];
  char ch1;
  FILE *fptr;
  fptr=fopen("Login.txt","r+");
  gotoxy(50,12);
  SetColor(10);
  gotoxy(20, 8);
  printf("Enter UserName =  ");
  scanf("%s", username);

  SetColor(7);
  gotoxy(20, 12);
  printf("Enter password = ");
  scanf("%s", pass);
  indexOf(fptr, username, &line, &col);
  fscanf(fptr, "%s", addpass);


  if ( !strcmp(pass,addpass) && line!=-1) {
    gotoxy(18, 16);
     
    printf("  Loading  ");
   SetColorAndBackground(7, 7);
    for (i = 0; i < 8; i++) {
      delay(1);
      printf("|");
    }
     SetColorAndBackground(15, 0);
    system("cls");
    while (1) {
     gotoxy(5,5);
      printf(
          " 1. Add Car Enter\t2. display Car\t3. Delete Car data\t4. Add Company Member\t5.Exit\n");
      gotoxy(10,7);
	  printf("Enter Your Choice = ");
	 
	  scanf("%d", &ch);
       gotoxy(10,9);
	  switch (ch) {
        case 1: {
          printf("Enter no. of Car you want to add ");
		  scanf("%d", &n);
          create_list(n);
          delay(1);
          system("cls");

          break;
        }
        case 2: {
          display_list(head);
          delay(2);
		  system("cls");
          break;
        }
        case 3: {
          printf("Enter Car name to Delete: ");
		  scanf("%s", carname_to_delete);
          deletec (carname_to_delete);
          delay(1);
          system("cls");
		  break;
        }
        case 4:
        	 fptr = freopen("Login.txt","a",fptr);
        	printf("Enter User Name ");
        	scanf("%s",adduser);
        	fprintf(fptr,"%s\n",adduser);
        	gotoxy(10,11);
			printf("Enter Password = ");
        	scanf("%s",addpass);
        	fprintf(fptr,"%s\n",addpass);
        	delay(1);
          system("cls");
          break;
        	
        	
        	
        case 5: {
          return;
          break;
        }
      }
    }
  } else {
    gotoxy(18, 16);
    printf("Incorrect Password or User name");
    delay(2);
  }
}
/************************************************************************************************************************/
// function for Buyer/Guest for taking Car Order
int guest() {
  queue q;
  q.rear = -1;
  q.front = 0;
  stack s;

  s.top = -1;
  int ch, order_no, search_index;
  char k, pass[1000];
  char detail[MAX][20];
  
  char order_name[1000];
  
  gotoxy(20,8);
  SetColor(14);  
  printf("Please provide ur information --->");
   gotoxy(5,10);
    SetColor(10);
	printf("Enter Your Data");
    gotoxy(5,12);
     SetColor(11);
    fflush(stdin);
	printf("Name :");
	gets(detail[0]);
	gotoxy(5,13);
   printf("Contact No :");
    gets(detail[1]);
    
	gotoxy(5,14);
	printf("Location  : ");
    gets(detail[2]);
	gotoxy(5,15);
	printf("Email Address: ");
	gets(detail[3]);
	
	while (1) {
		
	gotoxy(50,10);
	 SetColor(10);
    printf("Enter Cart Information");
    gotoxy(50,12);

     SetColor(11);
    printf("1.Buy Car");
    gotoxy(50,13);
	printf("2.See Your Order");
    gotoxy(50,14);
	printf("3.Display all car present in shop");
    gotoxy(50,15);
    /*
	printf("4.See Your Order");
	gotoxy(50,16);*/
	 SetColor(15);
   printf("Enter Your Choice Here : ");
	scanf("%d", &ch);
    switch (ch) {
      case 1:
  			gotoxy(35,18);
        printf("Enter name of car you want to purchase : ");
        fflush(stdin);
        gets(order_name);
          FILE * fptr;
         fptr = fopen("carname.txt", "r");
         int line,col;
        indexOf(fptr, order_name, &line, &col);
        fclose(fptr);
        if (line == -1) {
          gotoxy(35,20);
		  printf(
              "sorry,We don't Have a Car...We Will add and notify u as soon as "
              "possible\n");
        } else {
          order_no = Enqueue(&q, order_name);
			gotoxy(35,20);
          printf(
              "Your order no is %d \nThanks You For Purchasing Car...\nWe will "
              "Contact You shortly\n",
              order_no);
          deletec(order_name);
          Dequeue(&q);
          push(&s, order_name);
        }

        break;

      /*case 2:
      	gotoxy(35,18);
        printf("The current order is : %s ", Display_Front(&q));
        break;

      case 3:

        printf("Enter password to Verify that u r member of Company ");

        scanf("%s", pass);

        if (!strcmp(pass, "Ro&san")) {
          display_order(&q);
        } else
          printf("incorrect password");
        break;*/
      
      case 2:
      	gotoxy(35,18);
        display(&s);
        break;
      case 3:
      	system("cls");
         gotoxy(10,6);
         fptr = fopen("carname.txt", "r");
         char c;
         c = fgetc(fptr);
		 printf("Below are the list of car");
		 gotoxy(11,8); 
         int count=1;
         
	while (c != EOF) 
    { 
    
	if(c=='\n'){
	    gotoxy(11,8+count);
		
		
		count++;
	
       } 
       fflush(stdout);
      
      printf ("%c", c); 
        c = fgetc(fptr);   
	   
	    
        
    } 
    break;
      default:
      	gotoxy(35,18);
        printf(
            "Sorry,we couldn't recognize your query\nMake sure you have "
            "entered the correct button");
        break;
    }
    gotoxy(20,23);
    printf("Wish to continue (Y/N) ? : ");
    fflush(stdin);
    scanf("%c", &k);
    if (k != 'Y' && k != 'y') {
      return 0;
    }
    system("cls");
    gotoxy(5,6);
    printf("We are Again Ready To Serve You...");
  }
  return 0;
}
/********************************************************************************************************/
// HOME PAGE******

int main() {
  int i, n;
  SetColorAndBackground(9, 14);
  gotoxy(30, 5);
  printf("Welcome to Car Shop\t Ds Lab project 2");
  SetColorAndBackground(15, 0);
  gotoxy(20, 10);
  
  SetColorAndBackground(8, 14);
  printf(" **Name Of Group Member** ");
  gotoxy(22, 13);

  SetColorAndBackground(14, 8);
  printf("1)Rohit Kumar Gupta");
  gotoxy(22, 16);
  printf("2)Sandeep Das");
  gotoxy(60, 10);
  SetColorAndBackground(8, 14);
  printf("**Roll No**");
  gotoxy(60, 13);
  SetColorAndBackground(14, 8);
  printf("218\n");
  gotoxy(60, 16);
  printf("203");

  for (i = 0; i < 5; i++) {
    gotoxy(4, 18 + i);
    delay(1);
    SetColorAndBackground(15, 13);
    printf("Service Starting In %d Sec.\n", 5 - (i + 1));
  }
  SetColorAndBackground(4, 4);
  while (1) {
    
    system("cls");
    SetColorAndBackground(15, 0);
    gotoxy(20, 7);
    SetColor(15);
    SetColorAndBackground(15, 13);
	printf("Hii Please Select Option Given Below");
    SetColorAndBackground(15, 0);
    SetColor(14);
    gotoxy(20, 10);
    printf("1)Guess Login/Customer");
    gotoxy(20, 12);
    printf("2)Company Member/Admin");
    gotoxy(20, 14);
    printf("3)Exit/End");
    gotoxy(20, 16);
    SetColor(1);
    scanf("%d", &n);
    switch (n) {
      case 1:
        system("cls");

        guest();
    
        break;

      case 2:
        system("cls");
        admin();

        break;
      case 3:
        return 0;
        break;
      default:
        printf("Wrong Choice");
        delay(2);
    }
  }
}

