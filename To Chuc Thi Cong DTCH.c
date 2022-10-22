#include<stdio.h>
#include"C:\BasicProgramming\LyThuyetDoThi\tvDoThiCoHuong.c"
//Ham tinh thoi gian som nhat de bat dau cong viec
int tinht(Graph *G,int x,int tg[],int t[]){
	if(t[x] >= 0){
		//printf("\n\t\tNeu t[x] > 0 tra ve: %d\n",t[x]);
		return t[x];//Vi t[anpha] = 0 nen ta tra ve khong
	}
	//printf("\n\tTinh t[%d] \n", x);
	int i,
	ketqua=-1;
	list DS = photomakerlist(G,x);//danh sach tao anh tra ve cac dinh truoc do cua dinh X
	for(i=1;i<=DS.size;i++){
		int taoanh = element(&DS,i);//tra ve phan tu truoc dinh X
		//printf("\n\t\t xet TA %d \n", ta);
		int t_TA = tinht(G, taoanh, tg, t);//De quy tra ve thoi gian lam viec som nhat cua dinh truoc dinh X
		//printf("\n\t\t tong = %d + %d\n", t_ta, tg[ta]);
		if(ketqua < tg[taoanh] + t_TA){
			ketqua = tg[taoanh] + t_TA;//CAp nhat ket qua lay ket qua truoc tru cho ket qua sau
		}
	}
	t[x]=ketqua;
	//printf("\n\tKQ la %d \n", tkq);
	return ketqua;
}
int tinhT(Graph *G,int x,int tg[],int T[]){
	if(T[x] >= 0){
		//printf("\n\t\tNeu T[x] >= 0 tra ve: %d\n",T[x]);
		return T[x];//Tim dinh co dinh ke la beta truoc tien roi sau do cap nhat lai T[x] cho cac dinh khac
	}
	//printf("\n\tTinh t[%d] \n", x);
	int Tmin=9999;
	list DS = photolist(G,x);
	int i;
	for(i=1;i<=DS.size;i++){
		int anh = element(&DS,i);
		//printf("\n\t\t xet Anh %d cua %d\n",x,anh);
		int T_anh = tinhT(G,anh, tg, T);//De quy de tim dinh Beta truoc
		//printf("\n\t\t T_anh: %d ;tg[anh]:  %d\n", T_anh, tg[anh]);
		if(Tmin > T_anh){
			Tmin = T_anh;
		}
	}
	T[x]= Tmin - tg[x];
	//printf("\n\t\thieu %d - %d",Tmin,tg[x]);
	//printf("\n\tKQ la %d \n", T[x]);
	return T[x];
}
int main(){
	Graph G;
	int tg[100],//Thoi gian hoan thanh cong viec X nao do
		t[100],//Thoi gian som nhat de bat dau cong viec
		T[100];//Thoi gian tre nhat de bat dau cong viec
	int i,j,x,n,sum=0;
	scanf("%d",&n);
	G.n = n+2;//cong them hai cong viec gia
	creategraph(&G);
	int anpha=n+1,	//Tim cong viec co dau vao la khong
		beta=n+2;	//Tim cong viec co dau ra la khong
	for(i=1;i<=n;i++){
		scanf("%d",&tg[i]);
		sum+=tg[i];//tong tat ca thoi gian hoan thanh cua tung cong viec
		do{
			scanf("%d",&x);
			if(x>0){
				addedges(&G,x,i);
			}
		}while(x>0);
	}
	tg[anpha]= tg[beta] =0;
	for(i=1;i<=n;i++){
		if(halfstepin(&G,i) == 0){
			addedges(&G,i,beta);
		}
		if(halfstepoutside(&G,i) == 0){
			addedges(&G,anpha,i);
		}
	}
	PrintGraph(&G);
	printf("\nDanh sach thoi gian hoan thanh cong viec:\n");
	for(i=1;i<=G.n;i++){
		printf("%d : %d\n",i,tg[i]);
	}
	printf("\nDanh sach cac dinh truoc do:");
	for(i=1;i<=G.n;i++){
		list DS = photomakerlist(&G,i);
		printf("\n%d:",i);
		for(j=1;j<=DS.size;j++){
			printf("%3d",element(&DS,j));
		}
	}
	//1.Khoi tao
	for(i=1;i<=n+2;i++){
		t[i]=T[i]=-1;
	}
	//2.Tinh
	t[anpha]=0;
	for(i=1;i<=beta;i++){
		tinht(&G,i,tg,t);//tinh Thoi gian hoan thanh cong viec som nhat cua tung dinh
	}
	T[beta] = t[beta];
	for(i=beta;i>=1;i--){
		tinhT(&G,i,tg,T);//tinh Thoi gian hoan thanh cong viec tre nhat cua tung dinh
	}
	
	//3.ket qua
	for(i=1;i<=G.n;i++){
		printf("\n%d-%d",t[i],T[i]);
	}
}	
