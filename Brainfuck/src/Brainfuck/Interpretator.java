package Brainfuck;

import Brainfuck.command.Factory;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Brainfuck Interpretator
 */
public final class Interpretator {
    private static Logger log = LogManager.getLogger(Interpretator.class.getName());

    private Tape tape;
    private Parser parser;
    private Factory factory;
    private static final String pathToConfig = "Brainfuck/commands.config";
    private boolean flag;

    /**
     * Construct Brainfuck Interpretator
     * @param _tape Turing tape
     * @param _parser parse string
     */
    public Interpretator(Tape _tape, Parser _parser){
        log.trace("Construct Interpretator");
        tape = _tape;
        parser = _parser;
        factory = new Factory(pathToConfig);
    }

    /**
     * run brainfuck code
     */
    public void run(){
        flag = true;
        while(parser.isEnd() && flag){
            factory.get(parser.getCommand()).execute(tape, this);
        }
    }

    /**
     * stop if find close bracket
     */
    public void stop() {
        flag = false;
    }

    /**
     * call SubInterpretator to run cycle Brainfuck  code
     */
    public void callSubInt() {
        try{
            int endPos = parser.findClosingBracket();
            log.trace("Endpos = " + endPos);
            int startPos = parser.getPosition();
            log.trace("Startpos = " + startPos);
            Interpretator sub = new Interpretator(tape, parser);
            while(tape.getValue() != 0){
                parser.movePointerTo(startPos);
                sub.run();
            }
            parser.movePointerTo(endPos + 1);
        }
        catch(RuntimeException e){
            log.error(e);
            e.printStackTrace();
        }

    }
}
