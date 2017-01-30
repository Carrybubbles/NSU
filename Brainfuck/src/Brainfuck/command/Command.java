/**
 * Created by artem on 19.02.16.
 */
package Brainfuck.command;


import Brainfuck.Interpretator;
import Brainfuck.Tape;

/**
 * Interface to run Brainfuck commands
 */
public interface Command {
    void execute(Tape code, Interpretator subInt);
}
