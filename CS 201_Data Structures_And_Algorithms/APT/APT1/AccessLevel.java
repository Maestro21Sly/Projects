//package APT;

public class AccessLevel {
    public String canAccess(int[] rights, int minPermission) {
    StringBuilder result = new StringBuilder();
    for(int permission: rights){
        if (permission >= minPermission) {
            result.append('A');
        } else {
            result.append('D');
        }
    }
    return result.toString();
    }
    
}
