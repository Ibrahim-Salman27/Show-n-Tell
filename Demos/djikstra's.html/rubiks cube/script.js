const cube = document.getElementById('cube');
let isDragging = false;
let previousMousePosition = { x: 0, y: 0 };
let rotation = { x: 0, y: 0 };

// Handle dragging to rotate
cube.addEventListener('mousedown', (event) => {
    isDragging = true;
    previousMousePosition.x = event.clientX;
    previousMousePosition.y = event.clientY;
});

document.addEventListener('mousemove', (event) => {
    if (isDragging) {
        const deltaX = event.clientX - previousMousePosition.x;
        const deltaY = event.clientY - previousMousePosition.y;

        rotation.y += deltaX * 0.5;
        rotation.x -= deltaY * 0.5;

        cube.style.transform = `rotateX(${rotation.x}deg) rotateY(${rotation.y}deg)`;
        previousMousePosition.x = event.clientX;
        previousMousePosition.y = event.clientY;
    }
});

document.addEventListener('mouseup', () => {
    isDragging = false;
});

// Render scrambled cube
function renderCube(scrambledState) {
    const faces = ['up', 'right', 'front', 'down', 'left', 'back'];
    const faceColors = {
        W: 'white',
        Y: 'yellow',
        B: 'blue',
        G: 'green',
        R: 'red',
        O: 'orange',
    };

    faces.forEach((face, index) => {
        const faceDiv = document.querySelector(`.${face}`);
        faceDiv.innerHTML = ''; // Clear previous content
        for (let i = 0; i < 9; i++) {
            const color = faceColors[scrambledState[index * 9 + i]] || 'grey';
            const tile = document.createElement('div');
            tile.style.backgroundColor = color;
            faceDiv.appendChild(tile);
        }
    });
}

// Handle solve button
document.getElementById('solveBtn').addEventListener('click', () => {
    const scrambledInput = document.getElementById('scrambledInput').value.trim();
    if (scrambledInput.length !== 54) {
        alert('Invalid input! Enter 54 characters representing the cube state.');
        return;
    }
    renderCube(scrambledInput);
});
