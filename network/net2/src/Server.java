
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;

/**
 * Created by artem on 24.09.16.
 */
public class Server {
    public static final int ARRAY_SIZE = 1024 * 1024 ;
    public static final int SERVER_PORT = 5051;
    public static final int LATENCY = 5000;

    ServerSocketChannel ssc = null;
    Selector selector = null;
    SocketChannel sc = null;
    public Server() throws IOException {
        ssc = ServerSocketChannel.open();
        selector = Selector.open();
        ssc.configureBlocking(false);
        ssc.socket().bind(new InetSocketAddress(SERVER_PORT));
        ssc.register(selector,SelectionKey.OP_ACCEPT);
    }

    public void run(){
        try {
            long curTime = System.currentTimeMillis();
            for (;;) {
                selector.select();
                Iterator it = selector.selectedKeys().iterator();
                while (it.hasNext()) {
                    SelectionKey key = (SelectionKey) it.next();
                    it.remove();
                    if (key.isAcceptable()) {
                        sc = ssc.accept();
                        System.out.println("accept connection from" + sc.getRemoteAddress());
                        sc.configureBlocking(false);
                        sc.register(selector, SelectionKey.OP_READ, new Info(System.currentTimeMillis(),0,0));
                    } else if (key.isReadable() && key.attachment() instanceof  Info) {
                        ByteBuffer temp = ByteBuffer.allocate(ARRAY_SIZE);
                        sc = (SocketChannel) key.channel();
                        Info inInfo = (Info) key.attachment();
                        try {
                            int size = sc.read(temp);
                            if(size == 0){
                                inInfo.incTries();
                            }else if (size < 0){
                                System.out.println("lost connection");
                                sc.close();
                            }
                            if(inInfo.getTries() > 100){
                                System.out.println("lost connection");
                                sc.close();
                            }
                            inInfo.addData(size);
                            inInfo.setEndTime(System.currentTimeMillis());
                            if(System.currentTimeMillis() - curTime > LATENCY && inInfo.getEndTime() - inInfo.startTime() > 0) {
                                long sTime = inInfo.getEndTime() - inInfo.startTime();
                                long speed = 0;
                                if(sTime < 1000){
                                    speed = (inInfo.getDataSize() * 8) / sTime;
                                    System.out.println("speed of " + sc.getRemoteAddress() + " = " + speed / 1000 / 1000 + " Mb/ms");
                                }else{
                                    speed = (inInfo.getDataSize() * 8) / (sTime / 1000);
                                    System.out.println("speed of " + sc.getRemoteAddress() + " = " + speed / 1000 / 1000 + " Mb/s");
                                }
                                inInfo.deleteData();
                                inInfo.setStartTime(System.currentTimeMillis());
                                curTime = System.currentTimeMillis();
                            }
                        }catch (IOException e){
                            sc.close();
                        }
                    }
                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        try {
            Server ser = new Server();
            ser.run();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
