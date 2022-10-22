#include<stdio.h>
int main(){
	int tg;
	printf("Nhap thoi gian: "); scanf("%d",&tg);
	do{
		if(tg!= 11 && tg!=5){
			printf("Nhap lai thoi gian: "); scanf("%d",&tg);
		}	
	}while(tg!= 11 && tg!=5);
	printf("Hoan tat");
}
