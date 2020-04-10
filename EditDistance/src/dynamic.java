public class dynamic
{
	private int[][] matrix;
	private char[] chArray1;
	private char[] chArray2;
	private int row;
	private int col;
	public dynamic() {}
	public dynamic(String str1, String str2)
	{
		col = str1.length() + 1;
		row = str2.length() + 1;
		chArray1 = str1.toCharArray();
		chArray2 = str2.toCharArray();
		matrix = new int[row][col];
		init();
		dynamicProgramming();
	}

	public void print()
	{
		for (int i=0; i<row; i++)
		{
			for (int j=0; j<col; j++)
				System.out.print(matrix[i][j] + " ");
			System.out.print("\n");
		}
	}

	private void init()
	{
		for (int i=0; i<row; i++)
			for (int j=0; j<col; j++)
				if (i == 0)
					matrix[i][j] = j;
				else if (j == 0)
					matrix[i][j] = i;
	}

	private int min(int a, int b, int c)
	{
		// return the smallest value
		return (a<b?a:b)<c ? a<b?a:b : c;
	}
	
	private void dynamicProgramming()
	{
		for (int i=1; i<row; i++)
			for (int j=1; j<col; j++)
				if (chArray1[j-1] == chArray2[i-1])
					matrix[i][j] = min(matrix[i-1][j-1], matrix[i-1][j]+1, matrix[i][j-1]+1);
				else
					matrix[i][j] = min(matrix[i-1][j-1]+1, matrix[i-1][j]+1, matrix[i][j-1]+1);
	}
}