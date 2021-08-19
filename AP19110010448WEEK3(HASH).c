#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 20
void display();
int state=0;
int scope=0;
int num1=0;
struct DataItem {
   char data[20];   
   int key;
   char type[15];
   int scope;
   char data_struct[20];
};
struct DataItem* hashArray[SIZE][20]; 
struct DataItem* obj1[20];
struct DataItem* obj2;

void find_identifier_type(char *);
int search(int);
int hashCode(int key) {
   return key % SIZE;
}
void insert(int key,char *data,char *type,char *data_struct,int scope) {

   struct DataItem *obj2 = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(obj2->data,data);  
   obj2->key = key;
   strcpy(obj2->type,type);
   strcpy(obj2->data_struct,data_struct);
   obj2->scope=scope;
   int hashIndex = hashCode(key);
    while(hashArray[hashIndex][scope] != NULL && hashArray[hashIndex][scope]->key != -1) {
     ++hashIndex;
	 hashIndex %= SIZE;
   }
	
   hashArray[hashIndex][scope] = obj2;
}
char data_struct[20],type[15];
char  find_keyword[20];
char keyword[30][30]={"int","while","break","for","do","if","float","char","switch",
"double","short","long","unsigned","sizeof","else","register","extern","static","auto"
,"case","break","volatile","enum","typedef","strcmp","return","struct","void"};
char id[20], num[10],rel[5];

int check_keyword(char *s)
{
int i;
for(i=0;i<28;i++)
if(strcmp(s,keyword[i])==0){
strcpy(find_keyword,s);
return 1;
}
return 0;
}

int convertkey(char *);
int main()
{int k=0;

obj1[0]= (struct DataItem*) malloc(sizeof(struct DataItem));
obj1[0]->key = -1; 
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
    ++scope;
    num1++;
    obj1[scope]= (struct DataItem*) malloc(sizeof(struct DataItem));
    obj1[scope]->key = -1; 
    continue;
    
}
    if(strstr(word,"}")){
        scope--;
        continue;
    }
   state=check_keyword(word);
 if(state == 0){
    find_identifier_type(word); 
     
 }
    
}
display();
}

void find_identifier_type(char word[]){
    int k;
    char word1[20];
    char *token;
    
 if(strcmp(find_keyword,"int") || strcmp(find_keyword,"float") || strcmp(find_keyword,"char")){
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
 
 else if(strcmp(find_keyword,"void")){
         strcpy(data_struct,"function");
         strcpy(type,find_keyword);
           token = strtok(word, "(");
           strcpy(word,token);
 }
 else if(strcmp(find_keyword,"return")){
        
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
        
        insert(k,word,type,data_struct,scope);
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
	while(hashArray[hashIndex][scope] != NULL) {
	  if(hashArray[hashIndex][scope]->key == key)
         return 1; 
	 ++hashIndex;
     hashIndex %= SIZE;
   }        
	
   return 0;        
}
void display() {
   int i = 0;

	for(int j=0;j<num1;j++){
	    printf("\n\n\t\t\t\t\t\t\t%s%d\n\n","SCOPE",j);
	    	printf("%s","SRNO\t\t\tID\t\t\ttype\t\t\tdata_struct\t\t\tscope");
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i][j] != NULL){
         printf("\n");
         printf(" %d%s%s%s%s%s%s%s%d",hashArray[i][j]->key,"\t\t\t",hashArray[i][j]->data,"\t\t\t",hashArray[i][j]->type,"\t\t\t",hashArray[i][j]->data_struct,"\t\t\t",hashArray[i][j]->scope);
        
      }
     
   }
	}
}
