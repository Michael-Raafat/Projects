package tabularCoreMethodes.tests;

import java.util.ArrayList;

import org.junit.Assert;
import org.junit.Test;

import tabularCoreMethodes.OuterShell;
import tabularCoreMethodes.PetricksEngine;
import tabularCoreMethodes.QuineMcCluskeyApplication;

public class QuineMcCluskeyApplicationTesting {

	@Test
	public void problem1() {
		QuineMcCluskeyApplication qm = new QuineMcCluskeyApplication();
		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(0);
		list.add(1);
		list.add(2);
		list.add(3);
		list.add(5);
		qm.setLists(list, null);
		qm.settingTable();
		qm.gettingTables();
		qm.gettingPrimes();
		Assert.assertEquals(3, qm.getTablesCount());
	}
	@Test
	public void problem2() {
		QuineMcCluskeyApplication qm = new QuineMcCluskeyApplication();
		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(0);
		list.add(1);
		list.add(3);
		list.add(4);
		list.add(7);
		list.add(10);
		list.add(14);
		list.add(15);
		qm.setLists(list, null);
		qm.settingTable();
		qm.gettingTables();
		qm.gettingPrimes();
	}
	@Test
	public void problem3() {
		QuineMcCluskeyApplication qm = new QuineMcCluskeyApplication();
		ArrayList<Integer> list = new ArrayList<Integer>();
		ArrayList<Integer> list2 = new ArrayList<Integer>();
		list.add(4);
		list.add(8);
		list.add(10);
		list.add(11);
		list.add(12);
		list.add(15);
		list2.add(9);
		list2.add(14);
		OuterShell s = new OuterShell();
		s.solTwoList(list, list2);
		ArrayList<Integer> list3 = new ArrayList<Integer>();
		list3.add(0);
		list3.add(1);
		list3.add(2);
		list3.add(3);
		list3.add(5);
		s.solTwoList(list3, null);
		s.readFile("amr1");
		s.readFile("amr2");
		qm.setLists(list, list2);
		qm.settingTable();
		qm.gettingTables();
		qm.gettingPrimes();
		PetricksEngine qe = new PetricksEngine(qm);
		System.out.println(qe.getAnswer().size());
		System.out.println(qe.getAnswer().get(0));
		System.out.println(qe.getAnswer().get(1));
	}
	@Test
	public void problem4() {
		QuineMcCluskeyApplication qm = new QuineMcCluskeyApplication();
		ArrayList<Integer> list = new ArrayList<Integer>();
		ArrayList<Integer> list2 = new ArrayList<Integer>();
		list.add(0);
		list.add(1);
		list.add(2);
		list.add(3);
		qm.setLists(list, null);
		qm.settingTable();
		qm.gettingTables();
		qm.gettingPrimes();
		PetricksEngine qe = new PetricksEngine(qm);
	}
}
