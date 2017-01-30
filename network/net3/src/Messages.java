import java.nio.ByteBuffer;
import java.nio.charset.Charset;

/**
 * Created by artem on 02.10.16.
 */
public class Messages {
    public static ByteBuffer makeInfoMsg(String pathTofile, long sizeOfFile){
        byte[] bpath = pathTofile.getBytes();
        ByteBuffer buffer = ByteBuffer.allocate(bpath.length + Long.BYTES);
        buffer.putLong(sizeOfFile);
        buffer.put(bpath);
        return buffer;
    }
    public static String getNameOfFile(ByteBuffer buffer){
        byte[] bName = new byte[buffer.capacity() - buffer.remaining() - Long.BYTES];
        buffer.position(Long.BYTES);
        buffer.get(bName,0,bName.length);
        return new String(bName, Charset.forName("UTF-8"));
    }

    public static long getSizeOfFile(ByteBuffer buffer){
        buffer.position(0);
        return  buffer.getLong();
    }
}
