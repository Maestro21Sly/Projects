//package APT.APT3 ;
import java.util.ArrayList;
import java.util.HashMap;

public class Encryption {
    public String encrypt(String message){
        HashMap<Character,Character> placeholderMapping = new  HashMap<>();
        ArrayList<Character>  placeholders = new ArrayList<>();
        int placeholdersIndex =0;
        String encodedMessage ="";
        for (int t ='a'; t <= 'z';t++){
            placeholders.add((char)t);
        }

        for (int i =0; i< message.length(); i++){
            char currentChar = message.charAt(i);
            
            if(currentChar == ' '){
                encodedMessage += ' ';
            }
            else{
                if (placeholderMapping.containsKey(currentChar)){
                    char existingPlaceholder =placeholderMapping.get(currentChar);
                    encodedMessage += existingPlaceholder;
                 }
                 else{
                    char newPlaceholder = placeholders.get(placeholdersIndex);
                    placeholderMapping.put(currentChar,newPlaceholder);
                    encodedMessage += newPlaceholder;
                    placeholdersIndex++;   
                }
            }
        }
        return encodedMessage;
    }
}
