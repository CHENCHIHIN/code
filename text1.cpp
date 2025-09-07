#include<stdio.h>
#include<string.h>
char n[10];
int main(){
    while(1){
        scanf("%s",&n);
    if(strcmp(n,"Dian")==0)
        printf("2022\n");
    else if(strcmp(n,"Quit")==0)
        break;
    else
        printf("Error\n");
    }
}