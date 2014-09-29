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
    }
}
