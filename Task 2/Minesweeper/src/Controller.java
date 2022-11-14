//// Handles when a cell is clicked & when game is won or lost

// Imports
import java.util.ArrayList;     // Import for array

public class Controller {

    // Arrays to handle each cell
    private ArrayList<Cells> current = new ArrayList<>();
    private ArrayList<Cells> queue = new ArrayList<>();     // Handles cells that are adjacent to cells

    // Variable declaration
    private static int no_flagged_cells = 0;   // Keeps track of number of flagged cells

    // On_Click Function with cell as a parameter
    public void On_Click(Cells cells){

        // Instantiate variable
        int discovered_cells = 0;

        // Not able to discover cells that have been flagged (flagged is when player thinks the cell is a mine)
        if (!cells.isFlagged_cell()) {
            cells.setEnabled(false);
            // Set every cell to discovered
            cells.setDiscovered_cell(true);

            // position of the cell
            int cell_position = cells.getCell_position();

            //// If cell is blank
            if (cells.getCell_type() == 0) {
                //// If cell position is in the first row
                if (cell_position < Main.GRID_SIZE) {
                    // If cell position is in TOP LEFT hand corner
                    if (cell_position % Main.GRID_SIZE == 0) {
                        // Add adjacent cell to queue
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                        // Add cell to bottom right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)));
                        // Add cell to right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + 1)));
                    }
                    // If cell position is in TOP RIGHT hand corner
                    else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                        // Add adjacent cell to queue
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                        // Add cell to bottom left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)));
                        // Add cell to left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - 1)));
                    }
                    // Cells on TOP row that are not in the corners
                    else {
                        // Add bottom cell to queue
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                        // Add cell to bottom right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)));
                        // Add cell to bottom left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)));
                        // Add cell to right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + 1)));
                        // Add cell to left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - 1)));
                    }
                }

                //// If cell position is in the last row
                else if (cell_position >= (Main.GRID_SIZE * (Main.GRID_SIZE - 1))) {
                    // If cell position is in BOTTOM LEFT hand corner
                    if (cell_position % Main.GRID_SIZE == 0) {
                        // Add adjacent cell to queue
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                        // Add cell to top right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)));
                        // Add cell to right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + 1)));
                    }
                    // If cell position is in BOTTOM RIGHT hand corner
                    else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                        // Add adjacent cell to queue
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                        // Add cell to bottom right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)));
                        // Add cell to left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - 1)));
                    }
                    // Cells on TOP row that are not in the corners
                    else {
                        // Add bottom cell to queue
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                        // Add cell to bottom left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)));
                        // Add cell to bottom right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)));
                        // Add cell to left of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position + 1)));
                        // Add cell to right of adjacent cell
                        queue.add(Grid.cellGrid.get((cell_position - 1)));
                    }
                }

                //// If cell is in the left most column
                else if (cell_position % Main.GRID_SIZE == 0) {
                    // Add top cell to queue
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                    // Add bottom cell to queue
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                    // Add cell to top right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)));
                    // Add cell to bottom right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)));
                    // Add cell to right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + 1)));
                }

                //// If cell is in the right most column
                else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                    // Add top cell to queue
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                    // Add bottom cell to queue
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                    // Add cell to top left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)));
                    // Add cell to bottom left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)));
                    // Add cell to left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - 1)));
                }

