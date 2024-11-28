public class BigIndex {
    public ListNode filter(ListNode list){
        
        
        ListNode temp = new ListNode(0);
        temp.next = list;
        ListNode previous = temp;
        ListNode current =list; 
        
        int index=0;

        while(current.next !=null){
            if(current.info< index){
                previous.next = current.next;
                // current = current.next;
            }
            else{
                previous = current;     
            }
            current = current.next;
            index++;

            if(current.info <index){
                previous.next=current.next;
            }
        }
        return temp.next;
        
    }
        

    
}

//filter removes any value less than index 
//compare the info at a node with the indexIndex needs to increment
//pointers 