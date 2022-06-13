#include "header.h"

void currenttime(){//gives the local time the user

  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s", asctime (timeinfo) );
}
int timeh(){// Returns the current hour
    int h, min;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;                    
    // printf("%02d : ", h);
    return h;
}
int timem(){// Returns the current minute
    int h, min;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);        
    min = local->tm_min;              
    // printf("%02d\n", min);
    return min;
}
int checkfilelength(FILE*fichier){ // return total numbre of books/lines in the library
    char a[1000];
    int length = 0;
    while(fgets(a, 1000, fichier) != NULL){
        length = length +1;   
    }
    return length;
}
int read_int(int min, int max) {
    char  string[255];
    int   entier = 0;
    bool  OK;
    int   i;
    do {
        OK = false;
        scanf("%s", string);
        /* We make sure it is an int. */
        for (i = 0; i < strlen(string); i++) {
            if (!isdigit(string[i])) {
                /* If the scanned character isnt an int we stop the research */
                OK = true;
                break;
            }
            entier = 10 * entier + (string[i] - '0');
        }
        /* If we did scan an int we make sure its between min and max. */
        if (OK  &&  (entier < min  ||  entier > max)) {
            OK = true;
        }
        /* We print the errow message. */
        if (OK) {
            printf("Wrong input. Please enter either %d or %d.\n",
                   min, max);
        }
    } while (OK);
    return entier;
}

void readline( int read_line, FILE *filemidd){ //this function read a specific line in the library file and copy it to store it in a a draft txt file
     FILE *file=fopen("library.txt","r+");

     char buffer[maxline];
     if(file==NULL){
        printf("Error opening the library\n");
        exit(1);
     }

     bool keep_reading=true;
     int current_line=1;
     do{
       fgets(buffer,maxline,file);
       if (feof(file)){
           keep_reading=false;

           printf("Couldn't find line %d.\n",read_line);
}
       else if(current_line==read_line){
              keep_reading=false;
              
       }
       current_line++;
     }while(keep_reading);
     fputs(buffer,filemidd);
     fclose(file);
  
}
Book recuplivre(int num){// this function opens the draft txt file and and retrive all the information about a book
    Book b;
    
    FILE *file=fopen("middle_file.txt","w+");
    if(file==NULL){
        printf("Error opening the middle file\n");
        exit(1);
     }
    readline(num,file);
    rewind(file); 
    fscanf(file,"%d %s %s %s %s %d  %d %d %d",&b.id,b.title,b.author,b.username,b.username2,&b.category,&b.status,&b.hreturn,&b.minreturn);
    return b;
}

/*void addspace(char tab[],int taille){
    for(int i=0;i<taille;i++){
        if(tab[i]=='_'){
            printf(" ");
        }
        else{
            printf("%c",tab[i]);
        }
    }
}*/
void tri_alphabetiquetitle(Book tab[],int taille){// the function shows the user the titles available books in alphabetical order
    Book temp;
    for (int i = 1; i < taille; i++){
        for (int j = i+1; j < taille; j++){
            if (strcmp(tab[i].title, tab[j].title) > 0){
                temp=tab[i];
                tab[i]=tab[j];
                tab[j]= temp;
            }
        }
        if(tab[i].status==0){
               printf("\n%d.",tab[i].id);
               printf("%s",tab[i].title);
               //addspace(tab[i].title,1000);
        } 
    }printf("\n");
}
/*void tri_alphabetiqueauthor(Author tab[],int taille){//this function shows the user the authors of the available books
    Author temp;
    for (int i = 1; i < taille; i++){
        for (int j = i+1; j < taille; j++){
            if (strcmp(tab[i].name, tab[j].name) > 0){
                temp=tab[i];
                tab[i]=tab[j];
                tab[j]= temp;
            }
        }
         
        printf("%d.%s\n",tab[i].num,tab[i].name);
    
        }    
}*/