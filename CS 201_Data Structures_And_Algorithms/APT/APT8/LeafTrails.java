import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class LeafTrails {
    public String[] trails(TreeNode tree) 
    {
        Map<Integer, String> leafs = new HashMap<>();
        traverse(tree, "", leafs);
        
        List<Map.Entry<Integer, String>> entries = new ArrayList<>(leafs.entrySet());
        Collections.sort(entries, Map.Entry.comparingByKey());
        
        String[] result = new String[entries.size()];
        
        for (int i = 0; i < entries.size(); i++){
            result[i] = entries.get(i).getValue();
        }
        
        return result;
    }
    
    private void traverse(TreeNode node, String path, Map<Integer, String> leafs) {
        if (node == null){
            return;
        }
        
        if (node.left == null && node.right == null){
            leafs.put(node.info, path);
        } 

        else {
            traverse(node.left, path + "0", leafs);
            traverse(node.right, path + "1", leafs);
        }
    }
}