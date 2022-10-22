#include<stdio.h>
#define maxverties 50			//Dat Maxverties = 50
#define maxvedges 100
#define no_edges -1
/*-----------Ma tran chua co trong so-------------*/
	typedef struct{
		int n;					  //Quy dinh so luong dinh va so luong cung
		int A[maxverties][maxverties];//Quy dinh so luong toi da cua hang va cot 
	}Graph;
	//khoi tao ma tran khong
	void creategraph(Graph *G){
		int i,j;
		for(i=1;i<=G->n;i++)		//Tao dong
			for(j=1;j<=G->n;j++)	//Tao cot
				G->A[i][j]=0;
	}
	//In ma tran
	void PrintGraph(Graph *G){
		int i,j;
		printf("Ma tran cap %d\n",G->n);
		for(i=1;i<=G->n;i++){
			printf("\n%d:",i);
			for(j=1;j<=G->n;j++){
				printf(" %d",G->A[i][j]);
			}
		}
	}
	//Them cung vao ma tran
	void addedges(Graph *G,int a,int b){
		G->A[a][b]=G->A[b][a]=1;
	}
	//Kiem tra lang gieng cua cac cap dinh
	int CheckAdjacent(Graph *G,int a,int b){
		return(G->A[a][b]==1);
	}
	//Dem bac cua mot dinh X
	int Degree(Graph *G,int x){
		int i,dem=0;
		for(i=1;i<=G->n;i++){
			if(CheckAdjacent(G,x,i)){
				dem++;
			}
		}
		return dem;
	}
/*-----------Ma tran co trong so-------------*/
	typedef struct{
		int n,m;							//Quy dinh so luong dinh va so luong cung
		int u,v,w;							//Dinh U noi voi dinh V,W la tong so tren cung U,V
		int L[maxverties][maxvedges];		//Luu tru trong so tu dinh U den dinh V
	}DTVH;
	//khoi tao ma tran co trong so la khong
	void CreateGraphWeight(DTVH *G){
		int i,j;
		for(i=1;i<=G->n;i++){
			for(j=1;j<=G->m;j++){
				G->L[i][j]=no_edges;
			}
		}
	}
	//In ma tran trong so
	void PrintGraphWeight(DTVH *G){
		int i,j;
		printf("Ma tran cap %d\n",G->n);
		for(i=1;i<=G->n;i++){
			printf("\n%d:",i);
			for(j=1;j<=G->n;j++){
				printf(" %2d",G->L[i][j]);
			}
		}
	}
		//Them cung vao ma tran co trong so
	void AddEdgesWeight(DTVH *G,int u,int v,int w){
		G->L[u][v]=G->L[v][u]=w;
	}
	//Kiem Tra tinh lien ke giua goc va ngon cua ma tran co trong so
	int CheckneAdjacentWeight(DTVH *G,int a,int b){
		return (G->L[a][b]!=no_edges)? 1:0;
	}
	//Dem bac cua mot dinh X cua ma tran co trong so
	int Degree_weight(DTVH *G,int x){
		int i,dem=0;
		for(i=1;i<=G->n;i++){
			if(CheckneAdjacentWeight(G,x,i)==1){
				dem++;
			}
		}
		return dem;
	}
/*---	Danh sach	---*/
typedef struct{
	int data[maxverties];
	int size;
}list;
void makenull_list(list *L){
	L->size=0;
} 
void push_back(list *L,int x){
	L->data[L->size]=x;
	L->size++;
}
int element(list *L,int p){
	return L->data[p-1];
}
//danh sach cac dinh ke cua mot dinh X bat ky
list neighbour(Graph *G,int x){
	list danhsach;
	makenull_list(&danhsach);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,x,i)){
			push_back(&danhsach,i);
		}
	}
	return danhsach;
}
//danh sach cac dinh ke cua mot dinh X bat ky cua ma tran co trong so
list neighbourWeight(DTVH *G,int x){
	list danhsach;
	makenull_list(&danhsach);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckneAdjacentWeight(G,x,i)==1){
			push_back(&danhsach,i);
		}
	}
	return danhsach;
}
