#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiVoHuong.c"
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
List list_neighbour(Graph *G,int x){
	int i;
	List list;
	Makenull_List(&list);
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,x,i)==1){
			Insert_List(i,End_List(list),&list);
		}
	}
	return list;
}
#define white 1 	//La cac dinh chua duoc xet
#define gray 2 		//La cac dinh dang duoc xet
#define black 3 	//La cac dinh da duoc xet
//Cac bien ho tro
int mark[maxverties];
int color[maxverties];
int cycle;	//neu cycle = 0 Thi chua co chu trinh , neu cycle = 1 thi co chu trinh
//Kiem tra chu trinh
void CK(Graph *G,int x,int parent){
	color[x]=gray;
	//Xet cac phan tu ke V cua U
	int i;
	List L=list_neighbour(G,x);
	for(i=1;i<=L.Last;i++){
		int v=Retrieve(i,L);
		//Neu dinh ke V co xet lai cha cua no ma cha cua no duyet ro thi bo qua 
		if(v==parent){
			continue;//Da xet roi thi bo qua
		}
		//Neu cac dinh ke co cung mau xam thi tim thay chu trinh
		if(color[v]==gray){
			cycle =1;	//Ton tai chu trinh
			return;
		}
		if(color[v]==white){
			CK(G,v,x);
		}
	}
	color[x]=black;
}
int main(){
	FILE *f;
	f=fopen("DataGraph.txt","r");
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
			color[i]=white;
			mark[i]=0;
		}
		for(i=1;i<=G.n;i++){
			if(color[i]==white){//Neu co dinh mau trang chua duyet thi duyet
				CK(&G,i,0);
			}
		}
		(cycle==1)? printf("YES"):printf("NO");
	}else printf("Loi mo tep");
	fclose(f);
}
