package console;

import messages.Message;
import messages.MessageType;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Queue;

/**
 * Created by artem on 26.10.16.
 */
public class ConsoleThread extends Thread {
    private Queue<Message> queue = null;
    private String nodeName = "player";
    private final BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));

    public ConsoleThread(Queue<Message> queue, String nodeName){
        this.nodeName = nodeName;
        this.queue = queue;
    }

    private Message parseString(String message) throws IOException {
        if("dead".equals(message)){
            consoleReader.close();
            return new Message(message, nodeName, MessageType.KILL, null, Message.Status.SEND);
        }else{
            return new Message(message, nodeName, MessageType.MESSAGE, null, Message.Status.SEND);
        }
    }
    @Override
    public void run() {
        System.out.println("Enter message string");
        for(;;) {
            try {
                queue.add(parseString(consoleReader.readLine()));
            } catch (IOException e) {
                System.out.println("Bye bye");
                break;
            }
        }
    }
}
