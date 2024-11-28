//package APT.APT 4;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Closet {
    public String anywhere(String []list){
        HashMap<String,Boolean> allWords = new HashMap<>();
        ArrayList<String> results = new ArrayList<>();
        String finalResults = "";
        for(int i=0; i < list.length; i++){
            String [] wordsFromSentence = list[i].split(" ");
            for (int h =0; h < wordsFromSentence.length; h++){
                String currentWord = wordsFromSentence[h].toLowerCase();
                if(!allWords.containsKey(currentWord)){
                    allWords.put(currentWord, true);
                    results.add(currentWord);
                }
            }
        }
        Collections.sort(results);
        finalResults =String.join(" ", results);
        return finalResults;

    }
    
}
