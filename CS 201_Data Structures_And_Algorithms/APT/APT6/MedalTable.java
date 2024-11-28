import java.util.*;

public class MedalTable 
{
    public String[] generate(String[] results) {
        Map<String, int[]> medalTable = new HashMap<>();
        for (String result : results) {
            String[] medals = result.split(" ");
            for (int i = 0; i < 3; i++) {
                medalTable.putIfAbsent(medals[i], new int[3]);
                medalTable.get(medals[i])[i]++;
            }
        }

        List<Map.Entry<String, int[]>> list = new ArrayList<>(medalTable.entrySet());
        list.sort(new Comparator<Map.Entry<String, int[]>>() {
            @Override
            public int compare(Map.Entry<String, int[]> firstElement, Map.Entry<String, int[]> secondElement) {
                for (int x = 0; x < 3; x++) {
                    if (secondElement.getValue()[x] != firstElement.getValue()[x]) {
                        return Integer.compare(secondElement.getValue()[x], firstElement.getValue()[x]);
                    }
                }
                return firstElement.getKey().compareTo(secondElement.getKey());
            }
        });

        String[] sortedMedalTable = new String[list.size()];
        for (int i = 0; i < list.size(); i++) {
            Map.Entry<String, int[]> entry = list.get(i);
            sortedMedalTable[i] = String.format("%s %d %d %d", entry.getKey(), entry.getValue()[0], entry.getValue()[1], entry.getValue()[2]);
        }

        return sortedMedalTable;
    }
} 