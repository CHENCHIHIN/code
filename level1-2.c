#include<stdio.h>
#include<string.h>

char zhiling[20];
int is_logged=0;

char name1[100];
char number[100];
int floor1;
char date[7+1][1024]={"","Monday","Tuesday","Wenesday","Thursday","Friday","Saturday","Sunday"};
int m;
int k;
struct edge
{
	char name[10];
	int state;
}n[7+1][5+1][4][4];

int get_day(char a[]){
	for(int i=1;i<=7;i++){
		if(strcmp(a,date[i])==0)
			return i;
	}
	return -1;
}

int main(){
	while(1){
		if(is_logged!=1){
			scanf("%s",&zhiling);
			if(strcmp(zhiling,"Login")==0){
				printf("(Enter Your Name):");
				scanf("%s",&name1);
				printf("(%s Login Successful)\n",name1);
				is_logged=1; 
			}
			else if(strcmp(zhiling,"Quit")==0){
				printf("(OK!Quit Successful!)\n"); 
				break; 
			}
			else
				printf("(Please Login Now!)\n"); 
		}
		else{
			scanf("%s",&zhiling);
			if(strcmp(zhiling,"Exit")==0){
				printf("(OK!Exit successful!)\n\n"); 
				is_logged=0;
				for(int i=0;i<=5;i++){
						for(int j=0;j<=7;j++){
							for(int b=0;b<=4;b++){
								for(int l=0;l<=4;l++){
									if(n[i][j][b][l].state==2)
										n[i][j][b][l].state=1;
							}
						}
					}
				}
			}
			else if(get_day(zhiling)!=-1){
				printf("Floor ");
				scanf("%d",&floor1);
				for(int i=0;i<=3;i++){
					for(int j=0;j<=3;j++){
						if(strcmp(n[get_day(zhiling)][floor1][i][j].name,name1)==0&&n[get_day(zhiling)][floor1][i][j].state==1)
							printf("2");
						else
							printf("%d",n[get_day(zhiling)][floor1][i][j].state);
					}
					printf("\n");
				}
			}
			else if(strcmp(zhiling,"Reserve")==0){
				scanf("%s",&number);
				printf("Floor ");
				scanf("%d",&floor1);
				printf("seat ");
				scanf("%d%d",&m,&k);
				if(n[get_day(number)][floor1][m-1][k-1].state==0) {
					n[get_day(number)][floor1][m-1][k-1].state+=2;
					strcpy(n[get_day(number)][floor1][m-1][k-1].name,name1);
					printf("OK\n\n");
				}
				else
					printf("(The seat had been reserved!)\n");
			}
			else if(strcmp(zhiling,"Quit")==0){
				printf("(OK!Quit Successful!)\n"); 
				break; 
			}
			else{
				printf("(Error Order!)\n"); 
				continue;
			}
		}
	}
}
