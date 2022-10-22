#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi/tvDoThiVoHuong.c"
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
//Mot so bien ho tro
int color[maxverties];		//Dung de to mau cho cac nut trong do thi 1(mau den) va 0(mau trang)
int fail;
//To ma cho tat ca cac dinh X bang phuong phap dde quy
void colorfull(Graph *G,int x,int c){
	//Neu dinh X chua duoc to mau thi ta se to mau no
	if(color[x]==-1){
		int i;
		color[x]=c; 	//To mau cho dinh X
		List L=list_neighbour(G,x);
		//Kiem tra cac dinh ke cua X phai co mau khac voi no
		for(i=1;i<=L.Last;i++){
			int v=Retrieve(i,L);
			colorfull(G,v,!c);//De quy la tiep theo se to mau khac
		}
	}else //X da co mau roi
	if(color[x]!=c){// Mot dinh co 2 mau khac nhau
		fail=1;
	}
}
//Kiem tra do thi co phan doi khong
int Check_dichotomy(Graph *G){
	int i,x;
	//Ban dau chua co dinh nao to mau
	for(i=1;i<=G->n;i++){
		color[i]=-1;//Thi se cap phat la -1
	}
	fail=0;
	printf("\nNhap mot dinh de bat dau to mau: ");scanf("%d",&x);
	colorfull(G,x,0);//To mau dinh X la mau trang
	return !fail;
}
int main(){
	Graph G;
	int m,u,v;
	FILE *f=fopen("DataGraph.txt","r");
	fscanf(f,"%d%d",&G.n,&m);
	creategraph(&G);
	int i,j;
	for(i=1;i<=m;i++){
		fscanf(f,"%d%d",&u,&v);
		addedges(&G,u,v);
	}
	PrintGraph(&G);
	printf("\nDo thi tren la do thi phan doi: \n");
	if(Check_dichotomy(&G)){
		printf("YES.");
	}else printf("NO.");
}
