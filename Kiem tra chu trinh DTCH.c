#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCOHuong.c"
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
List list_neighbour(Graph *G,int x){
	int i;
	List list;
	Makenull_List(&list);
	for(i=1;i<=G->n;i++){
		if(checkneighbour(G,x,i)==1){
			Insert_List(i,End_List(list),&list);
		}
	}
	return list;
}
#define ChuaDuyet -1
#define DangDuyet 0
#define DaDuyet 1
int Xet[maxverties];
int cycle=0;
void KiemTraChuTrinh(Graph *G,int x){
	Xet[x]=DangDuyet;
	int i;
	List l=list_neighbour(G,x);
	for(i=1;i<=l.Last;i++){
		int v=Retrieve(i,l);
		if(Xet[v]==DangDuyet){
			cycle=1;
			return;
		}
		if(Xet[v]==ChuaDuyet){
			KiemTraChuTrinh(G,v);
		}
	}
	Xet[x]=DaDuyet;
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
		//Khoi tao
		cycle=0;
		for(i=1;i<=G.n;i++){
			Xet[i]=ChuaDuyet;
		}
		for(i=1;i<=G.n;i++){
			if(Xet[i]==ChuaDuyet){//Neu co dinh mau trang chua duyet thi duyet
				KiemTraChuTrinh(&G,i);
			}
		}
		(cycle==1)? printf("YES"):printf("NO");
	}else printf("Loi mo tep");
	fclose(f);
}
