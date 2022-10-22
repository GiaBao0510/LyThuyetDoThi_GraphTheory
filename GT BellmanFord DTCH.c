#include<stdio.h>
#define INFINITY 9999999
#define max 100
typedef struct{
	int u,v		//Dinh dau U va dinh cuoi V
	,w;			//W la trong so giua cung U,V
}Edges;
typedef struct{
	int n,				//So luong dinh
		m;				//Do dai cua cung
	Edges edges[max];	//Danh sach luu truu thong so cua cung
}graph;
//khoi tao do dai cua cung
void init_graph(graph *G){
	G->m=0;
}
//Them cung
void addEdges(graph *G,int u,int v,int w){
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;	//tang do dai cung len 1 don vi
}
//Cac bien ho tro
int pi[max];
int P[max];
void bell_manford(graph *G,int s){
	int i,k;
	//khoi tao
	for(i=1;i<=G->n;i++){
		pi[i]=INFINITY;
	}
	pi[s]=0;
	P[s]=-1;//Truoc dinh S khong co dinh nao nen cap -1
	for(i=1;i<G->n;i++){
		//Vong lap chinh lap(n-1) lan
		for(k=0;k<G->m;k++){//vong lap nay dung de kiem dinh bat dau
			int U = G->edges[k].u;
			int V = G->edges[k].v;
			int W = G->edges[k].w;
			if(pi[U] + W < pi[V]){//Duyet qua cac cung cap nhat neu thoa dieu kien
				pi[V]=pi[U]+W;
				P[V]=U;
			}
		}
	}
}
int main(){
	FILE *f=fopen("DataGraphWeight.txt","r");
	if(f!=NULL){
		graph G;
		int m,e,u,v,w,i;
		fscanf(f,"%d%d",&G.n,&m);
		init_graph(&G);
		for(e=1;e<=m;e++){
			fscanf(f,"%d %d %d",&u,&v,&w);
			addEdges(&G,u,v,w);
		}
		bell_manford(&G,1);
		for(i=1;i<=G.n;i++){
			printf("pi[%d] = %d , p[%d] = %d\n",i,pi[i],i,P[i]);
		}
		printf("\nKiem tra chu trinh co am khong: ");
		(pi[G.n]<0)? printf("YES"):printf("NO");
	}else printf("Loi mo tep");
	fclose(f);
}
