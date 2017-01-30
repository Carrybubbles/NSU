package pollers;

import java.io.*;
import java.net.*;

/**
 * Created by artem on 21.12.16.
 */
public class IMAPPoller implements Runnable {
    private static final long RECONNECTIONTIME = 10000;

    private Socket socket = null;
    private String fileName = "default.bin" ;
    private BufferedReader reader = null;
    private BufferedWriter writer = null;
    private String hostName;
    private long timeout = 0;
    private String user;
    private String pass;
    private int port =143;

    public IMAPPoller(String hostName, String user, String pass, String fileName) {
        this.fileName = fileName;
        this.hostName = hostName;
        this.user = user;
        this.pass = pass;
    }




    public void connect() throws IOException {
        System.out.println("Connecting to server");
        socket = new Socket(hostName,port);
        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

        String answer = reader.readLine();
        System.out.println(answer);
        if(!answer.startsWith("* OK"))
            throw  new IOException(answer);
        String curCommand  = "a " + "login " + user + "@" + hostName    + " " + pass;
        answer = sendCommand(curCommand);
        System.out.println(answer);
        if(!answer.startsWith("a OK"))
            throw  new IOException(answer);
    }


    public String sendCommand(String command) throws IOException {
        writer.write(command +'\n');
        writer.flush();
        return getAnswerFromFTP();
    }


    public String  getAnswerFromFTP() throws IOException {
        String answer = "";
        String temp;
        while((temp = reader.readLine()) != null ){
            answer += temp;
            if(temp.startsWith("a OK"))
                break;
        }

        return answer;
    }


    @Override
    public void run() {
        for(;;) {
            long curTime = System.currentTimeMillis();
            if(curTime - timeout > RECONNECTIONTIME ) {
                timeout = curTime;
                try {
                    connect();
                    String answer = goToInbox();
                    int size = getAmountOfMessages(answer);
                    System.out.println("Amount of messages = " + size);
                    if(size > 0) {
                        storeMessages(size);
                    }
                    disconnect();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    private String goToInbox(){
        try {
            String command = "a " + "SELECT INBOX";
            String answer = sendCommand(command);
            System.out.printf(answer);
            if(answer.startsWith("a"+ " NO MAILBOX")){
                throw  new IOException("THERE ARE NO INBOX");
            }
            return  answer;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
    private int getAmountOfMessages(String answer) throws IOException {
        String sSize = answer.substring(answer.indexOf(".")+3,answer.indexOf("EXISTS") - 1);
        System.out.println(sSize);
        return Integer.parseInt(sSize);
    }
    public void storeMessages(int size) {
        System.out.println("Downloading messages...");
        for(int i = 1;i <= size; i++){
            try {
                String pieces[] = fileName.split("\\.");
                String name = pieces[0] + i;
                String curFileName = name + "."+ pieces[1];

                File file = new File(curFileName);
                PrintWriter wr = new PrintWriter(new FileOutputStream(file));
                String command ="a FETCH " + i + " body[]\n";
                writer.write(command);
                writer.flush();
                String answer = reader.readLine();
                if(answer.startsWith("a BAD"))
                    continue;
                String line;
                while(!(line = reader.readLine()).equals("a OK Fetch completed.")){
                    wr.println(line);
                }
                wr.close();
                System.out.println("Download " + i + " message");
             } catch (IOException e) {
                e.printStackTrace();
            }
        }
        deleteMessage(size);
    }

    public void deleteMessage(int size){
        try {
            String answer = sendCommand("a STORE "+"1:"+ size + " FLAGS (\\DELETED)");
            if(answer.startsWith("a BAD"))
                throw new IOException("cant store messages for delete");
            System.out.println(answer);
            answer = sendCommand("a EXPUNGE");
            if(answer.startsWith("a BAD"))
                throw  new IOException("cant delete messages");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void disconnect() throws IOException {
        System.out.println("LOGOUT....");
        String answer = sendCommand("a LOGOUT");
        System.out.println(answer);
        if(answer.startsWith("a BAD")){
            throw  new IOException(answer);
        }
        socket = null;
    }
    public static void main(String[] args) {
        IMAPPoller poller = new IMAPPoller("nsu.some-body.ru","mail5","stupidpass","pupkinmail.txt");
        poller.run();
    }
}
