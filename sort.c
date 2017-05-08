#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Length 10
int d,i,j,k;
int temp;
int a[10]={Length,5,1,3,9,6,4,2,8,7};
void swap(int *x,int *y);
void shell_sort(int *a,int length);
void insert_sort(int a[], int length);
void bubble_sort(int a[], int length);
void select_sort(int a[],int length);
void quick_sort(int a[],int start,int end);
int  partition(int a[],int low,int high);
void merge_sort(int a[],unsigned int satrt,unsigned int end);
void merge(int a[],int low,int mid,int high);
void heap_sort(int a[],int length);
void heapAdjust(int a[], int parent, int length);
void radix_sort(int a[],int start, int end,int digit);
int  getDigit(int number,int digit_position);

main(){
	//shell_sort(a,Length);
	//bubble_sort(a,Length);
	//select_sort(a,Length);
	//quick_sort(a,0,Length-1);
	//merge_sort(a,0,Length-1);
	//heap_sort(a,Length);
	radix_sort(a,0,Length-1,2);
	for(i=0;i<Length;i++){
		printf("%d\t",a[i]);
	}
}   

//希尔排序
void shell_sort(int a[],int length){
	int block;//block步长
	block=length/2;//步长为数组长度一半
	while(block>0){//只要步长>0,步长为0，则排序完毕
		for(i=block; i<length; i++){//最开始 i从最大步长开始到最末
			temp=a[i];//缓存i的值，因为i前面可能有更大的值，可能需要交换
			j=i-block;//j在i前一步，j的值应该小于i的值
			while(j>=0 && a[j]>temp){//只要j的值大于temp的值，temp是基准
				a[j+block]=a[j];//把j的值后移一步（这里 第一次循环可能把i的值覆盖，所以有temp
				j-=block;//j前走一步
			}//循环如果持续进行，则j每前进一步，j的值严格变大（3 2 1），不会有3 1 2的情况
			a[j+block]=temp;//把缓存的值放回，使交换完整进行
		}
		block/=2;//步长减少，可以不是折半，如9 5 4 1序列，步长变小即可
	}
}

//插入排序
void insert_sort(int a[], int length){
	for(i=0; i<length; i++){
		j=0;
		while( a[j]<a[i] && i<j )
			j++;//j是i 左边 第一个 比i大 的值 的下标
		if(i!=j){
			temp=a[i];
			for(k=j; k<i; k++)//将j~i-1之间的值后移，把i插入为j
				a[k]=a[k+1];
			a[j]=temp;
		}
	}
}

//冒泡排序
void bubble_sort(int a[], int length){
	for(i=0; i<length-1; i++){//i的作用是使j循环长度-1，因为最大值冒泡到末尾了，已经排好
		for(j=0; j<length-i-1; j++){
			if(a[j]>a[j+1]) swap(&a[j],&a[j+1]);//相邻元素比较，较大值后移
		}
	}
}

//选择排序
void select_sort(int a[],int length){
	//每次i循环，在j循环中选出最小值与i值交换，使i的值排好
	//然后i++，因为i之前的元素已经排好
	for(i=0; i<length-1; i++){
		int min=i;
		for(j=i+1; j<length; j++){//j的范围是i+1~length，即i后面的全部元素
			if(a[j]<a[min])
				min=j;//选出最小值下标
		}
		if(i!=min) swap(&a[i],&a[min]);
	}
}

//快速排序
void quick_sort(int a[],int start,int end){
	int pos;
	if(start<end){
		pos=partition(a,start,end);//找出支点pos
		quick_sort(a,start,pos-1);//递归左边
		quick_sort(a,pos+1,end);//递归右边
	}
}
//partition函数：找支点
int partition(int a[],int low,int high){
	//middle是需要寻找的支点
	//middle左边的值都小于middle
	//middle右边的值都大于middle
	int middle=a[low];//不妨设支点middle为low的值,并缓存low的值，因为在找支点过程中low的值可能被覆盖
	while(low<high){//从两端交替地向中间扫描
		while(low<high && a[high]>=middle)//先扫右边
			high--;//high是比middle大的第一个值的下标
		a[low]=a[high];//将比支点记录小的交换到左端---覆盖low的值 
		
		while(low<high && a[low]<=middle)//再扫左边
			low++;//low是 middle左边 比middle大 的第一个值的下标
		a[high]=a[low];//将比支点记录大的交换到右端
	}
	a[low]=middle;//此时的low是middle支点的下标
	return low;//返回支点记录所在位置
}

//归并排序
void merge_sort(int a[],unsigned int start,unsigned int end){
	int mid=0;
	if(start<end){
		mid=(start+end)/2;//二路归并
		merge_sort(a,start,mid);//左边归并
		merge_sort(a,mid+1,end);//右边归并
		merge(a,start,mid,end);
	}
}
void merge(int a[],int low,int mid,int high){
	int *temp_space=(int *)malloc((high-low+1)*sizeof(int));//临时合并序列
	int left_low=low;
	int left_high=mid;
	int right_low=mid+1;
	int right_high=high;
	// 扫描第一段和第二段序列，直到有一个扫描结束
	for(i=0; left_low<=left_high && right_low<=right_high; i++){
		// 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
		if(a[left_low]<=a[right_low])
			temp_space[i]=a[left_low++];
		else
			temp_space[i]=a[right_low++];
	}
	if(left_low<=left_high)// 若第一段序列还没扫描完，将其全部复制到合并序列
		for(j=left_low; j<=left_high; j++)
			temp_space[i++]=a[j];
	if(right_low<=right_high)// 若第二段序列还没扫描完，将其全部复制到合并序列
		for(j=right_low; j<=right_high; j++)
			temp_space[i++]=a[j];
	// 将合并序列复制到原始序列中
	for(j=0; j<high-low+1; j++)
		a[low+j]=temp_space[j];
	free(temp_space);
}

