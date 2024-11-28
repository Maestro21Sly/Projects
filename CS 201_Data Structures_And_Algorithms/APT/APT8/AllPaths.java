import java.util.ArrayList;
import java.util.Collections;

public class AllPaths {
    public String[] paths(TreeNode t) {
        if (t == null) {
            return new String[0];
        }
        
        ArrayList<String> pathsList = new ArrayList<>();
        generatePaths(t, "", pathsList);
        Collections.sort(pathsList);
        
        return pathsList.toArray(new String[0]);
    }

    private void generatePaths(TreeNode node, String path, ArrayList<String> pathsList) {
        if (node == null) {
            return;
        }
        
        path += node.info;
        
        if (node.left == null && node.right == null) {
            pathsList.add(path);
        } else {
            path += "->";
            generatePaths(node.left, path, pathsList);
            generatePaths(node.right, path, pathsList);
        }
    }
}

