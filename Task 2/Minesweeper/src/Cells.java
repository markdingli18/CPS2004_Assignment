//// Creating the Cells for the game

// Imports
import javax.swing.*;
import java.awt.event.*;   // Import for Mouse Click

// Cells Class
// JButton changes the cells into buttons
public class Cells extends JButton {

    //// Variable Declaration for Cells
    private int cell_type;
    private int cell_position;
    private boolean discovered_cell, flagged_cell;

    // Controller instance variable
    private Controller controller;

    // Constructor
    public Cells(int cell_type, int cell_position, boolean discovered_cell, boolean flagged_cell, Controller controller) {

        // Assign instance Variables to parameters in class
        this.cell_type = cell_type;
        this.cell_position = cell_position;
        this.discovered_cell = discovered_cell;
        this.flagged_cell = flagged_cell;
        this.controller = controller;

        // Mouse Listener
        addMouseListener(new MouseListener(){
            // Override function
            @Override
            public void mouseClicked(MouseEvent e){

                // Checking if click is a right click
                if (SwingUtilities.isRightMouseButton(e)) {
                    // Call click button function
                    right_click_button();
                } else{
                    click_Button();
                }
            }
            public void mousePressed(MouseEvent e) {

            }
            public void mouseReleased(MouseEvent e) {

            }
            public void mouseEntered(MouseEvent e) {

            }
            public void mouseExited(MouseEvent e) {

            }
        });
    } // End of Cells Function

    //// Getters and Setters
    public int getCell_type(){

        // TYPES -- 0: Empty_Cell; 1: Mine_Cell; 2: Number_Cell

        return cell_type;
    }
    // -----------------------------------------------------------------------------
    public int getCell_position(){
        return cell_position;
    }
    // -----------------------------------------------------------------------------
    public boolean isDiscovered_cell(){
        return discovered_cell;
    }

    public void setDiscovered_cell(boolean d){
        this.discovered_cell = d;
    }
    // -----------------------------------------------------------------------------
    public boolean isFlagged_cell(){
        return  flagged_cell;
    }

    public void setFlagged_cell(boolean flagged){
        this.flagged_cell = flagged;
    }
    // -----------------------------------------------------------------------------
    public void click_Button() {
        controller.On_Click(this);
    }
    // -----------------------------------------------------------------------------

    // Function for right click
    public void right_click_button(){
        controller.rightClick(this);
    }
} // End of cells class