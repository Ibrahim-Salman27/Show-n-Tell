const gridElement = document.getElementById("grid");
const rows = 20;
const cols = 20;
let grid = [];
let startNode = null;
let endNode = null;

function createGrid() {
  gridElement.innerHTML = "";
  grid = [];
  for (let row = 0; row < rows; row++) {
    const currentRow = [];
    for (let col = 0; col < cols; col++) {
      const cell = document.createElement("div");
      cell.className = "cell";
      cell.dataset.row = row;
      cell.dataset.col = col;

      cell.addEventListener("click", () => handleCellClick(row, col, cell));
      gridElement.appendChild(cell);
      currentRow.push({ row, col, isWall: false, distance: Infinity, previous: null });
    }
    grid.push(currentRow);
  }
}

function handleCellClick(row, col, cell) {
  if (!startNode) {
    startNode = { row, col };
    cell.classList.add("start");
  } else if (!endNode) {
    endNode = { row, col };
    cell.classList.add("end");
  } else {
    cell.classList.toggle("wall");
    grid[row][col].isWall = !grid[row][col].isWall;
  }
}

function resetGrid() {
  startNode = null;
  endNode = null;
  createGrid();
}

function runDijkstra() {
  if (!startNode || !endNode) {
    alert("Please select a start and end node.");
    return;
  }

  const startCell = grid[startNode.row][startNode.col];
  startCell.distance = 0;

  const unvisited = grid.flat();
  const visitedNodes = [];

  while (unvisited.length > 0) {
    unvisited.sort((a, b) => a.distance - b.distance);
    const closestNode = unvisited.shift();

    if (closestNode.isWall) continue;

    if (closestNode.distance === Infinity) break;

    closestNode.visited = true;
    visitedNodes.push(closestNode);

    if (closestNode.row === endNode.row && closestNode.col === endNode.col) {
      animatePath(visitedNodes);
      return;
    }

    const neighbors = getNeighbors(closestNode);
    for (const neighbor of neighbors) {
      const distance = closestNode.distance + 1;
      if (distance < neighbor.distance) {
        neighbor.distance = distance;
        neighbor.previous = closestNode;
      }
    }
  }
  alert("No path found!");
}

function getNeighbors(node) {
  const neighbors = [];
  const { row, col } = node;
  if (row > 0) neighbors.push(grid[row - 1][col]);
  if (row < rows - 1) neighbors.push(grid[row + 1][col]);
  if (col > 0) neighbors.push(grid[row][col - 1]);
  if (col < cols - 1) neighbors.push(grid[row][col + 1]);
  return neighbors.filter((neighbor) => !neighbor.visited && !neighbor.isWall);
}

function animatePath(visitedNodes) {
  for (let i = 0; i < visitedNodes.length; i++) {
    setTimeout(() => {
      const node = visitedNodes[i];
      const cell = document.querySelector(`.cell[data-row="${node.row}"][data-col="${node.col}"]`);
      if (!cell.classList.contains("start") && !cell.classList.contains("end")) {
        cell.classList.add("visited");
      }

      if (i === visitedNodes.length - 1) {
        reconstructPath();
      }
    }, 50 * i);
  }
}

function reconstructPath() {
  let currentNode = grid[endNode.row][endNode.col];
  while (currentNode.previous) {
    const cell = document.querySelector(`.cell[data-row="${currentNode.row}"][data-col="${currentNode.col}"]`);
    cell.classList.add("path");
    currentNode = currentNode.previous;
  }
}

createGrid();
