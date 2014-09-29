import java.util.*;
import java.util.stream.*;

public class Test {
    static boolean isPrime(int n) {
        for (int i = 2; i < (int)Math.sqrt(n)+1; i++) {
            if ((n % i) == 0) {
                return false;
            }
        }
        return true;
    }
    
    public static void main(String args[]) {
        int[] arr = IntStream.range(0, 99999009).toArray();
        TreeMap<Integer,Boolean> calculations
            = new TreeMap<>();
        Arrays.stream(arr)
            .forEach(n -> calculations.put(n, isPrime(n)));
        for (Map.Entry<Integer, Boolean> entry : calculations.entrySet()) {
            System.out.println(entry.getKey() + " " + entry.getValue());
        }
    }
}
