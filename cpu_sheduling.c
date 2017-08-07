#include<stdlib.h>
#include<stdio.h>

typedef struct proc{
        int pid;
        int priority;
        int burst;
        // FOR OUTPUT PURPOSES:
        int waiting;
        int turnaround;

        struct proc* next;
        struct proc* prev;
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

void displayPriority(proc* HEAD, int n){
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

        proc* least;
        proc* largest;
        
        int init = 1;
        int last = 0;
        int last_id = -1;
        for(int i = 0;i<n;i++){
            least = temp;
            temp = temp->prev;

            while(temp->pid>0){
                if(init && temp->priority > least->priority)
                    largest = temp;

                if(temp->priority<least->priority && temp->priority>=last && temp->pid!=last_id){
                    least=temp;
                }
            temp = temp->prev;
            }
            init = 0;

            printf("%d          %d           %d                %d                   %d\n",least->pid,least->burst,least->priority,wait,least->burst);
            wait += least->burst;
            
            last = least->priority;
            last_id = least->pid;
            temp = largest;
        }
    }      
}

void displaySJN(proc* HEAD){
    
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
                displayPriority(HEAD,n);
            break;
        }

        printf("Retry (1/0): ");
        scanf("%d",&retry);
    }while(retry==1);
}