//堆排序
void heap_sort(int a[],int length){
	for(i=length/2; i>=0; i--)
		heapAdjust(a,i,length-1);//堆初始化
	for(i=length-1; i>0; i--){//进行n-1次循环
		swap(&a[0],&a[i]);//最后一个元素是最大元素，换到第一元素
		heapAdjust(a,0,i);//重建堆，i是未排的元素
	}
}
void heapAdjust(int a[], int parent, int length){
	temp=a[parent];//缓存父节点
	int child=2*parent+1;//先左孩子
	
	while(child<length){//不越界
		if(child+1<length && a[child]<a[child+1])
			//如果有右孩子，且右孩子值较左孩子大
			child++;//选右孩子
		if(temp>=a[child])
			//如果父节点的值已大于孩子的值
			break;//直接结束
		a[parent]=a[child];//将较大值上移给父节点
		parent=child;//以原先较大值的孩子为父节点
		child=2*child+1;//还是选左孩子，继续向下，
	}//直到child>length,保证全部选完
	
	a[parent]=temp;//此时parent在叶子上
}

//基数排序,digit:待排序数组的值的最大位数
void radix_sort(int a[],int start, int end,int digit){
	int radix=10;//基数0,1,2,3,4,5,6,7,8,9
	int *count,*bucket;
	//count存放各个桶的数据统计数量，bucket存放各个桶的元素
	count=(int *)malloc(radix*sizeof(int));//动态数组，大小根据基数
	bucket=(int *)malloc((end-start+1)*sizeof(int));//大小根据a[]中选取的长度start~end
	if(!count||!bucket)
		exit(-1);//内存分配不成功
	//从个位(digit=1)开始，到最大位数(digit=输入的digit)
	for(d=1; d<=digit; d++){
		for(i=0; i<radix; i++)//每当d变化(目标数位变化)都要先进行
			count[i]=0;//初始化各个桶
		for(i=start; i<=end; i++){
			j=getDigit(a[i], d);//取得a[i]第d位
			count[j]++;//根据a[i]第d位数 使桶中对应数字+1
			//(这里第d位数只可能是0~9，和count数组下标索引相同)
		}
		for(i=1; i<radix; i++)
			count[i]+=count[i-1];//对桶中数据进行滚动累加处理，留到下面(**)用
		for(i=end; i>=start; i--){//这里要从右向左扫描，保证排序稳定性
			//将数据根据count的计数依次装入bucket中
			j=getDigit(a[i],d);
			bucket[count[j]-1]=a[i];//装入bucket
			//(**)-1：数组下标需要，count[j]-1:a[i]应该被放置的位置
			//比如{1,21,41,25,51,31}
			//原count={0,5,0,0,1,0...}，处理后count={0,5,5,5,6,6,...}
			//应排成{1,21,41,51,31,25}
			//原25是a[3],count[5]-1=6,应排为a[6-1]=a[5],一步到位
			//如果count计数用柱形图表示
			//本质上是把count中计数的有格子的柱依次横置，形成分区
			//在把a[]中数据按位数的值丢到对应分区中
			//分区内不用理是否有序
			count[j]--;//对应位数的值的计数-1
		}
		for(i=start,j=0; i<=end;i++,j++)
			a[i]=bucket[j];//从bucket中再倒回去
	}
}
int getDigit(int number,int digit_position){
	int digit[4]={1,1,10,100};
	return (number/digit[digit_position])%10;
	//返回digit_position数位上的数，如getDigit(124,3)返回4
}

//桶排序,很无语的排序,max_number是a[]中的最大值
void bucket(int a[],int length,int max_number){
	int *temp_bucket,start=0;
	temp_bucket=(int *)malloc(max_number*sizeof(int));
	if(!temp_bucket)
		exit(-1);
	for(i=0; i<max_number; i++)
		temp_bucket[i]=0;//初始化
	for(i=0; i<length; i++)
		temp_bucket[a[i]]++;//统计
	for(i=0; i<max_number; i++){
		j=temp_bucket[i];//i出现次数
		if(j==0) continue;
		for(k=start; k<j+start; k++)//将a[start]~a[start+j]全部填为i
			//start初值=0，j范围start~j+start,保证填值时连续而不重叠
			a[k]=i;//原来的a[]已经转化成temp_bucket[],大胆重写
		start+=j;//更新start，也是为了保证填值时连续而不重叠
		//此算法适用重复数据多，数据为整数的集合
	}
}

void swap(int *x,int *y){
	temp=*x;*x=*y;*y=temp;
}