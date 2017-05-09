#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rec(int i,int j);
main(){
	
}   
//01背包问题：
//有n个重量weight[i]和价值value[i]的物品。
//从这些物品中挑选出总重量不超过W的物品。
//求所有挑选方案中价值总和的最大值.
//01背包问题 O(2^n)
int rec(int i,int j){//从第i个物品开始挑选总重小于j的部分
	int res;
	if(i==n)  //已经没有剩余物品了
		res=0;
	else if(j<weight[i])  //无法挑选这个物品
		res=rec(i+1,j);
	else  //挑选和不挑选 两种情况都试一下
		res=max(rec(i+1,j), rec(i+1,j-weight[i])-value[i]);
	return res;
}
void solve(){
	printf("%d\n",rec(0,W));
}

//01背包问题 O(nW)
int weight[MAX_N],v[MAX_N];  //MAX_N:所给数据的数组的最大长度
int dp[MAX_N][MAX_W+1];  //记忆化数组 MAX_W:
int rec(int i,int j){
	if(dp[i][j]>=0)
		return dp[i][j];  //已经计算过的话直接使用之前的结果
	int res;
	if(i==n)  //已经没有剩余物品了
		res=0;
	else if(j<weight[i])  //无法挑选这个物品
		res=rec(i+1,j);
	else  //挑选和不挑选 两种情况都试一下
		res=max(rec(i+1,j), rec(i+1,j-weight[i])-value[i]);
	return dp[i][j]=res;  //将结果记录在数组中
}
void solve(){
	memset(dp,-1,sizeof(dp));//用-1表示尚未计算过，初始化整个数组
	printf("%d\n",rec(0,W));
}

//01背包问题
//n=4 
//(weight,value)={(2,3),(1,2),(3,4),(2,2)}
//W=5
//MAX_N:所给物体数据的数组的最大长度  MAX_W:重量
//dp[i][j]为第i个物品开始挑选总重小于j时，总价值的最大值
int dp[MAX_N][MAX_W+1];  //记忆化数组 
void solve(){
	for(i=n-1; i>=0; i--){//从n-1之后的物品开始
		for(j=0; j<=W; j++){//j是背包容量,从背包容量为0开始
			if(j<weight[i]) //如果背包容量小于当前物品容量，不能放进背包
				dp[i][j]=dp[i+1][j];
			else
				dp[i][j]=max(dp[i+1][j], 
							 dp[i+1][ j-weight[i] ]+value[i]);
		}
	}
	printf("%d\n",dp[0][W]);
}
//dp[i+1][j]为从i个物品中挑选总重小于j时，总价值的最大值
void solve(){
	for(i=0; i<n; i++){//i是所用物品，从0个物品开始
		for(j=0; j<=W; j++){//j是背包容量,从背包容量为0开始
			//现在背包容量改变了
			if(j<weight[i]) //如果背包容量j小于当前物品容量weight[i]，不能放进背包
				dp[i+1][j]=dp[i][j];//前i个都不可以了，前i+1个肯定也不可以，值不变
			else//当前物品能放进去，前i个可以
				dp[i+1][j]=max(dp[i][j],//如果放进去后比原来小,保持原值
							   dp[i][ j-weight[i] ]+value[i]);//放进去后比原来价值大
				//dp[i][j-weight[i]]:(注意i是前面已放物品，i+1是当前物品)
				//在dp[i][j]时j-weight[i]表示拿出前面放的物品，放进当前物品
				//得前面价值+当前物品价值
		}
	}
	printf("%d\n",dp[n][W]);
}