import java.util.*;
import java.io.*;

public class RegexDeux {
    public static void main(String args[]) {
	String firstPat  = "^hackerrank.*";
	String secondPat = "^.*hackerrank$";
	String thirdPat  = "^hackerrank*hackerrank$";
	String fourthPat = "^hackerrank$";
	Scanner stdin = new Scanner(System.in);
	int numLines = stdin.nextInt(), count = 0;
	String[] lines = new String[numLines];
	stdin.nextLine();
	while (count < numLines) {
	    lines[count++] = stdin.nextLine();
	}

	for (String x : lines) {
	    if (x.matches(thirdPat) || x.matches(fourthPat)) {
		System.out.println(0);
	    } else if (x.matches(firstPat)) {
		System.out.println(1);
	    } else if (x.matches(secondPat)) {
		System.out.println(2);
	    } else {
		System.out.println(-1);
	    }
	}
    }
}