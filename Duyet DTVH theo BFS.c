#include<stdio.h>
#include"C:\BasicProgramming\DanhSachList\CacPhepToanList.cpp"
#include"C:\BasicProgramming\LyThuyetDoThi/tvDoThiVoHuong.c"
#define MaxlengthQueue 50
/*Danh sach luu tru dinh ke cua dinh x trong do thi*/
List listneighbour(Graph *G,int x){
	List L;
	Makenull_List(&L);
	int i;
	for(i=1;i<=G->n;i++){
		if(CheckAdjacent(G,x,i)==1){
			Insert_List(i,End_List(L),&L);
		}
	}
	return L;
}
void printlistneighbour(Graph *G){
	int i,j;
	printf("\nDanh sach cac dinh ke nhau\n");
	for(i=1;i<=G->n;i++){
		List L=listneighbour(G,i);
		printf("\n%d:",i);
		for(j=1;j<=L.Last;j++){
			printf(" %d",Retrieve(j,L));
		}
	}
}
/*---Cau truc hang doi---*/
	typedef struct{
		int element[MaxlengthQueue];
		int Front,Rear;
	}Queue;
	//Khoi tao hang doi rong
	void makenull_Queue(Queue *Q){
		Q->Front=0;
		Q->Rear=-1;
	}
	//Kiem tra hang doi rong
	int empty_Queue(Queue *Q){
		return Q->Front > Q->Rear;
	}
	//Tra ve phan tu dau hang doi
	int Front_queue(Queue *Q){
		return Q->element[Q->Front];
	}
	//Them phan tu X vao cuoi hang doi
	void Enter_Queue(Queue *Q,int x){
		Q->Rear++;
		Q->element[Q->Rear]=x;
	}
	//Xoa phan tu o dau hang doi
	void Delete_Queue(Queue *Q){
		Q->Front++;
	}
//Duyet do thi theo chieu rong cua mot dinh bat ky
List BFS(Graph *G,int x,int parent[]){
	//tao danh sach dung de luu tru cac dinh da duoc duyet
	List list;
	Makenull_List(&list);
	Queue Q;
	makenull_Queue(&Q);
	int i,mark[MaxlengthQueue],k=1;
	//Khoi tao ban dau tat ca cac dinh chua duyet 
	for(i=1;i<=G->n;i++){
		mark[i]=0;
	}
	Enter_Queue(&Q,x);//Dua mot dinh bat ky vao trong hang doi
	parent[x]=0;	//Vi co mot dinh duyet dau tien(Nut goc) nen ta gan dinh do co cha bang 0
	//Vong lap chinh
	while(!empty_Queue(&Q)){
		int u=Front_queue(&Q);//Lay mot dinh trong hang doi ra
		Delete_Queue(&Q);
		//Neu dinh U da duoc duyet thi bo qua
		if(mark[u]==1){
			continue;
		}
		//Neu Dinh U chua duyet thi ta duyet dinh U
		//printf("%d.Duyet: %d\n",k,u);
		Insert_List(u,End_List(list),&list);
		k++;
		mark[u]=1;
		//Tim cac dinh ke V cua U
		List L=listneighbour(G,u);
		int j;
		for(j=1;j<=L.Last;j++){
			int v=Retrieve(j,L);
			if(mark[v]==0){
				Enter_Queue(&Q,v);
				parent[v]=u;//Cap nhap lai cha cua cac dinh ke V la dinh U(cha cua V la U)
			}
		}
	}
	return list;//Tra ve dang danh sach luu cac dinh da duyet theo chieu rong
}
int main(){
	int m,u,v;
	FILE *F;
	F=fopen("DataGraph.txt","r");
	if(F!=NULL){
		Graph G;
		fscanf(F,"%d%d",&G.n,&m);
		creategraph(&G);
		int i;
		for(i=1;i<=m;i++){
			fscanf(F,"%d%d",&u,&v);
			addedges(&G,u,v);
		}
		PrintGraph(&G);
		printlistneighbour(&G);
		//Khai bao dinh cha luu tru cac dinh V
		int parent[50];
		for(i=1;i<=G.n;i++){
			parent[i]=-1;	//Ban dau chua co dinh nao co cha het
		}
		int x;
		/*printf("\nNhap vao mot dinh bat ky de duoc duyet: ");scanf("%d",&x);*/
		//Duyet them cac nut ben ngoai do thi (kiem tra co bao nhieu bo phan lien thong
		printf("\nDuyet theo chieu rong(Best first search):\n");
		int j,Mark[50];
		for(j=1;j<=G.n;j++){
			Mark[j]=0;
		}
		for(i=1;i<=G.n;i++){
			if(Mark[i]==0){
				List list=BFS(&G,i,parent);
				for(j=1;j<=list.Last;j++){
					printf("\n%d Duyet: %d",j,Retrieve(j,list));
					Mark[Retrieve(j,list)]=1;		//Danh dau dinh nay da duyet roi
				}
			}
		}
		printf("\nCha cua tat ca cac dinh trong do thi(Dung cay do thi):\n");
		for(i=1;i<=G.n;i++){
			printf("\nParent[%d]: %d",i,parent[i]);
		}
	}else printf("Loi Mo Tep!!!");
	fclose(F);
}	

