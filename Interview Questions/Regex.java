import java.io.*;
import java.util.Scanner;

public class Regex {
    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	int tests = scan.nextInt(), count = 0;
	String[] testStrings = new String[tests];
	scan.nextLine();
	while (count < tests) {
	    testStrings[count++] = scan.nextLine();
	}
	final String panPattern = "[A-Z]{5}\\d{4}[A-Z]$";
	for (int i = 0; i < tests; i++) {
	    System.out.println((testStrings[i].matches(panPattern) == true
				? "YES" : "NO"));
	}
    }
}
