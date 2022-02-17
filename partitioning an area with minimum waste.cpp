#include "the5.h"
// do not add extra libraries here

/*
W: the width of the field
L: the length of the field
partitions: 2D Boolean array for partitions, if a partition of w x l exists then partitions[x][y] is true.
numberOfCalls/numberOfIterations: method specific control parameter
*/

int recursiveMethod(int W, int L, bool** partitions, int* numberOfCalls){

    int WastedArea, i, j, min, min2;
    WastedArea = (W)*(L);
    *numberOfCalls += 1;
    min = 0;
    min2 = 0;
    if (partitions[W][L])
    {
        return 0;
    }
    else
    {
        for (i = 1; i <= W/2; i++)
        {
            min = recursiveMethod(W-i, L, partitions, numberOfCalls) + recursiveMethod(i, L, partitions, numberOfCalls);
            if (min < WastedArea)
            {
                WastedArea = min;
            }
        }
        for (j = 1; j <= L/2; j++)
        {
            min2 = recursiveMethod(W, L-j, partitions, numberOfCalls) + recursiveMethod(W, j, partitions, numberOfCalls);
            if (min2 < WastedArea)
            {
                WastedArea = min2;
            }
        }
        return WastedArea;
    }
}

int memoSol(int W, int L, bool** partitions, int *numberOfCalls, int** memo)
{
    *numberOfCalls += 1;
    if (memo[W][L] != -1)
    {
        return memo[W][L];
    }
    else
    {
        int WastedArea, i, j, min, min2;
        WastedArea = (W)*(L);
        if (partitions[W][L])
        {
            memo[W][L] = 0;
        }
        else
        {
            for (i = 1; i <= W/2; i++)
            {
                min = memoSol(W-i, L, partitions, numberOfCalls, memo) + memoSol(i, L, partitions, numberOfCalls, memo);
                if (min < WastedArea)
                {
                    WastedArea = min;
                }
            }
            for (j = 1; j <= L/2; j++)
            {
                min2 = memoSol(W, L-j, partitions, numberOfCalls, memo) + memoSol(W, j, partitions, numberOfCalls, memo);
                if (min2 < WastedArea)
                {
                    WastedArea = min2;
                }
            }
            memo[W][L] = WastedArea;
        }
        return memo[W][L];
    }
}
int memoizationMethod(int W, int L, bool** partitions, int* numberOfCalls){
    *numberOfCalls += 1;
    int** memo = new int*[W+1];
    int call;
	for(int i = 0; i < W+1; i++){
		memo[i] = new int[L+1];
		for (int j = 0; j < L+1; j++){
			memo[i][j] = -1;
		}
	}
	call = memoSol(W, L, partitions, numberOfCalls, memo);
    return call; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
int wasteCalculator(int W, int L, int x, int y)
{
    return ((W*L) % (x*y));
}
int bottomUpMethod(int W, int L, bool** partitions, int* numberOfIterations){
    int** memo = new int*[W];
    int k, m;
    int min;
	for(int i = 0; i < W; i++)
	{
		memo[i] = new int[L];
		for (int j = 0; j < L; j++)
		{
		    k = 1;
		    m = 1;
		    if (partitions[i][j])
		    {
		        while(k*i < W)
		        {
		            while(m*j < L)
		            {
		                memo[k*i][k*j] = 0;
		                m += 1;
		            }
		            m = 1;
		            k += 1;
		        }
		        k = 1;
		    }
		    else
		    {
			    memo[i][j] = -1;
		    }
		}
	}
	if (partitions[0][0])
	{
	    return 0;
	}
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < L; j++)
        {
            if (memo[i][j] != 0)
            {    
                if (i == 0 && j == 0)
                {
                    memo[i][j] = 1;
                }
                else if (i == 0)
                {
                    if (memo[i][j-1] != 0)
                    {
                        memo[i][j] = memo[i][j-1] + 1;
                    }
                    else
                    {
                        memo[i][j] = 1;
                    }
                }
                else if (j == 0)
                {
                    if (memo[i-1][j] != 0)
                    {
                        memo[i][j] = memo[i][j-1] + 1;
                    }
                    else
                    {
                        memo[i][j] = 1;
                    }
                }
                else
                {
                    if (memo[i-1][j] == 0 && memo[i][j-1] == 0)
                    {
                        memo[i][j] = 1;
                    }
                    else if (memo[i-1][j] == 0)
                    {
                        memo[i][j] = j+1;
                    }
                    else if (memo[i][j-1] == 0)
                    {
                        memo[i][j] = i+1;
                    }
                    else
                    {
                        if (memo[i][j-1] <= memo[i-1][j])
                        {
                            memo[i][j] = memo[i][j-1]+i+1;
                        }
                        else
                        {
                            memo[i][j] = memo[i-1][j]+j+1;
                        }
                    }
                }
            }
        }
    }
    
    return memo[W-1][L-1]; // this is a dummy return value. YOU SHOULD CHANGE THIS!

}
//
// Created by Oguz İlerle on 17.12.2021.
//

