//package APT QUIZ.APT QUIZ 1;
import java.util.*;

public class BigSpender {
    public String spend (String[] toys, int [] prices, int budget){
        StringBuilder itemsThatCanBeBought = new StringBuilder();
        int currentBudget = budget;
        Set <String> toysThatCanBeBought = new HashSet <>();
        //boolean [] hasAlreadyBoughtItem = new boolean[toys.length];

        for(int j = 0; j< toys.length; j++){
            if(!toysThatCanBeBought.contains(toys[j]) && currentBudget >= prices[j]){
                itemsThatCanBeBought.append(toys[j]).append(" ");
                //hasAlreadyBoughtItem[j] = true;
                toysThatCanBeBought.add(toys[j]);
                currentBudget -= prices[j];
                
            }
        }
        return itemsThatCanBeBought.toString().trim();
    }
    
}
//return items that can be bought in a String 
