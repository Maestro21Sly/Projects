//package APT.APT3 ;

import java.util.HashMap;
import java.util.Map;

public class BigWord {
    public String most (String[] sentences){
        HashMap<String,Integer> wordFrequencyMapping = new HashMap<>();
        for (int i = 0; i < sentences.length;i++){
            String [] wordsFromSentences = sentences[i].split(" "); 
            for (int h =0; h < wordsFromSentences.length; h++){
                String currentWord = wordsFromSentences[h];
                String currentWordInLowerCase = currentWord.toLowerCase();
                int count = wordFrequencyMapping.getOrDefault(currentWordInLowerCase, 0);
                wordFrequencyMapping.put(currentWordInLowerCase,count+1);
            } 
        }
        String mostFrequentWord="";
        int maxFrequency =0;

        for(Map.Entry<String,Integer> entry : wordFrequencyMapping.entrySet()){
            if(entry.getValue()> maxFrequency){
                maxFrequency= entry.getValue();
                mostFrequentWord=entry.getKey();
            }
        }
        return mostFrequentWord;
        
    }
}
