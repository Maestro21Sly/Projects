//package APT.APT5;

public class SortedListRemoval {
    public ListNode uniqify(ListNode list){
        if (list == null || list.next == null) {
            // If the list is empty or has only one element, no duplicates to remove
            return list;
        }
        ListNode first =list;
        ListNode prev = first;
        ListNode current = first.next;
        while (current !=null){
            if(current.info == prev.info){
                prev.next =current.next; 
            }
            else{
                prev = prev.next; 
            }
            current = current.next;
        }
        return first;
    }
    
    
}






