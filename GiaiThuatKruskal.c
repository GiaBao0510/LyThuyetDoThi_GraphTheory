#include<stdio.h>
typedef struct{
	int u,v,w;
}edges;
typedef struct{
	int n,m;
	edges E[100];
}dothi;
//khoi tao
void initgraph(dothi *G){
	G->m=0;
}
//them cung
void addedges(dothi *G,int u,int v,int w){
	G->E[G->m].u=u;
	G->E[G->m].v=v;
	G->E[G->m].w=w;
	G->m++;
}
//In 
void printedges(dothi G){
	int i;
	for(i=0;i<G.m;i++){
		printf("\n%d%3d%3d",G.E[i].u,G.E[i].v,G.E[i].w);
	}
}
//sap xep cung tang dan
void SWAP(edges *A,edges *B){
	edges T=*A;
	*A =*B;
	*B =T;
}
void insertionsort(dothi *G){
	int i,j;
	for(i=1;i<G->m;i++){
		j=i;
		while(j>0 && G->E[j-1].w>G->E[j].w){
			SWAP(&G->E[j-1],&G->E[j]);
			j--;
		}
	}
}
//Bien ho tro
int p[100];
//Ham tim nut goc
int find_root(int x){
	if(p[x]==x){
		return x;
	}
	return find_root(p[x]);
}
int kruskal(dothi *G,dothi *T){
	int i,tong=0;
	//khoi tao
	initgraph(T);
	for(i=1;i<=G->n;i++){
		p[i]=i;
	}
	//Lap tim so cung co trong so trong do thi
	for(i=0;i<G->m;i++){
		int u = G->E[i].u;
		int v = G->E[i].v;
		int w = G->E[i].w;
		int rootU = find_root(u);
		int rootV = find_root(v);
		if(rootU != rootV){
			if(u<v){
				addedges(T, u, v, w);
			}
			else{
				addedges(T, v, u, w);
			}
			p[rootV]=rootU;
			tong+=w;
		}
	}
	return tong;
}
int main(){
	int i,u,v,w,m;
	dothi G,T;
	scanf("%d %d",&G.n,&m);
	initgraph(&G);
	for(i=0;i<m;i++){
		scanf("%d %d %d",&u,&v,&w);
		addedges(&G, u, v, w);//Doc so cung
	}
	printedges( G);
	insertionsort(&G);
	printf("\nCac cung sao khi sap xep tang dan:\n");
	printedges(G);
	printf("\nTong do dai duong di: %d\n Duong di:",kruskal(&G,&T));
	printedges(T);
}
