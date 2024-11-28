//package APT;

public class Totality {
    public int sum(int[] a, String stype) {
        int sumValuesAtIndex = 0;
        for (int i = 0; i< a.length; i++ ){
            if ((stype.equals("odd") && i %2 != 0)||
                (stype.equals("even") && i%2 == 0)||
                stype.equals("all")){
                sumValuesAtIndex += a[i];
            }
        }
        return sumValuesAtIndex;

        }
    
    }   
