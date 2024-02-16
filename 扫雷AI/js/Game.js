class Game {
    constructor(row, col, mine) {
        this.row = row; //行数
        this.col = col; //列数
        this.maxCount = mine; //最大地雷数量
        this.isFirstOpen = true; //第一次打开方格
        this.boomArr = [];
        this.boardArr = [];
        this.fail = false;
        this.win = false;
        this.grid = this.InitBoom(); //初始化
        this.count = document.getElementById('count'); //剩余雷数
        this.count.innerHTML=this.maxCount;

    
    }
    //生成雷盘格
    InitBoom() {

        let gridHtml = '';
        for (let i = 0; i < this.row; i++) {
            gridHtml += '<tr>'
            this.boomArr[i] = [];
            this.boardArr[i] = [];
            for (let j = 0; j < this.col; j++) {
                this.boomArr[i][j] = 0;
                this.boardArr[i][j] = -1;
                gridHtml +=
                    '<td><span class="blocks" onmousedown="game.block_click(' + i + ',' + j + ', event.button)"></span></td>';
            }
            gridHtml += '<tr>'
        }
        document.getElementById('grid').innerHTML = gridHtml;

        let blocks = document.getElementsByClassName('blocks');
        let grid = [];
        for (let i = 0; i < blocks.length; i++) {
            if (i % this.col === 0) {
                grid.push([]);
            }
            //初始化计雷数
            blocks[i].count = 0;
            grid[parseInt(i / this.col)].push(blocks[i]);
        }
        return grid;
    }



    op(block) {
        block.isOpen = true;  //isOpen为自定义属性，设置为true代表已打开
        
    }

    //方格点击事件 ii：坐标i jj:坐标j e:鼠标事件
    block_click(ii, jj, e) {
        //跳过已打开的方格
        if (this.grid[ii][jj].isOpen) {
            return;
        }
        //鼠标左键打开方格
        if (e === 0) {
            this.boardArr[ii][jj] = this.boomArr[ii][jj];

            //第一次打开
            if (this.isFirstOpen) {

                this.isFirstOpen = false;
                let count = 0; //当前地雷数

                //生成地雷
                while (count < this.maxCount) {

                    //生成随机坐标
                    let ri = Math.floor(Math.random() * this.row);
                    let rj = Math.floor(Math.random() * this.col);

                    //坐标不等于第一次点击方格的坐标 && 非雷方格
                    if (!(ri === ii && rj === jj) && !this.grid[ri][rj].isMine) {
                        this.grid[ri][rj].isMine = true; //自定义属性isMine代表方格为地雷
                        count++; //当前地雷数+1
                        this.boomArr[ri][rj] = BOOM;

                        //更新九宫格内非雷方格的计雷数
                        for (let i = ri - 1; i < ri + 2; i++) {
                            for (let j = rj - 1; j < rj + 2; j++) {
                                //判断坐标防越界
                                if (i > -1 && j > -1 && i < this.row && j < this.col) {
                                    //计雷数+1
                                    this.grid[i][j].count++;
                                }
                            }
                        }
                    }
                }

                for (let i = 0; i < this.row; i++) {
                    for (let j = 0; j < this.col; j++) {
                        //判断坐标防越界
                        if (this.boomArr[i][j] !== BOOM) {
                            this.boomArr[i][j] = this.grid[i][j].count;
                        }
                    }
                }


            }
            this.blockOpen(ii, jj);
        }
        //鼠标右键标记方格
        else if (e === 2) {
            let block = this.grid[ii][jj];
            if (block.innerHTML !== '▲') {
                this.boardArr[ii][jj] = FLAG;
                block.innerHTML = '▲';
                this.count.innerHTML = parseInt(this.count.innerHTML) - 1;
            } else {
                this.count.innerHTML = parseInt(this.count.innerHTML) + 1;
                block.innerHTML = '';
            }
        }

        //判断游戏是否结束(所有的非雷方格已打开)
        for (let i = 0; i < this.row; i++) {
            for (let j = 0; j < this.col; j++) {
                if (!this.grid[i][j].isMine && !this.grid[i][j].isOpen) {
                    return;
                }
            }
        }
        this.win = true;
        ShowWin();
    }



    blockOpen(ii, jj) {

        let block = this.grid[ii][jj];
        this.op(block);

        this.boardArr[ii][jj] = this.boomArr[ii][jj];


        if (block.isMine) {


            //踩雷
            this.boardArr[ii][jj] = KILL;
            block.innerHTML = "<n>"+'*'+"</n>";
            for (let i = 0; i < this.row; i++) {
                for (let j = 0; j < this.col; j++) {
                    block = this.grid[i][j];
                    if (!block.isOpen && block.isMine) {
                        this.op(block); 
                        block.innerHTML ="<img src='imgs/boom.jpg'>"; 
                    }
                }
            }
            this.fail = true;
            ShowLose();

        }
        else if (block.count === EMPTY) {
            block.innerHTML ="<img src='imgs/bac.jpg'>";
            //遍历雷盘格周围格子
            for (let i = ii - 1; i < ii + 2; i++) {
                for (let j = jj - 1; j < jj + 2; j++) {
                    //判断是否越界并跳过已打开方格
                    if (i > -1 && j > -1 && i < this.row && j < this.col && !this.grid[i][j].isOpen && !this.grid[i][j].isMine) {
                        //递归
                        this.blockOpen(i, j);
                    }
                }
            }
        } else {
            //打开计雷数不为0的方格
            if(block.count==1)
            block.innerHTML = "<img src='imgs/1.jpg'>";
            else if(block.count==2)
            block.innerHTML = "<img src='imgs/2.jpg'>";
            else if(block.count==3)
            block.innerHTML = "<img src='imgs/3.jpg'>";
            else if(block.count==4)
            block.innerHTML = "<img src='imgs/4.jpg'>";
            else if(block.count==5)
            block.innerHTML = "<img src='imgs/5.jpg'>";
            else if(block.count==6)
            block.innerHTML = "<img src='imgs/6.jpg'>";
            else if(block.count==7)
            block.innerHTML = "<img src='imgs/7.jpg'>";
            else 
            block.innerHTML = "<img src='imgs/8.jpg'>";
        }

    }
}

