#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeNewLineFromString(char *strVal, size_t size){
    size_t len = strcspn(strVal, "\n");
    if (len < size){
        strVal[len] = '\0';
    }
}
struct Student{
  char studentName[40];
    char studentId[7];
    char pick_up_location[50];
  int routeNumber;

};
void RegisterStudent(){
  struct Student std;
    printf("\n********Register STUDENT*********\n");
    printf("Student Id: ");
    scanf("%s",std.studentId);


    while (getchar() != '\n');

    
  printf("Student Name: ");
    fgets(std.studentName, sizeof(std.studentName), stdin);
    removeNewLineFromString(std.studentName,sizeof(std.studentName));

    printf("Route Number: ");
    scanf("%d",&std.routeNumber);

    while (getchar() != '\n');
    printf("Enter pick_up location: ");
    fgets(std.pick_up_location, sizeof(std.pick_up_location), stdin);
    removeNewLineFromString(std.pick_up_location,sizeof(std.pick_up_location));
    FILE* file = fopen("Studentfile.txt", "a");
    if (file) {
        fprintf(file, "%1.7s*%s*%s*%d\n", std.studentId, std.studentName, std.pick_up_location,std.routeNumber);
        fclose(file);
        printf("\nNew Student has been Added Succussfully\n\n");
    }
    else {
      printf("Error opening file for writing\n");
  }
}

int CheckLocation(){
  int flag=0;
  char route[4];

  printf("\nEnter route number to get tracking info: ");
  scanf("%3s",route);

  removeNewLineFromString(route, sizeof(route));

  char string[100];

  FILE *file =fopen("TrackerInfo.txt","r");

    if (file == NULL) {
        printf("Error opening file");
        return 0;
    }

  while(fgets(string, 1000, file)!= NULL){
    char *busroute = strtok(string,"*");
    if (strcmp(route,busroute)==0){
        flag=1;
        char *temp;
        do{
          temp = strtok(NULL,"*");
          puts(temp);
          }
        while(temp!= NULL);  
    }
  }
  if(flag==0){
    printf("\nRoute not found\n");

  }
  return 0;
}

