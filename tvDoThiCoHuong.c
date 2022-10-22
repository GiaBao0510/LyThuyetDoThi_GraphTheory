#include<stdio.h>
#define maxverties 50			  //So dinh toi da
#define maxedges 100			  //So luong cung toi da
#define no_edges -1
/*--------------Ma tran khong co trong so---------------*/
	typedef struct{
		int n;					//Quy dinh so luong dinh va so luong cung
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
				printf("%3d",G->A[i][j]);
			}
		}
	}
	//Them cung vao ma tran
	void addedges(Graph *G,int a,int b){
		G->A[a][b]=1;
	}
	//Kiem Tra tinh lien ke giua goc va ngon
	int checkneighbour(Graph *G,int a,int b){
		return (G->A[a][b]==1);
	}
/*-----------Ma tran co trong so---------------*/
	typedef struct{
		int n,m;	//So luong dinh,so luong cung
		int u,v,w;	//Cung noi hai dinh U va dinh V, W la trong so
		int L[maxverties][maxedges];
	}DTCH;
	//khoi tao ma tran co trong so la -1
	void CreateGraphWeight(DTCH *G){
		int i,j;
		for(i=1;i<=G->n;i++){
			for(j=1;j<=G->m;j++){
				G->L[i][j]= no_edges;
			}
		}
	}
	//In ma tran trong so
	void PrintGraphWeight(DTCH *G){
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
	void AddEdgesWeight(DTCH *G,int u,int v,int w){
		G->L[u][v]=w;
	}
	//Kiem Tra tinh lien ke giua goc va ngon cua ma tran co trong so
	int CheckNeighbour_Weight(DTCH *G,int a,int b){
		return (G->L[a][b]!=no_edges)? 1:0;
	}
//Nua bac trong va nua bac ngoai cua dinh X
void halfstep(Graph *G,int x){
	int i,a=0,b=0;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i]==1){	//Nua bac Ngoai: chu yeu la tap hop cac dau ra 
			a++;
		}
		if(G->A[i][x]==1){	//Nua bac bac trong: chu yeu la tap hop cac dau vao 
			b++;
		}
	}
	printf("\nNua bac ngoai (d^+): %d",a);
	printf("\nNua bac trong (d^-): %d",b);
}
//Tra ve nua bac trong(Tim cac dinh co dau ra/Tap hop cac anh) cua dinh X
int halfstepin(Graph *G,int x){
	int i,dem=0;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i]==1){
			dem++;
		}
	}
	return dem;
}
//Tra ve nua bac ngoai(Tim cac dinh co dau vao/Tap hop cac tao anh) cua dinh X
int halfstepoutside(Graph *G,int x){
	int i,dem=0;
	for(i=1;i<=G->n;i++){
		if(G->A[i][x]==1){
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
	int empty_list(list *L){
		return L->size==0;
	}
	void push_back(list *L,int x){
		L->data[L->size]=x;
		L->size++;
	}
	int element(list *L,int p){
		return L->data[p-1];
	}
/*--------	Ngan xep	------------*/	
	typedef struct{
		int dataS[maxverties];
		int sizeS;
	}stack;
	void makenull_stack(stack *S){
		S->sizeS=0;
	}
	int empty_stack(stack *S){
		return S->sizeS==0;
	}
	void push_stack(stack *S,int x){
		S->dataS[S->sizeS]=x;
		S->sizeS++;
	}
	void pop(stack *S){
		S->sizeS--;
	}
	int top(stack *S){
		return S->dataS[S->sizeS-1];
	}
/*---	Hang doi	---*/
	typedef struct{
		int dataQ[maxverties];
		int front,rear;
	}queue;
	void makenull_queue(queue *Q){
		Q->front=0;
		Q->rear=-1;
	}
	int empty_queue(queue *Q){
		return Q->front > Q->rear;
	}
	void push_queue(queue *Q,int x){
		Q->rear++;
		Q->dataQ[Q->rear]=x;
	}
	void pop_queue(queue *Q){
		Q->front++;
	}
//danh sach cac dinh ke cua mot dinh X bat ky
list neighbour(Graph *G,int x){
	list danhsach;
	makenull_list(&danhsach);
	int i;
	for(i=1;i<=G->n;i++){
		if(checkneighbour(G,x,i)==1){
			push_back(&danhsach,i);
		}
	}
	return danhsach;
}
//danh sach cac dinh ke cua mot dinh X bat ky cua ma tran co trong so
list neighbourWeight(DTCH *G,int x){
	list danhsach;
	makenull_list(&danhsach);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckNeighbour_Weight(G,x,i)==1){
			push_back(&danhsach,i);
		}
	}
	return danhsach;
}
/*--- Ma tran chua co trong so ---*/
	//1.Danh sach cac anh cua mot dinh X bat ky
	list photolist(Graph *G,int x){
		list danhsach;
		makenull_list(&danhsach);
		int i;
		for(i=1;i<=G->n;i++){
			if(G->A[x][i]==1){
				push_back(&danhsach,i);
			}
		}
		return danhsach;
	}
	//2.Danh sach cac tao anh cua mot dinh X bat ky
	list photomakerlist(Graph *G,int x){
		list danhsach;
		makenull_list(&danhsach);
		int i;
		for(i=1;i<=G->n;i++){
			if(G->A[i][x]==1){
				push_back(&danhsach,i);
			}
		}
		return danhsach;
	}
/*--- Ma tran co trong so ---*/
	//1.Danh sach cac anh cua mot dinh X bat ky
	list photolistWeight(DTCH *G,int x){
		list danhsach;
		makenull_list(&danhsach);
		int i;
		for(i=1;i<=G->n;i++){
			if(CheckNeighbour_Weight(G,x,i)==1){
				push_back(&danhsach,i);
			}
		}
		return danhsach;
	}
	//2.Danh sach cac anh cua mot dinh X bat ky
	list photomakerlistWeight(DTCH *G,int x){
		list danhsach;
		makenull_list(&danhsach);
		int i;
		for(i=1;i<=G->n;i++){
			if(CheckNeighbour_Weight(G,x,i)==1){
				push_back(&danhsach,i);
			}
		}
		return danhsach;
	}
