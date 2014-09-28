import java.util.*;

public class Reverse {
    public static String reverseWords(String s) {
	String[] words = s.split("\\s+");
	StringBuilder ans = new StringBuilder();
	for (int i = words.length - 1; i >= 0; i--) {
	    ans.append(words[i]).append(" ");
	}
	ans.delete(ans.length()-1, ans.length());
	return ans.toString();
    }

    public static void main(String args[]) {
	System.out.println(reverseWords("     a      nb    asdf"));
    }
}