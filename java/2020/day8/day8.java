import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day8 {
    
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day8.in"));

        ArrayList<Instruction> instructions = new ArrayList<>();

        while (file.hasNextLine()) {
            String[] split = file.nextLine().split(" ");

            instructions.add(new Instruction(split[0], Integer.parseInt(split[1])));
        }
        file.close();

        int acc = 0;
        int pos = 0;

        Instruction current;

        do {
            current = instructions.get(pos);
            current.run();
            acc += current.getAccChange();
            pos += current.getStepChange();
            
        } while (current.getRunCount() <= 1);

        acc -= current.getAccChange();

        System.out.println(acc);

        current.setIns("nop");
        instructions.remove(pos);
        instructions.add(pos, current);

        acc = 0;
        pos = 0;

        do {
            current = instructions.get(pos);
            current.run();
            acc += current.getAccChange();
            pos += current.getStepChange();
            
        } while (pos < instructions.size());

        System.out.println(acc);
    }

}

class Instruction {

    private String ins;
    private int val, runCount;

    public Instruction(String ins, int val) {
        this.ins = ins;
        this.val = val;
        runCount = 0;
    }

    public int getStepChange() {
        if (ins.equals("jmp")) {
            return val;
        }
        return 1;
    }

    public int getAccChange() {
        if (ins.equals("acc")) {
            return val;
        }
        return 0;
    }

    public void setIns(String ins) {
        this.ins = ins;
    }

    public int getRunCount() {
        return runCount;
    }

    public void run() {
        runCount++;
    }
}