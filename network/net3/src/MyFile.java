import java.io.*;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;


public class MyFile {
    private long size = 0;
    public long curSize = 0;
    private boolean hasName = false;
    private FileChannel writer = null;
    private File file = null;

    public MyFile(){}

    public void createFile(String name) throws IOException {
        this.file = new File("uploads/" + name);
        if(!file.exists()) {
            file.getParentFile().mkdirs();
            file.createNewFile();
        }
        this.writer = new FileOutputStream(file).getChannel();
    }
    public void printBytesToFile(ByteBuffer buffer) throws IOException {
        if(writer != null) {
            buffer.flip();
            writer.write(buffer);
        }
    }
    public String getFileName(){
        return  file.getName();
    }
    public void setSize(long size) {
        this.size = size;
    }

    public void setHasName(boolean hasName) {
        this.hasName = hasName;
    }

    public boolean isEnd(){
        return size == curSize;
    }

    public void deleteFile() throws IOException {
        file.getParentFile().delete();
        file.delete();
        writer.close();
    }

    public boolean isHasName() {
        return hasName;
    }
}
