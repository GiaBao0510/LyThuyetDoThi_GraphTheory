#include<stdio.h>
#define maxvertices 50	//So luong toi da cua cac dinh
#define maxedges 50		//So luong toi da cua cac cung
typedef struct{
	int n,m;			//Quy dinh so luong dinh (N) va so luong cung (M)
	int A[maxvertices][maxedges]; //Ma tran dinh - canh(MA tran lien thong), doi vo do thi vo huong
}Graph;
//Tao ma tran khong
void Creategraph(Graph *G){
	int i,j;
	for(i=1;i<=G->n;i++){		//Dinh (Hang)
		for(j=1;j<=G->m;j++){	//Cung (Cot)
			G->A[i][j]=0;
		}
	}
}
//In ma tran
void Printgraph(Graph G){
	int i,j;
	printf("\nMa tran dinh - cung cua do thi vo huong\nMa tran cap %dx%d:\n",G.n,G.m);
	for(i=1;i<=G.n;i++){	
		printf("\n%d:",i);
		for(j=1;j<=G.m;j++){	
			printf(" %d",G.A[i][j]);
		}
	}
}
//Them cung e = (x,y) vao ma tran
void Addedges(Graph *G,int e,int x,int y){
	G->A[x][e]=1;							//Cho E lien thuoc voi dinh X
	G->A[y][e]=1;							//Cho E lien thuoc voi dinh Y
/* Noi cach khac E la mot cung noi dinh X va dinh Y lai voi nhau */	
}
//Kiem tra lang gieng giua 1 cap dinh X,Y
int Checkadjaccent(Graph G,int x,int y){
	int e;
	for(e=1;e<=G.m;e++){ 		//Cho chay giua cac canh 
		if(G.A[x][e]==1 && G.A[y][e]==1){
			return 1;
		}
	}
	return 0;
}
//Dem bac cua dinh X
int Degreevertices(Graph G,int x){
	int i,dem=0;
	for(i=1;i<=G.m;i++){
		if(G.A[x][i]==1){
			dem++;
		}
	}
	return dem;
}
