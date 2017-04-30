package question3;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

import question2.ExtendedEuclid;

public class Main {

	static Mapping mapFromAToAMulti = new Mapping();
	static ReverseMapping mapFromAMultiToA = new ReverseMapping();
	public static void main(String[] args) {

		ArrayList<BigInteger> m = new ArrayList<BigInteger>();
		Scanner input = new Scanner(System.in);
		int k = 0;
		System.out.println("Enter number of elements of M (k) :");
		k = input.nextInt();
		System.out.println("Enter each element of M separated by space :");
		
		for (int i = 0; i < k; i++) {
			m.add(input.nextBigInteger());
		}
		input = new Scanner(System.in);
		System.out.println("Enter elements of A separated by space  :");
		ArrayList<BigInteger> a = new ArrayList<BigInteger>();
		for (int i = 0; i < k; i++) {
			a.add(input.nextBigInteger());
		}
		input = new Scanner(System.in);
		System.out.println("Enter each element of B separated by space :");
		ArrayList<BigInteger> b = new ArrayList<BigInteger>();
		for (int i = 0; i < k; i++) {
			b.add(input.nextBigInteger());
		}
		System.out.println("Answer of A is " + mapFromAMultiToA.mapToA(a, m));
		System.out.println("Answer of method that map from A to (a1,a2...ak) is " + mapFromAToAMulti.mapMultiA(mapFromAMultiToA.mapToA(a, m), m));
		System.out.println("Answer of B is " + mapFromAMultiToA.mapToA(b, m));
		System.out.println("Answer of method that map from B to (b1,b2...bk) is " + mapFromAToAMulti.mapMultiA(mapFromAMultiToA.mapToA(b, m), m));
		input = new Scanner(System.in);
		long start = System.nanoTime();
		System.out.println("Answer of addition first way : " + mapFromAMultiToA.additionZMDomain(a,b,m));
		System.out.println("Time Taken is " + (System.nanoTime() - start) + " Nanoseconds");
		start = System.nanoTime();
		System.out.println("Answer of addition second way : " + mapFromAMultiToA.additionZmiDomain(a,b,m));
		System.out.println("Time Taken is " + (System.nanoTime() - start)  + " Nanoseconds");
		start = System.nanoTime();
		System.out.println("Answer of multiplicaton first way : " + mapFromAMultiToA.multiplicationZMDomain(a,b,m));
		System.out.println("Time Taken is " + (System.nanoTime() - start)+ " Nanoseconds");
		start = System.nanoTime();
		System.out.println("Answer of multiplication second way : " + mapFromAMultiToA.multiplicationZmiDomain(a,b,m));
		System.out.println("Time Taken is " + (System.nanoTime() - start)+ " Nanoseconds");
	}
	
	
		
}
