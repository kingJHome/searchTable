#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) < (b))
#define LQ(a,b) ((a) <= (b))
#define BT(a,b) ((a) > (b))
#define BQ(a,b) ((a) <= (b))

//简单查找表
typedef struct{
	int *elem;
	int length;
}SSTable;

//带权查找表
typedef struct{
	int data;
	float weight;
}NodeInfo;

typedef struct{
	NodeInfo *elem;
	int length;
}NodeWithWeight;

//带权查找树
typedef struct weightNode{
	NodeInfo *elem;
	struct weightNode *lchild,*rchild;
}BiTree;

//简单查找
int Search_Seq(SSTable ST,int key);

//二分查找(主要针对有序列表)
int Search_Bin(SSTable ST,int key);

//建立带权列表
void CreateWeightList(NodeWithWeight *R);

//求查找树的累计权值
float* WeightSum(NodeWithWeight R);

//构建次优查找树
//由有序表R[low..high]及其累计权值表sw(其中sw[0]==0)递归构造次优查找树T
void SecondOptimal(BiTree **T,NodeWithWeight R,float sw[],int low,int height);

//构建次优查找树过程
void CreateSOSTree(BiTree **T,NodeWithWeight R);
