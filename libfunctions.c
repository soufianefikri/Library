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
// /////////////////////////////////////////////////////////////////////////
//                        fonctions de base 1                            //
// ////////////////////////////////////////////////////////////////////////
void showbooks(Book book[],int taille){
    int type=0;
    int catego;
    while (1!=0){
        do{
        printf("How do you wanna see the books:\n1.By alphabetical order.\n2.By category.\n3.By authors.\n");
        type=read_int(1,3);
        }while(type<1 ||  type>3);
    
        if(type==1){
            tri_alphabetiquetitle(book,taille);
            break;
        }
        if(type==2){
            int confirm1=0;
            int confirm2=0;
            while(confirm1==0 && confirm2==0 ){
            printf("Chose a category from the following (type in the number of the category):\n");
            printf("1.History\n");
            printf("2.Philosophy\n");
            printf("3.Religion\n");
            printf("4.Economics\n");
            printf("5.Geography\n");
            printf("6.Science\n");
            printf("7.Science fiction\n");
            printf("8.Novels\n");
            printf("9.Comics\n");
            printf("10.Manga\n");
            printf("11.Law\n");
            printf("12.Art\n"); 
            catego=read_int(1,12);
            if(catego<=0 || catego>13){    
                confirm1=0;
                }
            else{    
                confirm1=1;
            }
            do{
            printf("Are you sure about the category n°%d?\n",catego);
            printf("0.No\n");
            printf("1.Yes\n"); 
            confirm2=read_int(0,1);
            }while(confirm2>1 && confirm2<0 );
                
            }
            for(int i=0;i<taille;i++){
                    if(catego==book[i].category && book[i].status==0 ){
                    printf("%d.%s\n",book[i].id,book[i].title);
                    }
            }
            break;
        }
        if(type==3){
            printf("Unfortunatly this feature is not available yet\n");
            type = 0;
        }
    }
} 

Book borrowbook(User user,Book book){
    book.status=1;  
    book.hreturn=timeh();
    book.minreturn=timem();
    for(int i=0;i<1000;i++){
        book.username[i]=user.nom[i];
    }
    for(int i=0;i<1000;i++){
        book.username2[i]=user.prenom[i];
    }
    if(user.role==1){
        if(book.minreturn==57){
            book.minreturn=00;
            book.hreturn++;
        }
        if(book.minreturn==58){
            book.minreturn=01;
            book.hreturn++;
        }        
        if(book.minreturn==59){
            book.minreturn=02;
            book.hreturn++;
        }
        else{
            book.minreturn=book.minreturn+3;
            
        }
    }
    if(user.role==0){

        if(book.minreturn==58){
            book.minreturn=00;
            book.hreturn++;
        }        
        if(book.minreturn==59){
            book.minreturn=01;
            book.hreturn++;
        }
        else{
            book.minreturn=book.minreturn+2;
            
        }
    }
    if(book.hreturn==24){
        book.hreturn=0;
        
    }
    
    return book;
}


void addbook(User user){// gives the professors the ability to add books to the library//tested
FILE *file=fopen("library.txt","a+");
    if (file==NULL){
       printf("Problem with openning the library!!\n");
       exit(1);
    }
    Book b;
    int length;
    int check=0;
    int check2=0;
    while (check==0 || check>1){
           printf("Please Type in the title of the book with using '_'instead of space:\n");
           scanf("%s",b.title);
           length=strlen(b.title);
           printf("Is this the title of the book you want to add to the library:\n");
           //addspace(b.title,length);
           printf("\n0.No\n1.Yes\n");
           check=read_int(0,1);
    }
    while (check2==0 || check2>1){
         printf("Please type in the name of the author of the book with using '_'instead of space\n");
         scanf("%s",b.author);
         length=strlen(b.author);
         printf("Is this the author who's book you want to add to the library:\n");
         //addspace(b.author,length);
         printf("\n0.No\n1.Yes\n");
         check2=read_int(0,1);
    }
    b.id=checkfilelength(file)+1;
    b.status=0;
    b.hreturn=00;
    b.minreturn=00;
    b.category=0;
    int confirmation=0;
    int conf=0;
    while (confirmation==0 || conf==0){
           printf("Chose a category from the following (type in the number of the category):\n");
           printf("1.History\n");
           printf("2.Philosophy\n");
           printf("3.Religion\n");
           printf("4.Economics\n");
           printf("5.Geography\n");
           printf("6.Science\n");
           printf("7.Science fiction\n");
           printf("8.Novels\n");
           printf("9.Comics\n");
           printf("10.Manga\n");
           printf("11.Law\n");
           printf("12.Art\n");
           scanf("%d",&b.category);
           if(b.category<=0 || b.category>12){    
             conf=0;
            }
           else{    
               conf=1;
           }   
           printf("Are you sure about the category n°%d?\n",b.category);
           printf("0.No\n");
           printf("1.Yes\n"); 
           scanf("%d",&confirmation);
    }
    for(int i=0;i<1000;i++){
        b.username[i]=user.nom[i];
    }
    
    for(int i=0;i<1000;i++){
        b.username2[i]=user.prenom[i];
    }
    fprintf(file,"%d %s %s %s %s %d %d %d %d\n",b.id,b.title,b.author,b.username,b.username2,b.category,b.status,b.hreturn,b.minreturn);
    fclose(file);
    
}

void new_library(Book book[],int numofbook){// at the end of the app the code write the new modified book[] in the library
    FILE *file=fopen("library.txt","w+");
    if (file==NULL){
        printf("Trouble opening library to write");
        exit(1);
    }
    Book temp;
    for(int i=0;i<numofbook;i++){ // here the function writes the books in the order of their id number to not cause bugs in the next login
        for(int j=i+1;j<numofbook;j++){
            if(book[i].id>book[j].id){
                temp=book[i];
                book[i]=book[j];
                book[j]=temp;
            }
        }   
    
    fprintf(file,"%d %s %s %s %s %d  %d %d %d\n",book[i].id,book[i].title,book[i].author,book[i].username,book[i].username2,book[i].category,book[i].status,book[i].hreturn,book[i].minreturn);
    }
    
    fclose(file);
}

Book return_book(Book book){
    book.status=0;
    book.hreturn=0;
    book.minreturn=0;
    return book;
}
void check_userbooks(User user,Book book[], int numofbook){
    for(int i;i<numofbook;i++){
        int check;
        int check2;
        check=strcmp(book[i].username,user.nom);
        check2=strcmp(book[i].username2,user.prenom);
        if(check==0 && check2==0){
          int h;
          int min;
          h=timeh();
          min=timem();
          if(h!=book[i].hreturn && min>book[i].minreturn){
              printf("It seems like you didn't return ");
              //addspace(book[i].title,1000);
              printf("\nUnfortunatly you can't borrow a book until your next log in");
              user.autorisation=0;
          }    
            printf("You borrowed:\n");
            //addspace(book[i].title,1000);
            printf(" The return time is %d:%d",book[i].hreturn,book[i].minreturn);
        }    
            
    }    
    
}
