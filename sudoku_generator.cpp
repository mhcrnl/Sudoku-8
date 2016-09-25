#include<bits/stdc++.h>
using namespace std;

int avail[82][10], sudoku[10][10], list1[2][82], pointer_n = 0;

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
/*
int checkbox(int ii,int jj, int next_num)
	{
		int boxno = box[ii][jj];
		cout<<"check1\n";
/*		if(c==235)
		{
			cout<<"boxno = "<<boxno<<endl;
		}*/
	/*	if(square[boxno][next_num] != 0)
			return boxno;
		return 0;
	}*/

int solve(int sudoku[10][10])
	{
		int i = 1, j = 1, empty[81], counter = 0, k, l, trial;
		while(i<=9 && i<=9)
		{
			if(sudoku[i][j]==0)
			{	
				for(trial=1;trial<=9;trial++)
				{
					k = 1, l = j;
					while(k<=9)
					{
						if(sudoku[k][l] == trial)
							break;
						k++;
					}
					k = i, l = 1;
					while(l<=9)
					{
						if(sudoku[k][l] == trial)
							break;
						l++;
					}
				//	int found = checkbox(k,l,trial);			//if found = 0 means the number is already present in the box
				
					int tempi = i, tempj = j, found = 1;
					while(tempi%3!=1)
						tempi--;
					while(tempj%3!=1)
						tempj--;
					for(int counteri=0;counteri<3;counteri++)
					{
						for(int counterj=0;counterj<3;counterj++)
						{
							if(sudoku[counteri+tempi][counterj+tempj] == trial)
								found = 0;
						}
					}
				
					if(k>9 && l>9 && found!=0)
					{
						//check for the number in the empty array also. The current "trial" number and the number in the array empty for the same cell shouldn't be the same
						empty[counter] = trial;
						counter++;
					}
				}
			}
			if(j==9)
				j = 1, i++;
			else
				j++;
		}
		int check = counter, flag = 0, found = 1;
		i = 1, j = 1, counter = 0;
		while(i<=9 && i<=9)
		{
			if(sudoku[i][j]==0)
			{
				for(trial=1;trial<=9 && empty[counter]!=trial;trial++)
				{
					k = 1, l = j;
					while(k<=9)
					{
						if(sudoku[k][l] == trial)
							break;
						k++;
					}
					k = i, l = 1;
					while(l<=9)
					{
						if(sudoku[k][l] == trial)
							break;
						l++;
					}
				//	int found = checkbox(k,l,trial);			//if found = 0 means the number is already present in the box
				
					int tempi = i, tempj = j, found = 1;
					while(tempi%3!=1)
						tempi--;
					while(tempj%3!=1)
						tempj--;
					for(int counteri=0;counteri<3;counteri++)
					{
						for(int counterj=0;counterj<3;counterj++)
						{
							if(sudoku[counteri+tempi][counterj+tempj] == trial)
								found = 0;
						}
					}
				
					if(k>9 && l>9 && found!=0)
					{
						//check for the number in the empty array also. The current "trial" number and the number in the array empty for the same cell shouldn't be the same
						flag = 1;
						counter++;
					}
				}
			}
			if(j==9)
				j = 1, i++;
			else
				j++;
		}
		if(counter==check && flag == 1)
			return 0;
		return 1;
	}

void shufflelist()
	{
		random_shuffle( list1[0], list1[0]+81 );
		random_shuffle( list1[1], list1[1]+81 );
	}

void createlist()
	{
		int i,j,counter = 0;
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				list1[0][counter] = i+1, list1[1][counter] = j+1, counter++;
		/*
		for(i=0;i<81;i++)
		{
			cout<<list1[0][i]<<" "<<list1[1][i]<<endl;
		}
		cout<<endl<<endl;*/
		shufflelist();
	}

void eliminate(int sudoku[10][10])
	{
		pointer_n = 0;
		while(pointer_n<81)
		{
			int x_i = list1[0][pointer_n];
			int y_i = list1[1][pointer_n];
			
			int next_num = sudoku[x_i][y_i];
			sudoku[x_i][y_i] = 0;
			
			if(solve(sudoku)==0)
				sudoku[x_i][y_i] = next_num;
			
			pointer_n++;
		}/*
			for(int i=1;i<=9;i++)
			{
				for(int j=1;j<=9;j++)
				{
					cout<<sudoku[i][j]<<" ";
					if(j%3 == 0)
						cout<<" ";
				}
				if(i%3 == 0)
					cout<<"\n";
				cout<<"\n";
			}*/
		//	cout<<"pointer_n = "<<pointer_n<<endl;
	}

int main()
{
	//srand(time(NULL));
	int i,j;
	
	freopen("generator.txt","w",stdout);
	
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			sudoku[i][j] = 0;
	
	for(i=0;i<81;i++)
		for(j=1;j<=9;j++)
			avail[i][j] = 1;

	generate(sudoku,1,1);
	
	cout<<"Generated grid is:\n\n";
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
	
	cout<<"\n\n\n\n";
	
	createlist();
	eliminate(sudoku);
	cout<<"Generated sudoku is:\n\n";
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
