#include<stdio.h>
#include<string.h>

char line[1024];

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
			printf("%s:",zhiqian);
			printf("%s\n",zhihou);	
		}
	}
	return 0;
}