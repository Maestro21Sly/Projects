import java.util.Arrays;

public class AlphaLength {
    public ListNode create(String[] words) {
        Arrays.sort(words);
        String[] uniqueArray = removeDuplicates(words);

        ListNode head = new ListNode(0);
        ListNode current = head;

        for (String word : uniqueArray) {
            ListNode newNode = null;
            if (word != null && !word.isEmpty()) {  // Check if the word is not null and not empty
                newNode = new ListNode(word.length());
            }
            current.next = newNode;
            current = newNode;
        }

        return head.next; // Skip the dummy node
    }

    private String[] removeDuplicates(String[] array) {
        int uniqueCount = 1;

        for (int i = 0; i < array.length - 1; i++) {
            if (!array[i].equals(array[i + 1])) {
                uniqueCount++;
            }
        }

        String[] uniqueArray = new String[uniqueCount];

        int index = 0;
        for (int i = 0; i < array.length; i++) {
            if (i == array.length - 1 || !array[i].equals(array[i + 1])) {
                uniqueArray[index++] = array[i];
            }
        }

        return uniqueArray;
    }
}
