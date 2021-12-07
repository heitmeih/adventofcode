import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day5 {

    public static int getRow(String pass) {
        String rowStr = pass.substring(0, 7);
        int upperLimit = 127;
        int lowerLimit = 0;
        for (int i = 0; i < rowStr.length(); i++) {
            if (rowStr.charAt(i) == 'F') { // Front or Lower Half
                upperLimit = lowerLimit+((upperLimit-lowerLimit)/2);
            } else { // Back or Upper Half
                lowerLimit = upperLimit-((upperLimit-lowerLimit)/2);
            }
        }
        return upperLimit;
    }

    public static int getCol(String pass) {
        String colStr = pass.substring(7);
        int upperLimit = 7;
        int lowerLimit = 0;
        for (int i = 0; i < colStr.length(); i++) {
            if (colStr.charAt(i) == 'L') { // Front or Lower Half
                upperLimit = lowerLimit+((upperLimit-lowerLimit)/2);
            } else { // Back or Upper Half
                lowerLimit = upperLimit-((upperLimit-lowerLimit)/2);
            }
        }
        return lowerLimit;
    }

    public static int getID(String pass) {
        return getRow(pass) * 8 + getCol(pass);
    }

    public static int max(ArrayList<Integer> list) {
        int max = Integer.MIN_VALUE;
        for (int num : list) {
            if (num > max) {
                max = num;
            }
        }
        return max;
    }

    public static int[] minWithIndex(ArrayList<Integer> list) {
        int min = Integer.MAX_VALUE;
        int minIndex = -1;
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) < min) {
                min = list.get(i);
                minIndex = i;
            }
        }
        return new int[] {min, minIndex};
    }

    public static ArrayList<Integer> sorted(ArrayList<Integer> list) { // sorts an integer array list from least to greatest
        ArrayList<Integer> result = new ArrayList<>();
        while (list.size() > 0) {
            int[] min = minWithIndex(list);
            result.add(min[0]);
            list.remove(min[1]);
        }
        return result;

    }
    public static void main(String[] args) throws FileNotFoundException{
        Scanner file = new Scanner(new File("./day5.in"));

        ArrayList<String> passes = new ArrayList<>();

        while (file.hasNextLine()) {
            passes.add(file.nextLine());
        }

        ArrayList<Integer> ids = new ArrayList<>();

        for (String pass : passes) {
            ids.add(getID(pass));
        }

        System.out.println(max(ids));

        ids = sorted(ids);
        int myID = -1;

        for (int i = 0; i < ids.size()-1; i++) {
            if (ids.get(i) + 1 == ids.get(i+1) - 1){
                myID = ids.get(i) + 1;
            }
        }

        System.out.println(myID);


        file.close();
    }
}