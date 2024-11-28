public class Overpaid {
    public int count (TreeNode root){
        if(root == null){
            return 0;
        }
        return HelperMethod(root, Integer.MIN_VALUE)-1;//for correcting counting start from 1 vs 0
    }

    private int HelperMethod(TreeNode node, int ValueofParentNode){
        if(node == null){
            return 0;
        }
        int counter =0;
        if(node.info > ValueofParentNode){
            counter=1;
        }
        counter+=HelperMethod(node.left, node.info);
        counter+=HelperMethod(node.right, node.info);

        return counter;

    }
    
}
//retrun number of nodes with values  greater than those of parents 