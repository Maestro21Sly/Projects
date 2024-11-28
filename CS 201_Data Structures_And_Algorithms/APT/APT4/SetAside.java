import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class SetAside {
    public String common(String[] list){
        HashMap<String,Integer> frequencyMonitor = new HashMap<>();
        ArrayList<String> results = new ArrayList<>();
        String finalResults = "";
        for(int i=0; i < list.length; i++){
            String [] wordsFromSentence = list[i].split(" ");
            HashMap<String,Boolean> distinctWords = new HashMap<>(); 
            for (int h =0; h < wordsFromSentence.length; h++){
                String currentWord = wordsFromSentence[h].toLowerCase();
                if(!distinctWords.containsKey(currentWord)){
                    int count = frequencyMonitor.getOrDefault(currentWord, 0);
                    frequencyMonitor.put(currentWord,count+1);
                    distinctWords.put(currentWord,true);

                }
                
            }
        }
        for (String word: frequencyMonitor.keySet()){
            int frequency = frequencyMonitor.get(word);
            if (frequency ==list.length){
                results.add(word);  
            }
        }
        Collections.sort(results);
        finalResults =String.join(" ", results);
        return finalResults;
    }
}
    

