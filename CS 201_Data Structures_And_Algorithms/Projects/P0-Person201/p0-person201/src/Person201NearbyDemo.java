/**
 * @author Alex Steiger
 * Modified from Fall 2023, Owen Astrachan
 * Reads a data file and finds all those people within a specified distance
 * of a specified person.
 */

public class Person201NearbyDemo {
    public static void main(String[] args) throws Exception {
        Person201 query = new Person201("Ricardo",46.9994, -122.3921,"harambee");

        String largeFileName = "data/large.txt";
        String encryptedFileName = "data/encrypted.txt";
        String largeURL = "https://courses.cs.duke.edu/spring24/compsci201/data/large.txt";
        String encryptedURL = "https://courses.cs.duke.edu/spring24/compsci201/data/encrypted.txt";
        String encryptKey = "DukeComputing201";

        double minDistance = 50.0;

        //Person201[] people = Person201Utilities.readFile(largeFileName);
        //Person201[] people = Person201Utilities.readEncryptedFile(encryptedFileName,encryptKey);      
        //Person201[] people = Person201Utilities.readEncryptedURL(encryptedURL,encryptKey);
        Person201 [] people = Person201Utilities.readURL(largeURL);
 

        System.out.println("\nSearching for people near " + query.getName());
        System.out.println("distance\tperson");
        int total = 0;
        for (Person201 p : people) {
            double d = query.distanceFrom(p);
           
            if (d < minDistance) {
                System.out.printf("%3.2f:\t%s\n",d,p);
                total++;
            }
        }
        System.out.println("\nFound " + total + " people near " + query.getName() + "\n");
    }
}
