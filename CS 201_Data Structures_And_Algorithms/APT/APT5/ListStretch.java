//package APT.APT5;

public class ListStretch {
    public ListNode stretch(ListNode list, int amount){
        if(list == null){
            return null;
        }else if (amount <=0){
            return list;
        }
        else{
            ListNode current = list;
            while (current != null){
                for (int i=1; i < amount; i++){
                    current.next = new ListNode (current.info, current.next);
                    current = current.next;
                }
                current = current.next;
            }
            return list;
        }
    }
}
