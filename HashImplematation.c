#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 20
#define MAX 50
int size;
char st[MAX][MAX];
int top=0;

void display();
int state=0;
int scope=0;
int num1=0;
struct DataItem {
   char data[20];   
   int key;
   char type[15];
   char scope[20];
   char data_struct[20];
};
struct DataItem* hashArray[SIZE]; 
struct DataItem* obj1[20];
struct DataItem* obj2;

void find_identifier_type(char *);
int search(int);
int hashCode(int key) {
   return key % SIZE;
}
void insert(int key,char *data,char *type,char *data_struct,char  *scope) {

   struct DataItem *obj2 = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(obj2->data,data);  
   obj2->key = key;
   strcpy(obj2->type,type);
   strcpy(obj2->data_struct,data_struct);
   strcpy(obj2->scope,scope);
   int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
     ++hashIndex;
	 hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = obj2;
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
 else {  printf("\n%s",find_keyword);
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
   
   int hashIndex = hashCode(key);  
	while(hashArray[hashIndex] != NULL) {
	  if(hashArray[hashIndex]->key == key)
         return hashIndex; 
	 ++hashIndex;
     hashIndex %= SIZE;
   }        
	
   return 0;        
}
void display() {

   int i = 0;


	printf("%s","SRNO\t\t\tID\t\t\ttype\t\t\tdata_struct\t\t\tscope");
   for(i = 0; i<=SIZE; i++) {
	
      if(hashArray[i]!= NULL){
         printf("\n");
         printf(" %d%s%s%s%s%s%s%s%s",hashArray[i]->key,"\t\t\t",hashArray[i]->data,"\t\t\t",hashArray[i]->type,"\t\t\t",hashArray[i]->data_struct,"\t\t\t",hashArray[i]->scope);
        
      }
     
   
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
    int k,i ;
    char string[20];
    printf("\nEnter word to find");
    scanf("%s",string);
    k=convertkey(string);
    i=search(k);
    if(i!=0){
        printf("%s","SRNO\t\t\tID\t\t\ttype\t\t\tdata_struct\t\t\tscope\n");
         printf(" %d%s%s%s%s%s%s%s%s",hashArray[i]->key,"\t\t\t",hashArray[i]->data,"\t\t\t",hashArray[i]->type,"\t\t\t",hashArray[i]->data_struct,"\t\t\t",hashArray[i]->scope);
    }else{
        printf("cannot found data in the table")
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
    printf("%s\n",st[top]);
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
