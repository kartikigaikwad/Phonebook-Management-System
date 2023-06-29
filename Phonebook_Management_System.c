#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For Personal Contact - type 0, name, mobile number, email
For Professional Contact - type 1, name, mobile number, email, office number, address,institute/office*/

typedef enum{SUCCESS, FAILURE} status;

struct contact
{
    struct personal *pers;
    struct professional *prof;
};

struct personal
{
    char name[50];
    char mobile_num[10];
    char email[50];
};

struct professional
{
    char name[50];
    char mobile_num[10];
    char email[50];
    char office_num[10];
    char address[50];
    char institute[50];
};

struct phonebook
{
    struct contact *cont;
    struct phonebook *next;
    struct phonebook *prev;
};

void create_cont(struct phonebook** head);
status check(struct phonebook *head);
void edit_cont(struct phonebook **head);
void delete_cont(struct phonebook **head);
void search_cont(struct phonebook *head);
void sort_perproff(struct phonebook **head);
void sort_ascdesc(struct phonebook **head);
void display_cont(struct phonebook *head);
void unio(struct phonebook *head1,struct phonebook *head2);
void remove_duplicate(struct phonebook *head);

int main()
{
    struct phonebook *head,*head1;
    head=NULL;
    head1=NULL;
    int choice;
    int i=0,j=0;
    int input=1;
    int counter=0;
    while(i==0)
    {
    	printf("*********************************\n");
        printf("Enter 1 to create contact\n");
        printf("Enter 2 to edit existing contact \n");
        printf("Enter 3 to delete contact \n");
        printf("Enter 4 to search contact \n");
        printf("Enter 5 to sort on name \n");
        printf("Enter 6 to sort on personal & professional \n");
        printf("Enter 7 to display_cont contact \n");
        printf("Enter 8 to merge contact \n");
        printf("Enter 9 to remove duplicate contact \n");
        printf("Enter 10 to check whether contact exist or not \n");
        printf("Enter 11 to insert for head2(list 2)\n");
        printf("Enter 12 to exit\n");
        printf("***********************************\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                create_cont(&head);
                counter+=1;
                break;
            case 2:
                edit_cont(&head) ;
                break;
            case 3:
                delete_cont(&head) ;
                break;
            case 4:
                search_cont(head) ;
                break;
            case 5:
                for(j=0;j<counter+2/2;j++)
                {
                	sort_ascdesc(&head);
				} 
                break;
            case 6:
                sort_perproff(&head) ;
                break;
            case 7:
                display_cont(head);
                break;
            case 8:
                unio(head,head1) ;
                break;
            case 9:
            	remove_duplicate(head);
                break;
            case 10:
                check(head);
                break;
            case 11:
                create_cont(&head1);
                break;
            case 12:
                i=1;
                break;
            default:
                printf("Choice not valid\n");
        }
    }
    return 0;
}

//1.Insert/create contact: 
//no restriction for the contact with same name

void create_cont(struct phonebook** head)
{
    struct phonebook *temp;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp->cont = (struct contact *)malloc(sizeof(struct contact));
    temp->cont->pers = (struct personal *)malloc(sizeof(struct personal));
    temp->cont->prof = (struct professional *)malloc(sizeof(struct professional));
    temp->next = NULL;
    temp->prev = NULL;
    printf("Enter 1 for personal contact and 2 for professional contact\n");
    int choice=1;
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("Enter name\n");
        scanf("%s",temp->cont->pers->name);
        printf("Enter mobile number\n");
        scanf("%s",temp->cont->pers->mobile_num);
        printf("Enter email\n");
        scanf("%s",temp->cont->pers->email);
        temp->cont->prof = NULL;
    }
    else if(choice==2)
    {
        printf("Enter name\n");
        scanf("%s",temp->cont->prof->name);
        printf("Enter mobile number\n");
        scanf("%s",temp->cont->prof->mobile_num);
        printf("Enter email\n");
        scanf("%s",temp->cont->prof->email);
        printf("Enter office number\n");
        scanf("%s",temp->cont->prof->office_num);
        printf("Enter address\n");
        scanf("%s",temp->cont->prof->address);
        printf("Enter institute/office\n");
        scanf("%s",temp->cont->prof->institute);
        temp->cont->pers = NULL;
    }
    else
    {
        printf("Choice is not valid\n");
    }
    if ((*head) == NULL)
    {
        (*head) = temp;
    }
    else
    {
        temp->next = (*head);
        (*head)->prev = temp;
        (*head) = temp;
    }
   
}

