import java.util.Arrays;
import java.util.Collections;

public class VoteRigging {
    public int minimumVotes(int[]votes){
        if(votes.length==1){
            return 0;
        }
        Integer[] others = new Integer[votes.length -1];
        for(int i = 1; i < votes.length; i++){
            others[i-1]= votes[i];
        }
        Arrays.sort(others, Collections.reverseOrder());
        int count = 0;
        while(votes[0]<= others[0]){
            votes[0]++;
            others[0]--;
            count++;
            Arrays.sort(others, Collections.reverseOrder());
        }
        return count;
    }
}
