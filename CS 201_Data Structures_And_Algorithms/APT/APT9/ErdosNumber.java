import java.util.*;

public class ErdosNumber {
    
    public String[] calculateNumbers(String[] pubs) {
        Set<String> allAuthors = getAllAuthors(pubs);
        Map<String, List<String>> graph = buildGraph(pubs);
        Map<String, Integer> erdosNumbers = assignErdosNumbers(graph);
        
        // Sort authors lexicographically
        List<String> sortedAuthors = new ArrayList<>(allAuthors);
        Collections.sort(sortedAuthors);
        
        // Construct the result array
        String[] result = new String[sortedAuthors.size()];
        for (int i = 0; i < sortedAuthors.size(); i++) {
            String author = sortedAuthors.get(i);
            if (erdosNumbers.containsKey(author)) {
                if (erdosNumbers.get(author) == Integer.MAX_VALUE) {
                    result[i] = author;
                } else {
                    result[i] = author + " " + erdosNumbers.get(author);
                }
            } else {
                result[i] = author;
            }
        }
        return result;
    }
    
    // Get all unique authors mentioned in the publications
    private Set<String> getAllAuthors(String[] pubs) {
        Set<String> allAuthors = new HashSet<>();
        for (String pub : pubs) {
            String[] authors = pub.split(" ");
            allAuthors.addAll(Arrays.asList(authors));
        }
        return allAuthors;
    }
    
    // Build the graph where authors are nodes and edges represent co-authorship
    private Map<String, List<String>> buildGraph(String[] pubs) {
        Map<String, List<String>> graph = new HashMap<>();
        for (String pub : pubs) {
            String[] authors = pub.split(" ");
            for (String author : authors) {
                if (!graph.containsKey(author)) {
                    graph.put(author, new ArrayList<>());
                }
                List<String> coAuthors = graph.get(author);
                for (String coAuthor : authors) {
                    if (!coAuthor.equals(author)) {
                        coAuthors.add(coAuthor);
                    }
                }
            }
        }
        return graph;
    }
    
    // Assign Erdos numbers using BFS
    private Map<String, Integer> assignErdosNumbers(Map<String, List<String>> graph) {
        Map<String, Integer> erdosNumbers = new HashMap<>();
        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        
        queue.offer("ERDOS");
        erdosNumbers.put("ERDOS", 0);
        visited.add("ERDOS");
        
        while (!queue.isEmpty()) {
            String author = queue.poll();
            int number = erdosNumbers.get(author);
            for (String coAuthor : graph.getOrDefault(author, new ArrayList<>())) {
                if (!visited.contains(coAuthor)) {
                    erdosNumbers.put(coAuthor, number + 1);
                    visited.add(coAuthor);
                    queue.offer(coAuthor);
                }
            }
        }
        
        // Assign "Infinity" to authors not reachable from Paul Erdos
        for (String author : graph.keySet()) {
            if (!visited.contains(author)) {
                erdosNumbers.put(author, Integer.MAX_VALUE);
            }
        }
        
        return erdosNumbers;
    }
}
