package controllers;

import javafx.util.Pair;

import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * Created by artem on 09.11.16.
 */
public class NodeController {
    private Map<Pair<Integer,InetAddress>,Integer> affermation = null;
    private List<Pair<Integer,InetAddress>> deadNodes = new ArrayList<>();

    public List<Pair<Integer, InetAddress>> getDeadNodes() {
        return deadNodes;
    }

    public void setDeadNodes(List<Pair<Integer, InetAddress>> deadNodes) {
        this.deadNodes = deadNodes;
    }


    public Map<Pair<Integer, InetAddress>, Integer> getAffermation() {
        return affermation;
    }

    public void setAffermation(Map<Pair<Integer, InetAddress>, Integer> affermation) {
        this.affermation = affermation;
    }



    public NodeController(List<Pair<Integer,InetAddress>> nodes){
        initMapWithNodes(nodes);
    }

    public List<Pair<Integer,InetAddress>> getAliveNodes(){
        return affermation.entrySet().stream().map(Map.Entry<Pair<Integer, InetAddress>, Integer>::getKey).collect(Collectors.toList());
    }



    private void initMapWithNodes(List<Pair<Integer, InetAddress>> nodes){
        affermation = new HashMap<>();
        for(Pair<Integer, InetAddress> cur: nodes){
            affermation.put(cur,0);
        }
    }

    public void removeNode(Pair<Integer,InetAddress> node){
        affermation.remove(node);
    }

    public void incrTries(){
        for (Map.Entry<Pair<Integer, InetAddress>, Integer> cur : affermation.entrySet()) {
            Integer tr = cur.getValue();
            cur.setValue(++tr);
        }
    }

    public  void removeDeadnodes(){
        for (Map.Entry<Pair<Integer, InetAddress>, Integer> cur : affermation.entrySet()) {
            Integer tr = cur.getValue();
            if(3 == tr){
                Pair<Integer,InetAddress> addr = cur.getKey();
                deadNodes.add(addr);
            }
        }
        for(Pair cur: deadNodes){
            affermation.remove(cur);
        }
    }

}
