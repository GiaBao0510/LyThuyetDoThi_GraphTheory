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
/*---- Giai thuat Tarjan ----*/		
	//bien ho tro
	int cnt=0,idx=1;
	int num[50],
		min_num[50],
		on_stack[50],//Kiem xem dinh X co trong dah sach hay khong
		MARK[50];
	NganXep S;	
	//kiem tra lien thong manh
	void strongconnect(Graph *G,int x){
		int i;
		num[x]=min_num[x]=idx;
		idx++;
		Push_stack(&S,x);//Day X vao trong danh sach
		on_stack[x]=1;//danh dau X co trong danh sach
		//Cac dinh Anh cua X
		List L=Anh(G, x);
		for(i=1;i<=L.Last;i++){
			int y=Retrieve(i,L);
			if(num[y]<0){
				strongconnect(G, y);
				min_num[x]=Min(min_num[x],min_num[y]);
			}
			else if(on_stack[y]){
				min_num[x]=Min(min_num[x],num[y]);
			}
		}
		if(min_num[x]==num[x]){
			cnt++;
			int w;
			printf("\nBo phan lien thong thu %d:",cnt);
			do{
				w=Top_stack( S);
				printf("\n%2d",w);
				on_stack[w]=0;
				Pop_stack(&S);
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
		PrintGraph(&G);
			//khoi tao
		idx=1;
		for(i=1;i<=G.n;i++){
			num[i]=-1;
			on_stack[i]=0;
		}
		makenullstack(&S);
		for(i=1;i<=G.n;i++){
			if(num[i]==-1){
				strongconnect(&G,i);
			}
		}
		(cnt==1)? printf("\nStrongconnected"):printf("\nUnconected");
		printf("\nSo bo phan lien thong: %d",cnt);
	}else printf("@@@ - Loi mo tep - @@@");
	fclose(f);
}
