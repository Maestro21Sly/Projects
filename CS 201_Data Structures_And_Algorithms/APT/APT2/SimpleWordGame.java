import java.util.HashSet;
import java.util.Arrays;



public class SimpleWordGame {
    public int points(String[] player, String[] dictionary){
        HashSet<String> distinctWordsFromPlayer = new HashSet<>(Arrays.asList(player));
        HashSet<String> distinctWordsFromDictionary = new HashSet<>(Arrays.asList(dictionary));
        HashSet<String> mySetToFindScore =new HashSet<>(distinctWordsFromPlayer);
        mySetToFindScore.retainAll(distinctWordsFromDictionary);
        int score =0;
        for (String wordsRemembered : mySetToFindScore){
            score += wordsRemembered.length()*wordsRemembered.length();  
        }
        return score;
    }    
}
//score for each word correctly remembered is the square of the word's length
// Even if word appears multiple times, count it once
//Goal is to return player's score
