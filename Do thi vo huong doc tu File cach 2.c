#include<stdio.h>
#define maxverties 50			//Dat Maxverties = 50
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
//Dem bac cua tat ca cac dinh 
void VerticesDegree(Graph *G){
	int i;
	for(i=1;i<=G->n;i++){
		printf("\nBac cua dinh %d = %d.",i,Degree(G,i));
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
//Tao danh sach de luu cac dinh ke cua dinh X
List neighbour_list(Graph *G,int x){
	List L;
	int i;
	makenull_list(&L);
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,i,x)){
			insert_list(&L,end_list(&L),i);
		}
	}
	return L;
}
//In cac dinh ke cua tat ca cac dinh
void printneighbour(Graph *G){
	int i,j;
	printf("\n Hang xom cua tat ca cac dinh\n");
	for(i=1;i<=G->n;i++){
		printf("\nNeighbour %d: ",i);
		List L=neighbour_list(G,i);
		for(j=1;j<=L.size;j++){
			printf("%d ",retrieve_list(&L,j));
		}
	}
}
int main(){
	int m,u,v;
	Graph G;
	freopen("DataGraph.txt","r",stdin);
	printf("\n\tDo thi vo huong doc tu file cach 2:\n");
	scanf("%d%d",&G.n,&m);
	creategraph(&G);
	//Doc cac cung trong file 
	int i;
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		addedges(&G,u,v);
	}
	PrintGraph(&G);
	VerticesDegree(&G);	
	printneighbour(&G);
}
