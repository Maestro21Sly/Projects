//package APT.APT 4;

public class PairDown {
    public int[] fold(int[]list){
        int[] newListForAddednumbers = new int[(int) Math.ceil((double)list.length/2)];
        for (int j = 0, t=0; j < list.length; j+=2, t++){
            int firstNumber = list[j];
            int secondNumber = (j+1<list.length)?list[j+1]:0;
            newListForAddednumbers[t]= firstNumber+secondNumber;
        }

        return newListForAddednumbers;
    }
    
}
