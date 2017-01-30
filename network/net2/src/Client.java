

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.Socket;

/**
 * Created by artem on 24.09.16.
 */
public class Client {
    static final String SERVER_IP = "127.0.0.1";
    static final int SERVER_PORT = 5051;
    public static final int ARRAY_SIZE = 1024 * 1024;
    public static void main(String[] args) {
        try {
            Socket socket = new Socket(SERVER_IP,SERVER_PORT);
            byte[] sendData = new byte[ARRAY_SIZE];

            OutputStream out = socket.getOutputStream();
            for(;;) {
                out.write(sendData);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
