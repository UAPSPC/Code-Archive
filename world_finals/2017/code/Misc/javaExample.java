import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.GregorianCalendar;
import java.util.Scanner;
class Main {
    public static void main (String args[]) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        // Different option for input.
        BufferedReader inputHandler = new BufferedReader(new InputStreamReader(System.in));
        try {
            String line = inputHandler.readLine();
            // Do more
        } catch (Exception e) { // Better not reach here
        }
    }
    GregorianCalendar createCal(int year, int zeroIndexMonth, int day, int dayIncrease)
        GregorianCalendar cal = new GregorianCalendar(year, zeroIndexMonth, day);
        cal.add(Calendar.DAY_OF_MONTH, dayIncrease);
        return cal;
    }
}
