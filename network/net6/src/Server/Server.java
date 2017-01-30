package Server;

import Constants.Constant;
import Controllers.WordGenerator;
import Handlers.TaskHandler;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.concurrent.LinkedBlockingQueue;

import static java.lang.Thread.sleep;


/**
 * Created by artem on 14.11.16.
 */
public class Server implements Runnable{
    private ServerSocket sc = null;
    private byte[] hash = null;
    private final List<TaskHandler> taskHandlers = Collections.synchronizedList(new LinkedList<>());
    private final List<String> result = Collections.synchronizedList(new LinkedList<>());
    private final Queue<TaskHandler> unsolvedTasks = new LinkedBlockingQueue<>();

    public Server(String word) throws IOException, NoSuchAlgorithmException {
        hash = MessageDigest.getInstance("MD5").digest(word.getBytes(Charset.forName("UTF-8")));
        sc = new ServerSocket(Constant.SERVER_PORT);
        sc.setSoTimeout(Constant.TIMEOUT);

    }

    @Override
    public void run() {
        boolean alive = true;
        WordGenerator wordGenerator = new WordGenerator("A");
        String start;
        String end;
        while(alive) {
            try {
                Socket clientSocket = sc.accept();
                TaskHandler task = unsolvedTasks.poll();
                if( task != null){
                    start = task.getStart();
                    end = task.getEnd();
                }else{
                    start = wordGenerator.getWord();
                    end = wordGenerator.generateNextWord(1000000);
                }
                System.out.println("Give " + start + "-"+ end);
                Accepter accepter = new Accepter(clientSocket, start, end, hash, taskHandlers, result);
                accepter.start();
            } catch (IOException e) {
                checkAliveInfos();
                if (!result.isEmpty()) {
                    alive = false;
                }
            }
        }

    }

    private synchronized void checkAliveInfos() {
        Iterator<TaskHandler> it = taskHandlers.iterator();
        while(it.hasNext()){
            TaskHandler curInfo = it.next();
            long startInitTime = curInfo.getTime();
            if(System.currentTimeMillis() - startInitTime > Constant.ALIVE_TIME){
                unsolvedTasks.add(curInfo);
                it.remove();
            }
        }
    }


    public static void main(String[] args) {
        try {
            Server server = new Server("ATTTAAAAACCCGGGAAA");
            server.run();
        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
}
