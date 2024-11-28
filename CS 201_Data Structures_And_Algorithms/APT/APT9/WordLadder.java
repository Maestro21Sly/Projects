// import java.util.HashSet;
// import java.util.LinkedList;
// import java.util.Queue;
// import java.util.Set;

// public class WordLadder {
//     public String ladderExists(String[] words, String from, String to) {
//         Set<String> wordSet = new HashSet<>();
//         for (String word : words) {
//             wordSet.add(word);
//         }

//         Queue<String> queue = new LinkedList<>();
//         Set<String> visited = new HashSet<>();
//         queue.offer(from);
//         visited.add(from);

//         while (!queue.isEmpty()) {
//             String current = queue.poll();

//             // Check if current word is one step away from the target
//             if (isAdjacent(current, to)) {
//                 return "ladder";
//             }

//             // Iterate through all possible one-letter transformations of the current word
//             for (int i = 0; i < current.length(); i++) {
//                 char[] chars = current.toCharArray();
//                 for (char c = 'a'; c <= 'z'; c++) {
//                     chars[i] = c;
//                     String next = new String(chars);

//                     // If the transformation exists in the word set and has not been visited yet
//                     if (wordSet.contains(next) && !visited.contains(next)) {
//                         queue.offer(next);
//                         visited.add(next);
//                     }
//                 }
//             }
//         }

//         return "none";
//     }

//     // Method to check if two words are adjacent
//     private boolean isAdjacent(String word1, String word2) {
//         int diffCount = 0;
//         for (int i = 0; i < word1.length(); i++) {
//             if (word1.charAt(i) != word2.charAt(i)) {
//                 diffCount++;
//                 if (diffCount > 1) {
//                     return false;
//                 }
//             }
//         }
//         return diffCount == 1;
//     }
// }
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class WordLadder {
    public String ladderExists(String[] words, String from, String to) {
        Set<String> wordSet = new HashSet<>();
        for (String word : words) {
            wordSet.add(word);
        }

        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(from);
        visited.add(from);

        while (!queue.isEmpty()) {
            String current = queue.poll();

            // Check if current word is one step away from the target
            if (isAdjacent(current, to)) {
                return "ladder";
            }

            // Iterate through all possible one-letter transformations of the current word
            for (int i = 0; i < current.length(); i++) {
                char[] chars = current.toCharArray();
                for (char c = 'a'; c <= 'z'; c++) {
                    chars[i] = c;
                    String next = new String(chars);

                    // If the transformation exists in the word set and has not been visited yet
                    if (wordSet.contains(next) && !visited.contains(next)) {
                        queue.offer(next);
                        visited.add(next);
                    }
                }
            }
        }

        return "none";
    }

    // Method to check if two words are adjacent
    private boolean isAdjacent(String word1, String word2) {
        int diffCount = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                diffCount++;
                if (diffCount > 1) {
                    return false;
                }
            }
        }
        return diffCount == 1;
    }
}
