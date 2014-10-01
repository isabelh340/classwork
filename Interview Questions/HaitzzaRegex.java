public class HaitzzaRegex {
    public static void main(String args[]) {
        String timePattern = "(([01][0-2]|\\s[1-9]):[0-5]\\d:([0-5]\\d(.\\d{1,2})?)$)";
        System.out.println("12:53:15.100".matches(timePattern));
    }
}
