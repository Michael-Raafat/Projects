package question2;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		ExtendedEuclid e = new ExtendedEuclid();
		Scanner input = new Scanner(System.in);
		BigInteger a, n;
		System.out.println("Enter a :");
		a = input.nextBigInteger();
		System.out.println("Enter n :");
		n = input.nextBigInteger();
		if (e.isOne(n, a)) {
			System.out.print("multiplicative inverse b is ");
			System.out.println(e.euclid2(n, a,BigInteger.ONE,BigInteger.ZERO));
		}
		while (!e.isOne(n, a)) {
			System.out.println("Numbers are not relatively prime.");
			System.out.println("please enter another two numbers");
			System.out.println("Enter a :");
			a = input.nextBigInteger();
			System.out.println("Enter n :");
			n = input.nextBigInteger();
			if (e.isOne(n, a)) {
				System.out.print("multiplicative inverse b is ");
				System.out.println(e.euclid2(n, a,BigInteger.ONE,BigInteger.ZERO));
			}
		}
		
		
	}

}
