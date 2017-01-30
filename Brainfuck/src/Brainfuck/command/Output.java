package Brainfuck.command;

import Brainfuck.Interpretator;
import Brainfuck.Tape;

public final class Output implements Command {
    @Override
    public void execute(Tape code, Interpretator subInt) {
        System.out.print((char)code.getValue());
    }
}
