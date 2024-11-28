import java.util.ArrayList;

public class CounterAttack {
    public int[] analyze(String str, String [] words ){
        ArrayList<Integer> frequencyOfAppearancesFromWords = new ArrayList<>();
        String[] fetchedElementsFromStr = str.split(" ");
        
        for(int i =0; i < words.length; i++){
            int count = 0;
            for(int currentPosition = 0; currentPosition < fetchedElementsFromStr.length; currentPosition++){
                if (words[i].equals(fetchedElementsFromStr[currentPosition])){
                    count +=1;

                }
            }
            
            frequencyOfAppearancesFromWords.add(count);  
        }
        int[] frequencyOfAppearancesFromWordsArray = new int[frequencyOfAppearancesFromWords.size()];
        for (int i=0; i< frequencyOfAppearancesFromWords.size(); i++){
            frequencyOfAppearancesFromWordsArray [i] = frequencyOfAppearancesFromWords.get(i);
        }
        return frequencyOfAppearancesFromWordsArray;
    }
}

//for the ith element in words, check if str contains it and how many times it appears there
//Store this frequency found in the ith position of the arrayList created