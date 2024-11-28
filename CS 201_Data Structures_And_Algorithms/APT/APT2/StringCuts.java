import java.util.ArrayList;

public class StringCuts{
    public String[] filter (String[] list, int minLength){
        ArrayList<String> wordsThatPass = new ArrayList<>();

        for(int i = 0; i< list.length; i++){
            if (list[i].length() >= minLength && !wordsThatPass.contains(list[i]) ){
                wordsThatPass.add(list[i]);
        }
    }
    String[] wordsThatPassStringArray = wordsThatPass.toArray(new String[0]);
    return wordsThatPassStringArray;
    }
}