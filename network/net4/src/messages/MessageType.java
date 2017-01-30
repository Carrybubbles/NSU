package messages;

/**
 * Created by artem on 01.11.16.
 */
public enum MessageType {
    HELLO(0) ,ACCEPT(1),MESSAGE(2),KILL(3),PARENT(4);
    static final MessageType[] arr = new MessageType[]{HELLO,
                                                 ACCEPT,
                                                 MESSAGE,
                                                 KILL,
                                                 PARENT};

    
    private final int code;
    MessageType(int i) {
        this.code = i;
    }

    public int getCode(){
        return code;
    }

    public static MessageType getTypeMessage(byte msg){
        return arr[msg];
    }

    public byte getTypeMessageAsByte(){
        return (byte) code;
    }

}
