#include<bits/stdc++.h>
using namespace std;

int avail[82][10], sudoku[10][10];

int getnum()
	{
		 return rand()%9 + 1;
	}

int check(int sudoku[10][10], int i, int j, int num)
	{
		int tempi = i, tempj = j;
		while(tempi%3!=1)
			tempi--;
		while(tempj%3!=1)
			tempj--;
		for(int counteri=0;counteri<3;counteri++)
		{
			for(int counterj=0;counterj<3;counterj++)
			{
				if(sudoku[counteri+tempi][counterj+tempj] == num)
					return 0;
			}
		}
		
		for(int tempi = 1;tempi<=9;tempi++)
		{
			if(sudoku[tempi][j] == num)
					return 0;
		}
		
		for(int tempj = 1;tempj<=9;tempj++)
		{
			if(sudoku[i][tempj] == num)
					return 0;
		}
		return 1;
	}

void generate(int sudoku[10][10], int i, int j)
	{
		if(i>9 || j>9 || i<1 || j<1)
			return ;
		
		int cell = (9 * (i-1) + j) ;
		
		int count = 0, num;
		
		for(int temp = 1;temp<=9;temp++)		//check if all numbers are exhausted for this cell
		{
			if(avail[cell][temp]==0)
				count++;
		}
		
		if(count!=9)
		{	
			num = getnum();
			while(avail[cell][num]==0)
				num = getnum();
			
			if(avail[cell][num]==1 && check(sudoku,i,j,num)==1)				//number is possible in the cell
			{
				sudoku[i][j] = num;
				avail[cell][num] = 0;
				
				if(j==9)
					generate(sudoku,++i,j=1);
				else
					generate(sudoku,i,++j);
			}
			else								//number isn't possible in the cell
			{
				avail[cell][num] = 0;
				generate(sudoku,i,j);
			}
		}
		else
		{
			for(int temp=1;temp<=9;temp++)
				avail[cell][temp] = 1;
				
			if(j==1)
			{
				sudoku[i-1][9] = 0;
				generate(sudoku,--i,j=9);
			}
			else
			{
				sudoku[i][j-1] = 0;
				generate(sudoku,i,--j);
			}
		}
	}

int main()
{
	srand(time(NULL));
	int i,j;
	
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			sudoku[i][j] = 0;
	
	for(i=0;i<81;i++)
		for(j=1;j<=9;j++)
			avail[i][j] = 1;

	generate(sudoku,1,1);
	
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			cout<<sudoku[i][j]<<" ";
			if(j%3 == 0)
				cout<<" ";
		}
		if(i%3 == 0)
			cout<<"\n";
		cout<<"\n";
	}
	
	return 0;
}
