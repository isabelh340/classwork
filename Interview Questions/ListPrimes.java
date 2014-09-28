public class ListPrimes {
    static boolean isPrime(double x) {
	for (double i = 2; i < Math.floor(Math.sqrt(x)) + 1; i++) {
	    if ((x % i) == 0) {
		return false;
	    }
	}
	return true;
    }

    public static void main(String args[]) {
	int num = 3, count = 1;
	while (count <= 10001) {
	    if (isPrime(num)) {
		count++;
		if (count == 10001) {
		    System.out.println(num);
		}
	    }
	    num+=2;
	}
    }
}