import Constants.Constant;
import Controllers.WordGenerator;
import Handlers.BruteData;

import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.UUID;

/**
 * Created by artem on 14.11.16.
 */
public class Client implements Runnable {
    private Socket sc = null;
    private InetAddress serverIP = null;
    private int serverPort = 0;
    private final UUID id = UUID.randomUUID();
    private boolean alive = true;
    private int tries = 0;

    public Client(InetAddress serverIP, int serverPort) {
        this.serverIP = serverIP;
        this.serverPort = serverPort;
    }



    private BruteData getRange(){
        try {
            sc = new Socket();
            sc.connect(new InetSocketAddress(serverIP,serverPort));
            BufferedReader in = new BufferedReader(new InputStreamReader(sc.getInputStream()));
            PrintWriter out = new PrintWriter(sc.getOutputStream(),true);
            out.println(id.toString());
            out.println("give");
            String status = in.readLine();
            if(status.equals("work")){
                String start = in.readLine();
                String end = in.readLine();
                byte[] hash = new byte[16];
                sc.getInputStream().read(hash);
                return new BruteData(start, end, hash);

            }else if(status.equals("none")){
                System.out.println("There aren't any job");
                alive = false;
                return null;
            }
        } catch (IOException e) {
            tries++;
            System.out.println("Cant connect to server");
            e.printStackTrace();
            return null;
        }finally {
            try {
                sc.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return null;
    }

    private boolean sendResult(String result){
        for(int i = 0; i < 3; ++i) {
            try {
                sc = new Socket(serverIP,serverPort);
                try (PrintWriter out = new PrintWriter(sc.getOutputStream(),true)) {
                    out.println(id.toString());
                    out.println("done");
                    out.println(result);
                    return true;
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    try {
                        sc.close();
                    } catch (IOException e) {
                        System.out.println("cant close socket");
                        e.printStackTrace();
                    }
                }

            } catch (IOException e) {
                System.out.println("Cant connect to server");
                try {
                    Thread.currentThread().sleep(Constant.RECONNECTION_TIME);
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                }
                e.printStackTrace();
            }
        }
        return false;
    }

    @Override
    public void run() {
        while(alive) {
            BruteData handler = getRange();
            if(tries == 3){
                System.out.println("cant connect ot server!");
                alive = false;
            }else{
                if(handler != null) {
                    String result = bruteforce(handler.getStart(), handler.getEnd(), handler.getHash());
                    if(result != null){
                        if(sendResult(result)){
                            break;
                        } else{
                            System.out.println("Cant send data to server. ERROR!!");
                        }
                    }
                }
            }

        }
    }

    private String bruteforce(String start, String end, byte[] hash) {
        try {
            MessageDigest MD5Counter = MessageDigest.getInstance("MD5");
            WordGenerator wordGenerator = new WordGenerator(start);
            while(!wordGenerator.getWord().equals(end))
            {
                byte [] temphash = MD5Counter.digest(wordGenerator.getWord().getBytes(Charset.forName("UTF-8")));
                if (Arrays.equals(hash, temphash))
                {
                    System.out.println("Success");
                    return wordGenerator.getWord();
                }
                wordGenerator.increment();
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        System.out.println("Didn't find in current range ");
        return null;
    }


    public static void main(String[] args) {
        try {
            Client client = new Client(InetAddress.getByName("172.16.17.191"),14202);
            client.run();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
