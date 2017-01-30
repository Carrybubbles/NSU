package mypackage;

import java.util.*;
import java.lang.Exception;

public class Stack{
	private ArrayList<Integer> array = new ArrayList<Integer>();

	public Stack(){
	}
	public void push(int element){
		array.add(element);
	}

	public int top(){
		try{
			return array.get(array.size() - 1);
		}catch(IndexOutOfBoundsException  e){
			e.printStackTrace();
		}
		return 0;
	}	

	public void pop(){
		array.remove(array.size() - 1);
	}

	public int size(){
		return array.size();
	}

	public boolean empty(){
		return array.isEmpty();
	}

	public static void main(String[] argc){

		Stack lol = new Stack();
		lol.push(2);
		lol.push(4);
		System.out.println(lol.top());
		lol.pop();
		System.out.println(lol.top());
	}


}