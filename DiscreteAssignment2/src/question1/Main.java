package question1;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	private static Scanner input;

	public static void main(String[] args) {
		input = new Scanner(System.in);
		Methods method;
		System.out.println("Enter a:");
		BigInteger a = input.nextBigInteger();
		System.out.println("Enter b :");
		BigInteger b = input.nextBigInteger();
		System.out.println("Enter n :");
		BigInteger n = input.nextBigInteger();
		method = new FirstMethod();
		double start = System.nanoTime();
		System.out.println("First Answer is " + method.solve(a, b, n));
		System.out.println("Time Taken is " + (System.nanoTime() - start) + " Milliseconds");
		method = new SecondMethod();
		start = System.nanoTime();
		System.out.println("Second Answer is " + method.solve(a, b, n));
		System.out.println("Time Taken is " + (System.nanoTime() - start) + " Milliseconds");
		method = new ThirdMethod();
		start = System.nanoTime();
		System.out.println("Third Answer is " + method.solve(a, b, n));
		System.out.println("Time Taken is " + (System.nanoTime() - start) + " Milliseconds");
	}

}
