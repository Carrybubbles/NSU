package Brainfuck;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.Objects;
import java.util.Properties;;

/**
 * Work with input Brainfuck code(string)
 */
public final class Parser {
    private static Logger log = LogManager.getLogger(Interpretator.class.getName());
    /**
     * Brainfuck code
     */
    private String code;
    /**
     * Pointer set to the current symbol in Brainfuck code
     */
    private int pointer = 0;
    /**
     * Check commands in the tape
     */
    private Properties config = new Properties();
    /**
     * Path to config file
     */
    private static final String configPath = "Brainfuck/commands.config";

    /**
     * Construct Parser
     * @param curCode code of Brainfuck
     */
    public Parser(String curCode) {
        if(log.isDebugEnabled()){
            log.debug("current code = " + code);
        }
        code = curCode;
        log.trace("Construct parser");
        try (InputStream file = ClassLoader.getSystemResourceAsStream(configPath)) {
            config.load(file);
        } catch (IOException e) {
            log.error(e);
            //System.err.println("Cant open config file!");
            throw new RuntimeException(e);
        }
    }

    /**
     * Get length of Brainfcuk code
     * @return int
     */
    public int size() {
        log.trace("returs size = " + code.length() );
        return code.length();
    }

    /**
     * Get current command from tape and increment pointer by one
     * @return char
     */
    public char getCommand() {
        //log.info("current command = " + code.charAt(pointer + 1));
        return code.charAt(pointer++);
    }

    /**
     * Check place of pointer in the tape.If pointer greater then  length of code return false else true
     * @return true of false
     */
    public boolean isEnd() {
        log.trace("Code is END??" + (pointer < code.length()));
        return pointer < code.length();
    }

    /**
     * move pointer to certain cell in the tape
     * @param index Number of cell in the tape
     */
    public void movePointerTo(int index) {
        log.trace("Move to" + index);
        pointer = index;
    }

    /**
     * get pointer position in the cell
     * @return int
     */
    public int getPosition() {
        log.trace("get cur pos " + pointer);
        return pointer;
    }

    /**
     * Find position of closing bracket in current cycle
     * @return position in the tape
     * @throws java.lang.RuntimeException
     */
    public int findClosingBracket() {
        int count = 0;
        for (int i = pointer; i < size(); i++) {
            if(isOpenBracket(code.charAt(i))){
                count++;
            }else if(isCloseBracket(code.charAt(i))){
                if(0 == count){
                    return i;
                }
                else{
                    count--;
                }
            }
        }
        if(log.isDebugEnabled()){
            log.debug("Cant find closing bracket");
        }
        throw new RuntimeException();
    }

    public boolean isBrainFuckCode(){
        log.trace("Check input code ");
        for(int i = 0; i < code.length(); i++){
            if(!isBrainFuckCommand(getCommand())){
                return false;
            }
        }
        movePointerTo(0);
        return true;
    }
    private boolean isOpenBracket(char command){
        Object loop = config.getProperty(String.valueOf(command));
        return Objects.equals(loop.toString(), "Brainfuck.command.StartLoop");
    }

    /**
     * check close bracket
     * @param command current Brainfuck command
     * @return boolean
     */
    private boolean isCloseBracket(char command){
        Object loop = config.getProperty(String.valueOf(command));
        return Objects.equals(loop.toString(), "Brainfuck.command.EndLoop");

    }
    /**
     * belong to brainfuck commands or not
     * @param command curernt Brainfuck command
     * @return boolean
     */
    private boolean isBrainFuckCommand(Character command){
        return config.containsKey(String.valueOf(command));
    }
}

