package pollers;

import java.io.*;
import java.net.*;

/**
 * Created by artem on 21.12.16.
 */
public class POP3Poller implements Runnable {
    private static final long RECONNECTIONTIME = 10000;
    private Socket socket = null;
    private String fileName = "default.bin" ;
    private BufferedReader reader = null;
    private BufferedWriter writer = null;
    private String hostName;
    private long timeout = 0;
    private String user;
    private String pass;

    private int port =110;

    public POP3Poller(String hostName, String user, String pass,String fileName) {
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
        String answer = getAnswerFromFTP();
        System.out.println(answer);
        if(!answer.startsWith("+OK"))
            throw  new IOException(answer);
        answer = sendCommand("USER " + user);
        System.out.println(answer);
        if(!answer.startsWith("+OK"))
            throw  new IOException(answer);
        answer = sendCommand("PASS "+ pass);
        System.out.println(answer);
        if(!answer.startsWith("+OK"))
            throw  new IOException(answer);
    }


    public String sendCommand(String command) throws IOException {
        writer.write(command +'\n');
        writer.flush();
        return getAnswerFromFTP();
    }


    public String  getAnswerFromFTP() throws IOException {
        return reader.readLine();
    }


    @Override
    public void run() {
        for(;;) {
            long curTime = System.currentTimeMillis();
            if(curTime - timeout > RECONNECTIONTIME ) {
                timeout = curTime;
                try {
                    connect();
                    int size = getAmountOfMessages();
                    System.out.println(size);
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

    private int getAmountOfMessages() throws IOException {
        String answer = sendCommand("STAT");
        String pieces[] = answer.split(" ");
        if(pieces.length > 1) {
            return Integer.valueOf(pieces[1]);
        }else{
            return -1;
        }
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
                String answer = sendCommand("RETR " + i);
                System.out.println(answer);
                if(!answer.startsWith("+OK")) {
                    continue;
                }
                String line;
                while(!(line = reader.readLine()).equals(".")){
                    wr.println(line);
                }
                wr.close();
                answer = sendCommand("DELE " + i);
                System.out.println(answer);
                if(!answer.startsWith(("+OK"))){
                    System.out.println("Cant delete message");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    }
    public void disconnect() throws IOException {
        String answer = sendCommand("QUIT");
        if(!answer.startsWith("+OK")){
            throw  new IOException(answer);
        }
        socket = null;
    }
    public static void main(String[] args) {
        POP3Poller poller = new POP3Poller("ccfit.nsu.ru","fedin","fedin","pupkinmail.txt");
        poller.run();
    }
}
