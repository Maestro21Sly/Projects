public class HowHeavy {
    public int weight(TreeNode tree, int target){
        if(tree == null){
            return 0;
        }
        TreeNode targetNode = findtarget(tree, target);
        if(targetNode ==null){
            return 0;
        }
        return sumFromTree(targetNode);
    }
    private TreeNode findtarget(TreeNode node, int target){
        if(node == null){
            return null;
        }
        if (node.info == target){
            return node;
        }
        TreeNode left = findtarget(node.left, target);
        TreeNode right = findtarget(node.right, target);


        if (left!=null){
            return left;
        }else{
            return right;
        }
    
    }
    
    private int sumFromTree(TreeNode node){
        if(node ==null){
            return 0;
        }
        
        int sum = node.info;
        sum +=sumFromTree(node.left);
        sum += sumFromTree(node.right);
    
        return sum;
    }


        
}
    

//sum of values in a subtree after finding target 
