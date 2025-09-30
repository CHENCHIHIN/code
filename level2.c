#include<stdio.h>
#include<string.h>

char zhiling[20];
int is_logged=0;

char name1[100];
char number[100];
int floor1;
char date[7+1][1024]={"","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
char name_list[26+1][10]={"Admin","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
int m;
int k;
int jishuqi=0;
struct edge
{
    char name[10];
    int state;
}n[7+1][5+1][4][4]; 

void load(){
    FILE*fp=fopen("level2_data.bin", "rb"); //zhidu
    if(fp!=NULL){
        fread(n,sizeof(struct edge), 8*6*4*4, fp);
        fclose(fp);
    }
}

void save(){
    FILE*fp= fopen("level2_data.bin", "wb"); //fugai
    if(fp!=NULL){
        fwrite(n,sizeof(struct edge), 8*6*4*4, fp);
        fclose(fp);
    }
}
void clear(){
	for(int i=0;i<=7;i++){
        for(int j=0;j<=5;j++){
            for(int b=0;b<4;b++){
                for(int l=0;l<4;l++){
                    if(n[i][j][b][l].state!=-1){
                        n[i][j][b][l].state=0;
                        strcpy(n[i][j][b][l].name,"");
                    }
                }
            }
        }
    }
}

void clear1(){
	for(int i=0;i<=7;i++){
        for(int j=0;j<=5;j++){
            for(int b=0;b<4;b++){
                for(int l=0;l<4;l++){
                    n[i][j][b][l].state=0;
                    strcpy(n[i][j][b][l].name,"");
                }
            }
        }
    }
}

void help(){
    printf("For all user:\n");
    printf("1.Reserve(Reserve your seat:date floor seat.)\n");
    printf("2.Exit(Exit the name,but program is here.)\n");
    printf("3.Quit(Quit the program.)\n");
    printf("4.Login(Login your name.)\n");
    printf("5.Monday-Sunday(See all the seat situation on that day:Floor)\n");
    printf("6.Reservation(See your Reserve seat's imformation.)\n\n");
    printf("For Admin:\n");
    printf("1.Clear(Clear the list.But not'x')\n");
    printf("2.ClearAll(Clear the list.)\n");
    printf("3.Cancel(Cancel the Reserve:date floor seat.)\n");
    printf("4.Lock(Lock the seat,no one can reserve it.)\n");
    printf("5.Open(Open the seat,from the lock.)\n\n");
}

int get_day(char a[]){
    for(int i=1;i<=7;i++){
        if(strcmp(a,date[i])==0)
            return i;
    }
    return -1;
}

int main(){
    load();
    while(1){
        if(is_logged!=1){
            printf("(Please Login Now Or Help!)\n");
            scanf("%s",zhiling); 
            if(strcmp(zhiling,"Login")==0){
                printf("(Enter Your Name):");
                scanf("%s",name1);
                jishuqi=0;
                for(int i=0;i<=26;i++){
                    if(strcmp(name1,name_list[i])==0){
                        if(strcmp(name1,name_list[0])==0)
							printf("(%s Login Successful,Welcome %s)\n",name1,name1);
						else
							printf("(%s Login Successful)\n",name1);
                        is_logged=1;
                        jishuqi=1; 
                        break;
                    }
                }
                if(jishuqi==0)
                    printf("(You are not user!)\n");
            }
            else if(strcmp(zhiling,"Quit")==0){
                printf("(OK! Quit Successful!)\n"); 
                for(int i=0;i<=7;i++){
                    for(int j=0;j<=5;j++){
                        for(int b=0;b<4;b++){
                            for(int l=0;l<4;l++){
                                if(n[i][j][b][l].state==2)
                                    n[i][j][b][l].state=1;
                            }
                        }
                    }
                }
                save();
                break; 
            }
            else if(strcmp(zhiling,"Help")==0){
                help();
            }
            else
                printf("(Please Login Now Or Help!)\n"); 
        }
        else{
            scanf("%s",zhiling);
            if(strcmp(zhiling,"Exit")==0){
                printf("(OK! %s Exit successful!)\n\n",name1); 
                is_logged=0;
                jishuqi=0;
                for(int i=0;i<=7;i++){
                    for(int j=0;j<=5;j++){
                        for(int b=0;b<4;b++){
                            for(int l=0;l<4;l++){
                                if(n[i][j][b][l].state==2)
                                    n[i][j][b][l].state=1;
                            }
                        }
                    }
                }
            save();
            }
            else if(strcmp(zhiling,"Help")==0){
                help();
            }
            else if(get_day(zhiling)!=-1){
                printf("Floor: ");
                scanf("%d",&floor1);
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        if(n[get_day(zhiling)][floor1][i][j].state==-1)
                        	printf("X");
						else if(strcmp(n[get_day(zhiling)][floor1][i][j].name,name1)==0&&n[get_day(zhiling)][floor1][i][j].state==1)
                            printf("2");
                        else
                            printf("%d",n[get_day(zhiling)][floor1][i][j].state);
                    }
                    printf("\n");
                }
            }
            else if(strcmp(zhiling,"Reserve")==0){
                scanf("%s",number);
                printf("Floor: ");
                scanf("%d",&floor1);
                printf("seat: ");
                scanf("%d%d",&m,&k);
                if(n[get_day(number)][floor1][m-1][k-1].state==-1)
                	printf("(The seat can't not be reserved!)\n");
				else if(n[get_day(number)][floor1][m-1][k-1].state==0){
                    n[get_day(number)][floor1][m-1][k-1].state+=2;
                    strcpy(n[get_day(number)][floor1][m-1][k-1].name,name1);
                    printf("OK\n\n");
                }
                else
                    printf("(The seat had been reserved!)\n");
            }
			else if(strcmp(zhiling,"Reservation")==0){
                int time=0;
                for(int i=0;i<=7;i++){
                    for(int j=0;j<=5;j++){
                        for(int b=0;b<4;b++){
                            for(int l=0;l<4;l++){
                                if(strcmp(n[i][j][b][l].name,name1)==0&&n[i][j][b][l].state!=0){
                                    printf("%s Floor:%d seat:%d %d\n",date[i],j,b+1,l+1);
                                    time=time+1;
                                }
                            }
                        }
                    }
                }
                if(time==0)
                    printf("(Empty Reservation!)\n");
                time=0;
            }
            else if(strcmp(zhiling,"Quit")==0){
                printf("(OK!Quit Successful!)\n");
                for(int i=0;i<=7;i++){
                    for(int j=0;j<=5;j++){
                        for(int b=0;b<4;b++){
                            for(int l=0;l<4;l++){
                                if(n[i][j][b][l].state==2)
                                    n[i][j][b][l].state=1;
                            }
                        }
                    }
                }
                save();
                break;
            }
            else if(strcmp(name1,"Admin")==0){//admin code
            	if(strcmp(zhiling,"Open")==0){
                	scanf("%s",number);
                	printf("Floor: ");
                	scanf("%d",&floor1);
                	printf("seat: ");
                	scanf("%d%d",&m,&k);
                	if(n[get_day(number)][floor1][m-1][k-1].state==-1){
                		n[get_day(number)][floor1][m-1][k-1].state=0;
                		strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                		printf("(Open,OK)\n");
                		save();
					}
					else
						printf("(The seat is opening now!)\n");
            	}
            	else if(strcmp(zhiling,"Lock")==0){
                	scanf("%s",number);
                	printf("Floor: ");
                	scanf("%d",&floor1);
                	printf("seat: ");
                	scanf("%d%d",&m,&k);
                	if(n[get_day(number)][floor1][m-1][k-1].state!=-1){
                		n[get_day(number)][floor1][m-1][k-1].state=-1;
                		strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                		printf("(Lock,OK)\n");
                		save();
					}
					else
						printf("(The seat has been locked!)\n");
            	}
            	else if(strcmp(zhiling,"Clear")==0){
                	clear();
                	printf("(OK!Clear Successful!But not 'x')\n");
                	save();
            	}
                else if(strcmp(zhiling,"ClearAll")==0){
                	clear1();
                	printf("(OK!Clear Successful!)\n");
                	save();
            	}
            	else if(strcmp(zhiling,"Cancel")==0){
                	scanf("%s",number);
                	printf("Floor: ");
                	scanf("%d",&floor1);
                	printf("seat: ");
                	scanf("%d%d",&m,&k);
                	if(n[get_day(number)][floor1][m-1][k-1].state!=0){
                    	n[get_day(number)][floor1][m-1][k-1].state=0;
                    	strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                    	printf("(OK!Cancel Successful!)\n");
                	}
                	else
                    	printf("(The seat was empty!)\n");
                	save();
            	}
            	else{
            		printf("(Error Order!)\n");
                	continue;
				}
			}
			else{
                printf("(Error Order!)\n");
                continue;
            }
        }
    }
    return 0;
}