
import Brainfuck.Tape;
import org.junit.Test;

import static org.junit.Assert.*;

public class TapeTest {

    @Test
    public void testNext() throws Exception {
        Tape tape = new Tape();
        tape.next();
        assertEquals(1,tape.getPointer());
    }

    @Test
    public void testPrev() throws Exception {
        Tape tape = new Tape();
        tape.prev();
        assertEquals(29999, tape.getPointer());
    }

    @Test
    public void testInc() throws Exception {
        Tape tape = new Tape();
        tape.inc();
        assertEquals(1, tape.getValue());
    }

    @Test
    public void testDec() throws Exception {
        Tape tape = new Tape();
        tape.dec();
        assertEquals(-1, tape.getValue());
    }


    @Test
    public void testSetValue() throws Exception {
        Tape tape = new Tape();
        tape.setValue('a');
        assertEquals('a',tape.getValue());
    }
}