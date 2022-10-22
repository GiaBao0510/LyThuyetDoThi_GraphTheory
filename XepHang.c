#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCoHuong.c"
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
//Danh sach Anh cua Dinh X bat ky
List anh(Graph *G,int x){
	List list;
	Makenull_List(&list);
	int i;
	for(i=1;i<=G->n;i++){
		if(G->A[x][i]==1){
			Insert_List(i,End_List(list),&list);
		}
	}
	return list;
}
//Cac bien ho tro
List L1,L2;
int rank[maxverties];	//Luu tru hang cua tat ca cac dinh
int d[maxverties];		//Luu tru so luong tao anh
				//Buoc dem
//Tao ham sao chep DS2 qua DS1
void copy_List(List *L1,List *L2){	
	Makenull_List(L1);
	int i;
	for(i=1;i<=L2->Last;i++){
		int x =Retrieve(i,*L2);
		Insert_List(x,End_List(*L1),L1);//Day cac phan tu o DS L2 vao cuoi DS L1
	}
}
void XepHang(Graph *G){
	int i;
	int k=0;
	//Khoi tao
	for(i=1;i<=G->n;i++){
		d[i]=halfstepoutside(G,i);//Luu tru danh sach cac tao anh cua tat ca cac dinh
		rank[i]=0;
	}
	//Tao DS1 rong de luu tru cac dinh co tao anh la 0
	Makenull_List(&L1);
	for(i=1;i<=G->n;i++){
		if(d[i]==0){
			Insert_List(i,End_List(L1),&L1);
		}
	}
	//vong lap chinh. Neu DS L1 > 0 thi thuc hien
	while(L1.Last>0){
		//Tao DS rong L2 de day cac phan tu cua L2 vao L1
		Makenull_List(&L2);
		for(i=1;i<=L1.Last;i++){//Tim cac phan tu trong DS L1 co d[i]==0
			int u=Retrieve(i,L1);
			rank[u]=k;
			//Danh Sach cac dinh ke V cua U
			int v;
			List L=anh(G,u);
			for(v=1;v<=L.Last;v++){
				int e=Retrieve(v,L);
				d[e]--;
				if(d[e]==0){//Neu d[v] == 0 thi day tao anh cua dinh V vao trong DS L2
					Insert_List(e,End_List(L2),&L2);
				}
			}
		}
		copy_List(&L1,&L2);//Ta day cac phan tu cua L2 vao L1
		k++;
	}
}
int main(){
	FILE *f=fopen("DataGraph.txt","r");
	if(f!=NULL){
		Graph G;
		int m,u,v;
		fscanf(f,"%d%d",&G.n,&m);
		creategraph(&G);
		int i;
		for(i=1;i<=m;i++){
			fscanf(f,"%d%d",&u,&v);
			addedges(&G,u,v);
		}
		PrintGraph(&G);
		int j,k;
		XepHang(&G);
		printf("\nXep hang cho tat ca cac dinh:\n");
		for(j=1;j<=G.n;j++){
			printf("\nRank[%d]: %d",j,rank[j]);
			
		}
	}else printf("@@@ - Loi mo tep - @@@");
	fclose(f);
}