status check(struct phonebook *head)
{
    status retval=FAILURE;
    struct phonebook *temp;
    temp = head;
    char name[20];
    char phone_num[20];
    printf("Enter the first name: ");
    scanf("%s",name);
    printf("Enter phone_num\n");
    scanf("%s",phone_num);
    int flag=0;
    while(temp!=NULL && flag==0)
    {
        if(strcmp(temp->cont->pers->name,name)==0 && strcmp(temp->cont->pers->mobile_num,phone_num)==0)
        {
            retval=SUCCESS;
            flag=1;
        }
        else if(strcmp(temp->cont->prof->name,name)==0 && strcmp(temp->cont->prof->mobile_num,phone_num)==0)
        {
            retval=SUCCESS;
            flag=1;
        }
        temp = temp->next;
    }
    return retval;
}


//2.edit the contact list
void edit_cont(struct phonebook **head)
{
    struct phonebook *temp;
    temp = (*head);
    char name[20];
    char phone_num[20];
    printf("Enter the first name: ");
    scanf("%s",name);
    printf("Enter phone_num:\n");
    scanf("%s",phone_num);
    int flag=0;
    while(temp!=NULL && flag==0)
    {
        if(strcmp(temp->cont->pers->name,name)==0 && strcmp(temp->cont->pers->mobile_num,phone_num)==0)
        {
            printf("Contact found in personal vault");
            printf("Enter 1 for personal contact and 2 for professional contact\n");
            int choice=1;
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("Enter name:\n");
                scanf("%s",temp->cont->pers->name);
                printf("Enter mobile number:\n");
                scanf("%s",temp->cont->pers->mobile_num);
                printf("Enter email\n");
                scanf("%s",temp->cont->pers->email);
                temp->cont->prof = NULL;
            }
            else if(choice==2)
            {
                printf("Enter name\n");
                scanf("%s",temp->cont->prof->name);
                printf("Enter mobile number\n");
                scanf("%s",temp->cont->prof->mobile_num);
                printf("Enter email\n");
                scanf("%s",temp->cont->prof->email);
                printf("Enter office number\n");
                scanf("%s",temp->cont->prof->office_num);
                printf("Enter address\n");
                scanf("%s",temp->cont->prof->address);
                printf("Enter institute/office\n");
                scanf("%s",temp->cont->prof->institute);
                temp->cont->pers = NULL;
            }
            else
            {
                printf("choice is not valid\n");
            }
            flag=1;
        }
        else if(strcmp(temp->cont->prof->name,name)==0 && strcmp(temp->cont->prof->mobile_num,phone_num)==0)
        {
            printf("Contact found in professional vault");
            printf("Enter 1 for personal contact and 2 for professional contact\n");
            int choice=1;
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("Enter name\n");
                scanf("%s",temp->cont->pers->name);
                printf("Enter mobile number\n");
                scanf("%s",temp->cont->pers->mobile_num);
                printf("Enter email-Id\n");
                scanf("%s",temp->cont->pers->email);
                temp->cont->prof = NULL;
            }
            else if(choice==2)
            {
                printf("Enter name\n");
                scanf("%s",temp->cont->prof->name);
                printf("Enter mobile number\n");
                scanf("%s",temp->cont->prof->mobile_num);
                printf("Enter office number\n");
                scanf("%s",temp->cont->prof->office_num);
                printf("Enter email-Id\n");
                scanf("%s",temp->cont->prof->email);
                printf("Enter address\n");
                scanf("%s",temp->cont->prof->address);
                printf("Enter institute/office\n");
                scanf("%s",temp->cont->prof->institute);
                temp->cont->pers = NULL;
            }
            else
            {
                printf(" choice is not valid\n");
            }
            flag=1;
        }
        else
        {
            printf("Contact not found\n");
        }
        temp = temp->next;
    }
}

