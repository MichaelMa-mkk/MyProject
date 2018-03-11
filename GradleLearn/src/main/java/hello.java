import java.util.*;
import java.io.*;

public class hello {

    public static void error(String str_) {
        throw new RuntimeException(str_);
    }

    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        outer:
        while (true) {
            try {
                System.out.print("Dictionary file name? ");
                String file_name;
                file_name = br.readLine();
                Graph ladder = new Graph(file_name);
                while (true) {
                    try {
                        String s_begin, s_end;
                        System.out.println();
                        System.out.print("Word #1 (or Enter to quit): ");
                        s_begin = br.readLine();
                        if (s_begin.length() == 0) break outer;
                        System.out.print("Word #2 (or Enter to quit): ");
                        s_end = br.readLine();
                        if (s_end.length() == 0) break outer;
                        if (s_begin.equalsIgnoreCase(s_end)) error("The two words must be different.");
                        if (s_begin.length() != s_end.length()) error("The two words must be the same length.");
                        ladder.init(s_begin, s_end);
                        if (ladder.access(s_begin, s_end)) {
                            Vector<String> path = new Vector<>();
                            ladder.getLadder(s_begin, s_end, path);
                            System.out.print("A ladder from " + s_end + " back to " + s_begin + ":\n");
                            for (String i : path) {
                                System.out.print(i + " ");
                            }
                            System.out.println();
                        } else {
                            System.out.println("No word ladder found from " + s_end + " back to " + s_begin + ".");
                            System.out.println();
                        }
                    } catch (RuntimeException e) {
                        System.out.println(e.getMessage());
                    }
                }
            } catch (IOException e) {
                System.out.println(e.toString());
            } catch (RuntimeException e) {
                System.out.println(e.getMessage());
            }
        }
        System.out.println("Have a nice day.");
        System.out.println();
    }
}
