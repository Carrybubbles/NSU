package Brainfuck.command;

import Brainfuck.Interpretator;
import Brainfuck.Tape;

public final class EndLoop implements Command {
    @Override
    public void execute(Tape code, Interpretator subInt) {
        subInt.stop();
    }
}