//3. delete the contact in the list

void delete_cont(struct phonebook **head)
{
    struct phonebook *temp;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp = *head;
    char name[50];
    char mobile_num[10];
    printf("Enter the name of the contact: ");
    scanf("%s", name);
    printf("Enter the mobile number of the contact: ");
    scanf("%s", mobile_num);
    int flag=0;
    while(temp != NULL && flag==0)
    {
        if(strcmp(temp->cont->pers->name,name)==0 && strcmp(temp->cont->pers->mobile_num,mobile_num)==0 )
        {
            if(temp->prev == NULL)
            {
                *head = temp->next;
                free(temp);
                flag=1;
            }
            else
            {
                temp->prev->next = temp->next;
                free(temp);
                flag=1;
            }
        }
        else if(strcmp(temp->cont->prof->name,name)==0 && strcmp(temp->cont->prof->mobile_num,mobile_num)==0 )
        {
            if(temp->prev == NULL)
            {
                *head = temp->next;
                free(temp);
                flag=1;
            }
            else
            {
                temp->prev->next = temp->next;
                free(temp);
                flag=1;
            }
        }
        else
        {
            printf("done once\n");
            temp = temp->next;
        }
    }
    if(flag==0)
    {
        printf("Contact not found\n");
    }
}

//4. search the contact in the list

void search_cont(struct phonebook *head)
{
    struct phonebook *temp;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp = head;
    char name[50];
    char mobile_num[10];
    printf("Enter the name of the contact: ");
    scanf("%s", name);
    printf("Enter the mobile number of the contact: ");
    scanf("%s", mobile_num);
    int flag=0;
    while(temp != NULL && flag==0)
    {
        if(strcmp(temp->cont->pers->name,name)==0 && strcmp(temp->cont->pers->mobile_num,mobile_num)==0 )
        {
            if(temp->cont->pers != NULL)
            {
                printf("Name: %s\n",temp->cont->pers->name);
                printf("Mobile Number: %s\n",temp->cont->pers->mobile_num);
                printf("Email: %s\n",temp->cont->pers->email);
                flag=1;
            }
        }
        else if(strcmp(temp->cont->prof->name,name)==0 && strcmp(temp->cont->prof->mobile_num,mobile_num)==0 )
        {
            if(temp->cont->prof != NULL)
            {
                printf("Name: %s\n",temp->cont->prof->name);
                printf("Mobile Number: %s\n",temp->cont->prof->mobile_num);
                printf("Email: %s\n",temp->cont->prof->email);
                printf("Office Number: %s\n",temp->cont->prof->office_num);
                printf("Address: %s\n",temp->cont->prof->address);
                printf("Institute/Office: %s\n",temp->cont->prof->institute);
                flag=1;
            }
        }
        temp = temp->next;
    }
}

//5.Sort the contacts in the list
//Sort in proffessional/personal
void sort_perproff(struct phonebook **head)
{
    int choice;
    printf("Enter 1 to sort in professional first\n");
    printf("Enter 2 to sort in personal first\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        struct phonebook *temp1;
        temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
        temp1 = *head;
        struct phonebook *temp2;
        temp2 = (struct phonebook *)malloc(sizeof(struct phonebook));
        temp2 = *head;
        while(temp1 != NULL)
        {
            if(temp1->cont->prof != NULL)
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            else
            {
                temp2->next = temp1->next;
                temp1->next = *head;
                *head = temp1;
                temp1 = temp2->next;
            }
        }
    }
    else if(choice==2)
    {
        struct phonebook *temp1;
        temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
        temp1 = *head;
        struct phonebook *temp2;
        temp2 = (struct phonebook *)malloc(sizeof(struct phonebook));
        temp2 = *head;
        while(temp1 != NULL)
        {
            if(temp1->cont->pers != NULL)
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            else
            {
                temp2->next = temp1->next;
                temp1->next = *head;
                *head = temp1;
                temp1 = temp2->next;
            }
        }
    }
    else
    {
        printf("choice is not valid\n");
    }

}


