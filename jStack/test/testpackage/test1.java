package testpackage;

import org.junit.Test;
import static org.junit.Assert.*;
import mypackage.*;

public class test1{
	@Test
	public void testPush(){
		Stack stack = new Stack();
		stack.push(1);
		assertEquals(stack.top(), 1);
	}
	@Test
	public void testSize(){
		Stack stack = new Stack();
		stack.push(1);
		stack.push(1);
		stack.push(1);
		assertEquals(3, stack.size());
	}
	@Test
	public void testEmpty(){
		Stack stack = new Stack();
		assertTrue(stack.empty());
		stack.push(1);
		assertFalse(stack.empty());
	}
	@Test
	public void testPop(){
		Stack stack = new Stack();
		stack.push(1);
		stack.pop();
		assertTrue(stack.empty());
	}
}