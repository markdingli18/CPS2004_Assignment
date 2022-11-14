//// Creating, Checking & Adding Cells to JFrame window

// Imports
import javax.swing.*;      // Import for JPanel class
import java.awt.*;          // Import Dimension Class
import java.util.ArrayList;     // Import for Arrays

// Grid Class
// JPanel changes the Grid into a container that can store a group of components
public class Grid extends JPanel {

    //// Variable Declaration for Grid
    private int upper_bound = Main.GRID_SIZE * Main.GRID_SIZE;      // Max number of Cells (16*16)
    private boolean is_picked = false;    // Used to check if cell is picked

    // Arrays:
    private ArrayList<Integer> mines = new ArrayList<Integer>();        // Position of each mine in the Grid
    public static ArrayList<Cells> cellGrid = new ArrayList<Cells>();   // Holds every cell that is in the grid

    // Constructor
    public Grid(GridLayout x, Controller c) {

        // Super Class
        super(x);
        // Calling Methods
        Created_Cells(c);
        add_Cells();

    }

    // Function that creates instances of each cell
    public void Created_Cells(Controller c) {

        // Creating the Mine Cells
        for (int i = 1; i <= Main.No_of_Mines; i++) {

            // While loop to create Random number until the number is unique
            while (!is_picked) {
                // Random number & finding best place for mine
                int mine_position = (int) (Math.random() * upper_bound);

                ///////// TESTING!!
                // Checking if generated random number is a duplicate
                // If mine position is not duplicate:
                if (!mines.contains(mine_position)) {
                    mines.add(mine_position);
                    is_picked = true;
                }
            }
            is_picked = false;
        }

        // ---------------------------------------------------------------------------------------------
        // Looking at index and deciding what kind of cell is going to be added
        for (int i = 0; i < upper_bound; i++) {

            //// Checking to see if cell is a mine
            if (mines.contains(i)) {
                // Create new cell
                cellGrid.add(new Cells(1, i, false, false, c));
            }
            // Checking if cell is blank or has a number
            // Checking for the LEFT edge of grid
            else if (i % Main.GRID_SIZE == 0){
                // Check every adjacent cell to see if there is a mine
                if (mines.contains(i - Main.GRID_SIZE) ||
                        mines.contains(i - Main.GRID_SIZE + 1) ||
                        mines.contains(i + 1) ||
                        mines.contains(i + Main.GRID_SIZE) ||
                        mines.contains(i + Main.GRID_SIZE + 1)) {
                    // Create a Number Cell
                    cellGrid.add(new Cells(2, i, false, false, c));
                } else {
                    // Create a blank Cell
                    cellGrid.add(new Cells(0, i, false, false, c));
                }
            }
            // Checking for the RIGHT edge of grid
            else if (i % Main.GRID_SIZE == Main.GRID_SIZE - 1){
                // Check every adjacent cell to see if there is a mine
                if (mines.contains(i - Main.GRID_SIZE - 1) ||
                        mines.contains(i - Main.GRID_SIZE) ||
                        mines.contains(i - 1) ||
                        mines.contains(i + Main.GRID_SIZE - 1) ||
                        mines.contains(i + Main.GRID_SIZE)) {
                    // Create a Number Cell
                    cellGrid.add(new Cells(2, i, false, false, c));
                } else {
                    // Create a blank Cell
                    cellGrid.add(new Cells(0, i, false, false, c));
                }
            }

            // Checking REST of the grid
            else {
                // Check every adjacent cell to see if there is a mine
                if (mines.contains(i - Main.GRID_SIZE - 1) ||
                        mines.contains(i - Main.GRID_SIZE) ||
                        mines.contains(i - Main.GRID_SIZE + 1) ||
                        mines.contains(i - 1) ||
                        mines.contains(i + 1) ||
                        mines.contains(i + Main.GRID_SIZE - 1) ||
                        mines.contains(i + Main.GRID_SIZE) ||
                        mines.contains(i + Main.GRID_SIZE + 1)) {
                    // Create a Number Cell
                    cellGrid.add(new Cells(2, i, false, false, c));
                } else {
                    // Create a blank Cell
                    cellGrid.add(new Cells(0, i, false, false, c));
                }
            }
        } // End of for loop
    } // End of method
    // ---------------------------------------------------------------------------------------------

    // Function that adds cells to the Grid
    public void add_Cells() {

        // Loop through entire cell grid and add to JFrame Window
        for (int i = 0; i < cellGrid.size(); i++) {
            // Adding buttons to JFrame Window
            add(cellGrid.get(i));
        }

    }
} // End of class