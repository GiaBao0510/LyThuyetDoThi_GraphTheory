#include<stdio.h>
#define max 100
#define NO_EDGES -1
typedef struct{
	int n,m;
	int A[max][max];
}thanhpho;
//khoi tao
void KhoiTao(thanhpho *G){
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			G->A[i][j]=NO_EDGES;
		}
	}
}
//In
void InCacDuongDi(thanhpho *G){
	int i,j;
	printf("   ");
	for(i=1;i<=G->n;i++){
			printf("%4d",i);
	}
	for(i=1;i<=G->n;i++){
		printf("\n%d: ",i);
		for(j=1;j<=G->n;j++){
			printf("%4d",G->A[i][j]);
		}
	}
}
//Do dai duong di
void dodai(thanhpho *G,int a,int b,int w){
	G->A[a][b]=w;
	G->A[b][a]=w;
}
//cac bien ho tro
#define INFINITY 999
int pi[max],
	p[max],
	mark[max];
void Di(thanhpho *G,int s){
	int i,j,k,x;
	//khoi tao
	for(i=1;i<=G->n;i++){
		mark[i]=0;
		pi[i]=INFINITY;
	}
	pi[s]=0;
	p[i]=-1;//Vi truoc diem S khong co diem nao ca nen gan la -1
	//vong lap chinh lap(n-1) lan
	for(k=1;k<G->n;k++){
		//tim pi nho nhat
		int min_pi=INFINITY;
		for(j=1;j<=G->n;j++){
			if(mark[j]==0 && min_pi>pi[j]){
				min_pi=pi[j];
				x=j;
			}
		}
		if(min_pi==INFINITY){
			break;//khong tim duoc diem nao nho nhat thi huy vong lap 
		}
		//danh dau duyet
		mark[x]=1;
		//cap nhat duong di tot nhat
		for(j=1;j<=G->n;j++){
			if(mark[j]==0 && G->A[x][j]!=NO_EDGES){
				if(G->A[x][j]+pi[x] < pi[j]){
					pi[j]=G->A[x][j]+pi[x];
					p[j]=x;
				}
			}
		}
	}
}
int main(){
	thanhpho G;
	int u,v,w,i,j;
	scanf("%d %d",&G.n,&G.m);//Doc so luong thanh pho va d=so luong duong di
	KhoiTao(&G);
	for(i=1;i<=G.m;i++){
		scanf("%d %d %d",&u,&v,&w);
		dodai(&G,u,v,w);
	}
	int s,e;//diem bat dau va diem ket thuc
	scanf("%d %d",&s,&e);
	InCacDuongDi(&G);
	Di(&G,s);
	printf("\nDuong di tu thanh pho %d den thanh pho %d la: %d",s,e,pi[e]);//In ra do dai duong di thanh pho can den
}
