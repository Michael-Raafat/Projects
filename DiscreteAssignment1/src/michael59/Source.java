package michael59;
import java.util.Arrays;
import java.util.Scanner;
import java.util.logging.Logger;
import java.util.ArrayList;
public class Source {
	    static String[] universe;
	public static void main (String args[]){
		ArrayList<String[]> all = new ArrayList<String[]>();
	    
		String set;
		Scanner input = new Scanner(System.in);
		System.out.println("Enter Your Universe Set ( elements are separated by commas ) : ");
		set = input.nextLine();
		universe = set.split(",");
		System.out.println("Enter number of sets you want : ");
		int y = input.nextInt();
		set = null;
		for(int i = 0; i < y ; i++){
			System.out.println("Enter Set " + (i+1) + " ( elements are separated by commas , print \"phi\" if set is empty ) :");
			set = input.next();
			if (set.equals("phi")){
				String[] phi = {} ;
				all.add(phi);
			}
			else if (set.length() == 1){
				String[] one = {set};
				all.add(one);
			}
			else if (!handle(set.split(","))){
				System.out.println("Invalid Set !");
				i--;
			} else {
			    all.add(set.split(","));
			}
		}
		int u;
		do{
		System.out.println("Choose any operation you want :");
		System.out.println("1. Intersection \n2. Union\n3. Complement\n4. Exit");
		u = input.nextInt();
		switch(u){
		case 1:
			System.out.println("Enter number of two sets you want (separated by comma) :");
			String come = input.next();
			String[] b = come.split(",");
			System.out.println(Arrays.toString(intersection(all.get(Integer.parseInt(b[0])-1), all.get(Integer.parseInt(b[1])-1))));
			break;
		case 2:
			System.out.println("Enter number of two sets you want (separated by comma) :");
			String go = input.next();
			String[] c = go.split(",");
			System.out.println(Arrays.toString(union(all.get(Integer.parseInt(c[0])-1), all.get(Integer.parseInt(c[1])-1))));
			break;	
		case 3:
			System.out.println("Enter number of set you want :");
			int out = input.nextInt();
			System.out.println(Arrays.toString(complement(all.get(out - 1))));
			break;
		case 4:
			break;
		default :
			System.out.print("Invalid Input");
			break;
		}
	  } while (u != 4);
		
	}
	public static String[] complement(String[] a){
		StringBuilder y = new StringBuilder();
		for ( int i = 0 ; i < universe.length ; i++){
			int x = 0;
			for (int j = 0 ; j < a.length ; j++){
				if ((universe[i].equals(a[j]))){
					j = a.length;
					x = 1;
				}
			}
			if(x == 0){
				y.append(universe[i] + ",");
			}
		}
		if(y.length() > 0){
			y.deleteCharAt(y.length()-1);
		}
		return y.toString().split(",");
	}
	public static String[] intersection(String[] a , String[] b){
		StringBuilder y = new StringBuilder();
		for ( int i = 0 ; i < a.length ; i++){
			for (int j = 0 ; j < b.length ; j++){
				if (a[i].equals(b[j])){
					y.append(a[i] + ",");
					j = b.length;
				}
			}
		}
		if(y.length() > 0){
			y.deleteCharAt(y.length()-1);
		}
		return y.toString().split(",");
	}
	public static boolean handle(String[] a){
		int rEle = 0;
		for(int i = 0; i < a.length ; i++){
			for (int j = 0; j < universe.length; j++){
				if (universe[j].equals(a[i])){
					rEle++;
					j = universe.length;
				}
			}
		}
		if (rEle == a.length){
			return true;
		}
		return false;
	}
	public static String[] union(String[] a , String[] b){
		int x = 0;
		StringBuilder y = new StringBuilder();
	    for(int o = 0; o < a.length ; o++){
	    	y.append(a[o] + ",");
	    }
	    for ( int i = 0 ; i < b.length ; i++){
			x = 0;
			for (int j = 0 ; j < a.length ; j++){
				if ((b[i].equals(a[j]))){
					j = a.length;
					x = 1;
				}
			}
			if(x == 0){
				y.append(b[i] + ",");
			}
		}
	    if(y.length() > 0){
			y.deleteCharAt(y.length()-1);
		}
		return y.toString().split(",");
	}
}
