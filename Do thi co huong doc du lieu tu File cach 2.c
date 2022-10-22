#include<stdio.h>
#define maxverties 50			  //So dinh toi da
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCoHuong.c"
//In ma tran
void printgraph(Graph *G){
	int i,j;
	printf("\nMa tran co huong:\n");
	printf("\nMa tran cap %d:\n",G->n);
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
		
}
void degreenode(Graph *G){
	printf("\n\tNua bac trong va nua bac ngoai cua cac dinh:");
	int i;
	for(i=1;i<=G->n;i++){
		printf("\nDinh %d: ",i);
		halfstep(G,i);
	}
}
//Tao danh sach 
typedef struct{
	int data[maxverties];//luu truu gia tri
	int size;			//Do dai cua danh sach
}List;
//Tao danh sach rong
void makenull_list(List *L){
	L->size=0;
}
int end_list(List *L){
	return(L->size+1);
}
//The phan tu X vao vi tri P trong danh sach L
void insert_list(List *L,int p,int x){
	if(L->size==maxverties){
		printf("Danh sach day");
	}
	if((p<1)||(p>L->size+1)){
		printf("vi tri khong hop le");
	}
	else{
		int i;
		for(i=(L->size-1)+1;i>p-1;i--){
			L->data[i]=L->data[i-1];
		}
		L->data[p-1]=x;
		L->size++;
	}
}
//Tra ve gia tri tai vi tri P
int retrieve_list(List *L,int p){
	return L->data[p-1];
}
//Tao danh sach luu cac anh cua dinh X
List anh(Graph *G,int x){
	List L;
	makenull_list(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i]==1){
			insert_list(&L,end_list(&L),i);
		}
	}
	return L;
} 
//Tao danh sach luu cac tao anh cua dinh X
List taoanh(Graph *G,int x){
	List L;
	makenull_list(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[i][x]==1){
			insert_list(&L,end_list(&L),i);
		}
	}
	return L;
} 
//In ra tat ca cac anh va tao anh cua cac dinh
void Inanhvataoanh(Graph G){
	int i,j;
	printf("\n\tAnh cua ta cac ca dinh (R^i):\n");
	for(i=1;i<=G.n;i++){
		List L=anh(&G,i);
		printf("\n%d |-->",i);
		for(j=1;j<=L.size;j++){
			printf(" %d",retrieve_list(&L,j));
		}
	}
	printf("\n\tTao anh cua ta cac ca dinh(R^-i):\n");
	for(i=1;i<=G.n;i++){
		List L=taoanh(&G,i);
		printf("\n%d |-->",i);
		for(j=1;j<=L.size;j++){
			printf(" %d",retrieve_list(&L,j));
		}
	}
}
int main(){
	Graph G;
	printf("\tMa tran co huong doc du lieu theo cach 2:\n");
	freopen("DataGraph.txt","r",stdin);
	int m,u,v;
	scanf("%d%d",&G.n,&m);
	creategraph(&G);
	//Doc du lieu tu file
	int i;
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		addedges(&G,u,v); 			//them cung vao ma tran
	}
	printgraph(&G);
	degreenode(&G);
	Inanhvataoanh(G);
}
