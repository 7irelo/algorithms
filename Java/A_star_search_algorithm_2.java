import java.util.*;

// Class representing a cell in the grid
class Cell {
    int row, col; // Row and column indices of the cell
    int f, g, h;  // f = g + h, g = cost from start to current cell, h = heuristic cost from current cell to goal
    Cell parent;  // Parent cell (used to reconstruct the path)

    public Cell(int row, int col) {
        this.row = row;
        this.col = col;
        this.f = 0;
        this.g = 0;
        this.h = 0;
        this.parent = null;
    }
}

// Class representing the grid environment
class Grid {
    int[][] grid;  // Grid representing obstacles and empty spaces
    int rows, cols; // Number of rows and columns in the grid
    Cell start, goal; // Start and goal cells

    public Grid(int[][] grid, Cell start, Cell goal) {
        this.grid = grid;
        this.rows = grid.length;
        this.cols = grid[0].length;
        this.start = start;
        this.goal = goal;
    }

    // A* search algorithm to find the shortest path from start to goal
    public List<Cell> astar() {
        PriorityQueue<Cell> openSet = new PriorityQueue<>((a, b) -> a.f - b.f); // Priority queue for open set
        Set<Cell> closedSet = new HashSet<>(); // Set for closed set

        openSet.add(start); // Add start cell to open set

        while (!openSet.isEmpty()) {
            Cell current = openSet.poll(); // Get the cell with lowest f-score from open set

            if (current.row == goal.row && current.col == goal.col)
                return reconstructPath(current); // Reconstruct and return path if goal is reached

            closedSet.add(current); // Add current cell to closed set

            // Generate neighbors of the current cell
            List<Cell> neighbors = generateNeighbors(current);
            for (Cell neighbor : neighbors) {
                if (closedSet.contains(neighbor)) // Skip neighbor if it is in closed set
                    continue;

                int tentativeGScore = current.g + 1; // Tentative g-score from start to neighbor

                if (!openSet.contains(neighbor) || tentativeGScore < neighbor.g) {
                    neighbor.parent = current;
                    neighbor.g = tentativeGScore;
                    neighbor.h = heuristic(neighbor, goal);
                    neighbor.f = neighbor.g + neighbor.h;

                    if (!openSet.contains(neighbor))
                        openSet.add(neighbor);
                }
            }
        }

        return null; // If no path found
    }

    // Heuristic function (Euclidean distance)
    private int heuristic(Cell a, Cell b) {
        return Math.abs(a.row - b.row) + Math.abs(a.col - b.col);
    }

    // Generate neighbors of a given cell
    private List<Cell> generateNeighbors(Cell cell) {
        List<Cell> neighbors = new ArrayList<>();

        int[] dx = {-1, 1, 0, 0}; // Delta row
        int[] dy = {0, 0, -1, 1}; // Delta column

        for (int i = 0; i < 4; i++) {
            int newRow = cell.row + dx[i];
            int newCol = cell.col + dy[i];

            // Check if the neighbor is within the grid and is not an obstacle
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] != 1) {
                neighbors.add(new Cell(newRow, newCol));
            }
        }

        return neighbors;
    }

    // Reconstruct path from start to current cell
    private List<Cell> reconstructPath(Cell current) {
        List<Cell> path = new ArrayList<>();
        while (current != null) {
            path.add(current);
            current = current.parent;
        }
        Collections.reverse(path);
        return path;
    }
}

public class Main {
    public static void main(String[] args) {
        int[][] grid = {
            {0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 1, 0}
        };

        Cell start = new Cell(0, 0);
        Cell goal = new Cell(4, 5);

        Grid g = new Grid(grid, start, goal);
        List<Cell> path = g.astar();

        if (path != null) {
            for (Cell cell : path) {
                System.out.println("(" + cell.row + ", " + cell.col + ")");
            }
        } else {
            System.out.println("No path found.");
        }
    }
}
