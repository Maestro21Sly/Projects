import java.util.HashMap;
import java.util.Map;

public class Common {
    public int count (String first , String second){
        int scoreboard = 0;
        Map<Character, Integer > charScoreboard =new HashMap<>();
        for(char i:first.toCharArray()){
            charScoreboard.put(i,charScoreboard.getOrDefault(i, 0)+1);
        }
        for (char i: second.toCharArray()){
            if (charScoreboard.containsKey(i)&&charScoreboard.get(i)>0){
                scoreboard++;
                charScoreboard.put(i,charScoreboard.get(i)-1);
            }
        }
        return scoreboard;


    }
    
}
