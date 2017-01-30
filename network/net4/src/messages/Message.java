package messages;

import javafx.util.Pair;
import org.jetbrains.annotations.NotNull;

import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.UUID;

/**
 * Created by artem on 26.10.16.
 */
public class Message {
    private static final int MAX_MESSAGE_SIZE = 256;
    private static final int UUID_SIZE = 16;
    public static final int MAX_PACKET_SIZE = 4098;

    private String msg = "";
    private int msgSize = 0;
    private int tries = 0;
    public String getNodeName() {
        return nodeName;
    }

    public void setNodeName(String nodeName) {
        this.nodeName = nodeName;
    }

    private String nodeName = "";
    private int nameSize = 0;
    private UUID id = null;
    private MessageType msgType = null;

    private Pair<Integer,InetAddress> destination = null;
    public enum Status{
        REC,SEND
    }
    private Status stat = null;

    public Message(String message, String nodeName, MessageType msgType, Integer parentPort, InetAddress parentIP,Status stat) {
        this.msg = message;
        this.msgSize = message.toCharArray().length;
        this.nodeName = nodeName;
        this.nameSize = nodeName.toCharArray().length;
        this.msgType = msgType;
        this.id = UUID.randomUUID();
        this.stat = stat;
        destination = new Pair<>(parentPort,parentIP);
    }

    public Message(byte[] msg, Integer port, InetAddress IP, Status stat) {
        parseBytes(msg);
        this.stat = stat;
        if(port != null && IP != null){
            destination = new Pair<>(port,IP);
        }
    }

    public Message(String message, String nodeName, MessageType msgType, Pair<Integer,InetAddress> destination, Status stat) {
        this.msg = message;
        this.msgSize = message.toCharArray().length;

        this.nodeName = nodeName;
        this.nameSize = nodeName.toCharArray().length;

        this.msgType = msgType;
        this.id = UUID.randomUUID();
        this.destination = destination;
        this.stat = stat;
    }

    public Message(String message, String nodeName, MessageType msgType, UUID id, Pair<Integer,InetAddress> destination, Status stat) {
        this.msg = message;
        this.msgSize = message.toCharArray().length;

        this.msgType = msgType;

        this.nodeName = nodeName;
        this.nameSize = nodeName.toCharArray().length;

        this.id = id;
        this.destination = destination;
        this.stat = stat;

    }

    public int getTries() {
        return tries;
    }

    public void inctries() {
        tries++;
    }

    public MessageType getMsgType() {
        return msgType;
    }

    private void parseBytes(byte[] message){
        ByteBuffer buf = ByteBuffer.wrap(message);

        long high = buf.getLong();
        long low = buf.getLong();
        this.id = new UUID(high, low);

        this.msgType = MessageType.getTypeMessage(buf.get());

        this.msgSize = buf.getInt();

        byte[] stringMessage = new byte[msgSize];
        buf.get(stringMessage);
        this.msg = new String(stringMessage,Charset.forName("UTF-8")) ;

        this.nameSize = buf.getInt();

        byte[] stringName = new byte[nameSize];
        buf.get(stringName);
        this.nodeName = new String(stringName,Charset.forName("UTF-8")) ;

    }

    public byte[] getMessageAsBytes(){
        byte[] uuid = getUUIDAsBytes();
        byte   tmsg = msgType.getTypeMessageAsByte();
        byte[] smsg = msg.getBytes(Charset.forName("UTF-8"));
        byte[] nmsg = nodeName.getBytes(Charset.forName("UTF-8"));
        ByteBuffer msize = ByteBuffer.allocate(Integer.BYTES);
        msize.putInt(msgSize);
        ByteBuffer nsize = ByteBuffer.allocate(Integer.BYTES);
        nsize.putInt(nameSize);

        ByteBuffer buffer = ByteBuffer.allocate(uuid.length+1+smsg.length + 2*Integer.BYTES + nmsg.length );
        buffer.put(uuid);
        buffer.put(tmsg);
        buffer.put(msize.array());
        buffer.put(smsg);
        buffer.put(nsize.array());
        buffer.put(nmsg);
        return buffer.array();
    }

    @NotNull
    private byte[] getUUIDAsBytes(){
        ByteBuffer buf = ByteBuffer.allocate(UUID_SIZE);
        buf.putLong(id.getMostSignificantBits());
        buf.putLong(id.getLeastSignificantBits());

        return  buf.array();
    }

    public static UUID getUUID(byte[] buffer){
        ByteBuffer buf = ByteBuffer.wrap(buffer);
        long high = buf.getLong();
        long low = buf.getLong();

        return new UUID(high,low);
    }

    public static String getMessageAsString(byte[] buffer){
        ByteBuffer buf = ByteBuffer.wrap(buffer);
        byte[] res = new byte[MAX_MESSAGE_SIZE];
        buf.position(UUID_SIZE);
        buf.get(res,0,MAX_MESSAGE_SIZE);

        return new String(res,Charset.forName("UTF-8"));
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
        this.msgSize = msg.toCharArray().length;
    }

    public Pair<Integer, InetAddress> getDestination() {
        return destination;
    }

    public void setDestination(Pair<Integer, InetAddress> destination) {
        this.destination = destination;
    }

    public Status getStat() {
        return stat;
    }

    public void setStat(Status stat) {
        this.stat = stat;
    }
}
