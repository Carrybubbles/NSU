package controllers;

import constants.Constants;
import javafx.util.Pair;
import messages.Message;
import messages.MessageType;

import java.io.IOException;
import java.net.*;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Created by artem on 01.11.16.
 */
public class MessageController {
    private DatagramSocket ds = null;
    private List<Pair<Integer, InetAddress>> nodes = null;


    public MessageController(DatagramSocket ds){
        this.ds = ds;
    }

    public Message receiveMessage() throws IOException {
        DatagramPacket packet = new DatagramPacket(new byte[Message.MAX_PACKET_SIZE],Message.MAX_PACKET_SIZE );
        ds.receive(packet);
        return new Message(packet.getData(), packet.getPort(), packet.getAddress(), Message.Status.REC);
    }


    public Pair<Pair<Integer, InetAddress>,String> parseKillMessage(Message msg){
        String[] info = msg.getMsg().split("/");
        String root = "empty";
        try {
            Pair<Integer,InetAddress> addr = new Pair<>(Integer.parseInt(info[0]) ,InetAddress.getByName(info[1]));
            if(info.length == 3){
                root = info[2];
            }
            return  new Pair<>(addr,root);
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        return null;
    }


    public List<Pair<Integer,InetAddress>> receiveMessageFromNodes(Message sendmsg){
        NodeController killer = new NodeController(nodes);
        int i = 0;
        while(!killer.getAffermation().isEmpty()) {
            try {
                ds.setSoTimeout(100);
                Message msg = receiveMessage();
                if (msg.getMsgType().equals(MessageType.ACCEPT)) {
                    killer.getAffermation().remove(msg.getDestination());
                }
            } catch (IOException e) {
                killer.incrTries();
                killer.removeDeadnodes();
                System.out.println("Don't catch ACCEPT message from nodes");
                System.out.println("Resending messages " + ++i);
                createNodesAddressTrain(killer.getAliveNodes());
                sendMessageToNodes(sendmsg);
            }
        }
        try {
            ds.setSoTimeout(Constants.RECEIVE_TIMEOUT);
        } catch (SocketException e) {
            e.printStackTrace();
        }
        return  killer.getDeadNodes();
    }

    private void createNodesAddressTrain(List<Pair<Integer, InetAddress>> aliveNodes) {
        nodes = new ArrayList<>();
        nodes.addAll(aliveNodes.stream().collect(Collectors.toList()));
    }

    public void createNodesAddressTrain(List<Pair<Integer,InetAddress>> children, Pair<Integer,InetAddress> parent, Pair<Integer,InetAddress> fromNode){
        nodes = new ArrayList<>();
        if(parent != null){
            if(!parent.equals(fromNode)) {
                nodes.add(parent);
            }
        }
        nodes.addAll(children.stream().filter(cur -> !cur.equals(fromNode)).collect(Collectors.toList()));
    }

    public void sendMessageToNodes(Message msg) {
        for (Pair<Integer, InetAddress> cur : nodes) {
            try {
                msg.setDestination(cur);
                sendMessage(msg);
            } catch (IOException e) {
                System.out.println("cant send packet to " + cur.getValue() + cur.getKey());
                e.printStackTrace();
            }
        }

    }

    public void sendMessage(Message msg) throws IOException {
        if(msg.getDestination() != null) {
            byte[] data = msg.getMessageAsBytes();
            DatagramPacket packet = new DatagramPacket(data, data.length);
            packet.setAddress(msg.getDestination().getValue());
            packet.setPort(msg.getDestination().getKey());
            ds.send(packet);
        }
    }



}
