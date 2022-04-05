#include <iostream>  
#include <stdio.h>
using namespace std;  
  
int input[1001][1001], n, start, end;  
int next(int row, int col)  
{  
    int cur = input[row][col];  
    if(cur%n == start){//the current is in the start col  
        if(cur/n == start-1)//the current is in the left-up   
            return cur+1;  
        else  
            return cur-n;  
    }else if(cur/n == start-1){//the current is in the start row  
        if((cur%n == end) || (cur%n == 0))//the current is in the right-up  
            return cur+n;  
        else  
            return cur+1;  
    }else if((cur%n == end) || (cur%n == 0)){//the current is in the end col  
        if((cur-1)/n == end-1)//the current is in the right-down  
            return cur-1;  
        else  
            return cur+n;  
    }else if((cur-1)/n == end-1){//the current is in the end row  
        if(cur%n == start)//the current is in the left-down  
            return cur-n;  
        else  
            return cur-1;  
    }  
}  
  
bool compare(int k)  
{  
    end = n-k+1, start = k;  
    for(int i = k; i < end; i++){  
        if(input[k][i+1] != next(k,i))  
            return false;  
    }  
    for(int i = k; i < end; i++){  
        if(input[i+1][end] != next(i,end))  
            return false;  
    }  
    for(int i = end; i > k; i--){  
        if(input[end][i-1] != next(end,i))  
            return false;  
    }  
    for(int i = end; i > k; i--){  
        if(input[i-1][k] != next(i,k))  
            return false;  
    }  
    return true;  
}  
  
int main()  
{  
    int turn = 1;  
    while(cin>>n){  
        if(!n)  
            break;  
        for(int i = 1; i <= n; i++)  
            for(int j = 1; j <= n; j++)  
                scanf("%d", &input[i][j]);  
        bool ans = true;  
        for(int i = 1; i <= n/2; i++){  
            if(!compare(i)){  
                ans = false;  
                break;  
            }  
        }  
        if((n%2 == 1) && ans){  
            if(input[n/2+1][n/2+1] != (n*n)/2+1)  
                ans = false;  
        }  
        if(ans)  
            printf("%d. YES\n", turn++);  
        else  
            printf("%d. NO\n", turn++);  
    }  
    return 0;  
}  

