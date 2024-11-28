import java.util.HashMap;
import java.util.Map;

public class HuffmanDecoding {
    public String decode(String archive, String[] dictionary) {
        if (archive == null || archive.isEmpty() || dictionary == null || dictionary.length == 0)
            return "";

        // Build the decoding map
        Map<String, Character> decodingMap = buildDecodingMap(dictionary);

        // Decode the archive
        StringBuilder decodedString = new StringBuilder();
        StringBuilder currentCode = new StringBuilder();
        for (char c : archive.toCharArray()) {
            currentCode.append(c);
            if (decodingMap.containsKey(currentCode.toString())) {
                decodedString.append(decodingMap.get(currentCode.toString()));
                currentCode.setLength(0); // Clear currentCode
            }
        }

        return decodedString.toString();
    }

    private Map<String, Character> buildDecodingMap(String[] dictionary) {
        Map<String, Character> decodingMap = new HashMap<>();
        for (int i = 0; i < dictionary.length; i++) {
            decodingMap.put(dictionary[i], (char) ('A' + i));
        }
        return decodingMap;
    }
}

