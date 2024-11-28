public class Circuits {
    public int getCriticalPath(String[] connects, String[] costs) {
        int n = connects.length;
        int[] dp = new int[n];

        for (int i = 0; i < n; i++) {
            dp[i] = findLongestPath(connects, costs, dp, i);
        }

        int maxPath = 0;
        for (int path : dp) {
            maxPath = Math.max(maxPath, path);
        }

        return maxPath;
    }

    private int findLongestPath(String[] connects, String[] costs, int[] dp, int node) {
        if (dp[node] != 0) {
            return dp[node];
        }

        String[] connections = connects[node].split(" ");
        String[] connectionCosts = costs[node].split(" ");
        int maxPath = 0;

        for (int i = 0; i < connections.length; i++) {
            if (!connections[i].isEmpty()) {
                int connectedNode = Integer.parseInt(connections[i]);
                int cost = Integer.parseInt(connectionCosts[i]);
                maxPath = Math.max(maxPath, findLongestPath(connects, costs, dp, connectedNode) + cost);
            }
        }

        dp[node] = maxPath;
        return maxPath;
    }
}
