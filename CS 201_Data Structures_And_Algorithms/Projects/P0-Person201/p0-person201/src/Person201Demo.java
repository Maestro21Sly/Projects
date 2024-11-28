/**
 * Demo of Person201 objects for CompSci 201 @ Duke
 * @author Alex Steiger
 * Modified from Fall 2023, Owen Astrachan
 * This versions new in Fall 2023
 */
public class Person201Demo {
    public static void main(String[] args) {
        Person201 c = new Person201("claire",37.8044,-122.2712,"courons");
        Person201 r = new Person201("ricardo",-1.2921, 36.8219,"harambee");
        Person201 j = new Person201("julie",40.7081,-73.9571,"help");
        Person201 s = new Person201("Sam", 44.9978, -93.2650,"hello");
        Person201[] people = {c, r, s, j, new Person201()};

        for(Person201 p : people) {
            System.out.println(p);
        }
        System.out.printf("names: ");
        for(Person201 p : people) {
            System.out.print(p.getName()+" ");
        }
        System.out.println();
    }
}
