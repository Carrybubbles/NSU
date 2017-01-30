package nodes;

import console.ConsoleThread;
import constants.Constants;
import controllers.MessageController;
import controllers.PackageLossController;
import javafx.util.Pair;
import messages.Message;
import messages.MessageType;

import java.io.IOException;
import java.net.*;
import java.sql.SQLOutput;
import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;


public class Node implements Runnable {
    private String name = null;
    private DatagramSocket ds = null;
    private Pair<Integer,InetAddress> self = null;
    private Pair<Integer,InetAddress> parent = null;
    private List<Pair<Integer, InetAddress>> children = new ArrayList<>();


    private PackageLossController lossController = null;
    private MessageController msgController = null;
    private boolean isalive = true;
    private boolean root = false;
    private ConsoleThread thread = null;
    private List<Message> havingMessages = new LinkedList<>();
    private Queue<Message> messagesQueue = new ConcurrentLinkedQueue<>();


    public Node(String name, int port, InetAddress IP, int parentPort, InetAddress parentIP, int loss) throws IOException {
        this.name = name;
        this.self = new Pair<>(port,IP);
        this.ds = new DatagramSocket(port);
        this.parent = new Pair<>(parentPort,parentIP);
        this.ds.setSoTimeout(100);
        this.thread = new ConsoleThread(messagesQueue,name);
        this.msgController = new MessageController(ds);
        this.lossController = new PackageLossController(loss);
        this.messagesQueue.add(new Message("Hello",name, MessageType.HELLO,parentPort,parentIP, Message.Status.SEND));

    }

    public Node(String name, int port, InetAddress IP, int loss) throws SocketException {
        this.name = name;
        this.self = new Pair<>(port,IP);
        this.ds = new DatagramSocket(port);
        this.ds.setSoTimeout(100);
        this.root = true;
        this.thread = new ConsoleThread(messagesQueue,name);
        this.msgController = new MessageController(ds);
        this.lossController = new PackageLossController(loss);
    }


    private void addChild(Message msg){
        children.add(msg.getDestination());
    }

    private Pair findAliveChild(Pair<Integer,InetAddress> from){
        for(Pair cur : children){
            if(!cur.equals(from)){
                return cur;
            }
        }
        return null;
    }

    private void removeDeadNodes(List<Pair<Integer,InetAddress>> dead){
        for(Pair cur: dead){
            if(children.remove(cur)){
                System.out.println("Remove: " + cur);

            }
        }
        for(Pair cur: dead){
            if(parent != null) {
                if (cur.equals(parent)) {
                    System.out.println("Remove parent");
                    parent = null;
                    return;
                }
            }
        }
    }

