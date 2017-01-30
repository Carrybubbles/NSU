import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by artem on 02.12.16.
 */
public class TCP implements TCPBehaviour {
    Socket sc = new Socket();
    public static void main(String[] args) {

    }

    @Override
    public void listen() {

    }

    @Override
    public void close() {

    }

    @Override
    public void connect(InetAddress address, String port) {

    }

    @Override
    public void send(byte[] buffer, int size) {

    }

    @Override
    public int recv(byte[] buffer) {
        return 0;
    }

    @Override
    public void accept() {

    }
}
