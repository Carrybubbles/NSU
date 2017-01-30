import java.io.IOException;
import java.net.*;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static final long LATENCY = 5000;
    public static final long SEND_LATENCY = 2000;
    public static final long ALIVE_TIME = 10000;
    public static final long SHOW_LATANCY = 5000;
    public static final String BROADIP = "255.255.255.255";

    public static void main(String[] args) {

        Map<InetAddress,Long> mapa = new HashMap<>();
        byte[] sendData = new byte[1024];
        sendData[0] = 1;
        byte[] receiveData = new byte[1024];

        try {
            DatagramSocket socket = new DatagramSocket(14202);
            DatagramPacket sendPacket = new DatagramPacket(sendData,sendData.length);
            DatagramPacket recievePacket = new DatagramPacket(receiveData, receiveData.length);

            socket.setBroadcast(true);
            sendPacket.setAddress(InetAddress.getByName(BROADIP));
            sendPacket.setPort(14202);
            socket.setSoTimeout((int) LATENCY);
            long sendTime = System.currentTimeMillis();
            socket.send(sendPacket);
            long showtime = System.currentTimeMillis();
            for(;;) {
                if(System.currentTimeMillis() - showtime > SHOW_LATANCY) {
                    for (Map.Entry<InetAddress, Long> pair : mapa.entrySet()) {
                        showtime = System.currentTimeMillis();
                        if (System.currentTimeMillis() - pair.getValue() < ALIVE_TIME) {
                            System.out.println(pair.getKey() + " is alive");
                        } else {
                            mapa.remove(pair);
                        }
                    }
                }
                long curTime = System.currentTimeMillis();
                if(curTime - sendTime > SEND_LATENCY ) {
                    socket.send(sendPacket);
                    sendTime = curTime;
                }
                try {
                    socket.receive(recievePacket);
                    long recieveTime = System.currentTimeMillis();
                    InetAddress curAddr = recievePacket.getAddress();
                    mapa.put(curAddr, recieveTime);

                }catch (SocketTimeoutException ignored){}
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}