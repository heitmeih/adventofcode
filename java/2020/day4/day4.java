import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day4 {

    public static boolean isValid(String passport) {
        String[] checks = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        for (String key : checks) {
            if (passport.indexOf(key) == -1) {
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args) throws FileNotFoundException {
        Scanner file = new Scanner(new File("./day4.in"));

        ArrayList<Passport> passports = new ArrayList<>();

        String currentPass = "";
        while (file.hasNextLine()) {
            String line = file.nextLine();
            if (line.length() != 0) {
                currentPass += line.strip() + " ";
            } else {
                passports.add(new Passport(currentPass.strip()));
                currentPass = "";
            }
        }
        passports.add(new Passport(currentPass.strip())); // adds last passport

        int p1Valid = 0;
        int p2Valid = 0;

        for (Passport passport : passports) {
            if (passport.containsRequiredKeys()) {
                p1Valid++;
            }
            if (passport.isValid()) {
                p2Valid++;
            }
        }

        System.out.println(p1Valid);
        System.out.println(p2Valid);
        
        file.close();
    }
}

class Passport {
    
    private int birthYear, issueYear, expirationYear;
    private String height, hairColor, eyeColor, passID;
    private String passportString;
    private boolean valid = true;

    public static boolean containsRequiredKeys(String passport) {
        String[] checks = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        for (String key : checks) {
            if (passport.indexOf(key) == -1) {
                return false;
            }
        }
        return true;
    }

    public boolean containsRequiredKeys() {
        return containsRequiredKeys(passportString);
    }

    private static String[] sortAlphabetically(String[] strings) {
        String temp;
        for (int i = 0; i < strings.length; i++) 
        {
            for (int j = i + 1; j < strings.length; j++) { 
                if (strings[i].compareTo(strings[j])>0) 
                {
                    temp = strings[i];
                    strings[i] = strings[j];
                    strings[j] = temp;
                }
            }
        }
        return strings;
    }

    private static String[] removeCID(String[] passport) {
        String[] result = new String[7];
        int index = 0;
        for (String key : passport) {
            if (!key.startsWith("cid")) {
                result[index] = key;
                index++;
            }
        }
        return result;
    }

    private static String[] createPassportArray(String passport) {
        String[] result = sortAlphabetically(passport.split(" "));
        // when sorted, key order is "byr", "cid", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"
        if (result.length == 8) {
            result = removeCID(result);
        }
        for (int i = 0; i < result.length; i++) {
            result[i] = result[i].substring(4);
        }
        return result;
        
    }

    public Passport(String passport) {
        passportString = passport;
        if (containsRequiredKeys(passport)) {
            String[] pass = createPassportArray(passport);
            // key order is "byr" (0), "ecl" (1), "eyr" (2), "hcl" (3), "hgt" (4), "iyr" (5), "pid" (6)
            birthYear = Integer.parseInt(pass[0]);
            eyeColor = pass[1];
            expirationYear = Integer.parseInt(pass[2]);
            hairColor = pass[3];
            height = pass[4];
            issueYear = Integer.parseInt(pass[5]);
            passID = pass[6];
        } else {
            valid = false;
        }
    }


    public boolean validBirthYear() {
        return (birthYear >= 1920 && birthYear <= 2002);
    }

    public boolean validEyeColor() {
        String[] validColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        for (String c : validColors) {
            if (eyeColor.equals(c)) {
                return true;
            }
        }
        return false;
    }

    public boolean validExpirationYear() {
        return (expirationYear >= 2020 && expirationYear <= 2030);
    }

    public boolean validHairColor() {
        if (hairColor.length() == 7 && hairColor.charAt(0) == '#') {
            for (int i = 1; i < hairColor.length(); i++) {
                if ("0123456789abcdef".indexOf(hairColor.charAt(i)) == -1) {
                    return false;
                }
            }
            return true;
        }
        //System.out.println(hairColor);
        return false;
    }

    public boolean validHeight() {
        if (height.endsWith("cm")) {
            int val = Integer.parseInt(height.substring(0, height.length()-2));
            if (val >= 150 && val <= 193) {
                return true;
            }
        } else if (height.endsWith("in")) {
            int val = Integer.parseInt(height.substring(0, height.length()-2));
            if (val >= 59 && val <= 76) {
                return true;
            }
        }
        return false;
    }

    public boolean validIssueYear() {
        return (issueYear >= 2010 && issueYear <= 2020);
    }

    public boolean validPassportID() {
        try {
            Integer.parseInt(passID);
            
            if (passID.length() == 9) {
                return true;
            }
        } catch (NumberFormatException e) {
            System.out.println(passID);
            return false;
        } 
        return false;
    }

    public boolean isValid() {
        return (valid && validBirthYear() && validExpirationYear() && validEyeColor() && validHairColor() && validHeight() && validIssueYear() && validPassportID());
    }

}