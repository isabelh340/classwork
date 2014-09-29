import java.util.stream.*;
public class PrimeSum {
    public static boolean isPrime(long n) {
        for (int i = 2; i <= (long)Math.sqrt(n); i++) {
            if ((n % i) == 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String args[]) {
        System.out.println(LongStream
                           .range(2,2000000)
                           .filter(n -> isPrime(n))
                           .sum());
    }
}
