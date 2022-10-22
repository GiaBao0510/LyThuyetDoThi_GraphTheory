#include<stdio.h>
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
#include"C:\BasicProgramming\LyThuyetDoThi/tvDoThiVoHuong.c"
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
//Duyet theo chieu sau de quy bat dau 1 dinh X bat ky
int Mark[maxverties],P[maxverties];
void DFS_Recursive(Graph *G,int x,int p){
	//Neu dinh X duyet roi thi
	if(Mark[x]==1){
		return;	//Bo qua
	}
	//Nguoc lai thi duyet dinh X
	int i;
	printf("Duyet %d\n",x);
	Mark[x]=1;
	P[x]=p;		//Gan cha cua dinh X la v
	List L=list_neighbour(G,x);//tim cac dinh ke X de duyet cho dot tiep theo
	for(i=1;i<=L.Last;i++){
		int v= Retrieve(i,L); //V la cac dinh ke cua X
		DFS_Recursive(G,v,x); //Cap nhat la cha cua dinh V la X
	//Tiep tu de quy trong vong lap for de duyet cac dinh chua duoc duyet	
	}
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
		PrintGraph(&G);
		//ban dau chua co dinh nao duoc duyet va chua co dinh nao co cha
		for(i=1;i<=G.n;i++){
			Mark[i]=0;	//Chua co dinh nao duoc duyet danh dau la 0
			P[i]=-1;	//Chua co dinh nao co cha danh dau la -1
		}
		printf("\n\t------------------------------\n");
		printf("\nDuyet do thi theo chieu sau su dung de quy.\n");
		//dem so bo phan lien thong
		int count=0;
		for(i=1;i<=G.n;i++){
			if(Mark[i]==0){
				count++;
				printf("\nSo bo phan lien thong %d\n",count);
				DFS_Recursive(&G,i,0);
			}
		}
		if(count>1){
			printf("\nDo thi chinh khong lien thong");
		}else printf("\nDo thi chinh tren la lien thong");
		printf("\nSo bo phan lien thong la: %d",count);
		//IN ra cha cua cac dinh tren do thi
		printf("\nCha cua cac dinh tren la:");
		for(i=1;i<=G.n;i++){
			printf("\nParent[%d]: %d",i,P[i]);
		}
		
	}else printf("Loi mo tep");
	fclose(f);
}
