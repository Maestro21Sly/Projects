//package APT.APT5;

public class RemoveMin {
    public ListNode remove(ListNode list) {
        if (list == null || list.next == null) {
            // Handling the case where the list is empty or has only one node
            return null;
        }

        ListNode current = list;
        ListNode minNode = list;
        ListNode prevMinNode = null;

        while (current.next != null) {
            if (current.next.info < minNode.info) {
                prevMinNode = current;
                minNode = current.next;
            }
            current = current.next;
        }
        // Update pointers to remove the minNode
        if (prevMinNode != null) {
            prevMinNode.next = minNode.next;
        } else {
            // If the minimum node is the head of the list
            list = minNode.next;
        }

        return list; 
    }
}
