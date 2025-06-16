// Get DOM elements
const startButton = document.querySelector('.start');
const stopButton = document.querySelector('.stop');
const gameStatus = document.querySelector('.gamestatus');
const score = document.querySelector('.score');
const canvas = document.getElementById("snake");
const canvasWidth = document.getElementById("snake").offsetWidth;
const canvasHeight = document.getElementById("snake").offsetHeight;
const context = canvas.getContext("2d");

// Set initial game state
var isStart = false;
var isStop = false;
var isOver = false;

// Some preset parameters
const boxSize = 20;
const startX = 10;
const startY = 10;
var foodX = 60;
var foodY = 60;

// Set basic snake state
var snake = [];
snake[0] = {
    x: startX * boxSize,
    y: startY * boxSize,
};
var direction = "right";

// Event
document.addEventListener('keydown', monitorKeys);
document.addEventListener('click', monitorButtons);

function monitorKeys(event) {
    if (event.keyCode == 37 && direction != "right") direction = "left";
    if (event.keyCode == 38 && direction != "down") direction = "up";
    if (event.keyCode == 39 && direction != "left") direction = "right";
    if (event.keyCode == 40 && direction != "up") direction = "down";
}

function monitorButtons(event) {
    if (event.target.classList.contains('start')) {
        isStart = true;
    } else if (event.target.classList.contains('stop')) {
        isStop = ~isStop;
    }

    if(isOver) {
        gameStatus.innerHTML = "Game Over :(";
        return;
    }

    if(isStart && !isStop) {
        gameStatus.innerHTML = "Playing...";
    } else if(isStart && isStop) {
        gameStatus.innerHTML = "Paused...";
    }
}

// Utils functions
function getRandomInt(min, max) {
    const minInt = Math.ceil(min);
    const maxInt = Math.floor(max);
    return Math.floor(Math.random() * (maxInt - minInt) + minInt);
}
// Drawer functions
function drawBackground() {
    context.fillStyle = "lightgreen";
    context.fillRect(0, 0, canvas.width, canvas.height);
}

function drawSnakeBody() {
    for (let i = 0; i < snake.length; i++) {
        context.fillStyle = "green";
        context.fillRect(snake[i].x, snake[i].y, boxSize, boxSize);
    }
}

function drawFood() {
    context.fillStyle = "red";
    context.fillRect(foodX, foodY, boxSize, boxSize);
    isFoodEaten = false;
}

// Game Logic
function updateSnake() {
    // Record the tail position
    let tailX = snake[snake.length - 1].x;
    let tailY = snake[snake.length - 1].y;

    // Moving Tails
    for (let i = snake.length - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    // Eating
    if (snake[0].x == foodX && snake[0].y == foodY) {
        snake.push({
            x: tailX,
            y: tailY
        })
        updateFood();
    }

    // Moving Head
    if (direction == "right") {
        snake[0].x += boxSize;
    } else if (direction == "left") {
        snake[0].x -= boxSize;
    } else if (direction == "up") {
        snake[0].y -= boxSize;
    } else if (direction == "down") {
        snake[0].y += boxSize;
    }

    // Over
    if (snake[0].x < 0 || snake[0].x > canvasWidth || snake[0].y < 0 || snake[0].y > canvasHeight) {
        isOver = true;
        gameStatus.innerHTML = "Game Over :(";
        isStart = false;
    }

    for (let i = 1; i < snake.length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            isOver = true;
            gameStatus.innerHTML = "Game Over :(";
            isStart = false;
        }
    }
}

function updateFood() {
    foodX = getRandomInt(10, canvasWidth/boxSize) * boxSize;
    foodY = getRandomInt(10, canvasHeight/boxSize) * boxSize;

    // Without snake body
    for (let i = 0; i < snake.length; i++) {
        if (snake[i].x == foodX && snake[i].y == foodY) {
            updateFood();
            return;
        }
    }
}

function showScore() {
    score.innerHTML = "Score: " + snake.length;
}

// Main Game Loop
function gameLoop() {
    drawBackground();
    drawSnakeBody();
    drawFood();
    showScore();
    if(isOver || !isStart || isStop) return;
    updateSnake();
}

// Loop
var gameLoop = setInterval(gameLoop, 100);