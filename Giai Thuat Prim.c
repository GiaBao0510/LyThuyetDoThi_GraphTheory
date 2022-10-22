#include<stdio.h>
#define no_edges -1
typedef struct{
	int n,m;//Dinh-Cung
	int A[50][50];//Trong so cua cung
}graph;
typedef struct{
	int u,v,w;
}Edges;
//Khoi tao do thi
void initgraph(graph *G){
	G->m=0;
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			G->A[i][j]= no_edges;
		}
	}
}
//Them cung
void addedges(graph *g,int x,int y,int w){
	g->A[x][y] = g->A[y][x] =w;
}
//Danh sach
	typedef struct{
		int data[100];
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
//Dinh ke
list neighbour(graph *g,int x){
	list DSKE;
	makenull_list(&DSKE);
	int i;
	for(i=1;i<=g->n;i++){
		if(g->A[x][i]!=no_edges){
			push_back(&DSKE,i);
		}
	}
	return DSKE;
}
//Bien ho tro
int p[50],pi[50],mark[50],dem=0;
Edges E[50];
//Giai thuat prim
void prim(graph *G,int s,int *tong){
	int i,j,k,e;
	list DS;
	//1.khoi tao
	makenull_list(&DS);//danh sach rong
	for(i=1;i<=G->n;i++){
		p[i]=-1;
		pi[i]=999;
		mark[i]=0;
	}
	//2. bo  dinh bat dau vao danh sach
	pi[s]=0;
	p[s]=-1;
	mark[s]=1;
	push_back(&DS,s);
	//3.Lap n-1 lan
	for(i=1;i<G->n;i++){
		int minPI=999,U,V,minU,minV,tamU=999;
		for(j=1;j<=DS.size;j++){//Danh sach chinh(U)
			U =element(&DS,j);
			list dske =neighbour(G,U);
			for(k=1;k<=dske.size;k++){//Danh sach ke (V)
				V =element(&dske,k);
				if(mark[V]==0){//Neu dinh ke chua co trong danh sach thi thuc hien cong viec
					if(pi[V] > G->A[U][V] && G->A[U][V] != no_edges){
						pi[V]=G->A[U][V];	//cap nhat pi cua tung dinh
						p[V]=U;				//Cap nhat cha cua dinh V la dinh U	
					}
					if(tamU > G->A[U][V]){//Tim duong tu U den V nho nhat
						tamU = G->A[U][V];
						minU = U;		 //Chon duoc duong dinh U
					}
				}	
			}
		}
	//Tim pi nho nhat bo vao danh sach/Tuc la tim Dinh ke no nho nhat,danh dau no da duyet
		for(e=1;e<=G->n;e++){
			if(mark[e]==0 && minPI > pi[e]){
				minPI = pi[e];
				minV=e;
			}
		}
	//Bo dinh gan nhat(minV) vao danh sach chinh
		mark[minV]=1;		//duyet
		*tong+=pi[minV];		//tong do dai duong di
		push_back(&DS,minV);//Day dinh ke gan nhat vao danh sach
	//Tim duoc duong di ngan nhat
		if(G->A[minU][minV] != no_edges){//Kiem tra dieu kien
			E[dem].u=minU;
			E[dem].v=minV;
			E[dem].w=pi[minV];
			dem++;	
		}
	}
}	
int main(){
	int u,v,w,i,m,s,TongW=0;
	graph G;
	scanf("%d %d",&G.n,&m);
	initgraph(&G);
	for(i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		addedges(&G, u,v, w);
		TongW+=w;
	}
	printf("\nNhap dinh bat dau: ");scanf("%d",&s);
	int tong=0;	
	prim(&G,s,&tong);
	printf("\nTong do dai duong di sau khi ap dung giai thuat Prim: %d",tong);
	printf("\nDuong di nhin theo cach thu 1: ");
	for(i=1;i<=G.n;i++){
		printf("\npi[%d] = %d\t|\tp[%d] = %d",i,pi[i],i,p[i]);
	}
	printf("\nDuong di nhin theo cach thu 2:\n\tDinh(U): \tDinh(V): \tTrong_so(W):");
	for(i=0;i<dem;i++){
		printf("\n\t%2d\t\t%d\t\t%5d",E[i].u,E[i].v,E[i].w);
	}
	printf("\n\nTong trong so cac cung bi xoa: %d",TongW-tong);
	return 0;	
}
