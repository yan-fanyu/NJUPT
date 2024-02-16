class AutoSweeper {
    // AI 的构造函数
    constructor(row, col, mine){
        this.row = row;
        this.col = col;
        this.mine = mine;
        //计算杨辉三角形
        this.YangHuiTriangle = this.Vector2(row*col + 1, mine+2, 0);
        this.YangHuiTriangle[0][0] = 1.0;
        for (let i = 0; i < row * col; i++){
            for (let j = 0; j <= mine; j++){
                this.YangHuiTriangle[i + 1][j] += this.YangHuiTriangle[i][j];
                this.YangHuiTriangle[i + 1][j + 1] += this.YangHuiTriangle[i][j];
            }
        }
    }


    // 二维数组初始化
    Vector2(row, col, value)
    {
        let a = [];
        for(let i = 0; i < row  ; i++){
            a[i] = [];
            for (let j = 0; j < col; j++){
                a[i][j] = value;
            }
        }
        return a;
    }

    // 判断二维数组是否包含元组
    Vector2Contain(vector, ii, jj){
        for (let i = 0; i < vector.length; i++){
            if(vector[i][0] === ii && vector[i][1] === jj){
                return true;
            }
        }
        return false;
    }


    // 数字格数字===周围已经标记的雷数
    GetSafePoints(board, pointsLeft)
    {
        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++)
            {
                if (board[i][j] >= 1 && board[i][j] <= 8)
                {
                    let s = 0;
                    for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
                    {
                        for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                        {
                            if(board[ii][jj] === FLAG)
                                s++;
                        }
                    }
                    if (s === board[i][j])
                    {
                        for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
                        {
                            for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                            {
                                if (board[ii][jj] === UNKNOWN)
                                {
                                    pointsLeft.push([ii, jj]);
                                }
                            }
                        }
                    }
                }
            }
        }
        //console.log("length = ", pointsLeft.length)
        return pointsLeft.length > 0;
    }

    //未知格 + 已知标记的地雷 === 数字
    GetBoomPoints(board, pointsRight)
    {

        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++)
            {
                if (board[i][j] >= 1 && board[i][j] <= 8)
                {
                    let s = 0;
                    for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
                    {
                        for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                        {
                            // 如果是未知格 或 已知标记的地雷
                            s += (board[ii][jj] === UNKNOWN || board[ii][jj] === FLAG);
                        }
                    }
                    if (s === board[i][j])
                    {
                        for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
                        {
                            for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                            {
                                if(board[ii][jj] === UNKNOWN && this.Vector2Contain(pointsRight, ii, jj)=== false)
                                {
                                    pointsRight.push([ii, jj]);
                                }
                            }
                        }
                    }
                }
            }
        }
        //console.log("pointsRight = ", pointsRight);
        return pointsRight.length > 0;
    }

    // 计算一个连通区域所有的解
    GetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum, presumeAsBoomCountList,
                            presumeStatusList, totalSolutionNum, mineMin, mineMax, solutionNumOfpresumeBoomNum, perBoardCnt)
    {


        if (totalSolutionNum > SUMLIMIT)
        {
            return;
        }

        //console.log("perBoardCnt = ", perBoardCnt);

        if (mineMax < 0 || mineMin > (unknowNum - presumeNum))
            return;

        for (let j = 0; j < markable_unknownNumList.length; j++)
            if (markable_unknownNumList[j][0] < 0 || markable_unknownNumList[j][1] < markable_unknownNumList[j][0])
                return;

        if (presumeNum === unknowNum)
        {
            totalSolutionNum++;
            let presumeBoomNum = 0;
            for (let i = 0; i < presumeAsBoomCountList.length; i++)
            {
                presumeAsBoomCountList[i] += presumeStatusList[i];
                presumeBoomNum += presumeStatusList[i];
                //console.log(presumeBoomNum)
            }
            solutionNumOfpresumeBoomNum[presumeBoomNum]++;
            for (let i = 0; i < presumeAsBoomCountList.length; i++)
            {

                perBoardCnt[i] = new Map();
                perBoardCnt[i].set(presumeBoomNum, 0);
                // vector<map<int, long double>> &perBoardCnt
                if (presumeStatusList[i] !== 0)
                    perBoardCnt[i][presumeBoomNum]++;
            }
            return;
        }


        //console.log("connected = ", connected);

        // **1、假设第i个边缘未知格设为安全格
        presumeStatusList[presumeNum] = 0;
        for (let j = 0; j < connected[presumeNum].length; j++)
            markable_unknownNumList[connected[presumeNum][j]][1]--;
        this.GetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum + 1, presumeAsBoomCountList, presumeStatusList, totalSolutionNum, mineMin, mineMax, solutionNumOfpresumeBoomNum, perBoardCnt);


        // **2、假设第i个边缘未知格设为雷格
        presumeStatusList[presumeNum] = 1;
        for (let j = 0; j < connected[presumeNum].length; j++)
            markable_unknownNumList[connected[presumeNum][j]][0]--;
        this.GetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum + 1, presumeAsBoomCountList, presumeStatusList, totalSolutionNum, mineMin - 1, mineMax - 1, solutionNumOfpresumeBoomNum, perBoardCnt);

        // **3、撤销操作，即将假设为雷格第presumeNum个边缘未知格再变为假设未知格
        presumeStatusList[presumeNum] = 0;
        for (let j = 0; j < connected[presumeNum].length; j++)
        {
            markable_unknownNumList[connected[presumeNum][j]][0]++;
            markable_unknownNumList[connected[presumeNum][j]][1]++;
        }
    }

    // 一维数组初始化
    Vector1(n, v)
    {
        let i;
        let a = [];
        for(i = 0; i < n; i++){
            a[i] = v;
        }
        return a;
    }

    // 基于一个联通区扫雷
    SweepBasedOnConnectedComponent( board, pointsLeft, pointsRight, safeCells, unknownCells,
                                    prob, mineMin, mineMax,solutionNumOfpresumeBoomNum, perBoardCnt)
    {
        // set<pair<let, let>>
        let unknownSet = [];
        for (let i = 0; i < unknownCells.length; i++)
            this.Insert(unknownSet, unknownCells[i]);

        // vector<pair<let, let>>
        let markable_unknownNumList = [];

        // vector<vector<let>>
        let connected = [];

        this.GetMarkable_unknownNumList(board, safeCells, unknownSet, markable_unknownNumList);

        //console.log("markable_unknownNumList = ", markable_unknownNumList);


        this.GetConnectedRelation(safeCells, unknownCells, connected);

        // 第 i 个 unknownCells 和 第 j 个 safeCells 相邻
        //console.log("connected = ", connected);

        // ********************************* 以上没问题 *************

        let unknowNum = unknownCells.length;
        let totalSolutionNum = 0;
        let presumeAsBoomCountList = this.Vector1(unknowNum, 0);
        let presumeStatusList = this.Vector1(unknowNum, 0);

        // map<int, double> &solutionNumOfPresumeBoomNum
        solutionNumOfpresumeBoomNum = [0, 0];

        // vector<map<int, double>> &perBoardCnt
        perBoardCnt = [];



        // ***** 进入GetAllSolution 开始对连通区域进行枚举假设*****
        this.GetAllSolution(markable_unknownNumList, connected, unknowNum, 0, presumeAsBoomCountList, presumeStatusList, totalSolutionNum, mineMin, mineMax, solutionNumOfpresumeBoomNum, perBoardCnt);

        // 连通区域解出所有的情况分布，执行下面的代码
        this.GetSafePoletsByConnectedComponent(unknownCells, presumeAsBoomCountList, pointsLeft, pointsRight, prob, unknowNum, totalSolutionNum);

    }


    // 获取某个格子可标记的和未知格子的个数
    GetMarkable_unknownNumList(board, safeCells, unknownSet, markable_unknownNumList)
    {
        for (let i = 0; i < safeCells.length; i++)
        {
            let it = safeCells[i];

            markable_unknownNumList.push([board[it[0]][it[1]], 0]);
            for (let ii = Math.max(0, it[0] - 1); ii < Math.min(this.row, it[0] + 2); ii++)
            {
                for (let jj = Math.max(0, it[1] - 1); jj < Math.min(this.col, it[1] + 2); jj++)
                {
                    if(board[ii][jj] === FLAG)
                    {
                        markable_unknownNumList[i][0]--;
                    }
                    else if (board[ii][jj] === UNKNOWN)
                    {
                        if (this.Contain(unknownSet, [ii, jj]) === true)
                        {
                            markable_unknownNumList[i][1]++;
                        }
                    }
                }
            }
        }
    }

    // 判断格子是否是孤立的
    IsIsolated(board, i, j)
    {
        for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
            for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                if(board[ii][jj] !== UNKNOWN && board[ii][jj] !== FLAG)
                    return false;

        return true;
    }

    GetAngle(board, orgin)
    {
        if(IsIsolated(board, this.row - 1, 0))
            return make_pair(this.row - 1, 0);

        if(IsIsolated(board, 0, this.col - 1))
            return make_pair(0, this.col - 1);

        if(IsIsolated(board, this.row - 1,  this.col - 1))
            return make_pair(this.row - 1,  this.col - 1);

        let i = 0;
        let j = 0;

        for(i = 0; i < this.row; i++)
            if(IsIsolated(board, i, j))
                return make_pair(i, j);

        j = this.col - 1;
        for(i = 0; i < this.row; i++)
            if(IsIsolated(board, i, j))
                return make_pair(i, j);

        i = 0;
        for(j = 0; j < this.col; j++)
            if(IsIsolated(board, i, j))
                return make_pair(i, j);

        i = this.row - 1;
        for(j = 0; j < this.col; j++)
            if(IsIsolated(board, i, j))
                return make_pair(i, j);

        return orgin;
    }

    // 通过联通区域解的情况获得安全点
    GetSafePoletsByConnectedComponent(unknownCells, presumeAsBoomCountList, poletsLeft, poletsRight, prob, unknowNum, totalSolutionNum)
    {
        for (let i = 0; i < unknowNum; i++)
        {
            if (presumeAsBoomCountList[i] === 0)
                poletsLeft.push(unknownCells[i]);
            else if (presumeAsBoomCountList[i] === totalSolutionNum)
                poletsRight.push([unknownCells[i][0], unknownCells[i][1]]);
            else
                prob[unknownCells[i][0]][unknownCells[i][1]] = presumeAsBoomCountList[i] / totalSolutionNum;
        }
    }

    // 模拟 Set 容器插入
    Insert(set, item)
    {
        for (let i = 0; i < set.length; i++)
        {
            if (item[0] === set[i][0] && item[1] === set[i][1])
            {
                return;
            }
        }
        set[set.length] = item;
    }

    // 获取一个连通区域
    GetConnectedComponent(board, use, safeCells, unkownCells, i, j)
    {
        this.Insert(use, [i, j]);

        if (board[i][j] === UNKNOWN)
            unkownCells.push([i, j]);
        else
            safeCells.push([i, j]);

        for (let ii = Math.max(0, i - 1); ii < Math.min(this.row, i + 2); ii++)
            for (let jj = Math.max(0, j - 1); jj < Math.min(this.col, j + 2); jj++)
                if (board[ii][jj] !== FLAG && this.Contain(use, [ii, jj]) === false && (board[ii][jj] * board[i][j] < 0))
                    this.GetConnectedComponent(board, use, safeCells, unkownCells, ii, jj);
    }

    // 判断 set 容器中是否包含元素 item
    Contain(set, item)
    {
        for (let i = 0; i < set.length; i++)
        {
            if (item[0] === set[i][0] && item[1] === set[i][1])
            {
                return true;
            }
        }
        return false;
    }


    // 探索
    Explore(board, pointsLeft, pointsRight, prob)
    {
        let unkownNum = 0;
        let mineNum = this.mine;
        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++)
            {
                unkownNum += (board[i][j] === UNKNOWN);	  // 未知的格数++
                mineNum -= (board[i][j] === FLAG);	  // 未知的地雷--
            }
        }
        //console.log("259 unkownNum = ", unkownNum);
        //console.log("361 mineNum = ", mineNum);

        // vector<vector<pair<let, let>>>
        let safeCellsList = [];
        let unkownCellsList = [];

        /*
        map<let, let> solutionNumOfpresumeBoomNum;
        vector<map<let, let>> solutionNumOfpresumeBoomNumList;
        vector<map<let, let>> perBoardCnt;
        vector<vector<map<let, let>>> perBoardCntList;
         */

        let solutionNumOfpresumeBoomNum = [];
        let solutionNumOfpresumeBoomNumList = [];
        let perBoardCnt = [];
        let perBoardCntList = [];



        // set<pair<let, let>>
        let use = [];



        // 遍历棋盘,通过一个格子以扩散的方式寻找连通区域，如果找到安全的格子，返回Main()
        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++)
            {

                // 如果ij格不是已知雷(未知，空白，数字) && ij格不在use里面，即(i, j)格没有被探索过
                if (board[i][j] !== FLAG && this.Contain(use, [i, j]) === false)
                {
                    // vector<pair<let, let>>
                    let safeCells = [];
                    let unknownCells = [];

                    //console.log("402");

                    this.GetConnectedComponent(board, use, safeCells, unknownCells, i, j);



                    if (safeCells.length >= 1 && unknownCells.length >= 1)
                    {

                        //console.log("安全联通区 = ", safeCells);
                        //console.log("未知联通区 = ", unknownCells);

                        this.SweepBasedOnConnectedComponent(board, pointsLeft, pointsRight, safeCells, unknownCells, prob, 0, mineNum, solutionNumOfpresumeBoomNum, perBoardCnt);

                        //console.log("455 prob = ", prob);

                        if (pointsLeft.length > 0 || pointsRight.length > 0)
                            return true;

                        safeCellsList.push(safeCells);
                        unkownCellsList.push(unknownCells);
                        solutionNumOfpresumeBoomNumList.push(solutionNumOfpresumeBoomNum);
                        perBoardCntList.push(perBoardCnt);
                    }
                }
            }
        }

        //console.log("联通区安全集合 = ", safeCellsList);
        //console.log("联通区未知集合 = ", unkownCellsList);

        let isolatedBoardNum1 = 0;
        // 非连通区域的未知格的格子数
        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++)
            {

                if(board[i][j] === UNKNOWN)
                {
                    isolatedBoardNum1++;
                }
            }

        }

        return false;
    }

    // 获取格子与其周围邻居的关系
    GetConnectedRelation(safeCells, unknownCells, connected)
    {

        for (let i = 0; i < unknownCells.length; i++)
        {
            connected[i] = [];
            let n = 0;
            for (let j = 0; j < safeCells.length; j++)
            {
                if (Math.abs(safeCells[j][0] - unknownCells[i][0]) <= 1 && Math.abs(safeCells[j][1] - unknownCells[i][1]) <= 1)
                {
                    connected[i][n] = j;
                    n++;
                }
            }
        }
    }


    MySweepBasedOnConnectedComponent(board, safeCells, unknownCells, mineMin, mineMax)
    {
        // set<pair<let, let>> unknownSet;
        let unknownSet = [];
        for (let i = 0; i < unknownCells.length(); i++)
        unknownSet.insert(unknownCells[i]);

        // vector<pair<let, let>>
        let markable_unknownNumList = [];
        // vector<vector<let>>
        let connected = [];

        GetMarkable_unknownNumList(board, safeCells, unknownSet, markable_unknownNumList);

        GetConnectedRelation(safeCells, unknownCells, connected);

        let unknowNum = unknownCells.size();
        let presumeAsBoomCountList = InitVector1(unknowNum, 0);
        let cur = InitVector1(unknowNum, 0);
        let mytotalSolutionNum = 0;
        MyGetAllSolution(markable_unknownNumList, connected, unknowNum, 0, presumeAsBoomCountList, cur, mineMin, mineMax, mytotalSolutionNum);

        let num = GetOneCCSafeNum(presumeAsBoomCountList, unknowNum, mytotalSolutionNum);

        return num;
    }




    MyGetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum, presumeAsBoomCountList,
                              presumeStatusList, mineMin, mineMax, mytotalSolutionNum) {
        // 如果最大地雷数<0 || 最小地雷数 > 连通分区中剩余的还未进行假设的未知格子数
        if (mineMax < 0 || mineMin > (unknowNum - presumeNum))
            return;

        for (let i = 0; i < markable_unknownNumList.length; i++) {
            let mu = markable_unknownNumList[i];
            if (mu[0] < 0 || mu[1] < mu[0])
                return;
        }


        //  如果此连通区域假设的个数===未知的格数，即完成了一次连通区域假设枚举
        if (presumeNum === unknowNum) {
            mytotalSolutionNum++;
            for (let i = 0; i < presumeAsBoomCountList.size(); i++) {
                presumeAsBoomCountList[i] += presumeStatusList[i];
            }
            return;
        }


        // **1、假设第i个边缘未知格设为安全格
        presumeStatusList[presumeNum] = 0;
        //遍历与第i个未知格相邻的数字格

        for (let i = 0; i < connected[presumeNum].length; i++) {
            let cc = connected[presumeNum][i];
            markable_unknownNumList[cc][1]--;
        }
        MyGetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum + 1, presumeAsBoomCountList, presumeStatusList, mineMin, mineMax, mytotalSolutionNum);


        // **2、假设第i个边缘未知格设为雷格
        presumeStatusList[presumeNum] = 1;

        for (let i = 0; i < connected[presumeNum].length; i++) {
            let cc = connected[presumeNum][i];
            markable_unknownNumList[cc][0]--;
        }
        MyGetAllSolution(markable_unknownNumList, connected, unknowNum, presumeNum + 1, presumeAsBoomCountList, presumeStatusList, mineMin - 1, mineMax - 1, mytotalSolutionNum);

        // **3、撤销操作，即将假设为雷格第presumeNum个边缘未知格再变为假设未知格
        presumeStatusList[presumeNum] = 0;

        for (let i = 0; i < connected[presumeNum].length; i++) {
            let cc = connected[presumeNum][i];
            markable_unknownNumList[cc][0]++;
            markable_unknownNumList[cc][1]++;
        }
    }



    GetMinBoomProbBlock(board, prob)
    {
        let minP = 100000;
        let minBoomProbBlock = [-1, -1];

        for (let i = 0; i < this.row; i++)
        {
            for (let j = 0; j < this.col; j++ )
            {
                if (board[i][j] === UNKNOWN)
                    minBoomProbBlock = [i, j];
                if (board[i][j] === UNKNOWN && prob[i][j] < minP) {
                    minP = prob[i][j];
                    minBoomProbBlock = [i, j];
                }
            }
        }
        return minBoomProbBlock;
    }



    Main(board, pointsLeft, pointsRight)
    {

        // **0、如果第一个格子未知，即刚开局第一步点哪个
        if (board[0][0] === UNKNOWN)
        {
            // 我要左击(0, 0)
            pointsLeft.push([0, 0]);
            return true;
        }

        // **1、如果有100%是地雷的点  与它周围的8个邻居
        if(this.GetBoomPoints(board, pointsRight)) {
            // console.log("Main pointsRight = ", pointsRight);
            return true;
        }

        // **2、如果有100%安全的点
        if (this.GetSafePoints(board, pointsLeft))
            return true;


        // 初始化为雷概率数组
        let prob = this.Vector2(this.row, this.col, -1);
        if (this.Explore(board, pointsLeft, pointsRight, prob)) {
            //console.log("联通区找到了");
            return true;
        }


        //console.log(prob)

        // **5、如果通过连通区域没找到100%安全的格子，寻找概率最小的点，存入pointsLeft
        let minBoomProbBlock = this.GetMinBoomProbBlock(board, prob);
        pointsLeft.push(minBoomProbBlock);

        //console.log("min = ", minBoomProbBlock);

        return false;
    }
}








