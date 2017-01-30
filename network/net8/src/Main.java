import pollers.IMAPPoller;
import pollers.POP3Poller;

import java.io.IOException;
import java.util.Scanner;

/**
 * Created by artem on 22.12.16.
 */
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter type of protocol");
        String pr = sc.nextLine();
        if("pop3".equals(pr)){
            String[] arg = sc.nextLine().split(" ");
            new POP3Poller(arg[0],arg[1],arg[2],arg[3]).run();
        }else if("imap".equals(pr)){
            String[] arg = sc.nextLine().split(" ");
            new IMAPPoller(arg[0],arg[1],arg[2],arg[3]).run();
        }
    }
}
