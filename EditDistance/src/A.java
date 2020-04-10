import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.Map;

public class A
{
	private int[][] matrix;
	private char[] chArray1;
	private char[] chArray2;
	private int row;
	private int col;
	Map<Key, node> map;
	private PriorityQueue<node> openSet;
	private LinkedList<node> closeSet;

	public A() {}
	public A(String str1, String str2)
	{
		col = str1.length() + 1;
		row = str2.length() + 1;
		chArray1 = str1.toCharArray();
		chArray2 = str2.toCharArray();
		matrix = new int[row][col];
		map = new HashMap<Key, node>();
		Comparator<node> comparator = new nodeComparator();
		openSet = new PriorityQueue<node>(row*col, comparator);
		closeSet = new LinkedList<node>();
		aStar();
	}

	private void updateMatrix()
	{
		for (node n : closeSet)
			matrix[n.getI()][n.getJ()] = n.getGscore();
		for (node n : openSet)
			matrix[n.getI()][n.getJ()] = n.getGscore();
	}

	public void print()
	{
		updateMatrix();
		for (int i=0; i<row; i++)
		{
			System.out.print("\n");
			for (int j=0; j<col; j++)
				System.out.print(matrix[i][j] + " ");
		}
		System.out.println("\n");
	}

	// heuristic cost estimate
	// only insert and mismatch will have penalty
	// diagnal path can be considered as match(without penalty)
	// So we only return the differece between i and j;
	private int hEstimate(int i, int j) { return row-1-i<col-1-j ? (col-j)-(row-i) : (row-i)-(col-j); }

	private void update(int i, int j, int dist, node current, LinkedList<node> lst)
	{
		if (map.containsKey(new Key(i, j)) && map.get(new Key(i, j)).getGscore() > current.getGscore()+dist)
			{
				map.get(new Key(i, j)).setGscore(current.getGscore() + dist);
				map.get(new Key(i, j)).setFscore(current.getGscore() + dist + hEstimate(i+1, j));
				// in order to sort priority queue
				openSet.remove(map.get(new Key(i, j)));
				openSet.add(map.get(new Key(i, j)));
			}
			else
			{
				map.put(new Key(i, j), new node(i, j, current.getGscore() + dist, current.getGscore() + dist + hEstimate(i, j)));
				lst.add(map.get(new Key(i, j)));
			}
	}

	// find and update neighbors
	private LinkedList<node> findNeighbor(node current)
	{
		int i = current.getI();
		int j = current.getJ();
		LinkedList<node> lst = new LinkedList<node>();

		if (i<row-1)
			update(i+1, j, 1, current, lst);

		if (j<col-1)
			update(i, j+1, 1, current, lst);

		if (i<row-1 && j<col-1)
			update(i+1, j+1, chArray1[j]==chArray2[i] ? 0 : 1, current, lst);

		return lst;
	}

	private boolean isIn(node n, LinkedList<node> lst)
	{
		for (node tmp : lst)
			if ( (n.getI() == tmp.getI()) && (n.getJ() == tmp.getJ()) )
				return true;
		return false;
	}

	private boolean isIn(node n, PriorityQueue<node> pQueue)
	{
		for (node tmp : pQueue)
			if ( (n.getI() == tmp.getI()) && (n.getJ() == tmp.getJ()) )
				return true;
		return false;
	}

	private int dist_between(node current, node neighbor)
	{
		int x = neighbor.getI() - current.getI();
		int y = neighbor.getJ() - current.getJ();
		int intIsMatch = 0;
		if ((x+y) == 2)
			intIsMatch = chArray1[neighbor.getJ()-1]==chArray2[neighbor.getI()-1] ? 0 : 1;
		return (x+y)==2 ? intIsMatch : 1;
	}

	private void aStar()
	{
		openSet.add(new node(0, 0, 0, hEstimate(0, 0)));
		matrix[0][0] = 0;
		node current;
		while (openSet.size() != 0)
		{
			current = openSet.remove();
			closeSet.add(current);
			// current == goal
			if ((current.getI() == row-1) && (current.getJ() == col-1))
				return;
			// go through all neighbors of current
			// (i,j+1), (i+1,j), (i+1,j+1)
			int tentative_gscore;
			for (node neighbor : findNeighbor(current))
			{
				if (isIn(neighbor, closeSet))
					continue;
				if (!isIn(neighbor, openSet))
					openSet.add(neighbor);
				tentative_gscore = current.getGscore() + dist_between(current, neighbor);
				if (tentative_gscore >= neighbor.getGscore())
					continue;
				neighbor.setGscore(tentative_gscore);
				neighbor.setFscore(tentative_gscore + hEstimate(neighbor.getI(), neighbor.getJ()));
			}
		}
	}
}

class Key {

    private final int x;
    private final int y;

    public Key(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Key)) return false;
        Key key = (Key) o;
        return x == key.x && y == key.y;
    }

    @Override
    public int hashCode() {
        int result = x;
        result = 31 * result + y;
        return result;
    }

}

class nodeComparator implements Comparator<node>
{
    @Override
    public int compare(node x, node y)
    {
        if (x.getFscore() < y.getFscore())
            return -1;
        if (x.getFscore() > y.getFscore())
            return 1;
        return 0;
    }
}

class node
{
	private int i;
	private int j;
	private int fscore;
	private int gscore;
	// update matrix

	public node(int i, int j, int gscore, int fscore)
	{
		this.i = i;
		this.j = j;
		this.gscore = gscore;
		this.fscore = fscore;
	}

	public int getI() { return i; }
	public int getJ() { return j; }
	public int getGscore() { return gscore; }
	public int getFscore() { return fscore; }
	public void setGscore(int newGscore) { gscore = newGscore; }
	public void setFscore(int newFscore) { fscore = newFscore; }
}