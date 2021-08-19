#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define MAX 50
char st[MAX][MAX];
int top=0;
void assign();
void display();
void find_identifier_type(char *);
int search(int);
int state=0;
int scope=0;
int num1=0;
struct node 
{
   char data[20];   
   int key;
   char type[15];
   char scope[20];
   char data_struct[20];
   struct node *next;
};
struct node *head = NULL;
struct node *current = NULL;



void insert(int key,char *data,char *type,char *data_struct,char  *scope) {

   struct node *obj2 = (struct node*) malloc(sizeof(struct node));
   strcpy(obj2->data,data);  
   obj2->key = key;
   strcpy(obj2->type,type);
   strcpy(obj2->data_struct,data_struct);
   strcpy(obj2->scope,scope);
   obj2->next=head;
   head=obj2;
}
char data_struct[20],type[15];
char prev[20];
char  find_keyword[20];
char keyword[30][30]={"int","while","break","for","do","if","float","char","switch",
"double","short","long","unsigned","sizeof","else","register","extern","static","auto"
,"case","break","volatile","enum","typedef","strcmp","return","struct","void"};
char id[20], num[10],rel[5];

int check_keyword(char s[])
{
int i;
for(i=0;i<28;i++)
if(strcmp(s,keyword[i])==0){
strcpy(find_keyword,s);
return 1;
}
return 0;
}
void Insert();
void Search();
int convertkey(char *);
int main()
{
strcpy(st[top],"global");

int choice;
assign();
do{
    
printf("\nPress 1 to enter code\n");
printf("Press 2 to display table\n");
printf("Press 3 to search in table\n");
printf("Press 4 to exit\n");
printf("Enter yout choice");
scanf("%d",&choice);
switch(choice){
    case 1: Insert();
             break;
    case 2: display();
             break;
    case 3: Search();
             break;
              
}
}while(choice!=4);

}

void find_identifier_type(char word[]){
    int k;
    char word1[20];
    char *token;
    
 if(strcmp(find_keyword,"int")==0|| strcmp(find_keyword,"float")==0 || strcmp(find_keyword,"char")==0)
 {
     
     if(strstr(word,"(")){
         strcpy(data_struct,"function");
         strcpy(type,find_keyword);
         token = strtok(word, "(");
         strcpy(word,token);
         
     }else if(strstr (word,"[")){
         strcpy(data_struct,"array");
         strcpy(type,find_keyword);
           token = strtok(word, "[");
           strcpy(word,token);
     }else if(strstr(word,"*")){
         strcpy(data_struct,"pointer");
         strcpy(type,find_keyword);
        token = strtok(word, "*");
        strcpy(word,token);
     }else {
         strcpy(data_struct,"variable");
         strcpy(type,find_keyword);
         
     }
     
     
 }
 
 else if(strcmp(find_keyword,"void")==0){
         strcpy(data_struct,"function");
         strcpy(type,find_keyword);
           token = strtok(word, "(");
           strcpy(word,token);
 }
 else if(strcmp(find_keyword,"return")==0){
        
         strcpy(type,find_keyword);
 }
 else {  
         strcpy(data_struct,"structure");
         strcpy(type,find_keyword);
 }
 
 k=convertkey(word);
if(k!=0){
    int found=search(k);
    if(found==0){
        
        insert(k,word,type,data_struct,st[top]);
        strcpy(prev,word);
    }
}
    
} 
int convertkey(char *id){
    int sum =0;
    for(int i=0;i< strlen(id);i++){
       
       int num =(int)id[i]*(i+1);
       sum= sum+num;
    }
  
   return sum%2069;
}
int search(int key) {
   
  struct node *ptr = head;
   
	 while(ptr != NULL) {
      if(ptr->key==key)
        return 1;
      ptr = ptr->next;
   }
	
     return 0;        
}
void display() {
struct node *ptr = head;
   int i = 0;


	printf("%s","SRNO\t\t\tID\t\t\ttype\t\t\tdata_struct\t\t\tscope");
  
	
      while(ptr!= NULL){
         printf("\n");
         printf(" %d%s%s%s%s%s%s%s%s",ptr->key,"\t\t\t",ptr->data,"\t\t\t",ptr->type,"\t\t\t",ptr->data_struct,"\t\t\t",ptr->scope);
        ptr=ptr->next;
      }
     
   
}

void Insert()
{
    char string[100];
printf("Enter line to insert");
scanf("%s",string);
FILE *fp2;
fp2=fopen("x.txt","a");
fprintf(fp2,"\n%s",string);
fclose(fp2);
assign();
}
void Search(){
    int key,i ;
    char string[20];
    printf("\nEnter word to find");
    scanf("%s",string);
    key=convertkey(string);
     struct node *ptr = head;
   
	 while(ptr != NULL) {
      if(ptr->key==key)
        {printf("%s","SRNO\t\t\tID\t\t\ttype\t\t\tdata_struct\t\t\tscope\n");
        printf(" %d%s%s%s%s%s%s%s%s",ptr->key,"\t\t\t",ptr->data,"\t\t\t",ptr->type,"\t\t\t",ptr->data_struct,"\t\t\t",ptr->scope);
         break;}
      ptr = ptr->next;
   }
    
}
   
void assign(){
    int k=0;
FILE *fp1;
char c;
int i=0,j=0,t=0;
fp1=fopen("x.txt","r");
int state=0;
char word[20];

    while(fscanf(fp1, "%s", word)!=EOF)
{   
    if(strstr(word,";")){
         size_t len = strlen(";");
    if (len > 0) {
        char *p = word;
        while ((p = strstr(p, ";")) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    }  
    if(strstr(word,"{")){
    ++top;
    strcpy(st[top],prev);
   
    continue;
    
}
    if(strstr(word,"}")){
        scope--;
        top--;
        continue;
        
    }
   state=check_keyword(word);
 if(state == 0){
    find_identifier_type(word); 
     }
    
}

}
