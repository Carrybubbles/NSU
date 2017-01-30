
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Iterator;

public class Server {
    private static final int SERVER_PORT = 5051;
    private static final int SIZE_OF_NAME_FILE = 4096;
    public static final int SIZE_OF_BUFFER = 1024*1024;
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

    public void run() {
            for (; ; ) {
                try {
                    selector.select();
                } catch (IOException e) {
                    System.out.println("error");
                    e.printStackTrace();
                }
                Iterator it = selector.selectedKeys().iterator();
                while (it.hasNext()) {
                    SelectionKey key = (SelectionKey) it.next();
                    MyFile inInfo = (MyFile) key.attachment();
                    it.remove();
                    if (key.isAcceptable()) {
                        try {
                            sc = ssc.accept();
                            System.out.println("accept connection from" + sc.getRemoteAddress());
                            sc.configureBlocking(false);
                            sc.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE, new MyFile());
                        } catch (IOException e) {
                            System.out.println("Cant connect");
                            e.printStackTrace();
                        }
                    } else if (key.isReadable() && key.attachment() instanceof MyFile) {
                        try {
                            sc = (SocketChannel) key.channel();
                            if (!inInfo.isHasName()) {
                                ByteBuffer buf = ByteBuffer.allocate(SIZE_OF_NAME_FILE + Long.BYTES);

                                if(sc.read(buf) < 0){
                                    System.out.println("cant get name of file");
                                    sc.close();
                                }else{
                                    inInfo.setHasName(true);
                                    inInfo.createFile(Messages.getNameOfFile(buf));
                                    inInfo.setSize(Messages.getSizeOfFile(buf));
                                    sc.write(ByteBuffer.wrap(new byte[]{0x1}));
                                }
                            } else {
                                ByteBuffer buf = ByteBuffer.allocate(SIZE_OF_BUFFER);
                                int size = sc.read(buf);
                                if(size >= 0){
                                    inInfo.curSize += size;
                                    inInfo.printBytesToFile(buf);
                                    if(inInfo.isEnd()){
                                        System.out.println("File " +  inInfo.getFileName() +" was saved in uploads dir");
                                        sc.write(ByteBuffer.wrap(new byte[]{0x2}));
                                        sc.close();
                                    }
                                }else{
                                    if(!inInfo.isEnd()) {
                                        System.out.println("Cant get bytes");
                                        inInfo.deleteFile();
                                    }
                                    sc.close();
                                }
                            }
                        } catch (IOException e) {
                            try {
                                inInfo.deleteFile();
                                sc.close();
                            } catch (IOException ignored) {}
                        }
                    }
                }

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
