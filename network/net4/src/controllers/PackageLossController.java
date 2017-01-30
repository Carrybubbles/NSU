package controllers;

import java.time.LocalTime;
import java.util.Random;

/**
 * Created by artem on 09.11.16.
 */
public class PackageLossController {
    private int loss = 50;
    private final Random rand = new Random(LocalTime.now().getSecond());
    public PackageLossController(int loss){
        this.loss = loss;
    }

    public boolean isPackAlive(){
        return Math.abs(rand.nextInt() % 100)  >= loss;
    }
}
