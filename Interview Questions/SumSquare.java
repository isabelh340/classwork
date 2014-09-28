public class SumSquare {
    static long sumSquares(int n) {
	long ans = 0;
	for (int i = 1; i <= n; i++) {
	    ans += (i*i);
	}
	return ans;
    }
    
    public static void main(String args[]) {
	int n = 100;
	long sumFirstN = sumSquares(n);
	long squareSumFirstN = (n * (n + 1) / 2);
	squareSumFirstN *= squareSumFirstN;
	System.out.println(squareSumFirstN - sumFirstN);
    }
}