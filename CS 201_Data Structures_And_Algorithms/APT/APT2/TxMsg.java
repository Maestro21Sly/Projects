public class TxMsg {
    public String getMessage(String original) {
        String[] wordsFromSentence = original.split(" ");
        String[] abridgedWords = new String[wordsFromSentence.length];
        for (int k = 0; k < wordsFromSentence.length; k++) {
            String wordUnderConsideration = wordsFromSentence[k];
            abridgedWords[k] = convert(wordUnderConsideration);
        }
        return String.join(" ", abridgedWords);
    }
    public boolean allvowels(char c){
        return "aeiou".indexOf(c) != -1;
    }

    public String convert(String message) {
        char[] charactersFromWord = message.toCharArray();
        int lengthOfWord = charactersFromWord.length;
        String result = "";
        if (message.matches("[aeiou]+")){
            return message;
        }
        for (int i = 0; i< lengthOfWord; i++){
            if (!allvowels(charactersFromWord[i]) && (i ==0 || allvowels(charactersFromWord[i-1]))){
                result += charactersFromWord[i];
            }
        }
        return result;

    }
}
