import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day7 {

    private static ArrayList<String> searchQ = new ArrayList<>();
    private static int p1Count = 0;

    public static void search(ArrayList<String[]> bags) {
        String current = searchQ.remove(0);
        ArrayList<Integer> removeIndexes = new ArrayList<>();
        for (int i = 0; i < bags.size(); i++) {
            String[] bag = bags.get(i);
            if (bag[1].contains(current)) {
                searchQ.add(bag[0].strip());
                removeIndexes.add(0, i);
                p1Count++;
            }
        }
        for (int num : removeIndexes) {
            bags.remove(num);
        }
        if (searchQ.size() != 0) {
            search(bags);
        }

    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day7.in"));

        ArrayList<String[]> bags = new ArrayList<>();

        while (file.hasNextLine()) {
            bags.add(file.nextLine().split(" bags contain "));
        }
        file.close();

        searchQ.add("shiny gold");
        search(bags);
        System.out.println(p1Count);
    }
}