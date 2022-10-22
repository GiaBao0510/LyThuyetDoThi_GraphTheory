#include<stdio.h>
#define maxverties 50			//Dat Maxverties = 50
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
//In bac cua tat ca cac dinh
void printdegree(Graph G){
	printf("\nBac cua tat cac ca dinh:\n");
	int i;
	for(i=1;i<=G.n;i++){
		printf("\nDegree [%d]: %d",i,Degree(&G,i));
	}
}
int main(){
	int m,u,v;
	Graph G;
	FILE *F;
	F=fopen("DataGraph.txt","r");
	if(F!=NULL){
		printf("\n\tDo thi vo huong doc tu file cach 1:\n");
		fscanf(F,"%d%d",&G.n,&m);
		creategraph(&G);
		//Doc cac cung trong file 
		int i;
		for(i=1;i<=m;i++){
			fscanf(F,"%d%d",&u,&v);
			addedges(&G,u,v);
		}
	PrintGraph(&G);
	printdegree(G);	
	}
	else printf("Loi mo tep");
	fclose(F);
}
