let game = new Game(ROW, COL, BOOMNUM);
let ai = new AutoSweeper(ROW, COL, BOOMNUM);

let gameNum = 1;
let winNum = 0;

const AI = document.getElementById("AI");
const OneGame = document.getElementById("OneGame");
const Test10W = document.getElementById("Test10W");
const Restart = document.getElementById("Restart");
const WinOrLose = document.getElementById("WinOrLose");
const WinRate = document.getElementById("WinRate");
const Time = document.getElementById("T");



AI.onclick = function (){
    let left = [];
    let right = [];

    ai.Main(game.boardArr, left, right);

    for(let i = 0;i < left.length; i++){
        game.block_click(left[i][0], left[i][1], 0);
    }

    for(let i = 0;i < right.length; i++){
        game.block_click(right[i][0], right[i][1], 2);
    }

    if (game.win){
        winNum++;
    }
    console.log(left);
}

// 扫 10W 局
Test10W.onclick = function (){
    for (let i = 0; i < 100000; i++) {
        console.log(i);
        if((i+1)%10 === 0){
            ShowWinRate();
        }
        Restart.onclick();
        OneGame.onclick();
    }
}

// 重新开始
Restart.onclick = function (){
    ShowNothing();
    gameNum++;
    ai = new AutoSweeper(ROW, COL, BOOMNUM);
    game = new Game(ROW, COL, BOOMNUM);
   
    
}

// 完整的扫一局
OneGame.onclick = function (){
    while (!game.fail && !game.win){
        AI.onclick();
    }
}

// 完整的扫一局
OneGame.onclick = function (){
    while (!game.fail){
        AI.onclick();
    }
}

function ShowWin(){
    WinOrLose.value = "Win";
}

function ShowNothing(){
    WinOrLose.value = "";
}

function ShowLose(){
    WinOrLose.value = "Lose";
}

function ShowWinRate(){
    WinRate.value = (winNum / gameNum).toString();
}