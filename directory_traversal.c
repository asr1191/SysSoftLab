#include<stdlib.h>
#include<stdio.h>
#include<string.h>

const int MAX = 100;

typedef struct node1{
    int id;
    int isFile;//1 = File ; 0 = Folder
    char isSelected;
    char name[25];

    struct node1* children_HEAD;
    struct node1* parent;
    struct node1* prev_sibling;
    struct node1* next_sibling;
} node;

typedef struct path{ //Stack for search function which returns filepath
    char name[25];
    struct path* next;
} path;

void printDir(node* root, int level){

    for(int i = 0;i<level;i++)
        printf("----");
    if(root->isFile)
        printf("{=%d=} ",root->id);
    else
        printf("[_%d_] ",root->id);
    printf("%s\n",root->name);

    if(root->children_HEAD != NULL){
        printDir(root->children_HEAD, level + 1);
    }


    if(root->next_sibling != NULL)
        printDir(root->next_sibling, level);
    else
        return;
}

void createNode(char name[], int* listTop, node* list[], int selected,int isFile){
    node* newnode = NULL;
    newnode = (node*)malloc(sizeof(node));
    newnode->id = *listTop+1;
    newnode->isFile = isFile;
    strcpy(newnode->name,name);
    newnode->children_HEAD = NULL;
    newnode->next_sibling = NULL;
    newnode->parent = list[selected];

    if(newnode->parent->children_HEAD != NULL){
        
        node* temp = newnode->parent->children_HEAD;
        while(temp->next_sibling != NULL){
            temp = temp->next_sibling;
        }
        temp->next_sibling = newnode;
        newnode->prev_sibling = temp;

    }else{
        newnode->prev_sibling = NULL;
        newnode->parent->children_HEAD = newnode;
    }
    
    list[newnode->id] = newnode;
    *listTop+=1;
}

int main(){
    int retry = 0; //flag to rerun the menu
    node* list[MAX]; //Array which stores references to all nodes
    int listTop = 0; //stores index/id of last node created

    for(int i = 0;i<MAX;i++) //initialising reference list to null
        list[i] = NULL;
    

    //initialising root node, and list
    node* root = (node*)malloc(sizeof(node));
    root->id = 0;
    strcpy(root->name,"root");
    root->isFile = 0;
    root->children_HEAD = NULL;
    root->parent = NULL;
    root->next_sibling = NULL;
    list[0] = root;
    listTop = 0;

    
    int choice;

    do{
        system("clear"); //executes "clear" on bash terminal

        int selected;
        int found = 0;
        char filename[25];

        printDir(root,0);
        printf("\n\n1. Create a new directory.\n2. Create a new file\n3. Delete Directory/File\n4. Search\n\nEnter choice: ");
        scanf("%d",&choice);
        switch(choice){
            
            case 1:
                printf("\nEnter ID of parent folder: ");
                scanf("%d",&selected);
                if(list[selected]==NULL){
                    printf("\nNo such directory!\n");
                    break;
                }else if(list[selected]->isFile){
                    printf("\nSpecified id is not a directory");
                    break;

                }else{
                    printf("\nEnter name of folder: ");
                    char name[25];
                    scanf("%s",name);
                    createNode(name,&listTop,list,selected,0);
                }
            break;

            case 3:
                printf("\nEnter ID of file/folder to be deleted: ");
                scanf("%d",&selected);
                if(list[selected]==NULL){
                    printf("No file/folder found!");
                    break;
                }else{
                    if(list[selected]->prev_sibling == NULL){
                        list[selected]->parent->children_HEAD = NULL;
                    }else{
                        list[selected]->prev_sibling = list[selected]->next_sibling;
                    }

                    if(list[selected]->next_sibling != NULL)
                        list[selected]->next_sibling->prev_sibling = list[selected]->prev_sibling;
                    free(list[selected]);
                    list[selected] = NULL;
                }
            break;

            case 2:
                printf("\nEnter ID of parent folder: ");
                scanf("%d",&selected);
                if(list[selected]==NULL){
                    printf("\nNo such directory!\n");
                    break;
                }else if(list[selected]->isFile){
                    printf("\nSpecified id is not a directory");
                    break;

                }else{
                    printf("\nEnter name of file: ");
                    char name[25];
                    scanf("%s",name);
                    createNode(name,&listTop,list,selected,1);
                }
            break;

            case 4:
                printf("\nEnter filename: ");
                scanf("%s",filename);
                for(int i = 0;i<=listTop;i++){
                    if(list[i]!=NULL){
                        if(!strcmp(list[i]->name,filename)){
                            found = 1;
                            printf("\nFile found at: ");
                            //Creating path stack
                            path* path_HEAD = malloc(sizeof(path));
                            path_HEAD->next = malloc(sizeof(path));
                            strcpy(path_HEAD->next->name,filename);
                            node* temp = list[i]->parent;
                            while(temp != NULL){
                                path* newpath = malloc(sizeof(path));
                                strcpy(newpath->name,temp->name);
                                newpath->next = path_HEAD->next;
                                path_HEAD->next= newpath;
                                temp = temp->parent;
                            }
                            //Printing path stack
                            path* tempp = path_HEAD;
                            while(tempp != NULL){
                                if(tempp->next == NULL)
                                    printf("%s\n",tempp->name);
                                else
                                    printf("%s/",tempp->name);
                                tempp = tempp->next;
                            }
                        }
                    }
                }
                if(!found){
                    printf("\nFile not found!");
                }
                
            break;
        }
    
    printf("Continue? 1/0: ");
    scanf("%d",&choice);

    }while(choice);
}