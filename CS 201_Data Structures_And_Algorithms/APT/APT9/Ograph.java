import java.util.*;

public class Ograph {
    
    public int[] components(String[] data) {
        int n = data.length;
        boolean[] visited = new boolean[n];
        List<Integer> componentSizes = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int size = dfs(data, i, visited);
                componentSizes.add(size);
            }
        }
        
        // Convert ArrayList to int[]
        int[] result = new int[componentSizes.size()];
        for (int i = 0; i < result.length; i++) {
            result[i] = componentSizes.get(i);
        }
        
        // Sort the result array
        Arrays.sort(result);
        
        return result;
    }
    
    private int dfs(String[] data, int vertex, boolean[] visited) {
        visited[vertex] = true;
        int size = 1;
        
        // Get the connections of the current vertex
        String[] connections = data[vertex].split(" ");
        
        // Iterate through each connected vertex
        for (String connection : connections) {
            int neighbor = Integer.parseInt(connection);
            if (!visited[neighbor]) {
                size += dfs(data, neighbor, visited);
            }
        }
        
        return size;
    }
}
