package Server;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.*;

import Handlers.TaskHandler;

/**
 * Created by artem on 19.11.16.
 */
public class Accepter extends Thread {
    private Socket clientSocket = null;
    private byte[] hash = null;
    private List<TaskHandler> clientTask = null;
    private UUID id = null;
    private BufferedReader in = null;
    private PrintWriter out = null;
    private List<String> result = null;
    private String start = null;
    private String end = null;

    public Accepter(Socket clientSocket, String start, String end, byte[] hash, List<TaskHandler> clientTask, List<String> result) throws IOException {
        System.out.println("New client from " + clientSocket.getInetAddress());
        this.clientSocket = clientSocket;
        this.hash = hash;
        this.start = start;
        this.end = end;
        this.clientTask = clientTask;
        this.result = result;
        this.in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        this.out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()),true);
        String sid = in.readLine();
        ByteBuffer bb = ByteBuffer.wrap(sid.getBytes(Charset.forName("UTF-8")));
        long high = bb.getLong();
        long low = bb.getLong();
        this.id = new UUID(high, low);

    }

    private synchronized TaskHandler findClient(UUID id){
        for(TaskHandler cur: clientTask){
            if(cur.getId().equals(id)){
                return cur;
            }
        }
        return null;
    }

    @Override
    public void run() {
        try{
            String request = in.readLine();
            if("give".equals(request)){
                TaskHandler info = findClient(id);
                out.println("work");
                if(info != null){
                    System.out.println("Client " + id + " want to request range again");
                    info.setStart(start);
                    info.setEnd(end);
                    info.setTime(System.currentTimeMillis());
                }else{
                    System.out.println("Client " + id + " request range");
                    info = new TaskHandler(id,start,end);
                    clientTask.add(info);
                }
                out.println(info.getStart());
                out.println(info.getEnd());
                clientSocket.getOutputStream().write(hash);

            } else if("done".equals(request)){
                TaskHandler info = findClient(id);
                if(info != null) {
                    System.out.println("Wow! Client " + id + " found a solution!");
                    String resultString = in.readLine();
                    System.out.println("Result is " + resultString);
                    result.add(resultString);
                }else{
                    System.out.println("Ops ur timeout was expired ");
                }
            }
        }catch (IOException e){
            e.printStackTrace();
        }finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