    private void doStep(Message msg) {
        //loss packages

        if(Message.Status.REC.equals(msg.getStat())){
            if(!lossController.isPackAlive()){
                System.out.println("lost package!");
                return;
            }
        }

        //RECEIVE
        if (Message.Status.REC.equals(msg.getStat())) {

            if (msg.getMsgType().equals(MessageType.HELLO)) {
                addChild(msg);
                try {
                    msgController.sendMessage(new Message(msg.getMsg(), msg.getNodeName(), MessageType.ACCEPT, msg.getId(), msg.getDestination(), Message.Status.SEND));
                } catch (IOException e) {
                    e.printStackTrace();
                }
                System.out.println("ADD CHILDREN");
            } else if (msg.getMsgType().equals(MessageType.MESSAGE)) {
                if(parent == null && !root) {
                    System.out.println("OH MY GOD!MY PARENT IS ALIVE!!!");
                    parent = msg.getDestination();
                }
                if(!alreadyHaveIt(msg)){
                    System.out.println(msg.getNodeName() + " : " + msg.getMsg());
                }
                try {
                    msgController.sendMessage(new Message(msg.getMsg(), msg.getNodeName(), MessageType.ACCEPT, msg.getId(), msg.getDestination(), Message.Status.SEND));
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (!children.isEmpty() || parent != null) {
                    messagesQueue.add(new Message(msg.getMsg(), msg.getNodeName(), MessageType.MESSAGE, msg.getId(), msg.getDestination(), Message.Status.SEND));
                }

            } else if (msg.getMsgType().equals(MessageType.KILL)) {
                try {
                    msgController.sendMessage(new Message(msg.getMsg(), msg.getNodeName(), MessageType.ACCEPT, msg.getDestination(), Message.Status.SEND));
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if(!children.remove(msg.getDestination())){
                    parent = null;
                }
                Pair<Pair<Integer, InetAddress>,String> info = msgController.parseKillMessage(msg);
                Pair<Integer, InetAddress> parentAddress = info.getKey();
                String boss = info.getValue();
                if(boss.equals("root")){
                    root = true;
                }
                //if not me
                if (!parentAddress.equals(self)) {
                    parent = parentAddress;
                    messagesQueue.add(new Message("Hello", name, MessageType.HELLO, parentAddress.getKey(), parentAddress.getValue(), Message.Status.SEND));
                }
            }else if(msg.getMsgType().equals(MessageType.ACCEPT)){
                deleteHavingMessage(msg.getId());
            }
            //SEND
        }else if(Message.Status.SEND.equals(msg.getStat())){
            havingMessages.add(msg);
            if(msg.getMsgType().equals(MessageType.HELLO)) {
                try {
                    msgController.sendMessage(msg);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }else if (msg.getMsgType().equals(MessageType.MESSAGE)){
                msgController.createNodesAddressTrain(children, parent, msg.getDestination());
                msgController.sendMessageToNodes(msg);

            }else if(msg.getMsgType().equals(MessageType.KILL)){
                isalive = false;
                msgController.createNodesAddressTrain(children, parent, self);
                if(parent != null){
                    msg.setMsg(parent.getKey().toString() + parent.getValue().toString());
                }else if(!children.isEmpty()){
                    Pair aliveChild = findAliveChild(msg.getDestination());
                    if(aliveChild != null){
                        msg.setMsg(aliveChild.getKey().toString() + aliveChild.getValue().toString() + "/root");
                    }
                }else{
                    return;
                }
                msgController.sendMessageToNodes(msg);
                List<Pair<Integer,InetAddress>> dead = msgController.receiveMessageFromNodes(msg);
                removeDeadNodes(dead);
            } if (msg.getMsgType().equals(MessageType.HELLO)) {
                try {
                    msgController.sendMessage(msg);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private boolean alreadyHaveIt(Message msg) {
        for (Message cur:
             havingMessages) {
            if(msg.getId().equals(cur.getId())){
                return true;
            }
        }
        return false;
    }

    private void deleteHavingMessage(UUID id) {
        Iterator<Message> it = havingMessages.iterator();
        while (it.hasNext()){
            Message cur = it.next();
            if(cur.getId().equals(id)){
                it.remove();
                return;
            }
        }
    }

    private void reSendMessages(){
        if(havingMessages.size() > 10) {
            List<Pair<Integer, InetAddress>> dead = new ArrayList<>();
            Iterator<Message> it = havingMessages.iterator();
            while(it.hasNext()) {
                Message cur = it.next();
                if (cur.getMsgType() == MessageType.MESSAGE) {
                    if (cur.getTries() == 3) {
                        dead.add(cur.getDestination());
                        it.remove();
                    } else {
                        cur.inctries();
                        messagesQueue.add(cur);
                    }
                }
            }
            removeDeadNodes(dead);
        }
    }

    @Override
    public void run(){
        thread.start();
        while(isalive){
            if(!messagesQueue.isEmpty()){
                reSendMessages();
                Message msg = messagesQueue.poll();
                doStep(msg);
            }else{
                try {
                    Message msg = msgController.receiveMessage();
                    messagesQueue.add(msg);
                } catch (IOException e) {}
            }
        }
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static void main(String[] args) {
        try {
           Node node = new Node("lol",14202, InetAddress.getByName("172.16.18.85"),50);
//           Node node = new Node("lol1",14206, InetAddress.getByName("172.16.18.85"), 14202,InetAddress.getByName("172.16.18.85"),20);
//           Node node = new Node("lol2",14209, InetAddress.getByName("172.16.18.85"), 14202,InetAddress.getByName("172.16.18.85"),30);
//            Node node = new Node("lol3",14210, InetAddress.getByName("172.16.18.85"), 14209,InetAddress.getByName("172.16.18.85"),0);
//            Node node = new Node("lol4",14211, InetAddress.getByName("172.16.18.85"), 14209,InetAddress.getByName("172.16.18.85"),50);
            node.run();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

