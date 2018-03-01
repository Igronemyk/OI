import java.util.Scanner;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        scan.close();
        if(n == 1) {
            System.out.println(1);
            return;
        }else if(n == 2) {
            System.out.println(5);
            return;
        }
        BigInteger num3 = new BigInteger("3"),num2 = new BigInteger("2");
        BigInteger b1 = new BigInteger("1"),b2 = new BigInteger("5");
        for(int i = 3;i <= n;i++) {
            BigInteger tmp = b2.multiply(num3).subtract(b1).add(num2);
            b1 = b2;
            b2 = tmp;
        }
        System.out.println(b2.toString());
    }
}
