public class MonitorC {

  public void printf() {
    System.out.println("Nice to be here THREADS!!!!!!");
  }
  public static void main(String[] args) {
    Thread t = new Thread("Dipankar");
    System.out.println(t.getId() + " " + t.getName() + " " + t.getState());
    t.start();
    System.out.println(t.getId() + " " + t.getName() + " " + t.getState());
  }
}