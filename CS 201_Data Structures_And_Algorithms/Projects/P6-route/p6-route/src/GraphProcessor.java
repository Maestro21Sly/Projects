import java.security.InvalidAlgorithmParameterException;
import java.io.*;
import java.util.*;


/**
 * Models a weighted graph of latitude-longitude points
 * and supports various distance and routing operations.
 * To do: Add your name(s) as additional authors
 * @author Brandon Fain
 * @author Owen Astrachan modified in Fall 2023
 *
 */
public class GraphProcessor {
    /**
     * Creates and initializes a graph from a source data
     * file in the .graph format. Should be called
     * before any other methods work.
     * @param file a FileInputStream of the .graph file
     * @throws Exception if file not found or error reading
     */

    // include instance variables here
    private String[] vertexID;
    private Point[] vertices;
    private int totalnumberOfVertices;
    private Map<Point, Set<Point>> graph;
    private int numNeighbours;


    public GraphProcessor(){
        // TODO initialize instance variables
        graph = new HashMap<>();
        totalnumberOfVertices=0;
        numNeighbours=0;
    }

    /**
     * Creates and initializes a graph from a source data
     * file in the .graph format. Should be called
     * before any other methods work.
     * @param file a FileInputStream of the .graph file
     * @throws IOException if file not found or error reading
     */

    public void initialize(FileInputStream file) throws IOException {
        // TODO implement by reading info and creating graph
        Scanner mapReader = new Scanner(file);
        String[] Line1Data = mapReader.nextLine().split(" ");
        totalnumberOfVertices = Integer.parseInt(Line1Data[0]);
        numNeighbours = Integer.parseInt(Line1Data[1]);

        vertexID= new String[totalnumberOfVertices];
        vertices = new Point[totalnumberOfVertices];

        for (int i =0; i< totalnumberOfVertices; i++){
            if(!mapReader.hasNextLine()){
                throw new IOException("could not read .graph file");
            }
            String[] path = mapReader.nextLine().split(" ");
            vertexID[i] = path[0];

            Point J = new Point(Double.parseDouble(path[1]),Double.parseDouble(path[2]));
            vertices[i]=J;

            graph.put(vertices[i], new HashSet<>());
        }

        for(int j =0;j<numNeighbours;j++ ){
            if(!mapReader.hasNextLine()){
                throw new IOException("could not read .graph file");
            }
            String[] path = mapReader.nextLine().split(" ");
            Point point1 = vertices[Integer.parseInt(path[0])];
            Point point2 = vertices[Integer.parseInt(path[1])];
            graph.get(point1).add(point2);
            graph.get(point2).add(point1);
        }
        mapReader.close();
    }

    /**
     * Searches for the point in the graph that is closest in
     * straight-line distance to the parameter point p
     * @param p is a point, not necessarily in the graph
     * @return The closest point in the graph to p
     */
    public Point nearestPoint(Point p) {
        // TODO implement nearestPoint
        Point leastDistance = null;
        double leastDistanceValue = Double.MAX_VALUE;

        for(Point datasets: vertices){
            double distance = datasets.distance(p);
            if(distance < leastDistanceValue ){
                leastDistanceValue = distance;
                leastDistance = datasets;
            }
        }
        return leastDistance;
    }

    /**
     * Calculates the total distance along the route, summing
     * the distance between the first and the second Points, 
     * the second and the third, ..., the second to last and
     * the last. Distance returned in miles.
     * @param start Beginning point. May or may not be in the graph.
     * @param end Destination point May or may not be in the graph.
     * @return The distance to get from start to end
     */
    public double routeDistance(List<Point> route) {
        double d = 0.0;
        // TODO implement routeDistance
        for(int i=0; i < route.size()-1;i++){
            d+= route.get(i).distance(route.get(i+1));
        }
        return d;
    }
    

    /**
     * Checks if input points are part of a connected component
     * in the graph, that is, can one get from one to the other
     * only traversing edges in the graph
     * @param p1 one point
     * @param p2 another point
     * @return true if and onlyu if p2 is reachable from p1 (and vice versa)
     */
    public boolean connected(Point p1, Point p2) {
        // TODO implement connected
        Set<Point> visited = new HashSet<>();
        visited.add(p1);

        Queue<Point> mutated = new LinkedList<>();
        mutated.add(p1);

        while (!mutated.isEmpty()) {
            Point current = mutated.remove();

            for (Point newLocation : graph.get(current)) {
                if (!visited.contains(newLocation)) {
                    if (newLocation.equals(p2)) {
                        return true; // Early exit
                    }
                    visited.add(newLocation);
                    mutated.add(newLocation);
                }
            }
        }

        return false;

        // HashSet<Point> visited = new HashSet<>();
        // Queue<Point> mutated = new LinkedList<>();
        // mutated.add(p1);

        // while (mutated.size()>0){
        //     Point current = mutated.remove();
        //     visited.add(current);

        //     for(Point newLocation: graph.get(current)){
        //         if(!visited.contains(newLocation)){
        //             if(newLocation.equals(p2)){
        //                 return true;
        //             }
        //             mutated.add(newLocation);
        //         }
        //     }
        // }
        // return false;
    }

    /**
     * Returns the shortest path, traversing the graph, that begins at start
     * and terminates at end, including start and end as the first and last
     * points in the returned list. If there is no such route, either because
     * start is not connected to end or because start equals end, throws an
     * exception.
     * @param start Beginning point.
     * @param end Destination point.
     * @return The shortest path [start, ..., end].
     * @throws IllegalArgumentException if there is no such route, 
     * either because start is not connected to end or because start equals end.
     */
    public List<Point> route(Point start, Point end) throws IllegalArgumentException {
        // TODO implement route
        if(start.equals(end)){
            throw new IllegalArgumentException("No path between start and end");
        }
        Map<Point, Double> distances = new HashMap<>();
        Map<Point, Point> retracedFrom = new HashMap<>();
        Set<Point> visited = new HashSet<>();

        for(Point vertex: vertices){
            distances.put(vertex,vertex.equals(start)? 0: Double.MAX_VALUE);
        }

        PriorityQueue<Point> queue = new PriorityQueue<>(Comparator.comparing(distances::get));
        queue.add(start);

        while(!queue.isEmpty()){
            Point current =queue.poll();
            visited.add(current);
            for(Point psets: graph.get(current)){
                if(visited.contains(psets)){
                    continue;
                }
                double currentDistance = distances.get(current) + current.distance(psets);
                if(currentDistance < distances.get(psets)){
                    distances.put(psets,currentDistance);
                    retracedFrom.put(psets,current);
                    queue.add(psets);
                }
            }

        }
        if(!retracedFrom.containsKey(end)){
            throw new IllegalArgumentException("No path between start and end.");
        }
        LinkedList<Point> path = new LinkedList<>();
        Point current = end;

        while(current!=null){
            path.addFirst(current);
            current=retracedFrom.get(current);
        }

        return path;
    }
    public static void main(String[] args) throws FileNotFoundException, IOException {
        String name = "data/usa.graph";
        GraphProcessor gp = new GraphProcessor();
        gp.initialize(new FileInputStream(name));
        System.out.println("running GraphProcessor");
    }


    
}
