// BUS TICKET GENERATOR 
#include <stdio.h>
#include <stdlib.h>
int ticket = 1000;
int ran = 1;
int count = 0;
struct bus
{   
    char name[30];
    int seatflag[30];
    int seatticket[30];
}b[8];

void menu();
void get_info();
void find_bus();
void display_routes();
void bus_selector();
void display_select();
void display_seats();
void display_proc();
void route(int,char[]);
void store_file(int,int,int);
void open_file();
void count_file();
int check_file();

void main()
{
    int j;
    printf("--------------------------------------------\n  WELCOME TO BUS TICKET GENERATING SYSTEM\n----------------------------------------------\n");
    j = check_file();
    if(j==0)
    open_file();
    menu();
}
void menu(){
    int x;
    printf("-------------\n MAIN MENU\n-------------\n");
    printf("-------------------\n 1.BOOK TICKETS\n 2.BUS INFO\n 3.FIND PNR\n 4.EXIT\n-------------------\n");
    printf("\n INPUT:  ");
    scanf("%d",&x);
    printf("\n");
        switch(x){
        case 1:display_routes();display_select();break;
        case 2:get_info();break;
        case 3:find_bus();break;
        case 4:exit(0);break;
        }

}
void get_info(){
    int opt;
    printf("---------------------------\n INFORMATION PORTAL \n---------------------------\n");
    display_routes();
    printf(" entre option:  ");
    scanf("%d",&opt);
   printf("-----------\n INFO: \n---------\n"); 
    switch(opt)
    {
        case 1:display_seats(0);break;
        case 2:display_seats(1);break;
        case 3:display_seats(2);break;
        case 4:display_seats(3);break;
        case 5:display_seats(4);break;
        case 6:display_seats(5);break;
        case 7:display_seats(6);break;  
        case 8:menu();break;
        default:printf(" CONDITIONS EXCEDED\n input correct option\n");break;
    }
    menu();
}
void find_bus(){
    int tn,i,j,flag=0;
    printf("-------------\n FIND BUS PORTAL \n-------------\n");
    printf("\n ENTRE THE TICKET NUMBER OF FIND BUS:  ");
    scanf("%d",&tn);
    for(i=0;i<8;i++){
        for(j=0;j<30;j++){
            if(tn == b[i].seatticket[j]){
            printf(" BUS - %d\n SEAT - %d\n",i,j);
            flag = 1;}
        }
    }
    if(flag==0)
    printf("\n-----------NOT FOUND-----------\nREDIRECTING TO MAIN MENU------------------\n");
    menu();
}
void display_routes(){
    printf("--------------------------------\n 1. ROUTE 1 - Secunderabad\n 2. ROUTE 2 - Ameerpet\n 3. ROUTE 3 - Hitech City\n 4. ROUTE 4 - Kompally\n 5. ROUTE 5 - Uppal\n 6. ROUTE 6 - Gachibowli\n 7. ROUTE 7 - Vikarabad\n 8. MAIN MENU\n--------------------------------\n\n");
}
void bus_selector(){
    int n;
    scanf("%d",&n);
  
        switch(n)
        {
            case 1:route(0,"SECUNDRABAD");break;
            case 2:route(1,"AMEERPET");break;
            case 3:route(2,"HITECH CITY");break;
            case 4:route(3,"KOMPALLY");break;
            case 5:route(4,"UPPAL");break;
            case 6:route(5,"GACHIBOWLI");break;
            case 7:route(6,"VIKARABAD");break;
            case 8:menu();break;
            default:printf(" CONDITIONS EXCEDED\n input correct option\n");display_routes();bus_selector();break;
        }
   
    
}   
void display_select(){
    printf("\n SELECT A ROUTE:  ");
    bus_selector();
}
void display_seats(int busn){
    int i,j;
    printf("----------\n SEATS \n----------");
    printf("\n BUS NUMBER %d\n",busn+1);
    printf("--------------------------------\n");
    printf(" 0. MENU/CANCEL \n");
    for(i=1;i<=30;i++){
        if(b[busn].seatflag[i]==1)
        printf(" %d. OCCUPIED BY %d\n",i,b[busn].seatticket[i]);
        else if((i)%2!=0)
        printf(" %d. COVID 19 RESTRICTION\n",i);
        else if((i)%2==0)
        printf(" %d. empty\n",i);
        }
        printf("--------------------------------\n");
    }
void display_ticket(int x){
printf("#####################\n YOUR TICKET IS %d\n######################\n",x);
}    
void display_proc(){
    int opt;
    printf("----------------\n1. BOOK AGAIN \n2. MAIN MENU\n----------------\n");
    scanf("%d",&opt);

       switch(opt){
           case 1:display_routes();bus_selector();break;
           case 2:menu();break;
           default:printf(" CONDITIONS EXCEDED\n input correct option\n");display_proc();break;
       } 
    
}
void route(int x,char y[]){
    int seat;
    printf("------------------------------------\n PORTAL FOR %s BUS TICKETS \n------------------------------------\n",y);
    printf("--------------------------------------\n DISTINATION KL UNIVERSITY HYDERABAD \n--------------------------------------\n");
    display_seats(x);
    printf("\n entre the seat to be booked:  ");
    scanf("%d",&seat);
    if(seat>=31||seat<=-1){
        printf("\n !!! SEAT DOES NOT EXIST !!! \n\n");
        display_proc();
    }
    else if(seat == 0){
        menu();
    }
    else if(seat%2!=0){
        printf("\n !!! NOT AVALABLE DUE TO COVID 19 REGULATIONS !!! \n\n");
        display_proc();
        }
    else{
        if(b[x].seatflag[seat]==1){
        printf("\n !!! ALREADY BOOKED !!! \n\n");
        display_proc();
        }
        else{
        b[x].seatflag[seat]=1;
        b[x].seatticket[seat]=ran+ticket;
        ran++;
        count_file();
        display_ticket(b[x].seatticket[seat]);
        printf("#####################\n YOUR TICKET PRICE IS Rs. 350\n######################\n");
        store_file(x,seat,b[x].seatticket[seat]);
        display_proc();
        
        }
    }
}
void store_file(int x,int y,int z){
    FILE *f;
    f = fopen("busfile.txt","a");
    fprintf(f,"%d %d %d\n",x,y,z);
    fclose(f);
}
void open_file(){
    int i,x,y,z,n;
    FILE *f,*c;
    c = fopen("count.txt","r");
    fscanf(c,"%d",&n);
    f = fopen("busfile.txt","r+");
    for(i=0;i<=n;i++){
    fscanf(f,"%d %d %d\n",&x,&y,&z);
    b[x].seatticket[y] = z;
    b[x].seatflag[y] = 1;
    }
    fclose(f);
    fclose(c);
    
}
void count_file(){
    FILE *f;
    f = fopen("count.txt","w");
    fprintf(f,"%d",count);
    count++;
    fclose(f);
}
int check_file(){
    FILE *f;
    f = fopen("busfile.txt","r");
    if(f==NULL)
    return 1;
    else
    return 0;
    fclose(f);
}
