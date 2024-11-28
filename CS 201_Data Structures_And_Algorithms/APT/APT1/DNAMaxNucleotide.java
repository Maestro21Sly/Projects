//package APT;

public class DNAMaxNucleotide {
    
    public String max(String[] strands, String nuc) {
        // fill in code here
        int nucLength =0;
        String maxItem = "";
        for (String strand: strands){
            int count =numNuc(strand, nuc);
            
            if (count > 0 && (nucLength < count || (nucLength == count && strand.length() > maxItem.length()))){
                nucLength = count;
                maxItem = strand;
            }
        }
        return maxItem;
    }
        
    
 

    public int numNuc (String strand, String nuc){
        int count =0;
        for (int i =0;i < strand.length();i++ ){
            if(strand.charAt(i) == nuc.charAt(0)){
                count ++;
        }
    }  
    return count;
    }    
}
