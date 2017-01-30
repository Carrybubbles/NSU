package Brainfuck.command;

import Brainfuck.Interpretator;
import Brainfuck.Tape;


public final class Decrement implements Command {
    @Override
    public void execute(Tape code, Interpretator subInt) {
        code.prev();
    }
}
