public class Teste {
    public static double fib(double a) {
        if(a <= 1) {
            return a;
        }
        return fib(a - 1) + fib(a - 2);
    }
    public static void main() {
        double cnt;
        double max;
        max = lerDouble();
        cnt = 1;
        while(cnt <= max) {
            println(fib(cnt));
            cnt = cnt + 1;
        }
    }
}