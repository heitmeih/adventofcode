package advent2020;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Day6 {

    public static int getUniqueCharCount(String s) {
        Set<Character> temp = new HashSet<>();
        for (int i = 0; i < s.length(); i++) {
            temp.add(s.charAt(i));
        }
        return temp.size() - 1; // ignores space characters
    }

    public static int getNumAllAnswered(String group) {
        String[] individualAnswers = group.strip().split(" ");

        Set<Character> commonAnswers = new HashSet<>();
        for (int i = 0; i < individualAnswers[0].length(); i++) { 
            // this works because all possible common answers must be answered in the first person's set of answers
            commonAnswers.add(individualAnswers[0].charAt(i));
        }
        for (String a : individualAnswers) {
            Set<Character> temp = new HashSet<>();
            for (int i = 0; i < a.length(); i++) {
                if (commonAnswers.contains(a.charAt(i))) {
                    temp.add(a.charAt(i));
                }
            }
            commonAnswers = temp;
        }
        return commonAnswers.size();
    }
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day6.in"));

        ArrayList<String> groupAnswers = new ArrayList<>();

        String currentGroupAnswer = "";
        while (file.hasNextLine()) {
            String line = file.nextLine();
            if (line.length() != 0) {
                currentGroupAnswer += line.strip() + " ";
            } else {
                groupAnswers.add(currentGroupAnswer);
                currentGroupAnswer = "";
            }
        }
        groupAnswers.add(currentGroupAnswer);

        int part1 = 0;
        int part2 = 0;

        for (String a : groupAnswers) {
            part1 += getUniqueCharCount(a);
            part2 += getNumAllAnswered(a);
        }

        System.out.println(part1);
        System.out.println(part2);
    }
}