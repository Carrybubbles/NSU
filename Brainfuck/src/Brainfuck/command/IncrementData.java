
/**
 * Created by artem on 25.02.16.
 */
package Brainfuck.command;


import Brainfuck.Interpretator;
import Brainfuck.Tape;

public final class IncrementData implements Command {
    @Override
    public void execute(Tape tape, Interpretator subInt) {
        tape.inc();
    }
}
