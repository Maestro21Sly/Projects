//package APT.APT 4;

import java.util.HashMap;
import java.util.Map;

public class IsomorphicWords {
    public int countPairs(String[] words) {
        int count = 0;
        int n = words.length;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (areIsomorphic(words[i], words[j])) {
                    count++;
                }
            }
        }

        return count;
    }

    private boolean areIsomorphic(String word1, String word2) {
        if (word1.length() != word2.length()) {
            return false;
        }

        Map<Character, Character> mapping = new HashMap<>();

        for (int i = 0; i < word1.length(); i++) {
            char char1 = word1.charAt(i);
            char char2 = word2.charAt(i);

            if (mapping.containsKey(char1)) {
                if (mapping.get(char1) != char2) {
                    return false; // Violation of isomorphism rule
                }
            } else {
                if (mapping.containsValue(char2)) {
                    return false; // Two letters cannot map to the same letter
                }
                mapping.put(char1, char2);
            }
        }

        return true;
    }
}

