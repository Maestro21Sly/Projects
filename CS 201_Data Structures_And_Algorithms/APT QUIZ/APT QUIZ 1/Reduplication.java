//package APT QUIZ.APT QUIZ 1;

import java.util.HashMap;
import java.util.Map;

public class Reduplication { 
    public int count(String[] words ){
        int wordcount =0;
        @SuppressWarnings({ "rawtypes", "unchecked" })
        Map<String, Integer> wordCounts = new HashMap();
        for (String word :words){
            String reduplication = word + "-"+ word;
            if(doesItContainReduplication(words, reduplication)){
                wordCounts.put(word, wordCounts.getOrDefault(word, 0)+1);
              //wordcount++;   
            }
            
        }
        
        return wordcount;
    }
    private static boolean doesItContainReduplication(String [] words, String reduplication){
        for (String word: words){
            if(reduplication.equals(word)){
                return true;
            }
        }
        return false;
    }
    
}
// implement count to keep track of words in the string array 
// find reduplications 
//Go through wordsfind reduplications as defined 
//find source of reduplications 
//count them including duplicates 