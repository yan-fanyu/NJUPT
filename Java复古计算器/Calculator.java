import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.Stack;


public class Calculator extends JFrame implements ActionListener
{
    public static final boolean DEC = true;
    public static final boolean HEX = false;
    public static boolean MODE = DEC;

    private final boolean LEFT = true;
    private final boolean RIGHT = false;
    private boolean LEFT_RIGHT = LEFT;

    public int ModeTextZuo = 25;

    // 缩放比例尺
    public int Zoom = 1;
    public int Height = 1000*Zoom;
    public int Width = 600*Zoom;

    public int ResultWidth = 500*Zoom;
    public int ResultHeight = 80*Zoom;

    public int ButtonWidth = 80*Zoom;
    public int ButtonHeight = 60*Zoom;

    private JinZhiZhuanHuan z = new JinZhiZhuanHuan();

    public InfixToSuffix changer = new InfixToSuffix();

    public int ButtonX = 20;
    public int ButtonY = 32;

    public final boolean HasShift = true;
    public final boolean NotShift = false;
    public boolean IsShift = NotShift;

    private String label = null;

    public int FirstButtonLeft = 40;
    public int FirstButtonUp = 100;

    private String RealText = "";

    Work work = new Work();

    private final int ButtonFontSize = 20;

    private final int ShowTextFontSize = 40;





    public String Switch(String s){
        if(s == "1"){
            return "0001";
        }
        else if (s=="2") {
            return "0010";
        }
        else if (s=="3") {
            return "0011";
        }
        else if (s=="4") {
            return "0100";
        }
        else if (s=="5") {
            return "0101";
        }
        else if (s=="6") {
            return "0110";
        }
        else if (s=="7") {
            return "0111";
        }
        else if (s=="8") {
            return "1000";
        }
        else if (s=="9") {
            return "1001";
        }
        else if (s=="A") {
            return "1010";
        }
        else if (s=="B") {
            return "1011";
        }
        else if (s=="C") {
            return "1100";
        }
        else if (s=="D") {
            return "1101";
        }
        else if (s=="E") {
            return "1110";
        }
        else if (s=="F") {
            return "1111";
        }
        else {
            return "2'sC";
        }
    }

    private String[] KEYS={
            "DEC", "HEX", "OCT", "OFF", "ON/C",
            "STO", "RCL", "SUM", "(",   ")",
            "SHF", "D",   "E",   "F",   "K",
            "1'sC","A",   "B",   "C",   "/",
            "OR",  "7",   "8",   "9",   "*",
            "AND", "4",   "5",   "6",   "-",
            "XOR", "1",   "2",   "3",   "+",
            "CE",  "0",   ".",   "+/-", "=",
    };
    private JButton keys[]=new JButton[KEYS.length];
    private JTextField ShowButton = new JTextField("0");

    private JTextField JinZhi = new JTextField("DEX");

    private String ShowText = "";

