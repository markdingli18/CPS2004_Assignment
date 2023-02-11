//// Main Class

public class Main {

    //// Variable Declaration
    public static final int WIDTH = 900, HEIGHT = 900;      // Width and height for the JFrame (pixels)
    public static final int GRID_SIZE = 16;      // Number of individual cells in JFrame
    public static final int No_of_Mines = (int) Math.round(GRID_SIZE * GRID_SIZE * .1);   // Number of mines according to grid size

    // Variable for Controller Class
    private Controller controller = new Controller();

    // Constructor
    public Main() {
        // Instantiate Window class
        new Window(WIDTH, HEIGHT, GRID_SIZE, "Mine_Sweeper", this, controller);
    }

    // Main function
    public static void main(String[] args){

        // Call constructor
        new Main();
    }

} // End of Main