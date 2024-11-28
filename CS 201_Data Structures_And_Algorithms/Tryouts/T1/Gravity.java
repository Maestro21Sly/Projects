package Tryouts.T1;

public class Gravity {
    public double falling (double time, double velo){
    //calcualting how far object falls from time of flight and speed
    double accelerationDueToGravity = 9.8;
    double howFarObjectHasFallen = ((0.5*accelerationDueToGravity*time*time) + (velo*time));
       
    return howFarObjectHasFallen;
    }

}
    

