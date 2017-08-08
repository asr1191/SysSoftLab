#include<stdlib.h>
#include<stdio.h>

typedef struct proces{
        int pid;
        int priority;
        int burst;
        // FOR OUTPUT PURPOSES:
        int waiting;
        int turnaround;

        struct proces* next;
        struct proces* prev;
        } proc;

void displayProc(proc* HEAD){
    proc* temp;
    if(HEAD->next==NULL){
        printf("No processes to display");
    }
    else{
        temp = HEAD->prev;
        printf("\nProcesses to be executed: \n");
        printf("PID        Burst       Priority  \n");
        while(temp->pid>0){
            printf("%d          %d          %d\n",temp->pid,temp->burst,temp->priority);
            temp = temp->prev;
        }
    }
}

void displayFCFS(proc* HEAD){
    proc* temp;
    if(HEAD->next==NULL){
        printf("No processes to display");
    }
    else{
        temp = HEAD->prev;
        printf("\nProcesses to be executed: \n");
        printf("PID        Burst       Priority        WaitingTime          TurnaroundTime\n");
        int wait = 0;
        int burst = 0;
        while(temp->pid>0){
            wait += burst;
            printf("%d          %d           %d                 %d                  %d\n",temp->pid,temp->burst,temp->priority,wait,temp->burst);
            burst = temp->burst;
            temp = temp->prev;
        }
    }   
}

proc* duplicateList(proc* HEAD){
    proc* temp = HEAD->next;
    proc* newproc;

    proc* HEAD2 = malloc(sizeof(proc));
    HEAD2->next = NULL;
    HEAD2->prev = NULL;
    HEAD2->pid = -1;

    while(temp->pid > 0){

        newproc = malloc(sizeof(proc));
        newproc->pid = temp->pid;
        newproc->burst = temp->burst;
        newproc->priority = temp->priority;
        newproc->waiting = temp->waiting;
        newproc->turnaround = temp->turnaround;

        if(HEAD2->next == NULL){
            HEAD2->next = newproc;
            HEAD2->prev = newproc;
            newproc->next = HEAD2;
            newproc->prev = HEAD2;
        }else{
            HEAD2->next->prev = newproc;
            newproc->next = HEAD2->next;
            HEAD2->next = newproc;
            newproc->prev = HEAD2;
        }

        temp=temp->next;
    }

    return HEAD2;
}

void displaySJN(proc* HEAD){
    proc* HEAD2 = duplicateList(HEAD);
    proc* HEAD3 = malloc(sizeof(proc));
    HEAD3->next = NULL;
    HEAD3->prev = NULL;
    HEAD3->pid = -1;

    proc* temp = HEAD2->next;
    proc* least = HEAD2->next;

    proc* newproc;

    while(HEAD2->next != HEAD2){
        printf("\nInside While Loop in displaySJN()");
        while(temp->pid > 0){
            if(temp->burst < least->burst){
                least = temp;
            }
            temp = temp->next;
        }
        //ADDING TO HEAD3
        newproc = malloc(sizeof(proc));
        newproc->pid = least->pid;
        newproc->burst = least->burst;
        newproc->priority = least->priority;

        if(HEAD3->next == NULL){
            HEAD3->next = newproc;
            HEAD3->prev = newproc;
            newproc->next = HEAD3;
            newproc->prev = HEAD3;
            printf("\nAdding initial proc to HEAD3 PID: %d",HEAD3->next->pid);
        }else{
            HEAD3->next->prev = newproc;
            newproc->next = HEAD3->next;
            HEAD3->next = newproc;
            newproc->prev = HEAD3;
            printf("\nAdding more proc to HEAD3, PID: %d",HEAD3->next->pid);
        }

        //DELETING FROM HEAD2
        least->prev->next = least->next;
        least->next->prev = least->prev;
        free(least);

        //Reset temp and least
        temp = HEAD2->next;
        least = HEAD2->next;
    }

    temp = NULL;
    least = NULL;

    displayFCFS(HEAD3);
}

int main(){

    int n;
    proc* newproc;

//Initiatiing Linked List HEAD pointer --BEGIN--
    proc* HEAD = NULL;
    HEAD = malloc(sizeof(proc));

    if(HEAD == NULL){
        printf("\nHEAD initialisation failed!");
        return 2;
    }
    HEAD->pid = -1;
    HEAD->next = NULL;
    HEAD->prev = NULL;
//--END--
//Defining processes, assuming all processes 
    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        newproc = malloc(sizeof(proc));
        if(newproc == NULL)
            printf("Process creation failed!");

        printf("\nEnter P_ID: ");
        scanf("%d",&(newproc->pid));
        printf("Enter priority of PID %d: ",newproc->pid);
        scanf("%d",&(newproc->priority));
        printf("Enter burst time of PID %d: ",newproc->pid);
        scanf("%d",&(newproc->burst));

        newproc->waiting=0;
        newproc->turnaround=0;

        if(HEAD->next == NULL){
            HEAD->next = newproc;
            newproc->prev = HEAD;
            newproc->next = HEAD;
            HEAD->prev = newproc;
        }
        else{
            newproc->next = HEAD->next;
            HEAD->next->prev = newproc;
            HEAD->next = newproc;
            newproc->prev = HEAD;
        }
    }
//Listing processes:
    displayProc(HEAD);

    int retry;
    do{
        int choice;
        printf("\nScheduling Types: \n1. FCFS\n2. Shortest Job Next\n3. Priority Scheduling\n3. Round Robin\nEnter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                displayFCFS(HEAD);
            break;

            case 2:
                displaySJN(HEAD);
            break;

            case 3:
                
            break;
        }

        printf("Retry (1/0): ");
        scanf("%d",&retry);
    }while(retry==1);
}