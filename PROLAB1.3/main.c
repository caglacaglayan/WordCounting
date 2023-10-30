#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
    char kelime[50];
    int deger;
    struct node * next;
} node_t;

void bitis(node_t * head ,char kelime[]){
    node_t * current = head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->deger = 1;
    strcpy(current->next->kelime,kelime);
    current->next->next = NULL;
}

void baslangic(node_t ** head,char kelime[]){
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->deger = 1;
    new_node->next = *head;
    strcpy(new_node->kelime,kelime);
    *head = new_node;
}

void ekle(node_t * head,int pos,char kelime[]){
    node_t * current = head;

    while(current!=NULL && pos>0){
        current=current->next;
        pos--;
    }
    if(current==NULL){
        return;
    }
    node_t * new_node=(node_t *)malloc(sizeof(node_t));
    new_node->deger=1;
    strcpy(new_node->kelime,kelime);
    new_node->next=current->next;
    current->next=new_node;
}

void printList( node_t* n){
    int i=1;
    while (n != NULL) {
        printf("%d. %s: %d\n ",i,n->kelime, n->deger);
        n = n->next;
        i++;
    }
}

node_t * ifpresent(node_t * head,char kelime[]){
    node_t * current=head;
    while(current!=NULL && strcmp(current->kelime,kelime)!=0 ){
        current=current->next;
    }
    if(current==NULL){
        return NULL;
    }
    return current;
}

void siralanmisEkleme(node_t** head_ref, node_t * new_node){
    node_t * current;
    if (*head_ref == NULL || (*head_ref)->deger <= new_node->deger){
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else{
        current = *head_ref;
        while (current->next!=NULL && current->next->deger > new_node->deger){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void eklemeSirasi( node_t **head_ref){
     node_t *sorted = NULL;
     node_t *current = *head_ref;
    while (current != NULL){
        node_t *next = current->next;
        siralanmisEkleme(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
}

int main(){
    char text[500];

    FILE *dosya;
    dosya = fopen("text.txt","r");
    if(dosya!=NULL){
        for(int i=0 ; i<500 ; i++){
            fscanf(dosya,"%c",&text[i]);
        }
    }
    else{
        printf("Text dosyasi bulunamadi!\n");
        return 0;
    }

    char sinir[]=" ";
    char *ptr=strtok(text,sinir);
    node_t * head=NULL;
    int index=0;
    while(ptr!=NULL){
        node_t * temp=ifpresent(head,ptr);
        if(temp==NULL){
            if(index%2==0){
                 baslangic(&head,ptr);
            }
            else if(index%3==0){
                bitis(head,ptr);
            }
            else{
                ekle(head,1,ptr);
            }
        }
        else{
            temp->deger+=1;
        }
        ptr=strtok(NULL,sinir);
        index++;
    }
    eklemeSirasi(&head);
    printList(head);

    return 0;
}
