#include<bits/stdc++.h>

using namespace std;

int to_fill[2][82], counter = 0, avail[82][10], flag = 0;
int sudoku[10][10] /*= {{0,0,0,0,0,0,0,0,0},
{0, 6, 9, 8,  0, 2, 0,  0, 0, 7},  
{0, 0, 1, 7,  6, 0, 0,  0, 0, 5},  
{0, 0, 0, 0,  0, 7, 9,  6, 4, 0},  

{0, 8, 0, 2,  0, 0, 7,  0, 0, 0},  
{0, 7, 0, 0,  4, 0, 0,  0, 2, 0},  
{0, 1, 0, 4,  8, 0, 0,  0, 0, 0},  

{0, 0, 0, 3,  0, 4, 0,  9, 5, 1},  
{0, 9, 0, 0,  0, 0, 1,  0, 0, 0},  
{0, 0, 0, 0,  0, 3, 8,  7, 0, 0}  
}*/;

int getnum()
	{
		 return rand()%9 + 1;
	}

int maintain_list(int sudoku[10][10])
	{
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
			{
				if(sudoku[i][j]==0)
				{
					to_fill[0][counter] = i;
					to_fill[1][counter] = j;
					counter++;
				}
			}
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
	
int solve(int sudoku[10][10], int count)
	{
		if(count==counter)
			flag = 1;
		while(flag==0 && count>=0 && count<counter)
		{
			if(sudoku[to_fill[0][count]][to_fill[1][count]] == 0)
			{
				//int cell = (9 * (i-1) + j) ;
				int cell = (9 * (to_fill[0][count]-1) + to_fill[1][count]);
				int countnum = 0, num;
				
				for(int temp=1;temp<=9;temp++)		//check if all numbers are exhausted for this cell
				{
					if(avail[cell][temp]==0)
						countnum++;
				}
				
				if(countnum!=9)
				{	
					num = getnum();
					while(avail[cell][num]==0)
						num = getnum();
					
					if(avail[cell][num]==1 && check(sudoku,to_fill[0][count],to_fill[1][count],num)==1)				//number is possible in the cell
					{
						sudoku[to_fill[0][count]][to_fill[1][count]] = num;
						avail[cell][num] = 0;
					//	cout<<"Count: "<<count<<"  Filled: "<<num<<endl;
						solve(sudoku,++count);
						
						/*
						if(j==9)
							generate(sudoku,++i,j=1);
						else
							generate(sudoku,i,++j);*/
					}
					else								//number isn't possible in the cell
					{
						avail[cell][num] = 0;
						solve(sudoku,count);
					//	generate(sudoku,i,j);
					}
				}
				else
				{
					for(int temp=1;temp<=9;temp++)
						avail[cell][temp] = 1;
					sudoku[to_fill[0][count-1]][to_fill[1][count-1]] = 0;
					solve(sudoku,--count);
					/*	
					if(j==1)
					{
						sudoku[i-1][9] = 0;
						generate(sudoku,--i,j=9);
					}
					else
					{
						sudoku[i][j-1] = 0;
						generate(sudoku,i,--j);
					}*/
				}
			}
		}
	}

int main()
{
	int i,j;
	
	freopen("board.txt","r",stdin);
	freopen("solver.txt","w",stdout);
	
	
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			cin>>sudoku[i][j];

	for(i=0;i<81;i++)
		for(j=1;j<=9;j++)
			avail[i][j] = 1;
	
	maintain_list(sudoku);
/*
	for(j=0;j<counter;j++)
		cout<<to_fill[0][j]<<" "<<to_fill[1][j]<<endl;
*/			
	solve(sudoku,0);
	
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
