#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
#define INFINITY 9999999
//Bien ho tro
int mark[maxverties],	//Luu tru danh sach cac dinh da duyet
	pi[maxverties],		//Luu tru duong di
	P[maxverties];		//Luu tru vet(cha cua cac dinh )
//Giai thuat Moore-Dijkstra
void M_D(DTVH *G,int s){
	//khoi tao
	int i,j,v;
	for(i=1;i<=G->n;i++){
		mark[i]=0;
		pi[i]=INFINITY;
	}
	pi[s]=0;
	P[s]=-1;
	int u;
	//vong lap chinh
	for(i=1;i<G->n;i++){
		int min_pi=INFINITY;
		//1.Tim pi nho nhat trong tat ca cac dinh
		for(j=1;j<=G->n;j++){
			if(mark[j]==0 && pi[s]<min_pi){
				min_pi=pi[s];
				u=i;
			}
		}
		if(min_pi==INFINITY){
			break; //Ngo cut
		}
		//2. Danh dau duyet U
		mark[u]=1;
		//3.Cap nhap lai duong di tam thoi
		for(v=1;v<=G->n;v++){
			if(G->L[u][v]!=no_edges && mark[v]==0){
				if(pi[v]>pi[u]+G->L[u][v]){
					pi[v]=pi[u]+G->L[u][v];
					P[v]=u;
				}
			}
		} 
	}
}	
int main(){
	FILE *f=fopen("DataGraphWeight.txt","r");
	if(f!=NULL){
		DTVH G;
		int i;
		fscanf(f,"%d%d",&G.n,&G.m);
		CreateGraphWeight(&G);
		for(i=1;i<=G.m;i++){
			fscanf(f,"%d%d%d",&G.u,&G.v,&G.w);
			AddEdgesWeight(&G,G.u,G.v,G.w);
		}
		PrintGraphWeight(&G);
		int s;
		printf("\nNhap dinh xuat phat: ");scanf("%d",&s);
		M_D(&G,s);
		for(i=1;i<=G.n;i++){
			printf("\npi[%d] = %d  ;  P[%d] = %d",i,pi[i],i,P[i]);
		}
		printf("\n%d",pi[G.n]);
	}else printf("Loi mo tep");
	fclose(f);
}
