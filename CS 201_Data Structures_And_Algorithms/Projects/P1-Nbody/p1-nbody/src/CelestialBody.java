

/**
 * Celestial Body class for NBody
 * Modified from original Planet class
 * used at Princeton and Berkeley
 * @author ola
 *
 * If you add code here, add yourself as @author below
 * @author Johannes Sylvester Arizie
 *
 *
 */
public class CelestialBody {

	private double myXPos;
	private double myYPos;
	private double myXVel;
	private double myYVel;
	private double myMass;
	private String myFileName;

	/**
	 * Create a Body from parameters	
	 * @param xp initial x position
	 * @param yp initial y position
	 * @param xv initial x velocity
	 * @param yv initial y velocity
	 * @param mass of object
	 * @param filename of image for object animation
	 */
	public CelestialBody(double xp, double yp, double xv,
			             double yv, double mass, String filename){
		// TODO: complete constructor
		myXPos = xp;
		myYPos = yp;
		myXVel = xv;
		myYVel = yv;
		myMass = mass;
		myFileName = filename;

	}

	/**
	 *
	 * @return
	 */
	public double getX() {
		// TODO: complete method
		return myXPos;
	}

	/**
	 *
	 * @return
	 */
	public double getY() {
		// TODO: complete method
		return myYPos;
	}

	/**
	 * Accessor for the x-velocity
	 * @return the value of this object's x-velocity
	 */
	public double getXVel() {
		// TODO: complete method
		return myXVel;
	}
	/**
	 * Return y-velocity of this Body.
	 * @return value of y-velocity.
	 */
	public double getYVel() {
		// TODO: complete method
		return myYVel;
	}

	/**
	 *
	 * @return
	 */
	public double getMass() {
		// TODO: complete method
		return myMass;
	}

	/**
	 *
	 * @return
	 */
	public String getName() {
		// TODO: complete method
		return myFileName;
	}

	/**
	 * Return the distance between this body and another
	 * @param b the other body to which distance is calculated
	 * @return distance between this body and b
	 */
	public double calcDistance(CelestialBody b) {
		// TODO: complete method
		double originalDistanceBetweenTwoObjects = Math.sqrt(Math.pow(b.myXPos - this.myXPos,2 )+ Math.pow(b.myYPos - this.myYPos, 2));
		return originalDistanceBetweenTwoObjects;
	}

	public double calcForceExertedBy(CelestialBody b) {
		// TODO: complete method
		double gravitationalConstant = (6.67*1e-11);
		double gravitationalForceOfAttraction = (gravitationalConstant*myMass*b.myMass)/(Math.pow(calcDistance(b),2));
		return gravitationalForceOfAttraction;
	}

	public double calcForceExertedByX(CelestialBody b) {
		// TODO: complete method
		return (this.calcForceExertedBy(b)*(b.myXPos - this.myXPos))/this.calcDistance(b);
	}
	public double calcForceExertedByY(CelestialBody b) {
		// TODO: complete method
		return (this.calcForceExertedBy(b)*(b.myYPos - this.myYPos))/this.calcDistance(b);
	}

	public double calcNetForceExertedByX(CelestialBody[] bodies) {
		// TODO: complete method
		double sum = 0.0;
		for(CelestialBody b: bodies){
			if(!b.equals(this)){
				sum+=this.calcForceExertedByX(b);
			}
		}
		return sum;
	}

	public double calcNetForceExertedByY(CelestialBody[] bodies) {
		double sum = 0.0;
		for(CelestialBody b: bodies){
			if(!b.equals(this)){
				sum+=this.calcForceExertedByY(b);
			}
		}
		return sum;
	}

	public void update(double deltaT, double xforce, double yforce) {
		// TODO: complete method
		double a_x = xforce/this.myMass;
		double a_y = yforce/this.myMass;
		double nvx = this.myXVel + a_x*deltaT;
		double nvy = this.myYVel + a_y*deltaT;
		double nx = this.myXPos + nvx*deltaT;
		double ny = this.myYPos + nvy*deltaT;
		this.myXPos = nx;
		this.myYPos = ny;
		this.myXVel = nvx;
		this.myYVel = nvy;
	}

	/**
	 * Draws this planet's image at its current position
	 */
	public void draw() {
		StdDraw.picture(myXPos,myYPos,"images/"+myFileName);
	}
}
