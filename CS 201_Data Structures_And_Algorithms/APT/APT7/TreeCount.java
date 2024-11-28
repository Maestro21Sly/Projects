//package APT.APT7;

public class TreeCount {
    public int count (TreeNode tree){
        if (tree == null){
            return 0;
        }
        else 
        {
            return 1+ count(tree.left) + count(tree.right);
        }
    }
}
