
import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

/**
 * Created by artem on 02.10.16.
 */
public class Client {
    private File sendingFile;
    private String nameOfFile;
    private static int SERVER_PORT = 5051;
    private static String SERVER_IP = "127.0.0.1";
    private Socket socket;
    private static final int DONE = 2;
    private static final int CONNECTED = 1;

    public Client(String pathToFile) throws IOException {
        sendingFile = new File(pathToFile);
        if (sendingFile.exists()) {
            try {
                socket = new Socket(SERVER_IP, SERVER_PORT);
                nameOfFile = pathToFile;
            } catch (IOException e) {
                System.out.println("cant connect to server");
                e.printStackTrace();
            }
        } else {
            throw new IOException();
        }
    }

    public void run(){
        try {
            OutputStream out = socket.getOutputStream();
            InputStream in = socket.getInputStream();
            System.out.println("send name");
            ByteBuffer infoBuf = Messages.makeInfoMsg(nameOfFile,sendingFile.length());
            infoBuf.flip();
            out.write(infoBuf.array());

            int flag = in.read();
            if(CONNECTED == flag){
                FileInputStream stream = new FileInputStream(sendingFile);
                while(stream.available() > 0){
                    byte[] buffer = new byte[1024*1024];
                    int size = stream.read(buffer);
                    out.write(buffer,0,size);
                }
                flag = in.read();
                if(DONE == flag) {
                    System.out.println("Done!");
                }
            }else{
                System.out.println("error1");
            }

        } catch (IOException e) {
            System.out.println("error2");
            e.printStackTrace();
        }finally {
            try {
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        try {
            Client client = new Client("/home/artem/uploads.pdf");
            client.run();
        } catch (IOException e) {
            System.out.println("Cant connect to server");
            e.printStackTrace();
        }
    }
}
