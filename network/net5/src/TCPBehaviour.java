import java.net.InetAddress;

/**
 * Created by artem on 02.12.16.
 */
public interface TCPBehaviour {
    void listen();
    void close();
    void connect(InetAddress address, String port);
    void send(byte[] buffer, int size);
    int recv(byte[] buffer);
    void accept();
}
