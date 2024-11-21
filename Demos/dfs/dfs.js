const mazeElement = document.getElementById("maze");
const nextButton = document.getElementById("nextButton");

// Maze with multiple paths (0 = walkable, 1 = wall)
const maze = [
  [0, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [0, 0, 1, 0, 0, 0, 0, 1, 1, 1],
  [1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
  [1, 0, 0, 0, 0, 0, 0, 1, 1, 1],
  [1, 1, 1, 1, 0, 1, 0, 1, 1, 1],
  [1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
];

// Start and End positions
const start = [0, 0];
const end = [9, 9];

// DFS variables
let stack = [[...start]];
let visited = new Set();
let prev = {};
let isDone = false;

// Create maze grid
function drawMaze() {
  mazeElement.innerHTML = "";
  maze.forEach((row, i) => {
    row.forEach((cell, j) => {
      const div = document.createElement("div");
      div.className = "cell";
      if (cell === 1) div.classList.add("wall");
      if (i === start[0] && j === start[1]) div.classList.add("start");
      if (i === end[0] && j === end[1]) div.classList.add("end");
      div.dataset.row = i;
      div.dataset.col = j;
      mazeElement.appendChild(div);
    });
  });
}

// Perform one step of DFS
function dfsStep() {
  if (stack.length === 0 || isDone) {
    nextButton.disabled = true;
    return;
  }

  const [x, y] = stack.pop();
  const key = `${x},${y}`;
  if (visited.has(key)) return;

  visited.add(key);

  // Mark as visited
  const cell = document.querySelector(`[data-row="${x}"][data-col="${y}"]`);
  cell.classList.add("visited");

  // Check if we reached the end
  if (x === end[0] && y === end[1]) {
    isDone = true;
    drawPath(prev, end);
    return;
  }

  // Explore neighbors
  const directions = [
    [0, 1], [1, 0], [0, -1], [-1, 0], // Right, Down, Left, Up
  ];

  for (const [dx, dy] of directions) {
    const nx = x + dx;
    const ny = y + dy;
    const nKey = `${nx},${ny}`;
    if (nx >= 0 && ny >= 0 && nx < maze.length && ny < maze[0].length && maze[nx][ny] === 0 && !visited.has(nKey)) {
      stack.push([nx, ny]);
      prev[nKey] = [x, y];
    }
  }
}

// Draw the shortest path
async function drawPath(prev, [x, y]) {
  let key = `${x},${y}`;
  while (key in prev) {
    const [px, py] = prev[key];
    key = `${px},${py}`;
    const cell = document.querySelector(`[data-row="${px}"][data-col="${py}"]`);
    cell.classList.remove("visited");
    cell.classList.add("path");
    await new Promise((res) => setTimeout(res, 500)); // Slow path visualization
  }
}

// Initialize maze and set button functionality
drawMaze();
nextButton.addEventListener("click", dfsStep);
