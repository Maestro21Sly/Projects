//package APT;

public class SandwichBar {
    public int whichOrder(String[] available, String [] orders){
        for (int i = 0; i< orders.length; i++){
            String[] ingredientsInOrder = orders[i].split(" ");
            
            if(canMakeSandwichILike(available,ingredientsInOrder)){
                return i;
            }
        }
        return -1;
    }
    


//boolean to find if i can make sandwich i like
//main code find 
    private boolean canMakeSandwichILike(String[] available, String[] ingredientsInOrder){
        for (String ingredient : ingredientsInOrder){
            boolean ingredientAvailable =false;
            for(String availableIngredient : available){
                if (availableIngredient.equals(ingredient)){
                    ingredientAvailable =true;
                    break;

                }
            }
            if(!ingredientAvailable){
                return false;
            }
        }
        return true;
    }
}


