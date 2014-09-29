<<<<<<< HEAD
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
=======
import java.util.Arrays;
public class Test {
    static class Person {
        public String name;
        public int age;
        Person(String name, int age) {
            this.name = name;
            this.age  = age;
        }

        @Override
        public String toString() {
            return (name + " " +  age);
        }
    }
    public static void main(String args[]) {
        Person zach = new Person("zach", 22);
        Person bob  = new Person("bob", 51);
        Person[] people = new Person[2];
        people[0] = zach;
        people[1] = bob;
        Arrays.sort(people, (p1, p2) -> p2.age - p1.age);
        Arrays.stream(people).forEach(System.out::println);
        double avg = Arrays.stream(people)
            .mapToInt(p -> p.age)
            .average().getAsDouble();
        System.out.println(avg);
>>>>>>> bbf9dcf3860c041c75ad5c538fd8df49da26e083
    }
}
