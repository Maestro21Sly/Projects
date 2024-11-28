public class LinkStrand implements IDnaStrand {
    private class Node{
        String info;
        Node next;
        public Node (String info){
            this.info = info;
        }
    }
    private Node myFirst, myLast;
    private long mySize;
    private int myAppends;
    private int myIndex;
    private Node myCurrent;
    private int myLocalIndex;

    public LinkStrand(){
        this("");
    }
    public LinkStrand(String s){
        initialize(s);
    }

    @Override
    public long size() {
        // TODO Auto-generated method stub
        return mySize;
    }

    @Override
    public void initialize(String source) {
        // TODO Auto-generated method stub
        Node first = new Node(source);
        myFirst = first;
        myLast = first;
        mySize = source.length();
        myAppends=0;
        myIndex =0;
        myLocalIndex = 0;
        myCurrent = myFirst;
    }

    @Override
    public IDnaStrand getInstance(String source) {
        // TODO Auto-generated method stub
        return new LinkStrand(source);
    }
    @Override
    public IDnaStrand append(String dna) {
        // TODO Auto-generated method stub
        myLast.next = new Node (dna);
        myLast = myLast.next;
        mySize += dna.length();
        myAppends++;
        return this;
    }
    @Override
    public String toString(){
        StringBuilder result = new StringBuilder();
        Node newfirst = myFirst;
        while(newfirst != null){
            result.append(newfirst.info);
            newfirst=newfirst.next;
        }
        return result.toString();
    }

    @Override
    public IDnaStrand reverse() {
        // TODO Auto-generated method stub
        Node reversedFirst = null;
        Node current = myFirst;
        while(current != null){
            String reversedInfo = new StringBuilder(current.info).reverse().toString();
            Node newNode = new Node(reversedInfo);
            newNode.next = reversedFirst;
            current = current.next;
            reversedFirst = newNode;
        }
        LinkStrand reversedStrand = new LinkStrand();
        reversedStrand.myFirst= reversedFirst;
        reversedStrand.mySize = mySize;
        return reversedStrand; 
    }

    @Override
    public int getAppendCount() {
        // TODO Auto-generated method stub
        return myAppends;
    }

    @Override
    public char charAt(int index) {
        // TODO Auto-generated method stub
        if(index<0|| index>= mySize){
            throw new IndexOutOfBoundsException();
        }
        if (index< myIndex){
            myCurrent = myFirst;
            myIndex=0;
            myLocalIndex=0;
        }
        while (index >= myIndex+ myCurrent.info.length()-myLocalIndex){
            myIndex += myCurrent.info.length()-myLocalIndex;
            myLocalIndex=0;
            myCurrent= myCurrent.next;
        }
        myLocalIndex += index- myIndex;
        myIndex = index;
        return myCurrent.info.charAt(myLocalIndex);
    }
       
    
}
