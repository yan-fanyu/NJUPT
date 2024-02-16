
class Operation{
    private static int ADD = 1;
    private static int SUB = 1;
    private static int MUL = 1;
    private static int DIV = 1;
    private static int LEFT = 0;

    public static int getValue(String oper){
        int res = 0;
        switch (oper){


            case "+":
                res = ADD;
                break;
            case "-":
                res = SUB;
                break;
            case "*":
                res = MUL;
                break;
            case "/":
                res = DIV;
                break;
            case "(":
                res = LEFT;
                break;
            default:
                System.out.println("不存在该运算符");
                break;
        }
        return res;
    }
}