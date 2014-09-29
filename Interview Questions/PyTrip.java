public class PyTrip {
    public static void main(String[] args) {
        // O(n^2) can we do better?
        for (int i = 0; i < 333; i++) {
            int a = i, b, c;
            for (int j = (i+1); j < 500; j++) {
                b = j;
                c = 1000 - a -b;
                if ((a*a) + (b*b) == (c*c) && (a + b +c) == 1000) {
                        System.out.println(a*b*c);
                }  
            }
        }
    }
}