                // Check every cell adjacent
                else {
                    // Add top cell to queue
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE)));
                    // Add bottom cell to queue
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE)));
                    // Add cell to top left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)));
                    // Add cell to bottom left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)));
                    // Add cell to top right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)));
                    // Add cell to bottom right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)));
                    // Add cell to left of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position - 1)));
                    // Add cell to right of adjacent cell
                    queue.add(Grid.cellGrid.get((cell_position + 1)));
                }
            }

            // -------------------------------------------------------------------------------------------

            //// If cell is a number cell
            else if (cells.getCell_type() == 2) {

                int danger_counter = 0;

                // Check where cell is
                //// If cell is in the first row
                if (cell_position < Main.GRID_SIZE) {
                    // If cell is in the top left corner
                    if (cell_position % Main.GRID_SIZE == 0) {
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom right
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                    }

                    // If cell is in the top right corner
                    else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom left
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position - 1)).getCell_type() == 1) danger_counter++;
                    }

                    // Checks for top edge
                    else {
                        // Check for cells that are adjacent to the top row of cells
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom right
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)).getCell_type() == 1)
                            danger_counter++;
                        // Bottom left
                        if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                        if (Grid.cellGrid.get((cell_position - 1)).getCell_type() == 1) danger_counter++;
                        System.out.println(danger_counter);
                    }
                }

                //// Other side
                else if (cell_position >= (Main.GRID_SIZE * (Main.GRID_SIZE - 1))) {
                    // If cell is in the top left corner
                    if (cell_position % Main.GRID_SIZE == 0) {
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom left
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                    }

                    // If cell is in the top right corner
                    else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom right
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position - 1)).getCell_type() == 1) danger_counter++;
                    }

                    // Checks for top edge
                    else {
                        // Check for cells that are adjacent to the top row of cells
                        // If cell is a mine, Increment danger_count
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                        // Do the same for other cells that are adjacent to the top corner
                        // Bottom left
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)).getCell_type() == 1)
                            danger_counter++;
                        // Bottom right
                        if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)).getCell_type() == 1)
                            danger_counter++;
                        if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                        if (Grid.cellGrid.get((cell_position - 1)).getCell_type() == 1) danger_counter++;
                    }
                }

                //// Functionality for left most column
                else if (cell_position % Main.GRID_SIZE == 0) {
                    // Check for cells that are adjacent to the top row of cells
                    // If cell is a mine, Increment danger_count
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // Do the same for other cells that are adjacent to the top corner
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // Bottom right
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)).getCell_type() == 1) danger_counter++;
                    // Left
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)).getCell_type() == 1) danger_counter++;
                    if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                } else if (cell_position % Main.GRID_SIZE == Main.GRID_SIZE - 1) {
                    // Check for cells that are adjacent to the top row of cells
                    // If cell is a mine, Increment danger_count
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // Do the same for other cells that are adjacent to the top corner
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // left
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)).getCell_type() == 1) danger_counter++;
                    // right
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)).getCell_type() == 1) danger_counter++;
                    if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                }

                //// Catch all for the rest of the cells (Functionality for all the other cells)
                else {
                    // Check for cells that are adjacent to the top row of cells
                    // If cell is a mine, Increment danger_count
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // Do the same for other cells that are adjacent to the top corner
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE)).getCell_type() == 1) danger_counter++;
                    // Bottom left
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE - 1)).getCell_type() == 1) danger_counter++;
                    // right
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE - 1)).getCell_type() == 1) danger_counter++;
                    if (Grid.cellGrid.get((cell_position - Main.GRID_SIZE + 1)).getCell_type() == 1) danger_counter++;
                    // Left
                    if (Grid.cellGrid.get((cell_position + Main.GRID_SIZE + 1)).getCell_type() == 1) danger_counter++;
                    if (Grid.cellGrid.get((cell_position - 1)).getCell_type() == 1) danger_counter++;
                    if (Grid.cellGrid.get((cell_position + 1)).getCell_type() == 1) danger_counter++;
                }

                // Set text of every adjacent cell to the number cell
                cells.setText(String.valueOf(danger_counter));

            }

            // -------------------------------------------------------------------------------------------

            //// If cell is a mine
            else if (cells.getCell_type() == 1) {
                for (int i = 0; i < Grid.cellGrid.size(); i++) {
                    // Disable all cells
                    Grid.cellGrid.get(i).setEnabled(false);
                    // Set text to blank
                    Grid.cellGrid.get(i).setText("");
                    // If cell is a mine
                    if (Grid.cellGrid.get(i).getCell_type() == 1) {
                        // Set to bomb symbol
                        Grid.cellGrid.get(i).setText("\uD83D\uDCA3");
                    }
                }
                // Know which cell is clicked
                cells.setText("*");
            }

            // -------------------------------------------------------------------------------------------

            for (int x = 0; x < queue.size(); x++) {
                // If current cell has not been discovered, add to current array
                if (!queue.get(x).isDiscovered_cell()) {
                    current.add(queue.get(x));
                    queue.get(x).setDiscovered_cell(true);
                }
            }

            // Clear queue
            queue.clear();
            // Add functionality for checking cells
            while (!current.isEmpty()) {
                // Set temporary cell
                Cells temp = current.get(0);
                // Remove it
                current.remove(0);
                temp.click_Button();
            }

            // Increment discovered cells for win condition
            for (int i = 0; i < Grid.cellGrid.size(); i++) {
                // If cell has been discovered,
                if (Grid.cellGrid.get(i).isDiscovered_cell()){
                    // Increment discovered cells
                    discovered_cells++;
                }
            }

            if (discovered_cells == Grid.cellGrid.size() - Main.No_of_Mines) {
                // Iterate through everything
                for (int i = 0; i < Grid.cellGrid.size(); i++) {
                    // If it is a mine cell
                    if (Grid.cellGrid.get(i).getCell_type() == 1) {
                        // Set cell to be disabled
                        Grid.cellGrid.get(i).setEnabled(false);
                        // Set text to bomb symbol
                        Grid.cellGrid.get(i).setText("\uD83D\uDCA3");
                    } else {
                        // Disable cell
                        Grid.cellGrid.get(i).setEnabled(false);
                        Grid.cellGrid.get(i).setText("You win! :)");
                    }
                }
            }
        } // end of if statement
    } // end of On_Click method

    // Functionally for right click
    public void rightClick(Cells cells){
        // If cell has not been discovered
        if (!cells.isDiscovered_cell()){
            // If cell has not been flagged, flag it
            if(!cells.isFlagged_cell()){
                cells.setFlagged_cell(true);
                // Output flag symbol
                cells.setText("⚐");
                // Increment variable
                no_flagged_cells++;
                Window.update(no_flagged_cells);
            }

            else {
                // If cell is flagged, un-flag it
                cells.setFlagged_cell(false);
                // Cancel Text
                cells.setText("");
                no_flagged_cells--;
                Window.update(no_flagged_cells);
            }

        }
    } // End od rightClick method
} // End