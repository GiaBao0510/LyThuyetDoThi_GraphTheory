#include<stdio.h>
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
//Tao danh sach luu tru cac dinh ke cua dinh X
List Neighbour(Graph *G,int x){
	List L;
	Makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,i,x)==1){
			Insert_List(i,End_List(L),&L);
		}
	}
	return L;
}
//Danh sach duyet bat dau tu dinh X
List TraverceTheVertices(Graph *G,int x){
	List A,B,C;
	Makenull_List(&A);//Danh sach dung de luu tru cac dinh da duoc duyet
	Makenull_List(&B);//Danh sach dung de luu tru cac dinh cho duoc duyet
	Insert_List(x,End_List(B),&B);//Bat dau dua 1 dinh x vao danh sach
	//Khoi tao tat ca cac dinh chua duoc duyet
	int mark[20],i; 
	for(i=1;i<=G->n;i++){
		mark[i]=0;
	}
	while(!Empty_List(B)){
		int u=Retrieve(x,B);//Lay phan tu dau tien ra khoi danh sach
		
		if(mark[x]==1){//Kiem tra xem coi duyet chua
			continue;//da duyet roi thif bo qua cau lenh sau
		}
		//Duyet dinh P
		Insert_List(u,End_List(A),&A);
		mark[x]=1;
		//Tim cac dinh ke V cua U
		C=Neighbour(G,u);
		for(i=1;i<=C.Last;i++){
			int v=Retrieve(i,B);
			if(mark[v]==0){	//Kiem tra may dinh ke co duoc duyet chua
				Insert_List(v,End_List(B),&B);
			}
		}
	}
	return A;
}
int main(){
	Graph G;
	int i,m;
	freopen("DataGraph.txt","r",stdin);
	scanf("%d%d",&G.n,&m);				//Doc so luong dinh va cung tu tap tin
	creategraph(&G);
	int u,v;
	for(i=1;i<=G.n;i++){				//Doc cac cap cung trong tep
		scanf("%d%d",&u,&v);
		addedges(&G,u,v);
	}
	//Danh dau cac dinh chua duoc duyet
	int mark_vertice[20];
	for(i=1;i<=G.n;i++){
		mark_vertice[i]=0;
	}
	//Kiem tra tat cac cac dinh deu duoc duyet
	int j,k;
	for(j=1;j<=G.n;j++){
		if(mark_vertice[j]==0){
			List L=TraverceTheVertices(&G,j);
			for(k=1;k<=L.Last;k++){
				printf("\nDuyet %d: %d",k,Retrieve(k,L));
				mark_vertice[Retrieve(k,L)]=1; //Danh dau da duoc duyet
			}
		}
	}
}