void ChangeRoute() {
    char studentID[7];
   char newPickUpLocation[50];
    int newRoute;

    printf("\nEnter student ID for route change: ");
    scanf("%s", studentID);

    printf("Enter the new route: ");
    scanf("%d", &newRoute);

	while (getchar() != '\n');
    printf("Enter new pick_up location: ");
    fgets(newPickUpLocation, sizeof(newPickUpLocation), stdin);
    removeNewLineFromString(newPickUpLocation,sizeof(newPickUpLocation));
    FILE *file = fopen("Studentfile.txt", "r");
    if (file == NULL) {
        printf("Error opening file Studentfile.\n");
        return;
    }
    FILE *tempFile = fopen("tempfile.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }
    struct Student std;
    char currentStudentID[7];
    int found = 0;
    while (fscanf(file, "%7s*%39[^*]*%49[^*]*%d", currentStudentID, std.studentName, std.pick_up_location, &std.routeNumber) == 4) {
        if (strcmp(currentStudentID, studentID) == 0) {
            found = 1;
            fprintf(tempFile, "%7.7s*%s*%s*%d\n", currentStudentID, std.studentName, newPickUpLocation, newRoute);
            printf("\nChanging route and pickup location for %s from %d to %d and %s to %s.\n\n", std.studentName, std.routeNumber, newRoute,std.pick_up_location,newPickUpLocation);
        } else {
            fprintf(tempFile, "%7.7s*%s*%s*%d\n", currentStudentID, std.studentName, std.pick_up_location, std.routeNumber);
        }
    }
    if(found==0){
    	printf("\n\nOops!! No Student Found with Id %s\n",studentID);
    }

    fclose(file);
    fclose(tempFile);

    remove("Studentfile.txt");
    rename("tempfile.txt", "Studentfile.txt");
}


int CheckStudent(void)
{
    char input[9];
    int flag=0;
    printf("Enter Student ID: ");
    scanf("%8s",input);
    char string[100];
    FILE *file=fopen("Studentfile.txt","r");
    while(fgets(string,100,file)!=NULL)
    {
        char*id=strtok(string,"*");
        if(strcmp(input,id)==0)
        {
            flag=1;
            char*data=strtok(NULL,"*");


        }
    }
    flag==1?printf("Registered\n"):printf("Not Registered\n");
    fclose(file);
    return 0;
}

int CheckPickup(void) {

    char input[20], string[100];
    char* tokens[100];
    int i= 0,flag=0;;

    printf("Enter your Pickup location:");
    scanf("%s",input);
    FILE *file=fopen("RouteFile.txt","r");
    while(fgets(string,100,file)!=NULL)
    {
        char* route = strtok(string,"*");
        tokens[i++] = route;
        char* pickup = strtok(NULL, "*");
        while(pickup!= NULL)
        {
            tokens[i] = pickup;
            if(strcmp(pickup,input)==0)
            {
                flag=1;

                printf("Location: %s\n", tokens[i]);
                printf("Route number: %s\n", tokens[0]);
                 printf("Time: %s AM\n", tokens[i-1]);
                break;
            }
            pickup=strtok(NULL,"*");
            i++;
        }
        if(flag==1) break;
    }
    if(flag==0)
    {
        printf("Location not found in any Route\n");
    }
    fclose(file);
    return 0;
}

void RegisterDriver()
{
    char driverName[40];
    char driverId[7];
    int routeNumber;
    printf("\n*REGISTER DRIVER\n");
    printf("Enter Drivers' Id: ");
    scanf("%s", driverId);

    while (getchar() != '\n');


    printf("Enter Drivers' Name: ");
    fgets(driverName, sizeof(driverName), stdin);

    removeNewLineFromString(driverName, sizeof(driverName));

    printf("Route Number: ");
    scanf("%d", &routeNumber);

    FILE *file = fopen("Driver.txt", "a");
      if (file)
        { 
            printf("Driver added successfully\n");
            fprintf(file, "\n%s*%d*%s\n",
      driverId,routeNumber, driverName);

        fclose(file);
    }
    else
    {
        printf("Error opening file for writing\n");
    }
}

int AddLocation(){
  char routeNumber[4];
  char cellNum[12];
  char locationURL[50];
  printf("Enter data for location:\n");
  printf("Enter route Number : ");
  scanf("%s",routeNumber);
  printf("Enter cell number : ");
  scanf("%s",cellNum);
  printf("Enter location url: ");
  scanf("%s", locationURL);  
  FILE* file = fopen("TrackerInfo.txt", "a");
    if (file) {
      strcat(locationURL, "/route-");
      strcat(locationURL,routeNumber);
        fprintf(file, "%s*%s*%s*%s\n", routeNumber, cellNum, locationURL, "+92 3XX-XXXXXXX");
        fclose(file);
        printf("\nNew Location has been Added Succussfully\n\n");
    }
    else {
      printf("Error opening file for writing\n");
  }
  return 0;
}



int AddRoute()
{
    int routeNumber;
    char routeData[10000] = "";
    char stop[100];
    char time[5];

    printf("Enter the route number: ");
    scanf("%d", &routeNumber);

    printf("Route %d\n", routeNumber);

    while (1)
    {
        printf("Enter a pickup location (or 'FAST' to finish the route): ");
        scanf("%s", stop);

        if (strcmp(stop, "FAST") == 0)
        {
            strcat(routeData, "FAST\n");
            break;
        }

        printf("Enter the time for this bus stop (HHMM): ");
        scanf("%s", time);

        strcat(routeData, stop);
        strcat(routeData, "*");
        strcat(routeData, time);
        strcat(routeData, "*");
    }

    FILE *file = fopen("RouteFile.txt", "a");
    if(file==NULL)
    {
      printf("Error opening file for writing\n");
      return 0;
    }
    if (file)
    {
        fprintf(file, "%d*%s\n", routeNumber, routeData);
        fclose(file);
    }

    AddLocation();
    return 0;
}


void checkroute(){
        char id[9];
        char string[100];
        printf("\nEnter your ID: ");
        scanf("%8s", id);

        FILE *file = fopen("Studentfile.txt", "r");
        if (file == NULL) {
            printf("Could not open file\n");
            return;
        }

        while (fgets(string, 100, file) != NULL) {
            char *file_id = strtok(string, "*");
            if (file_id != NULL && strcmp(id, file_id) == 0) {
                char *name = strtok(NULL, "*");
                char *location = strtok(NULL, "*");
                char *route_no = strtok(NULL, "*");

                if (name != NULL && location != NULL && route_no != NULL) {
                    printf("Name: %s\n", name);
                    printf("Location: %s\n", location);
                    printf("Route No: %s\n", route_no);
                } else {
                    printf("Error reading file\n");
                }
                break;
            }
        }

        fclose(file);
    }

int main()
{
    int choice = 0, MS = 0, pin = 1234, guess, exit = 0, back;

    
    printf("\n==============================================================================\n");
    printf("\t\t Welcome TO Fast Point Management System [FPMS] \t\t\n");
    printf("\n==============================================================================\n\n");
    

    do
    {
        MS = 0;
        while (MS != 1 && MS != 2 && MS != 3)
        {
            
            printf("Enter 1 for Management\nEnter 2 for Student\nEnter 3 To Exit\nEnter choice: "); 
            scanf("%d", &MS);

            switch (MS)
            {
            case 1:
                
                printf("Welcome to Management options\n");
                printf("Enter pin to proceed: ");
                scanf("%d", &guess);
                
                while (pin != guess)
                {
                    
                    printf("Invalid Password, re-enter the password or enter 0 to exit: ");
                    
                    scanf("%d", &guess);

                    if (guess == 0)
                    {
                        exit = 1;
                        break;
                    }
                }

                do
                {

                    
                    printf("Enter\n1: Add New Route\n2: Change Route\n3: Register Student\n4: Register Driver\n5: Check if Student exists in the database\n"); 
          printf("6: Back to Management Menu\n");
          
                    scanf("%d", &back);

                    switch (back)
                    {
                    case 1:
                         AddRoute();
                        break;
                    case 2:
                         ChangeRoute();
                        break;
                    case 3:
                         RegisterStudent();
                        break;
                    case 4:
                         RegisterDriver();
                        break;
                    case 5:
                         CheckStudent();
                        break;
                    case 6:
                    	break;
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                        break;
                    }
                } while (back != 6);
                break;

            case 2:
                printf("Welcome to Student options\n");

                do
                {

                    printf("Enter\n1: Check Your Route Through ID\n2: Check Routes by Entering Pickup Point\n3: Check location of Bus through route number\n");                    
                    printf("4: Back to Student Menu\n");
                    scanf("%d", &back);

                    switch (back)
                    {
                    case 1:
                         checkroute();
                        break;
                    case 2:
                        CheckPickup();
                        break;
                    case 3:
                         CheckLocation();
                        break;
                    case 4:
				        break;    
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                        break;
                    }
                } while (back != 4);

                break;

            case 3:
                
                printf("\t\t Thank you for using our program :) \t\t");
                
                exit = 1;
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
        }
    } while (exit != 1);

    return 0;
}
