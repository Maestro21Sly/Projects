import java.util.ArrayList;
import java.util.List;

public class LeafCollector {
    public String [] getLeaves(TreeNode tree){
        List<String> expected = new ArrayList<>();
        List<Integer> leaves = new ArrayList<>();
        while(tree!= null){
            tree = eliminateLeaves(tree,  leaves);
            expected.add(String.join(" ", leaves.stream().map(String::valueOf).toArray(String[]::new)));
            leaves.clear();
        }
        return expected.toArray(new String[0]);
    }
    private TreeNode eliminateLeaves (TreeNode node, List<Integer> leaves){
        if(node == null){
            return null;
        }
        if(node.left == null && node.right == null){
            leaves.add(node.info);
            return null;
        }
        node.left= eliminateLeaves(node.left, leaves);
        node.right = eliminateLeaves(node.right, leaves);
        return node;
    }
    
}
