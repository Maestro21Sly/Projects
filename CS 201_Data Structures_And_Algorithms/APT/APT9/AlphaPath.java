import java.util.Stack;

public class AlphaPath {
    private int[] start;
    private char[][] grid;
    private int rows;
    private int cols;

    public String hasPath(String[] maze) {
        makeGrid(maze);
        Stack<int[]> toExplore = new Stack<>();
        int[][] diffs = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        toExplore.push(start);

        while (!toExplore.isEmpty()) {
            int[] current = toExplore.pop();
            int p = current[0];
            int q = current[1];
            char currentChar = grid[p][q];
            if (currentChar == 'Z') {
                return "YES";
            }
            for (int[] diff : diffs) {
                int[] neighbour = new int[]{p + diff[0], q + diff[1]};
                if (inBounds(neighbour)) {
                    char neighbourChar = grid[neighbour[0]][neighbour[1]];
                    if (neighbourChar == currentChar + 1) {
                        toExplore.push(neighbour);
                        // Mark the cell as visited to avoid infinite loops
                        //grid[neighbour[0]][neighbour[1]] = '#';
                    }
                }
            }
        }
        return "NO"; // There's no path from 'A' to 'Z'
    }

    private void makeGrid(String[] maze) {
        grid = new char[maze.length][maze[0].length()];
        start = new int[2];
        rows = maze.length;
        cols = maze[0].length();
        for (int i = 0; i < maze.length; i++) {
            for (int j = 0; j < maze[i].length(); j++) {
                grid[i][j] = maze[i].charAt(j);
                if (grid[i][j] == 'A') {
                    start[0] = i;
                    start[1] = j;
                }
            }
        }
    }

    private boolean inBounds(int[] neighbour) {
        int x = neighbour[0];
        int y = neighbour[1];
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
}
