import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.security.Key;

public class FileEncryptor {
    private static final String ALGORITHM = "AES";
    private static final String TRANSFORMATION = "AES";

    private Key key;
    private boolean encrypt = true;

    public FileEncryptor(String secret) {
        key = new SecretKeySpec(secret.getBytes(), ALGORITHM);
    }

    public String decryptFromFileName(String inputFile) throws Exception {
        encrypt = false;
        return encryptFileToString(Cipher.DECRYPT_MODE, inputFile);
    }

    public String decryptFromByteArray(byte[] source) throws Exception  {

        try {
            Cipher cipher = Cipher.getInstance(TRANSFORMATION);
            cipher.init(Cipher.DECRYPT_MODE, key);
            byte[] outputBytes = cipher.doFinal(source);
            String ret = new String(outputBytes);
            return ret;
        } catch (Exception e) {
            throw new Exception("error in decrypting from byte array");
        }

       
    }


    public void encrypt(String inputFile, String outputFile) throws Exception {
        encrypt = true;
        doCrypto(Cipher.ENCRYPT_MODE, inputFile, outputFile);
    }

    public void decrypt(String inputFile, String outputFile) throws Exception {
        encrypt = false;
        doCrypto(Cipher.DECRYPT_MODE, inputFile, outputFile);
    }

    private void doCrypto(int cipherMode, String inputFile, String outputFile) throws Exception {
        try {
            Cipher cipher = Cipher.getInstance(TRANSFORMATION);
            cipher.init(cipherMode, key);

            byte[] inputBytes = Files.readAllBytes(Paths.get(inputFile));
            byte[] outputBytes = cipher.doFinal(inputBytes);

            Files.write(Paths.get(outputFile), outputBytes, StandardOpenOption.CREATE);
        } catch (Exception ex) {
            if (encrypt) {
                System.out.println("encrypting " + inputFile + " to " + outputFile);
            }
            throw new Exception("Error encrypting/decrypting file", ex);
        }
    }
    
    private String encryptFileToString(int cipherMode, String inputFile) throws Exception {
        try {
            Cipher cipher = Cipher.getInstance(TRANSFORMATION);
            cipher.init(cipherMode, key);

            byte[] inputBytes = Files.readAllBytes(Paths.get(inputFile));
            byte[] outputBytes = cipher.doFinal(inputBytes);
            return new String(outputBytes);
        } catch (Exception ex) {
            if (encrypt) {
                System.out.println("decrypting " + inputFile + " to string");
            }
            throw new Exception("Error encrypting/decrypting file", ex);
        }
    }
}
