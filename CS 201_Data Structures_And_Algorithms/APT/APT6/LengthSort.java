//Make sorting algorithm that sorts by lenght
import java.util.Arrays;
import java.util.Comparator;

public class LengthSort 
{
    public String[] rearrange(String[] values)
    {
        Arrays.sort
            (
            values, new Comparator<String>() 
        
            {
            @Override
            public int compare(String First, String Second) 
            {
                int compareLength = Integer.compare(First.length(), Second.length());
                if (compareLength != 0) 
                {
                    return compareLength;
                }

                else 
                {
                    return First.compareTo(Second);
                }
            }
            }
        
        );

        return values;
    }
}