//sort ascending or descending 

void sort_ascdesc(struct phonebook **head)
{
    struct phonebook *temp;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp = *head;
    //sort both personal and professional based on name
    int choice=1; 
    printf("1 for ascending or 2 descending order\n");
    if(choice==1)
    {
        while(temp->next != NULL)
        {
            if(temp->cont->pers!=NULL && temp->next->cont->prof!=NULL)
            {
                if(strcmp(temp->cont->pers->name,temp->next->cont->prof->name)>0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->pers!=NULL && temp->next->cont->pers!=NULL)
            {
                if(strcmp(temp->cont->pers->name,temp->next->cont->pers->name)>0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->prof!=NULL && temp->next->cont->prof!=NULL)
            {
                if(strcmp(temp->cont->prof->name,temp->next->cont->prof->name)>0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->prof!=NULL && temp->next->cont->pers!=NULL)
            {
                if(strcmp(temp->cont->prof->name,temp->next->cont->pers->name)>0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
    }
    else
    {
        while(temp->next != NULL)
        {
            if(temp->cont->pers!=NULL && temp->next->cont->prof!=NULL)
            {
                if(strcmp(temp->cont->pers->name,temp->next->cont->prof->name)<0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->pers!=NULL && temp->next->cont->pers!=NULL)
            {
                if(strcmp(temp->cont->pers->name,temp->next->cont->pers->name)<0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->prof!=NULL && temp->next->cont->prof!=NULL)
            {
                if(strcmp(temp->cont->prof->name,temp->next->cont->prof->name)<0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
            else if(temp->cont->prof!=NULL && temp->next->cont->pers!=NULL)
            {
                if(strcmp(temp->cont->prof->name,temp->next->cont->pers->name)<0)
                {
                    struct phonebook *temp1;
                    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    temp1->next = *head;
                    *head = temp1;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
    }
}




//6. display_cont the contact list with porfessional and personal or all

void display_cont(struct phonebook *head)
{
    struct phonebook *temp;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp = head;
    int choice;
    printf("Enter 1 to display all contacts\n");
    printf("Enter 2 to display professional contacts\n");
    printf("Enter 3 to display personal contacts\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        while(temp != NULL)
        {
            if(temp->cont->pers != NULL)
            {
                printf("Name: %s\n",temp->cont->pers->name);
                printf("Mobile Number: %s\n",temp->cont->pers->mobile_num);
                printf("Email: %s\n",temp->cont->pers->email);
            }
            else
            {
                printf("Name: %s\n",temp->cont->prof->name);
                printf("Mobile Number: %s\n",temp->cont->prof->mobile_num);
                printf("Email: %s\n",temp->cont->prof->email);
                printf("Office Number: %s\n",temp->cont->prof->office_num);
                printf("Address: %s\n",temp->cont->prof->address);
                printf("Institute: %s\n",temp->cont->prof->institute);
            }
            temp = temp->next;
        }
    }
    else if(choice==2)
    {
        while(temp != NULL)
        {
            if(temp->cont->pers != NULL)
            {
                temp = temp->next;
            }
            else
            {
                if(temp->cont->prof != NULL)
                {
                    printf("Name: %s\n",temp->cont->prof->name);
                    printf("Mobile Number: %s\n",temp->cont->prof->mobile_num);
                    printf("Email: %s\n",temp->cont->prof->email);
                    printf("Office Number: %s\n",temp->cont->prof->office_num);
                    printf("Address: %s\n",temp->cont->prof->address);
                    printf("Institute: %s\n",temp->cont->prof->institute);
                }
                temp = temp->next;
            }
        }
    }
    else if(choice==3)
    {
        while(temp != NULL)
        {
            if(temp->cont->prof != NULL)
            {
                temp = temp->next;
            }
            else
            {
                if(temp->cont->pers != NULL)
                {
                    printf("Name: %s\n",temp->cont->pers->name);
                    printf("Mobile Number: %s\n",temp->cont->pers->mobile_num);
                    printf("Email: %s\n",temp->cont->pers->email);
                    
                }
                temp = temp->next;
            }
        }
    }
}

//7. merge two linked list based on name and phone number

void unio(struct phonebook *head1,struct phonebook *head2)
{
    struct phonebook *temp1,*temp2,*temp3;
    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp2 = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp3 = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp1 = head1;
    temp2 = head2;
    while(temp1 != NULL && temp2 != NULL)
    {
        if(strcmp(temp1->cont->pers->name,temp2->cont->pers->name)<0)
        {
            temp3->cont = temp1->cont;
            temp3->next = temp1->next;
            temp1->next = temp3;
            temp3->prev = temp1;
            temp1 = temp3;
            temp1 = temp1->next;
        }
        else if(strcmp(temp1->cont->pers->name,temp2->cont->pers->name)>0)
        {
            temp3->cont = temp2->cont;
            temp3->next = temp2->next;
            temp2->next = temp3;
            temp3->prev = temp2;
            temp2 = temp3;
            temp2 = temp2->next;
        }
        else
        {
            if(strcmp(temp1->cont->pers->mobile_num,temp2->cont->pers->mobile_num)<0)
            {
                temp3->cont = temp1->cont;
                temp3->next = temp1->next;
                temp1->next = temp3;
                temp3->prev = temp1;
                temp1 = temp3;
                temp1 = temp1->next;
            }
            else
            {
                temp3->cont = temp2->cont;
                temp3->next = temp2->next;
                temp2->next = temp3;
                temp3->prev = temp2;
                temp2 = temp3;
                temp2 = temp2->next;
            }
        }
    }
    if(temp1 == NULL)
    {
        temp1->next = temp2;
        temp2->prev = temp1;
    }
    else
    {
        temp1->next = temp2;
        temp2->prev = temp1;
    }
}

//8. remove duplicate contact from the list

void remove_duplicate(struct phonebook *head)
{
    struct phonebook *temp,*temp1,*dup;
    temp = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp1 = (struct phonebook *)malloc(sizeof(struct phonebook));
    temp = head;
    while(temp->next != NULL)
    {
        temp1=temp;
        if(temp->cont->pers!=NULL)
        {
            while(temp1->next != NULL)
            {
                if(temp->next->cont->pers==NULL)
                {
                    if(strcmp(temp->cont->pers->name,temp1->next->cont->prof->name)==0 && strcmp(temp->cont->pers->mobile_num,temp1->next->cont->prof->mobile_num)==0)
                    {
                        dup = temp1->next;
                        temp1->next = temp1->next->next;
                        free(dup);
                    }
                }
                else
                {
                    if(strcmp(temp->cont->pers->name,temp1->next->cont->pers->name)==0 && strcmp(temp->cont->pers->mobile_num,temp1->next->cont->pers->mobile_num)==0)
                    {
                        dup = temp1->next;
                        temp1->next = temp1->next->next;
                        free(dup);
                    }
                }
                temp1 = temp1->next;
            }
        }
        else if (temp->cont->prof!=NULL)
        {
            while(temp1->next != NULL)
            {
                if(temp->next->cont->prof==NULL)
                {
                    if(strcmp(temp->cont->prof->name,temp1->next->cont->pers->name)==0 && strcmp(temp->cont->prof->mobile_num,temp1->next->cont->pers->mobile_num)==0)
                    {
                        dup = temp1->next;
                        temp1->next = temp1->next->next;
                        free(dup);
                    }
                }
                else
                {
                    if(strcmp(temp->cont->prof->name,temp1->next->cont->prof->name)==0 && strcmp(temp->cont->prof->mobile_num,temp1->next->cont->prof->mobile_num)==0)
                    {
                        dup = temp1->next;
                        temp1->next = temp1->next->next;
                        free(dup);
                    }
                }
                temp1 = temp1->next;
            }
        }
        temp = temp->next;
    }
}


