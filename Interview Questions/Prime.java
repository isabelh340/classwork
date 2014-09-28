public class Prime {
    static boolean isPrime(double x) {
	for (double i = 2; i < Math.floor(Math.sqrt(x)) + 1; i++) {
	    if ((x % i) == 0) {
	       	return false;
	    }
	}	
	return true;
    }

    public static void main(String args[]) {
	double num = 600851475143.0;
	for (double i = Math.floor(Math.sqrt(num)); i >= 1; i--) {
	    if ((num % i) == 0 && isPrime(i)) {
		System.out.println(i);
		break;
	    }
	}
    }
}