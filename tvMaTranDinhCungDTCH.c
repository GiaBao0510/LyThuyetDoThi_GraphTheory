#include<stdio.h>
#define no_edges -1
#define maxvertices 50	//So luong toi da cua cac dinh
#define maxedges 50		//So luong toi da cua cac cung
/*---------Ma tran khong co trong so -----------*/
	typedef struct{
		int n,m;			//Quy dinh so luong dinh (N) va so luong cung (M)
		int A[maxvertices][maxedges]; //Ma tran dinh - canh(MA tran lien thong), doi vo do thi vo huong
	}Graph;
	//Tao ma tran khong
	void Creategraph(Graph *G){
		int i,j;
		for(i=1;i<=G->n;i++){		//Dinh
			for(j=1;j<=G->m;j++){	//Cung
				G->A[i][j]=0;
			}
		}
	}
	//In ma tran
	void Printgraph(Graph G){
		int i,j;
		printf("\nMa tran dinh - cung cua do thi co huong\nMa tran cap %dx%d:\n",G.n,G.m);
		for(i=1;i<=G.n;i++){	
			printf("\n%d:",i);
			for(j=1;j<=G.m;j++){	
				printf(" %2d",G.A[i][j]);
			}
		}
	}
	//Them cung e = (x,y) vao ma tran
	void Addedges(Graph *G,int e,int x,int y){
		G->A[x][e]=1;							//Cho E lien thuoc voi dinh X(goc)
		G->A[y][e]=-1;							//Cho E lien thuoc voi dinh Y(ngon)
	/* Noi cach khac E la mot cung noi dinh X va dinh Y lai voi nhau */	
	}
	//Kiem tra lang gieng giua 1 cap dinh X,Y
	int Checkadjaccent(Graph G,int x,int y){
		int e;
		for(e=1;e<=G.m;e++){ 		//Cho chay giua cac canh 
			if(G.A[x][e]==1 && G.A[y][e]==-1){
				return 1;
			}
		}
		return 0;
	}
//Dem so anh cua dinh X
int countpictures(Graph *G,int x){
	int dem=0,e;
	for(e=1;e<=G->m;e++){
		if(G->A[x][e]==1){
			dem++;
		}
	}
	return dem;
}
//Dem so tao anh cua dinh X
int countcreatepictures(Graph *G,int x){
	int dem=0,e;
	for(e=1;e<=G->m;e++){
		if(G->A[x][e]==-1){
			dem++;
		}
	}
	return dem;
}
/*----------------Danh sach--------------*/ 
	typedef struct{
		int data[maxvertices];
		int size;
	}List;
	void Makenull_list(List *L){
	 L->size=0;
	}
	int Empty_list(List *L){
		return L->size==0;
	}
	void Insert_list(List *L,int x){
		L->data[L->size]=x;
		L->size++;
	}
	int element_list(List *L,int p){
		return L->data[p-1];
	}
//Danh sach cac anh cua dinh X
List danhsachAnh(Graph *G,int x){
	List L;
	Makenull_list(&L);
	int i,j;
	for(i=1;i<=G->n;i++){
		if(i==x){
			continue;
		}
		else
			for(j=1;j<=G->m;j++){
				if(G->A[x][j]==1 && G->A[i][j]== -1){
					Insert_list(&L,i);
				}
			}
	}
	return L;
}
//Danh sach cac tao anh cua dinh X
List danhsachTaoAnh(Graph *G,int x){
	List L;	
	Makenull_list(&L);
	int i,j;
	for(i=1;i<=G->n;i++){
		if(i==x){
			continue;
		}
		else
			for(j=1;j<=G->m;j++){
				if(G->A[x][j]==-1 && G->A[i][j]== 1){
					Insert_list(&L,i);
				}
			}
	}
	return L;
}
