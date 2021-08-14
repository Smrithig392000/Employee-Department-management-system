#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee
{
    char emp_name[50];
    int emp_age;
    int emp_ID;
    char emp_dept[20];
    struct employee *next;
};

struct employee *insert(struct employee *front, int id,char name[],int age,char dept[])
{
    struct employee *temp;
    temp = (struct employee*)malloc(sizeof(struct employee));

    if (temp == NULL)
    {
        printf("\n Cannot Insert Employee Details !!! \n");
        exit(2);
    }
    temp->emp_ID = id;
    strcpy(temp->emp_name, name);
    temp->emp_age= age;
    strcpy(temp->emp_dept, dept);
    temp->next = front;
    front = temp ;
    return(front);
}

void bubbleSort(struct employee *front)
{
    int k;
    struct employee *ptr,*head,*temp;
    struct employee *lptr = NULL;

    head=front;
    if (front == NULL)
        return;

    do
    {
        k = 0;
        ptr = front;

        while (ptr->next != lptr)
        {
            if (ptr->emp_ID > ptr->next->emp_ID)
            {
                swap(ptr, ptr->next);
                k = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    }
    while (k);

}

struct employee *deleteNode(struct employee *front, int id)
{
     struct employee *temp , *prev;
     temp=front;
     printf("Employee Details deleted !!! \n");

    if (temp != NULL && temp->emp_ID == id) {
        front = temp->next;
        free(temp);
        return(front);
    }

    while (temp != NULL && temp->emp_ID!= id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        printf("Employee not found\n");

    prev->next = temp->next;

    free(temp);
    return (front);
}



void swap(struct employee *ptr1, struct employee *ptr2)
{
    int temp = ptr1->emp_ID;
    ptr1->emp_ID = ptr2->emp_ID;
    ptr2->emp_ID = temp;
}


void display(struct employee  *front)
{
    struct employee *ptr;

    for (ptr = front; ptr != NULL; ptr = ptr->next)
    {
        printNode(ptr);
    }
}

void search(struct employee *front, int ID)
{
    struct employee *ptr;

    for (ptr = front; ptr != NULL; ptr = ptr -> next)
    {
        if (ptr->emp_ID == ID)
        {
            printNode(ptr);
            return;
        }
    }
    printf("\n Employee not found ");
}


void printNode(struct employee *ptr)
{
    printf("\n Employee ID          : %d", ptr->emp_ID);
    printf("\n Employee Name        : %s", ptr->emp_name);
    printf("\n Age                  : %d", ptr->emp_age);
    printf("\n Employee Department  : %s", ptr->emp_dept);
    printf("\n-------------------------------------\n");
}

void edit(struct employee *front,int id)
{
    int opt,new_age;
    char new_name[50],new_dept[20];
    struct employee *ptr;
    ptr=front;
    printf("\nPress 1 for Employee Name  change");
    printf("\nPress 2 for Employee Age  change");
    printf("\nPress 3 for Employee Department  change");
    printf("\nEnter your choice: ");
    scanf("%d",&opt);
    printf("\n-------------------------------------\n");

for (ptr = front; ptr != NULL; ptr = ptr -> next)
{
    if(ptr->emp_ID==id)
    {
    switch(opt)
    {
    case 1:
        printf("\nEnter the new name: ");
        scanf("%s",new_name);
        strcpy(ptr->emp_name,new_name);
        break;
    case 2:
        printf("\nEnter the new age: ");
        scanf("%d",&new_age);
        ptr->emp_age=new_age;
        break;
    case 3:
        printf("\nEnter the new department: ");
        scanf("%s",new_dept);
        strcpy(ptr->emp_dept,new_dept);
        break;
    default:
        printf("\nInvalid Input !!!!! Please enter the correct choice");
        break;

    }
    }
    if(ptr==NULL)
    {
       printf("\nEmployee not found !!!!\n");
       break;
    }


}
}

void createfile(struct employee *front)
{
    struct employee *temp;
    temp=front;
     FILE *fp;
     int h=0;
     char *filename="Employee details.csv";
		fp=fopen(filename,"w+");
		fprintf(fp,"S.No,Employee ID,Employee Name,Employee Age,Department\n");
		for(temp = front; temp != NULL; temp = temp->next)
		{
			fprintf(fp,"%d,%d,%s,%d,%s\n",h+1,temp->emp_ID,temp->emp_name,temp->emp_age,temp->emp_dept);
			h++;
		}
		fclose(fp);


}

int main()
{
    struct employee *linkList;
    char name[50],dept[20];
    int ID,age,choice;

    linkList = NULL;
    printf("\n\t   EMPLOYEE-DEPARTMENT MANAGEMENT SYSTEM \n");
    printf("\t---------------------------------------------\n");
    do
    {
    printf("\n\n---------------------------------------------\n");
    printf("Press 1 to INSERT an Employee details\n");
    printf("Press 2 to DELETE an Employee details\n");
    printf("Press 3 to DISPLAY  all Employee details\n");
    printf("Press 4 to SEARCH a particular Employee details \n");
    printf("Press 5 to EDIT a particular Employee details \n");
    printf("Press 6 to EXIT                              \n");
    printf("---------------------------------------------\n");
    printf("\nEnter your choice:  ");
    scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("\nEnter the Employee ID        : ");
            scanf("%d", &ID);
            printf("Enter the Employee name      : ");
            scanf("%s",name);
            printf("Enter the Employee age       : ");
            scanf("%d",&age);
            printf("Enter the Employee Department: ");
            scanf("%s",dept);
            linkList = insert(linkList,ID,name, age,dept);
            bubbleSort(linkList);
            createfile(linkList);
            break;
        case 2:
            printf("\n\n Enter the Employee ID to be deleted: ");
            scanf("%d", &ID);
            linkList = deleteNode(linkList, ID);
            createfile(linkList);
            break;
        case 3:
            if (linkList == NULL)
            {
                printf("\n No details of Employees in Database\n");
                break;
            }
            printf("\n Employee Details...\n");
            printf("---------------------------------------------\n");
            display(linkList);
            break;
        case 4:
            printf("\n\n Enter the employee ID for searching: ");
            scanf("%d", &ID);
            printf("\n Employee Details...\n");
            printf("---------------------------------------------\n");
            search(linkList, ID);
            break;
        case 5:
            printf("\nEnter the Employee ID for editing :");
            scanf("%d",&ID);
            edit(linkList,ID);
            createfile(linkList);
            break;
        case 6:
            break;
        }
    } while (choice != 6);
    return 0;
}
