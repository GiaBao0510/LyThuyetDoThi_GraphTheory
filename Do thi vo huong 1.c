#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
#include<stdio.h>
//Nhap so luong cung Va cap dinh
void EnterEdgesGraph(Graph *G){
	int m;
	printf("Nhap so luong cung(Cap dinh): ");scanf("%d",&m);
	int i,x,y;
	for(i=1;i<=m;i++){
		printf("[%d]Nhap dinh: ",i);scanf("%d",&x);
		printf("[%d]Nhap dinh: ",i);scanf("%d",&y);
		addedges(&(*G),x,y);
	}
}
//In bac cua tat ca cac dinh
void printdegree(Graph G){
	printf("\nBac cua tat cac ca dinh:\n");
	int i;
	for(i=1;i<=G.n;i++){
		printf("\nDegree [%d]: %d",i,Degree(&G,i));
	}
}
void checkNeighbour(Graph G){
	int x,y;
	printf("\nNhap dinh X: ");scanf("%d",&x);
	printf("Nhap dinh Y: ");scanf("%d",&y);
	if(CheckAdjacent(&G,x,y)){
		printf("La lang gieng");
	}
	else printf("Khong la lang gieng");
}
int main(){
	Graph G;
	int n;
	printf("Nhap so luong dinh: ");scanf("%d",&G.n);
	creategraph(&G);
	EnterEdgesGraph(&G);
	PrintGraph(&G);
	printdegree(G);
	checkNeighbour(G);
}
