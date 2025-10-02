#include<stdio.h>
#include<string.h>

char zhiling[20];
int is_logged=0;

char name1[100];
char number[100];
int floor1;
char date[7+1][1024]={"","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
char name_list[26+1][10]={"Admin","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
char dark_list[26+1][10]={0};
int m,k;
int hang,lie;
int jishuqi=0;
struct edge
{
    char name[10];
    int state;
}n[7+1][5+1][4+6][4+6];

void load(){
    FILE*fp=fopen("level3_data.bin","rb"); //zhidu
    if(fp!=NULL){
        fread(&hang,sizeof(int),1,fp);
        fread(&lie,sizeof(int),1,fp);
        fread(n,sizeof(struct edge),8*6*(4+6)*(4+6),fp);
        fread(dark_list,sizeof(dark_list),1,fp);
        fclose(fp);
    }
}

void save(){
    FILE*fp= fopen("level3_data.bin","wb"); //fugai
    if(fp!=NULL){
        fwrite(&hang,sizeof(int),1,fp);
        fwrite(&lie,sizeof(int),1,fp);
        fwrite(n,sizeof(struct edge),8*6*(4+6)*(4+6),fp);
        fwrite(dark_list,sizeof(dark_list),1,fp);
        fclose(fp);
    }
}
void clear(){
	for(int i=0;i<=7;i++){
        for(int j=0;j<=5;j++){
            for(int b=0;b<4+6;b++){
                for(int l=0;l<4+6;l++){
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
            for(int b=0;b<4+6;b++){
                for(int l=0;l<4+6;l++){
                    n[i][j][b][l].state=0;
                    strcpy(n[i][j][b][l].name,"");
                }
            }
        }
    }
    hang=0;
    lie=0;
    for(int a=0;a<=26;a++){
        strcpy(dark_list[a],"");
    }
}

void list(){
    int list_time=0;
    for(int i=0;i<=7;i++){
        for(int j=0;j<=5;j++){
            for(int b=0;b<4+hang;b++){
                for(int l=0;l<4+lie;l++){
                    if(n[i][j][b][l].state!=0&&n[i][j][b][l].state!=-1){
                        printf("%s reserve %s Floor:%d Seat:%d %d\n",n[i][j][b][l].name,date[i],j,b+1,l+1);
                        list_time+=1;
                    }
                }
            }
        }
    }
    for(int a=0;a<=26;a++){
        if(strcmp("",dark_list[a])!=0){
            printf("%s in the dark_list.\n",dark_list[a]);
            list_time+=1;
        }
    }
    if(list_time==0)
        printf("(Empty list!)\n");
    list_time=0;
}

void help(){
    printf("For all user:\n");
    printf("1.Reserve(Reserve your seat:date floor seat.)\n");
    printf("2.Exit(Exit the name,but program is here.)\n");
    printf("3.Quit(Quit the program.)\n");
    printf("4.Login(Login your name.)\n");
    printf("5.Monday-Sunday(See all the seat situation on that day:Floor)\n");
    printf("6.Reservation(See your Reserve seat's imformation.)\n");
    printf("7.Cancel(Cancel the Reserve:date floor seat.)\n\n");
    printf("For Admin:\n");
    printf("1.Clear(Clear the list.But not 'x','Hang','Lie'.)\n");
    printf("2.ClearAll(Clear the list.)\n");
    printf("3.Lock(Lock the seat(s),no one can reserve it.)\n");
    printf("4.Open(Open the seat(s),from the lock.)\n");
    printf("5.List(Show All User's seat situation or situation.)\n");
    printf("6.ChangeHang(Chang the 'Hang' in the list)\n");
    printf("7.ChangeLie(Chang the 'Lie' in the list)\n");
    printf("8.DarkIn(Put user in the dark_list in.)\n");
    printf("9.DarkOut(Put user in the dark_list out.)\n\n");
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
                load();
                for(int i=0;i<=26;i++){
                    if(strcmp(name1,dark_list[i])==0){
                        printf("(You are in dark_list,you can't Login!)\n");
                        return 0;
                    }
                    else    
                        continue;
                }
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
                break; 
            }
            else if(strcmp(zhiling,"Help")==0){
                help();
            }
            else
                printf("(Please Login Now Or Help!)\n"); 
        }
        else{
            load();
            scanf("%s",zhiling);
            load();
            for(int i=0;i<=26;i++){
                if(strcmp(name1,dark_list[i])==0){
                    printf("(You are in dark_list,you can't move!)\n");
                    return 0;
                }
                else
                    continue;
            }
            if(strcmp(zhiling,"Exit")==0){
                printf("(OK! %s Exit successful!)\n\n",name1); 
                is_logged=0;
                jishuqi=0;
                save();
            }
            else if(strcmp(zhiling,"Help")==0){
                help();
            }
            else if(get_day(zhiling)!=-1){
                load();
                printf("Floor: ");
                scanf("%d",&floor1);
                for(int i=0;i<4+hang;i++){
                    for(int j=0;j<4+lie;j++){
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
                load();
                printf("Date:");
                scanf("%s",number);
                printf("Floor: ");
                scanf("%d",&floor1);
                printf("seat: ");
                scanf("%d%d",&m,&k);
                if(m-1>=4+hang||k-1>=4+lie){
                    printf("(The seat's location is illegal!)\n");
                }
                else if(n[get_day(number)][floor1][m-1][k-1].state==-1)
                	printf("(The seat has be Lock now!Can not Reserve.)\n");
				else if(n[get_day(number)][floor1][m-1][k-1].state==0){
                    n[get_day(number)][floor1][m-1][k-1].state+=1;
                    strcpy(n[get_day(number)][floor1][m-1][k-1].name,name1);
                    printf("OK\n\n");
                    save();
                }
                else
                    printf("(The seat had been reserved!)\n");
            }
			else if(strcmp(zhiling,"Reservation")==0){
                load();
                int time=0;
                for(int i=0;i<=7;i++){
                    for(int j=0;j<=5;j++){
                        for(int b=0;b<4+hang;b++){
                            for(int l=0;l<4+lie;l++){
                                if(strcmp(n[i][j][b][l].name,name1)==0&&n[i][j][b][l].state!=0){
                                    printf("(%s Floor:%d seat:%d %d)\n",date[i],j,b+1,l+1);
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
                break;
            }
            else if(strcmp(zhiling,"Cancel")==0){
                load();
                printf("Date:");
                scanf("%s",number);
                printf("Floor: ");
                scanf("%d",&floor1);
                printf("seat: ");
                scanf("%d%d",&m,&k);
                if(m-1>=4+hang||k-1>=4+lie){
                    printf("(The seat's location is illegal!)\n");
                }
                else if(strcmp(name1,"Admin")==0){
                    n[get_day(number)][floor1][m-1][k-1].state=0;
                    strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                    printf("(OK!Cancel successful from Admin!)\n");
                    save();
                }
                else if(n[get_day(number)][floor1][m-1][k-1].state!=0&&strcmp(n[get_day(number)][floor1][m-1][k-1].name,name1)==0){
                    n[get_day(number)][floor1][m-1][k-1].state=0;
                    strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                    printf("(OK!Cancel successful from yourself!)\n");
                    save();
                }
                else if(n[get_day(number)][floor1][m-1][k-1].state==1&&strcmp(n[get_day(number)][floor1][m-1][k-1].name,name1)!=0)
                    printf("(You can't cancel other's seat!)\n");
                else
                    printf("(The seat was empty!)\n");
            }
            else if(strcmp(name1,"Admin")==0){//admin code
            	if(strcmp(zhiling,"Open")==0){
                	char open[100];
                    load();
                    printf("Date:");
                    scanf("%s",number);
                	printf("Floor: ");
                	scanf("%d",&floor1);
                	printf("Hang,Lie,One?");
                    scanf("%s",open);
                    if(strcmp(open,"Hang")==0){
                        printf("Hang:");
                        scanf("%d",&m);
                        for(int i=0;i<4+lie;i++){
                            n[get_day(number)][floor1][m-1][i].state=0;
                            strcpy(n[get_day(number)][floor1][m-1][i].name,"");
                        }
                        printf("(Open'Hang',OK)\n");
                    }
                    else if(strcmp(open,"Lie")==0){
                        printf("Lie:");
                        scanf("%d",&k);
                        for(int i=0;i<4+hang;i++){
                            n[get_day(number)][floor1][i][k-1].state=0;
                            strcpy(n[get_day(number)][floor1][i][k-1].name,"");
                        }
                        printf("(Open'Lie',OK)\n");
                    }
                    else{
                        printf("seat: ");
                	    scanf("%d%d",&m,&k);
                	    if(n[get_day(number)][floor1][m-1][k-1].state==-1){
                		    n[get_day(number)][floor1][m-1][k-1].state=0;
                		    strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                		    printf("(Open'One',OK)\n");
					    }
					    else
						    printf("(The seat is opening now!)\n");
                    }
                    save();
            	}
            	else if(strcmp(zhiling,"Lock")==0){
                	char lock[100];
                    load();
                    printf("Date:");
                    scanf("%s",number);
                	printf("Floor: ");
                	scanf("%d",&floor1);
                	printf("Hang,Lie,One?\n");
                    scanf("%s",lock);
                    if(strcmp(lock,"Hang")==0){
                        printf("Hang:");
                        scanf("%d",&m);
                        for(int i=0;i<4+lie;i++){
                            n[get_day(number)][floor1][m-1][i].state=-1;
                            strcpy(n[get_day(number)][floor1][m-1][i].name,"");
                        }
                        printf("(Lock'Hang',OK)\n");
                    }
                    else if(strcmp(lock,"Lie")==0){
                        printf("Lie:");
                        scanf("%d",&k);
                        for(int i=0;i<4+hang;i++){
                            n[get_day(number)][floor1][i][k-1].state=-1;
                            strcpy(n[get_day(number)][floor1][i][k-1].name,"");
                        }
                        printf("(Lock'Lie',OK)\n");
                    }
                    else{
                        printf("seat: ");
                	    scanf("%d%d",&m,&k);
                	    if(n[get_day(number)][floor1][m-1][k-1].state!=-1){
                		    n[get_day(number)][floor1][m-1][k-1].state=-1;
                		    strcpy(n[get_day(number)][floor1][m-1][k-1].name,"");
                		    printf("(Lock'One',OK)\n");
					    }
					    else
						    printf("(The seat has been locked!)\n");
                    }
                    save();
            	}
                else if(strcmp(zhiling,"ClearAll")==0){
                	load();
                    clear1();
                	printf("(OK!Clear Successful!)\n");
                	save();
            	}
                else if(strcmp(zhiling,"Clear")==0){
                	load();
                    clear();
                	printf("(OK!Clear Successful!But not 'x','Hang','Lie'.)\n");
                	save();
            	}
                else if(strcmp(zhiling,"DarkIn")==0){
                	load();
                    char nameIn[100];
                    int timeIn=0;
                    printf("Who you what to DarkIN:");
                    scanf("%s",nameIn);
                    for(int i=0;i<=26;i++){
                        if(strcmp(nameIn,name_list[i])==0){
                            timeIn=timeIn+1;
                            if(strcmp(nameIn,name_list[0])==0)
                                printf("(You can't not be DarkIn.)\n");
                            else{
                                 strcpy(dark_list[i],nameIn);
                                 printf("(OK!DarkIn %s Successful.)\n",nameIn);
                                 save();
                                 break;
                            }
                        }
                    }
                    if(timeIn==0)
                        printf("(This people are not a user!)\n");
                    timeIn=0;
            	}
                else if(strcmp(zhiling,"DarkOut")==0){
                	load();
                    char nameOut[100];
                    int timeOut=0;
                    printf("Who you what to DarkOut:");
                    scanf("%s",nameOut);
                    for(int i=0;i<=26;i++){
                        if(strcmp(nameOut,dark_list[i])==0){
                            timeOut=timeOut+1;
                            strcpy(dark_list[i],"");
                            printf("(OK!DarkOut %s Successful.)\n",nameOut);
                            save();
                            break;
                        }
                    }
                    if(timeOut==0)
                        printf("(This people are not a user!)\n");
                    timeOut=0;
            	}
                else if(strcmp(zhiling,"ChangeHang")==0){
                	load();
                    printf("Change The 'Hang':4+");
                    int temp1;
                    scanf("%d",&temp1);
                    if(4+temp1>10){
                        printf("(That scale is too big(>10))\n");
                    }
                    else if(4+temp1<=0){
                        printf("(That scale is too small(<=0))\n");
                    }
                	else{
                        hang=temp1;
                        printf("(OK!'Hang' max is %d now!)\n",4+hang);
                        save();
                    }
            	}
                else if(strcmp(zhiling,"ChangeLie")==0){
                	load();
                    printf("Change The 'Lie':4+");
                    int temp2;
                    scanf("%d",&temp2);
                    if(4+temp2>10){
                        printf("(That scale is too big(>10))\n");
                    }
                    else if(4+temp2<=0){
                        printf("(That scale is too small(<=0))\n");
                    }
                	else{
                        lie=temp2;
                        printf("(OK!'Lie' max is %d now!)\n",4+lie);
                        save();
                    }
            	}
            	else if(strcmp(zhiling,"List")==0){
                    load();
                    list();
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