    // 构造函数
    public Calculator() {

        super("计算器");
        this.MODE = DEC;
        this.setLayout(null);
        ShowButton.setFont(new Font("黑体", Font.BOLD, ShowTextFontSize));
        JinZhi.setFont(new Font("黑体", Font.BOLD,15));
        ShowButton.setBounds(20, 5, ResultWidth, ResultHeight);
        JinZhi.setBounds(ModeTextZuo, 5, 30, 40);
        ShowButton.setHorizontalAlignment(JTextField.RIGHT);
        JinZhi.setHorizontalAlignment(JTextField.RIGHT);
        ShowButton.setEditable(false);
        JinZhi.setEditable(false);
        this.add(ShowButton);
        this.add(JinZhi);
        int x = FirstButtonLeft;
        int y = FirstButtonUp;
        for (int i = 0; i< KEYS.length; i++){


            keys[i] = new JButton();
            keys[i].setFont(new Font("黑体", Font.BOLD, ButtonFontSize*Zoom));
            keys[i].setText(KEYS[i]);
            keys[i].setBounds(x, y, ButtonWidth, ButtonHeight);

            if(KEYS[i] == "A" || KEYS[i] == "B" || KEYS[i] == "C" || KEYS[i] == "D" || KEYS[i] == "E" || KEYS[i] == "F" ||
                    KEYS[i] == "1" || KEYS[i] == "2" || KEYS[i] == "3" || KEYS[i] == "4" || KEYS[i] == "5"||
                    KEYS[i] == "6" || KEYS[i] == "7" || KEYS[i] == "8" || KEYS[i] == "9" || KEYS[i] == "+/-"){
                JButton button1 = new JButton();
                button1.setFont(new Font("黑体", Font.BOLD, 12));
                button1.setText(Switch(KEYS[i]));
                button1.setBorderPainted(false);
                button1.setBounds(x + 10, y - 30, 70, 30);
                button1.setEnabled(false);
                this.add(button1);
            }

            if(x<400){
                x = x + ButtonWidth + ButtonX;
            }
            else{
                x = FirstButtonLeft;
                y = y + ButtonHeight + ButtonY;
            }
            this.add(keys[i]);

        }


        for (int i = 0; i <KEYS.length; i++)
        {
            keys[i].addActionListener(this);
        }
        this.setBounds(500, 200, Width, Height);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public List<String> change(String s){
        System.out.println("RealText = " + s);
        List<String> list = changer.change(s);
        return list;
    }

    //转成十进制
    public String trans(String k){
        if(this.MODE == DEC){
            return k;
        }
        else{
            return z.HEX_DEC(k);
        }
    }

    public String jisuan(List<String> list){
        Stack<String> stack = new Stack<String>();

        for (int i = list.size() - 1; i >= 0; i--) {
            stack.add(list.get(i));

        }

        int current= 0;
        for(int i = 0; stack.size() > 1; i++){

            String num1 = stack.peek();
            int num_1 = Integer.parseInt(trans(num1));

            stack.pop();
            String num2 = stack.peek();
            int num_2 = Integer.parseInt(trans(num2));

            stack.pop();
            String param = stack.peek();

            stack.pop();

            switch (param){
                case "+":
                    current = work.Add(num_1,num_2,MODE);
                    break;
                case "-":
                    current = work.Sub(num_1,num_2,MODE);
                    break;
                case "*":
                    current = work.Multi(num_1,num_2,MODE);
                    break;
                case "/":
                    current = work.Div(num_1,num_2,MODE);
                    break;
                case "&":
                    current = Integer.parseInt(work.And(num1,num2,MODE), MODE?10:16);
                    break;
                case "|":
                    current = Integer.parseInt(work.Or(num1, num2, MODE), MODE?10:16);
                    break;
                case "^":
                    current = Integer.parseInt(work.Xor(num1, num2, MODE), MODE?10:16);
                    break;
                case "S":
                    current = Integer.parseInt(z.Shift(num1, MODE, num_2, LEFT_RIGHT), MODE?10:16);
                    break;
                default:
                    System.out.println("错误");
            }

            stack.add(String.valueOf(MODE?current:z.DEC_HEX(String.valueOf(current))));

            //System.out.println(stack);

        }
        System.out.println("结果 = " + current);
        return MODE ? String.valueOf(current) : z.DEC_HEX(String.valueOf(current));
    }

    // 获取键盘输入
    public void actionPerformed(ActionEvent e) {
        label = e.getActionCommand();

        if(label == "ON/C"){
            this.RealText = "";
            this.ShowText = "";
        }

        else if (label == "="){
            List<String> list = this.change(RealText);
            System.out.println("后缀 = " + list);
            System.out.println("左右移位 = " + (LEFT_RIGHT == LEFT?"左":"右"));
            ShowText = jisuan(list);
            RealText = ShowText;
            LEFT_RIGHT=LEFT;
        }

        else if(label == "-" && IsShift == HasShift){
            LEFT_RIGHT = RIGHT;
            ShowText += "-";
            IsShift = NotShift;
        }

        else if (label == "CE") {
            ShowText = "";
            ShowButton.setText(ShowText);
        }

        else if (label == "ON/C") {
            ShowText = ShowText.substring(0, ShowText.length()-1);
            ShowButton.setText(ShowText);
        }
        // 与运算
        else if(label == "AND"){
            ShowText = ShowText + "AND";
            RealText = RealText + "&";
            ShowButton.setText(ShowText);
        }

        // 或运算
        else if(label == "OR"){
            ShowText = ShowText + "OR";
            RealText = RealText + "|";
            ShowButton.setText(ShowText);
        }

        // 非运算
        else if(label == "XOR"){
            ShowText = ShowText + "XOR";
            RealText = RealText + "^";
            ShowButton.setText(ShowText);
        }

        // 与运算
        else if(label == "AND"){
            ShowText = ShowText + "AND";
            RealText = RealText + "&";
            ShowButton.setText(ShowText);
        }

        // 切换 16 进制
        else if (label == "HEX") {
            this.MODE = HEX;
            if(RealText != "" ){
                ShowText = z.DEC_HEX(ShowText);
                RealText = ShowText;
                ShowButton.setText(ShowText);
            }
        }

        // 切换 10 进制
        else if (label == "DEC") {
            this.MODE = DEC;
            if(RealText != "" ){
                ShowText = z.HEX_DEC(ShowText);
                RealText = ShowText;
                ShowButton.setText(ShowText);
            }
        }

        // 移位操作
        else if(label == "SHF"){
            this.IsShift = HasShift;
            ShowText = ShowText + "SHF";
            RealText = RealText + "S";
            ShowButton.setText(ShowText);
        }

        // 反码
        else if(label == "1'sC"){
            ShowText = work.ICode(RealText, MODE);
            RealText = ShowText;
            ShowButton.setText(ShowText);
            this.MODE = HEX;
        }

        // 补码
        else if(label == "+/-"){
            ShowText = work.BCode(RealText, MODE);
            RealText = ShowText;
            ShowButton.setText(ShowText);
        }

        else{
            if(MODE == DEC && (label == "A" || label == "B" || label == "C" || label == "D" || label == "E" || label == "F")){

            }
            else if(label == "OCT" || label == "STO" || label == "RCL" || label == "K"){

            }
            else {
                ShowText = ShowText + label;
                RealText = RealText + label;
            }

        }

        ShowButton.setText(ShowText);


        JinZhi.setBounds(ModeTextZuo - 3, 5, 40, 40);
        JinZhi.setText(this.MODE ? "DEC":"HEX");
    }


    public static void main(String arg[]) {
        Calculator a =new Calculator();
    }

}
 