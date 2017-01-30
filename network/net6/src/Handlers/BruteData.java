package Handlers;

/**
 * Created by artem on 20.11.16.
 */
public class BruteData {
    private byte[] hash = null;
    private String start = null;
    private String end = null;

    public BruteData(String start, String end, byte[] hash) {
        this.hash = hash;
        this.start = start;
        this.end = end;
    }

    public byte[] getHash() {
        return hash;
    }

    public void setHash(byte[] hash) {
        this.hash = hash;
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
}
