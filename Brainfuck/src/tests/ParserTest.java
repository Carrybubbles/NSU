
import Brainfuck.Parser;
import org.junit.Test;

import static org.junit.Assert.*;

public class ParserTest {

    @Test
    public void testSize() throws Exception {
        Parser parser = new Parser("+++-++--++");
        assertEquals(10,parser.size());
    }

    @Test
    public void testGetCommand() throws Exception {
        Parser parser = new Parser("+++-++--++");
        assertEquals('+',parser.getCommand());
    }

    @Test
    public void testIsEnd() throws Exception {
        Parser parser = new Parser("+++-++--++");
        assertTrue(parser.isEnd());
        parser.movePointerTo(11);
        assertFalse(parser.isEnd());
    }

    @Test
    public void testMoveTo() throws Exception {
        Parser parser = new Parser("+++-++--++");
        parser.movePointerTo(5);
        assertEquals(5,parser.getPosition());
    }

    @Test
    public void testIsBrainFuck() throws Exception {
        Parser parser = new Parser("+++-++--++");
        assertTrue(parser.isBrainFuckCode());
        Parser parser2 = new Parser("cv+++-++--++");
        assertFalse(parser2.isBrainFuckCode());
    }

    @Test
    public void testFindClosingBracket() throws Exception{
        Parser parser = new Parser("++]+-++--]++");
        assertEquals(2,parser.findClosingBracket());
        parser.movePointerTo(5);
        assertEquals(9, parser.findClosingBracket());


    }
    @Test(expected = RuntimeException.class)
    public void testException(){
        Parser parser2 = new Parser("+[++-++--++");
        parser2.findClosingBracket();
    }
}