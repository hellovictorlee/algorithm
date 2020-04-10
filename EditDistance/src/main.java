public class main
{
	public static void main(String[] args)
	{
		String str1 = "distance";
		String str2 = "editing";
		dynamic d = new dynamic(str1, str2);
		System.out.println("Dynamic Programming");
		d.print();

		System.out.print("\nA* Algorithm");
		A a = new A(str1, str2);
		a.print();
	}
}