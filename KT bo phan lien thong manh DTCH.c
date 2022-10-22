#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCoHuong.c"
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
//Danh sach luu tru cac anh cua dinh X
List Anh(Graph *G,int x){
	List L;
	Makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(checkneighbour(G,x,i)==1){
			Insert_List(i,End_List(L),&L);
		}
	}
	return L;
}
//Tim kiem gia tri nho nhat giua A va B
int Min(int a,int b){
	return (a<b)? a:b;
}
/*---Tao mot cau truc ngan xep.Dung de luu cac bo phan lien thong manh ---*/
	#define maxlengthstack maxverties
	typedef struct{
		int DataStack[maxlengthstack];
		int top;
	}NganXep;
	//tao ngan xep rong
	void makenullstack(NganXep *S){
		S->top=0;
	}
	//Kiem tra ngan xep rong
	int emptystack(NganXep S){
		return S.top==0;
	}
	//Them phan tu X vao dinh dau ngan xep
	void Push_stack(NganXep *S,int x){
		S->DataStack[S->top]=x;
		S->top++;
	}
	//xoa phan tu o dau ngan xep
	void Pop_stack(NganXep *S){
		S->top--;
	}
	//Lay phan tu dau o ngan xep
	int Top_stack(NganXep S){
		return S.DataStack[S.top-1];
	}
//Cac bien ho tro 
int num[maxverties];
int min_num[maxverties];
int on_stack[maxverties];
int k=0;
NganXep S;
int LTM=0;//Neu LTM = 1 thi do thi tren la lien thong manh
void KTLTM(Graph *G,int x){
	num[x]=min_num[x]=k;
	k++;
	Push_stack(&S,x);
	on_stack[x]=1;
	List L=Anh(G,x);
	int i;
	for(i=1;i<=L.Last;i++){
		int v=Retrieve(i,L);
		if(num[v]<0){//Neu dinh ke V chua duoc xet thi ta dung de quy de xet
			KTLTM(G,v);
			min_num[x]=Min(min_num[x],min_num[v]);
		}
		else if(on_stack[x]==1){
			min_num[x]=Min(min_num[x],min_num[v]);
		}
	}
	if(num[x]==min_num[x]){
		LTM++;
		int w;
		do{
			w=Top_stack(S);
			Pop_stack(&S);
			on_stack[w]=0;
		}while(w!=x);
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
		//khoi tao
		k=1;
		for(i=1;i<=G.n;i++){
			num[i]=-1;
			on_stack[i]=0;
		}
		makenullstack(&S);
		for(i=1;i<=G.n;i++){
			if(num[i]==-1){
				KTLTM(&G,i);
			}
		}
		if(LTM==1){
			printf("\nstrong connected");	
		}else printf("\nNot strong connected");
		printf("\nSo bo phan lien thong manh: %d",LTM);
		
	}else printf("@@@ - Loi mo tep - @@@");
	fclose(f);
}
