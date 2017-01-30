package Handlers;


import java.util.UUID;

/**
 * Created by artem on 19.11.16.
 */
public class TaskHandler {
    private UUID id;
    private String start = null;
    private String end  = null;
    private long  time = 0;


    public TaskHandler(UUID id, String start, String end) {
        this.id = id;
        this.start = start;
        this.end = end;
        time = System.currentTimeMillis();
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getStart() {
        return start;
    }

    public void setStart(String start) {
        this.start = start;
    }

    public String getEnd() {
        return end;
    }

    public void setEnd(String end) {
        this.end = end;
    }

    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }
}
