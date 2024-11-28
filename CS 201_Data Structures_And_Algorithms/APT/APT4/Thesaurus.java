import java.util.*;

public class Thesaurus {

    public String[] edit(String[] entry) {
        List<String> result = new ArrayList<>(Arrays.asList(entry));

        boolean merged;
        do {
            merged = false;
            for (int i = 0; i < result.size(); i++) {
                for (int j = i + 1; j < result.size(); j++) {
                    String sentence1 = result.get(i);
                    String sentence2 = result.get(j);

                    int commonWords = countCommonWords(sentence1, sentence2);

                    if (commonWords > 1) {
                        // Merge the sentences without duplicates
                        String mergedSentence = mergeTwoSentences(sentence1, sentence2);
                        result.remove(i);
                        result.remove(j - 1);
                        result.add(mergedSentence);
                        merged = true;
                        break;
                    }
                }
                if (merged) {
                    break;
                }
            }
        } while (merged);

        // Sort the words in each sentence and sort the sentences themselves
        result = sortSentences(result);

        return result.toArray(new String[0]);
    }

    private int countCommonWords(String sentence1, String sentence2) {
        String[] words1 = sentence1.split("\\s+");
        String[] words2 = sentence2.split("\\s+");

        int commonWords = 0;
        for (String word1 : words1) {
            for (String word2 : words2) {
                if (word1.equalsIgnoreCase(word2)) {
                    commonWords++;
                }
            }
        }

        return commonWords;
    }

    private String mergeTwoSentences(String sentence1, String sentence2) {
        String[] words1 = sentence1.split("\\s+");
        String[] words2 = sentence2.split("\\s+");

        Set<String> mergedWords = new LinkedHashSet<>(Arrays.asList(words1));

        for (String word : words2) {
            if (!mergedWords.contains(word)) {
                mergedWords.add(word);
            }
        }

        StringBuilder mergedSentence = new StringBuilder();
        for (String mergedWord : mergedWords) {
            mergedSentence.append(mergedWord).append(" ");
        }

        return mergedSentence.toString().trim();
    }

    private List<String> sortSentences(List<String> sentences) {
        List<String> sortedSentences = new ArrayList<>();
        for (String sentence : sentences) {
            String[] words = sentence.split("\\s+");
            Arrays.sort(words);
            sortedSentences.add(String.join(" ", words));
        }
        Collections.sort(sortedSentences);
        return sortedSentences;
    }
}
