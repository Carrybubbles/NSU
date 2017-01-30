
import Brainfuck.Interpretator;
import Brainfuck.Parser;
import Brainfuck.Tape;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.Assert.*;

public class InterpretatorTest {

    @Test
    public void testRun() throws Exception {
        String Hello_world = "++++++++++[>+++++++>++++++++++>+++<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.";
        Interpretator inter = new Interpretator(new Tape(), new Parser(Hello_world));


        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);
        PrintStream old = System.out;
        System.setOut(ps);
        inter.run();
        System.out.flush();
        System.setOut(old);

        assertEquals("Hello World!",baos.toString());
    }

}