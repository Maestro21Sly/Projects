import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Aaagmnrs {
    public String[] anagrams(String[] phrases) {
        List<String> nonAnagrams = new ArrayList<>();

        for (int i = 0; i < phrases.length; i++) {
            if (!isAnagram(phrases, i)) {
                nonAnagrams.add(phrases[i]);
            }
        }

        return nonAnagrams.toArray(new String[0]);
    }

    private boolean isAnagram(String[] phrases, int currentIndex) {
        String currentPhrase = phrases[currentIndex].toLowerCase().replaceAll(" ", "");
        char[] currentChars = currentPhrase.toCharArray();
        Arrays.sort(currentChars);

        for (int i = 0; i < currentIndex; i++) {
            String comparePhrase = phrases[i].toLowerCase().replaceAll(" ", "");
            char[] compareChars = comparePhrase.toCharArray();
            Arrays.sort(compareChars);

            if (Arrays.equals(currentChars, compareChars)) {
                return true; // It's an anagram, skip it
            }
        }

        return false; // It's not an anagram
    }
}
