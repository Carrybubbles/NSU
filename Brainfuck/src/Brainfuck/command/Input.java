package Brainfuck.command;
;

import Brainfuck.Interpretator;
import Brainfuck.Tape;

import java.io.IOException;
import java.io.InputStreamReader;

public final class Input implements Command {

    @Override
    public void execute(Tape code, Interpretator subInt) {
        try{
            code.setValue((char) System.in.read());
        }catch (IOException e){
            System.out.print("Cant set value!");
            e.printStackTrace();
        }
    }
}
