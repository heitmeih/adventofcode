import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day2 {

    public static int countChar(String s, char c) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == c) {
                count++;
            }
        }
        return count;
    }

    public static boolean part1IsValid(String pass, int upper, int lower, char reqChar) {
        int count = countChar(pass, reqChar);

        if (lower <= count && upper >= count) {
            return true;
        }
        return false;
    }

    public static boolean part2IsValid(String pass, int upper, int lower, char reqChar) {
        if (pass.charAt(lower-1) == reqChar ^ pass.charAt(upper-1) == reqChar) {
            return true;
        }
        return false;
    }
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day2.in"));

        ArrayList<String> passwords = new ArrayList<>();
        ArrayList<Character> reqChars = new ArrayList<>();
        ArrayList<Integer> lowerBounds = new ArrayList<>();
        ArrayList<Integer> upperBounds = new ArrayList<>();

        Pattern p = Pattern.compile("(\\d+)-(\\d+) (\\w): (\\w+)");

        while (file.hasNextLine()) {
            Matcher m = p.matcher(file.nextLine());
            if (m.matches()) {
                lowerBounds.add(Integer.parseInt(m.group(1)));
                upperBounds.add(Integer.parseInt(m.group(2)));
                reqChars.add(m.group(3).charAt(0));
                passwords.add(m.group(4));
            }
        }
        file.close();

        int validP1 = 0;
        int validP2 = 0;

        for (int i = 0; i < lowerBounds.size(); i++) {
            String pass = passwords.get(i);
            int lower = lowerBounds.get(i);
            int upper = upperBounds.get(i);
            char requiredChar = reqChars.get(i);

            if (part1IsValid(pass, upper, lower, requiredChar)) {
                validP1++;
            }

            if (part2IsValid(pass, upper, lower, requiredChar)) {
                validP2++;
            }
        }

        System.out.println(validP1);
        System.out.println(validP2);        
    }
}