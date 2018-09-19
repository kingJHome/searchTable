#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sstable.h"

int Search_Seq(SSTable ST,int key){
	int result = -1;

	for(int i = ST.length-1; EQ(ST.elem[i],key); --i);
	result = -1;

	return result;
}

int Search_Bin(SSTable ST,int key){
	int low = 0,
		high = ST.length - 1,
		mid,
		result = -1;

	while( LQ(low,high) ){
		mid = (low + high) / 2;

		if( !EQ(ST.elem[mid],key) ){
			result = mid;
			break;
		}else if( LT(ST.elem[mid],key) ){
			low = mid + 1;
		}else{
			high = mid - 1;
		}
	}

	return result;
}

void CreateWeightList(NodeWithWeight *R){
	FILE *fp = fopen("weight.txt","r");

	if( !fp ){
		R->length = 0;
		R->elem = NULL;
	}else{
		//统计行数
		int rows = 0;
		char *reads = NULL,				//从文件读取的每行字符
			 *allChars,			//文件的所有字符
			 seperator[] = "\n";		//分割字符
		size_t setSize = 0,readSize = 0;
		
		readSize = getline(&reads, &setSize, fp);
		if( readSize != -1){
			allChars = strdup(reads);
			setSize = 0;
			rows++;
			while( (readSize = getline(&reads, &setSize, fp)) != -1 ){
				setSize = 0;
				rows++;
				allChars = strcat(allChars, reads);
			}
		}
		fclose(fp);

		//构造数据
		rows++;		//多占用一个空间作哨兵
		R->elem = (NodeInfo*)malloc(rows * sizeof(NodeInfo));
		if( R->elem ){
			int curPos = 1;
			char *sepestr = strtok(allChars,seperator);

			R->length = rows;
			while( sepestr ){
				char *spacer = strstr(sepestr," "),
					 *num = strndup(sepestr,spacer-sepestr);
				int data = atoi(num);
				float weight = atof(spacer+1);
				R->elem[curPos].data = data;
				R->elem[curPos].weight = weight;
				curPos++;
				sepestr = strtok(NULL,seperator);
			}
		}
	}
}

float* WeightSum(NodeWithWeight R){
	int length = R.length;
	float *sw = (float*)malloc(length * sizeof(float));

	if( sw ){
		memset(sw,0,length * sizeof(float));
		for(int i = 1; i < length; ++i){
			for(int j = 1; j <= i; ++j){
				sw[i] += R.elem[j].weight;
			}
		}
	}

	return sw;
}

void SecondOptimal(BiTree **T,NodeWithWeight R,float sw[],int low,int high){
	int i = low;
	float min = abs(sw[high] - sw[low]),
		  dw = sw[high] + sw[low-1];

	for(int j = low + 1; j <= high; ++j){
		if(abs(dw-sw[j] - sw[j-1]) < min){
			i = j;
			min = abs(dw - sw[j] - sw[j-1]);
		}
	}

	*T = (BiTree*)malloc(sizeof(BiTree));
	if( *T != NULL ){
		(*T)->elem = R.elem + i;
		if( i != low ){
			SecondOptimal(&((*T)->lchild),R,sw,low,i-1);		//构建左子树
		}else{
			(*T)->lchild = NULL;
		}
		if( i != high ){
			SecondOptimal(&((*T)->rchild),R,sw,i+1,high);		//构建右子树
		}else{
			(*T)->rchild = NULL;
		}
	}
}

void CreateSOSTree(BiTree **T,NodeWithWeight R){
	if(R.length==0){
		*T = NULL;
	}else{
		float *sw = WeightSum(R);
		SecondOptimal(T,R,sw,1,R.length-1);
	}
}
