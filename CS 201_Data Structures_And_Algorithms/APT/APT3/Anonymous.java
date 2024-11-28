//package APT.APT3 ;

import java.util.HashMap;
import java.util.Map;

public class Anonymous {
    public int howMany(String [] headlines, String [] messages){
        HashMap<Character,Integer> mappingToKeepCharacterCount = new HashMap<>();
        
        for(String headline: headlines){
            headline =headline.replaceAll("\\s+" ,"");
            for(char c: headline.toCharArray()){
                if(Character.isLetter(c)){
                    c = Character.toLowerCase(c);
                    mappingToKeepCharacterCount.put(c,mappingToKeepCharacterCount.getOrDefault(c,0)+1);
                }
            }
        }
        int countOfFormedMessages =0;
        for(String message: messages){
            message = message.replaceAll("\\s+", "");
            HashMap<Character,Integer> mappingtoKeepCharCountForMessages =new HashMap<>();

            for(char c: message.toCharArray()){
                if (Character.isLetter(c)){
                    c = Character.toLowerCase(c);
                    mappingtoKeepCharCountForMessages.put(c,mappingtoKeepCharCountForMessages.getOrDefault(c,0)+1);
                }
            }

            boolean canFormMessage = true;
            
            for(Map.Entry<Character,Integer> entry: mappingtoKeepCharCountForMessages.entrySet()){
                char currentCharacter =entry.getKey();
                int currentCharacterCountInMessage = entry.getValue();

                if(!mappingToKeepCharacterCount.containsKey(currentCharacter)||mappingToKeepCharacterCount.get(currentCharacter)< currentCharacterCountInMessage){
                    canFormMessage = false;
                    break; 
                }
            }
            if(canFormMessage){
                countOfFormedMessages++;
            }
        }
        return countOfFormedMessages;

    }
    
}
