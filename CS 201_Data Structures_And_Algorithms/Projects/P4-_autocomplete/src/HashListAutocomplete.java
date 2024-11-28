import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class HashListAutocomplete implements Autocompletor {
    private static final int MAX_PREFIX = 10;
    private Map<String, List<Term>> myMap;
    private int mySize;

    private static final int CharacterWeight = 2;
    private static final int DoubleWeight =8;

    public HashListAutocomplete(String[] terms, double[] weights) {
        if(terms==null||weights==null){
            throw new NullPointerException("One or more arguments null");
        }
        if (terms.length != weights.length){
            throw new IllegalArgumentException("terms and weights are not the same length");
        }
        initialize(terms, weights);
    }

    @Override
    public List<Term> topMatches(String prefix, int k) {
        // TODO Auto-generated method stub
        if(prefix.length()>MAX_PREFIX){
            prefix = prefix.substring(0, MAX_PREFIX);
        }
        List <Term> all = myMap.getOrDefault(prefix, new ArrayList<>());
        return all.subList(0, Math.min(k,all.size()));
    }

    @Override
    public void initialize(String[] terms, double[] weights) {
        // TODO Auto-generated method stub
        myMap = new HashMap<>();
        mySize =0;
        for(int x = 0; x< terms.length; x++){
            if(weights[x]<0.0){
                throw new IllegalArgumentException("Array of weights contains a negative value");
            }
            if(terms[x]==null){
                throw new NullPointerException("Array of terms contains a null element");
            }
            for (int y =0; y<= Math.min(MAX_PREFIX, terms[x].length()); y++){
                String finish = terms[x].substring(0,y);
                if(!myMap.containsKey(finish)){
                    myMap.put(finish, new ArrayList<>());
                    mySize += CharacterWeight * finish.length();
                }
                myMap.get(finish).add(new Term(terms[x], weights[x]));
                mySize += CharacterWeight * terms[x].length() + DoubleWeight;
            }
        }
        for(List<Term> list: myMap.values()){
            list.sort(Comparator.comparing(Term::getWeight).reversed());
        }
    }

    @Override
    public int sizeInBytes() {
        // TODO Auto-generated method stub
        return mySize;
    }  
}

