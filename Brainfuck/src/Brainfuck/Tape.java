package Brainfuck;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Brainfuck Tape(like Turing machine tape)
 */
public final class Tape {
    private static Logger log = LogManager.getLogger(Tape.class.getName());
    /**
     * max size of tape
     */
    private static final int maxSize = 30000;
    /**
     * array of cells for Brainfuck commands
     */
    private byte data[];
    /**
     * pointer in the tape
     */
    private int pointer = 0;

    /**
     * Construct Brainfuck tape
     */
    public Tape(){
        data = new byte[maxSize];
    }

    /**
     * Increment pointer
     */
    public void next(){
        pointer++;
        if(pointer >= 30000){
            pointer = 0;
        }
        log.info("Increase pointer. Pointer = " + pointer);
    }

    /**
     * Decrement pointer
     */
    public void prev() {
        pointer--;
        if(pointer < 0){
            pointer = 29999;
        }
        log.trace("Decrease pointer. Pointer = " + pointer);
    }

    /**
     * Increment data by one in the current cell(point to it)
     */
    public void inc() {
        data[pointer]++;
        log.trace("Increase data value by one: Pointer =  " + pointer +  "data = " + data[pointer]);
    }

    /**
     * Decrement data by one in the current cell(point to it)
     */
    public void dec(){
        data[pointer]--;
        log.trace("Decrease data value by one. Pointer = " + pointer + " Data = " + data[pointer]);
    }

    /**
     * Get value of current cell( Value = ASCII code)
     * @return byte
     */
    public byte getValue(){
        log.trace("Value of current cell = " + data[pointer]);
        return data[pointer];
    }

    /**
     * Set value to current cell
     * @param value ASCII symbol
     */
    public void setValue(char value){
        log.trace("Set value for current cell. Value = " + value + "Current cell = " + pointer);
        data[pointer] = (byte)value;
    }

    /**
     * get pointer position from tape
     * @return int
     */
    public int getPointer(){
        return pointer;
    }


}
