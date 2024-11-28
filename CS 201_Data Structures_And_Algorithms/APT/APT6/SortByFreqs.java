import java.util.*;

public class SortByFreqs 
{
    public String[] sort(String[] data) 
    {
        Map<String, Integer> frequencyMap = new HashMap<>();
        
        for (String entity : data) 
        {
            frequencyMap.put(entity, frequencyMap.getOrDefault(entity, 0) + 1);
        }

        List<Map.Entry<String, Integer>> list = new ArrayList<>(frequencyMap.entrySet());
        list.sort(new Comparator<Map.Entry<String, Integer>>() 
        {
            @Override
            public int compare(Map.Entry<String, Integer> firstElement, Map.Entry<String, Integer> secondElement) 
            {
                int frequencyCompare = Integer.compare(secondElement.getValue(), firstElement.getValue());
                if (frequencyCompare != 0) 
                {
                    return frequencyCompare;
                } else 
                {
                    return firstElement.getKey().compareTo(secondElement.getKey());
                }
            }
        });

        String[] sortedData = new String[list.size()];
        for (int x = 0; x < list.size(); x++) {
            sortedData[x] = list.get(x).getKey();
        }

        return sortedData;
    }
}