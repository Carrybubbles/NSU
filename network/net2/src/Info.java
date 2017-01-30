import java.nio.ByteBuffer;

/**
 * Created by artem on 02.10.16.
 */
public class Info {
    private long connectionTime;
    private long endTime;
    private long dataSize;
    private int tries = 0;

    public Info(long connectionTime, long endTime, long dataSize ){
        this.connectionTime = connectionTime;
        this.endTime = endTime;
        this.dataSize = dataSize;
    }

    public void setStartTime(long  time){
        this.connectionTime = time;
    }

    public long startTime(){
        return  connectionTime;
    }

    public void setEndTime(long endTime) {
        this.endTime = endTime;
    }

    public long getEndTime() {
        return endTime;
    }

    public long getDataSize() {
        return dataSize;
    }

    public void addData(long dataSize) {
        this.dataSize += dataSize;
    }

    public void deleteData(){
        this.dataSize = 0;
    }

    public void incTries(){
        this.tries++;
    }

    public int getTries() {
        return tries;
    }
}
