import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day3 {

    public static int getTreesHit(int right, int down, ArrayList<String> slope) {
        int numTrees = 0;
        int x = 0;
        for (int y = 0; y < slope.size(); y += down) {
            if (slope.get(y).charAt(x % slope.get(y).length()) == '#') {
                numTrees++;
            }
            x += right;
        }
        return numTrees;
    }
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day3.in"));

        ArrayList<String> slope = new ArrayList<>();

        while (file.hasNextLine()) {
            slope.add(file.nextLine());
        }

        file.close();

        int part1 = getTreesHit(3, 1, slope);

        int[][] slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

        long part2 = 1;
        for (int[] s : slopes) {
            part2 *= getTreesHit(s[0], s[1], slope);
        }

        System.out.println(part1);
        System.out.println(part2);
    }
}