import java.util.*;

    public class SortedFreqs 
    {
        public int[] freqs(String[] data) 
        {
            TreeMap<String, Integer> frequencyMap = new TreeMap<>();
            for (String entity : data) 
            {
                frequencyMap.put(entity, frequencyMap.getOrDefault(entity, 0) + 1);
            }

            int[] frequencies = new int[frequencyMap.size()];
            int x = 0;
            for (Map.Entry<String, Integer> entry : frequencyMap.entrySet()) 
            {
                frequencies[x++] = entry.getValue();
            }

            return frequencies;
        }
    }