//package APT9;

public class AlphaPath {
    private int[] start;
    private char[] grid;
    private int rows;
    private int cols;

    public String hasPath(String[] maze){
        makeGrid(maze);
        Stack<int []> toExplore = new Stack<>();
        int[][] diffs = new  int [][]{new int[]{0,1}, new int[]{0,-1}, new int[]{1,0}, new int[]{-1,0}};
        toExplore.push(start);

        while(!toExplore.isEmpty()){
            int [] current = toExplore.pop();
            char currentChar = grid[i][j];
            if(currentChar =='Z'){
                return "YES";
            }
            for(int[]diff : diffs){
                int [] neighbour = new int []{current[0]+ diff[0], current[1]+ diff[1]};
            }
            if(inBounds(neighbour)){
                char neighbourChar = grid[neighbour[0][neighbour[1]]];
                if(neighbourChar == currentChar+1){
                    toExplore.push(neighbour)
                }
            }


        }
        return "YES";
    } 
}
private void makeGrid(String [] maze){
    grid = new char[maze.length][maze[0].length()];
    start = new int [2];
    rows = maze.length; cols = maze[0].length();
    for(int i =0; i< maze.length;i++){
        for (int j = 0; j< maze[i].length(); j++){
            grid[i][j]= maze[i].charAt(j);
            if(grid[i][j]=='A'){
                start[0]=i;start[1]=j;
            }
        }
    }
}

private boolean inBounds(int [] neighbour){

}
