import java.io.*;
import java.util.*;
import java.net.*;

/**
 * Static methods for reading data files, URLs, and encrypted files and URLs.
 * Also includes a method for computing distance between two points on earth.
 * @author Alex Steiger
 * Modified from Fall 2023, Owen Astrachan
 */

public class Person201Utilities {
    public static final double EARTH_RADIUS_KM = 6372.8;

    /**
     * Return distance between two points on earth in kilometers.
     * @param alat latitude of first point
     * @param along longitude of first point
     * @param blat latitude of second point
     * @param blong latitude of second point
     * @return straight line distance between two points
     * code taken from https://rosettacode.org/wiki/Haversine_formula#Java
     */

    public static double distance(double alat, double along, double blat, double blong) {

        double deltaLat = Math.toRadians(blat-alat);
        double deltaLong = Math.toRadians(blong-along);

        double alatRad = Math.toRadians(alat);
        double blatRad = Math.toRadians(blat);

        double calc = Math.pow(Math.sin(deltaLat/2),2) +
                   Math.pow(Math.sin(deltaLong/2),2) *
                   Math.cos(alatRad) * Math.cos(blatRad);
        double c = 2*Math.asin(Math.sqrt(calc));
        return EARTH_RADIUS_KM * c;
    }

    /**
     * Read file specified by parameter and return array of Person201 objects read from file
     * @param fname name of file to be open
     * @return array of Person201 objects read from file
     * @throws IOException if file cannot be open or reading fails
     */

    public static Person201[] readFile(String fname) throws IOException {
        Scanner s = new Scanner(new File(fname));
        Person201[] result = readFromScanner(s);
        s.close();
        return result;
    }

    /**
     * Read file specified by parameter and return array of Person201 objects read from file,
     * but file is encrypted using specified Secret
     * @param fname name of encrypted file
     * @param secret key used to decrypt file
     * @return array of Person201 objects read from file
     * @throws Exception if file cannot be open, or secret doesn't decrypt or reading fails
     */
    public static Person201[] readEncryptedFile(String fname, String secret) throws Exception {
        FileEncryptor fileEncryptor = new FileEncryptor(secret);
        String str = fileEncryptor.decryptFromFileName(fname);
        Scanner s = new Scanner(str);
        Person201[] result = readFromScanner(s);
        s.close();
        return result;
    }

    /**
     * Read URL specified by parameter and return array of Preson201 objects read from URL
     * @param url to be read
     * @return arary of Person201 objects read from URL
     * @throws IOException if URL cannot be open or reading fails
     */
    public static Person201[] readURL(String url) throws IOException {

        BufferedInputStream input = new BufferedInputStream(new URL(url).openStream());
        Scanner s = new Scanner(input);
        Person201[] result = readFromScanner(s);
        s.close();
        return result;
    }

    public static Person201[] readEncryptedURL(String url, String secret) throws Exception {

        InputStream input = new URL(url).openStream();
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        int bytesRead;
        byte[] data = new byte[1024];

        while ((bytesRead = input.read(data, 0, data.length)) != -1) {
            buffer.write(data, 0, bytesRead);
        }

        buffer.flush();
        byte[] bytes = buffer.toByteArray();
      
        FileEncryptor fileEncryptor = new FileEncryptor(secret);
        String clear = fileEncryptor.decryptFromByteArray(bytes);
        Person201[] result = readFromScanner(new Scanner(clear));
        buffer.close();
        return result;
    }

    /**
     * Read from Scanner and return array of Person201 objects read from Scanner
     * @param s is scanner holding source of data
     * @return arary of Person201 objects read from Scanner
     */
    private static Person201[] readFromScanner(Scanner s) {
        ArrayList<Person201> list = new ArrayList<>();

        while (s.hasNextLine()) {
            String line = s.nextLine();
            String[] data = line.split(",");
            Person201 p = new Person201(
                    data[0],
                    Double.parseDouble(data[1]),
                    Double.parseDouble(data[2]),
                    data[3]);
            list.add(p);
        }
        return list.toArray(new Person201[0]);
    }
}
