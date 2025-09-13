#include<stdio.h>
#include<string.h>

char line[1024];
char key[100][1024]={0};
char value[100][1024]={0};
char n[10];
int sum=0;


int main(){
	FILE*a=fopen("data.txt","r");
	while(fgets(line,sizeof(line),a)!=NULL){
		if(strlen(line)==0)
			continue;
		line[strcspn(line,"\n")]='\0';
		char*douhao=strchr(line,':');
		if(douhao!=NULL){
			*douhao='\0';
			char*zhiqian=line;
			char*zhihou=douhao+1;
			strcpy(key[sum],zhiqian);
			strcpy(value[sum],zhihou);
			sum=sum+1;	
		}
	}
	while(1){
		printf("key:");
		scanf("%s",&n);
		if(strcmp(n,"Quit")==0)
			break;
		for(int i=0;i<=sum-1;i++){
			if(strcmp(n,key[i])==0)
				printf("value:%s\n",value[i]);
			else
				continue;
		}
	}
	fclose(a);
	return 0;
}