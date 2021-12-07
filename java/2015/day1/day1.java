import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day1 {
    
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day1.in"));

        // part 1
        int currentFloor = 0;

        // part 2
        int position = 0;
        boolean basementReached = false;

        while (file.hasNextLine()) {
            String line = file.nextLine();

            for (int i = 0; i < line.length(); i++) {
                if (line.charAt(i) == '(') {
                    currentFloor++;
                } else {
                    currentFloor--;
                }

                if (currentFloor == -1 && !basementReached) { // part 2
                    position = i + 1;
                    basementReached = true;
                }
            }
        }

        System.out.printf("Part 1: %d\nPart 2: %d\n", currentFloor, position);

        file.close();
    }


}