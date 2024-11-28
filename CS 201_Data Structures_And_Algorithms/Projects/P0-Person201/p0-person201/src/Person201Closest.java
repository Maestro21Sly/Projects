
public class Person201Closest {
    public static void main(String[] args) throws Exception {
        String file = "data/large.txt";
        double min = Double.MAX_VALUE;
        Person201 a = null;
        Person201 b = null;
        // TODO: finish this method
        Person201 [] people = Person201Utilities.readFile(file);

        for (int i =0; i < people.length; i++){
            for (int j = i+1; j< people.length; j++){
                Person201 firstPerson = people[i];
                Person201 secondPerson = people[j];
                double positionVariable = firstPerson.distanceFrom(secondPerson);
                if (positionVariable < min){
                    min =  positionVariable;
                    a = firstPerson;
                    b = secondPerson;
                }
            }
        } 
        System.out.printf("closest distance is %3.2f between %s and %s\n",min,a.getName(),b.getName());       
    }  
}
    
