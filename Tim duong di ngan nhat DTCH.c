#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCoHuong.c"
#define INFINITY 9999999
//Cac bien ho tro
int pi[maxverties],		//Duong di ngan nhat tam thoi
	mark[maxverties]	//Danh dau da duoc duyet chua
	,P[maxverties];		//Cha cua cac dinh truoc
//Giai thuat Moore-Dijkstra
void MD(DTCH *G,int s){
	//Khoi tao
	int i,j;
	for(i=1;i<=G->n;i++){
		pi[i]=INFINITY;
		mark[i]=0;
	}
	pi[s]=0;
	P[s]=-1;//dinh truoc s khong co dinh nao ca
	int x;
	for(i=1;i<G->n;i++){
		int min_pi=INFINITY;
		//1.Tim pi nho nhat trong cac dinh ke
		for(j=1;j<=G->n;j++){
			if(min_pi>pi[j] && mark[j]==0){	//Neu dinh chua duoc duyet va co pi nho nhat
				min_pi=pi[j];	//Min_pi bang so duong di nhat tam thoi
				x=j;			//X bang dinh co pi nho nhat
			}
		}
		if(min_pi==INFINITY){
			break; //Ngo cut
		}
		//2.Danh dau da duyet X
		mark[x]=1;
		//3.Cap nhat lai duong di
		int y;
		for(y=1;y<=G->n;y++){
			if(mark[y]==0 && G->L[x][y]!=no_edges){//Neu dinh ke no chua duoc duyet va trong so no khac khong
				if(pi[y] > pi[x]+G->L[x][y]){//Neu pi tai dinh y lon hon dinh truoc no thi ta cap nhat lai duong di
					pi[y]=pi[x]+G->L[x][y];
					P[y]=x;//cap nhat cha cua dinh y la dinh x
				}
			}
		}
	}
}	
int main(){
	FILE *f=fopen("DataGraphWeight.txt","r");
	if(f!=NULL){
		DTCH G;
		int i;
		fscanf(f,"%d%d",&G.n,&G.m);
		CreateGraphWeight(&G); //creategraphWeight(&G);//Khoi tao do thi
		for(i=1;i<=G.m;i++){//them cung
			fscanf(f,"%d%d%d",&G.u,&G.v,&G.w);
			AddEdgesWeight(&G,G.u,G.v,G.w);//addedges_weight(&G,G.u,G.v,G.w);
		}
		PrintGraphWeight(&G);//PrintGraphWeight(&G);
		int s;
		printf("\nNhap dinh xuat phat: ");scanf("%d",&s);
		MD(&G,s);
		for(i=1;i<=G.n;i++){
			printf("\npi[%d] = %d ; P[%d] = %d",i,pi[i],i,P[i]);
		}
		printf("\nDuong di ngan nhat la: %d",(pi[G.n]>0)? pi[G.n]:-1);
	}else{
		printf("Loi mo tep");	
	} fclose(f); 
	return 0;
}
