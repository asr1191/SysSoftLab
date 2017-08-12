#include<stdlib.h>
#include<stdio.h>

const int MAX = 100;

typedef struct node1{
    int id;
    int isFile;
    char isSelected; //1 = File ; 0 = Folder
    char* name;

    struct node1* children_HEAD;
    struct node1* parent;
    struct node1* next_sibling;
} node;

void printDir(node* root, int level){
    if(root->children_HEAD != NULL){
        printDir(root->children_HEAD, level + 1);
    }

    for(int i = 0;i<level;i++)
        printf("--");
    if(root->isFile)
        printf("{=%d=} ",root->id);
    else
        printf("[_%d_] ",root->id);
    printf("%s\n",root->name);

    if(root->next_sibling != NULL)
        printDir(root->next_sibling, level);
    else
        return;
}

void createNode(int parentID, char name[25], int isFile, node* list[], int listTop){
    node* newnode = malloc(sizeof(node));
    newnode->id = listTop+1;
    newnode->isFile = isFile;
    newnode->name = name;
    newnode->children_HEAD = NULL;
    newnode->parent = list[parentID];

    node* temp = newnode->parent->children_HEAD;
    while(temp->next_sibling != NULL){
        temp = temp->next_sibling;
    }
    temp->next_sibling = newnode;

    list[newnode->id] = newnode;
    listTop++;
}

int main(){
    int retry = 0;
    node* list[MAX];
    int listTop = 0;

    for(int i = 0;i<MAX;i++)
        list[i] = NULL;
    
    node* root = malloc(sizeof(node));
    root->id = 0;
    root->name = "root";
    root->isFile = 0;
    root->children_HEAD = NULL;
    root->parent = NULL;
    root->next_sibling = NULL;
    list[root->id] = root;
    listTop = 0;

    system("clear");
    printf("Folders - [_id_]\nFiles   - {=id=}\n\n");

    do{
        int selected;
        int choice;

        printDir(root,0);
        printf("\n\n1. Create a new directory.\n2. Delete Directory\n3. Create a new file\n4. Delete a file\n\nEnter choice: ");
        scanf("%d",&choice);
        switch(choice){
            
            case 1:
                printf("\nEnter ID of parent folder: ");
                scanf("%d",&selected);
                if(list[selected]==NULL){
                    printf("\nNo such directory!");
                    break;
                }else{
                    printf("\nEnter name of folder: ");
                    char name[25];
                    scanf("%s",&name);

                    createNode(selected,name,0,list,listTop);
                }
            break;
        }
    }while(retry);
}