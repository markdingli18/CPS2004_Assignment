//// Setting up JFrame window

// Imports
import javax.swing.*;   // Import swing library for Jframe window
import java.awt.*;   // Import Dimension Class

public class Window {

    //// Variable Declaration
    private static JFrame frame;
    private static String title;    // Title of Jframe window

    // Constructor
    public Window(int width, int height, int grid_size, String title, Main game, Controller controller){

        // Creating window title
        Window.title = title;
        // Set Frame
        frame = new JFrame(title);

        // Set minimum and maximum size of window
        frame.setPreferredSize(new Dimension(width, height));
        frame.setMinimumSize(new Dimension(width, height));
        frame.setMaximumSize(new Dimension(width, height));

        // Set default Close operation
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // Centering JFrame window
        frame.setLocationRelativeTo(null);

        // Adding JPanel to JFrame Window
        JPanel panel = new Grid(new GridLayout(grid_size, grid_size), controller);
        frame.setContentPane(panel);
        frame.pack();

        // Makes frame appear on the screen
        frame.setVisible(true);

    }

    // This function update gives information about the game (next to the title)
    public static void update(int no_flagged_cells){
        frame.setTitle(title + "  Mines: " + Main.No_of_Mines + "  -  Flags: " + no_flagged_cells);
    }

} // End of Window Class