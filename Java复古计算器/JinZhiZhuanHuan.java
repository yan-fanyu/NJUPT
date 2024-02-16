import java.util.HashMap;
import java.util.Map;

public class JinZhiZhuanHuan{

    // 10 -> 16(TRUE)
    public String DEC_HEX(String src){
        int[] b=new int[src.length()];
        for(int i=0;i<src.length();i++){
            b[i]=Integer.parseInt(String.valueOf(src.charAt(i)));
        }
        return Integer.toHexString(Integer.parseInt(src)).toUpperCase();
    }

    // 16 -> 10(TRUE)
    public String HEX_DEC(String content) {
        int number = 0;
        String[] HighLetter = {"A", "B", "C", "D", "E", "F"};
        Map<String, Integer> map = new HashMap<>();
        for (int i = 0; i <= 9; i++) {
            map.put(i + "", i);
        }
        for (int j = 10; j < HighLetter.length + 10; j++) {
            map.put(HighLetter[j - 10], j);
        }
        String[] str = new String[content.length()];
        for (int i = 0; i < str.length; i++) {
            str[i] = content.substring(i, i + 1);
        }
        for (int i = 0; i < str.length; i++) {
            number += map.get(str[i]) * Math.pow(16, str.length - 1 - i);
        }
        return String.valueOf(number);
    }

    // 2 -> 16(TRUE)
    public String BIN_HEX(String string2){
        String string16 = "";


        int len = string2.length();

        System.out.println("len = " + len);


        while(string2.length() < 32){
            string2 = "0" + string2;
        }

        System.out.println("len = " + string2.length());

        System.out.println("string2 = "+ string2 );

        for (int i = 0; i < string2.length() / 4; i++){
            //每4个二进制位转换为1个十六进制位
            String temp = string2.substring(i * 4, (i + 1) * 4);
            int tempInt = Integer.parseInt(temp, 2);
            String tempHex = Integer.toHexString(tempInt).toUpperCase();
            string16 = string16 + tempHex;
        }

        for (int i = 0; i < string16.length(); i++) {
            if(string16.charAt(i) != '0'){
                string16 = string16.substring(i);
                break;
            }
        }



        return string16;
    }

    // 16 -> 2 (TRUE)
    public String HEX_BIN(String string16){
        System.out.println("140行 输入 string16 = "+ string16);
        String result = "";
        for(int i = string16.length() - 1; i >= 0 ; i--){
            int n = Integer.parseInt(String.valueOf(string16.charAt(i)), 16);
            String temp = Integer.toBinaryString(n);
            result = temp + result;
        }
        System.out.println("147行 输出 = " + result);
        return  result;
    }

    // 10 -> 2(TRUE)
    public String DEC_BIN(String string10){
        int a = Integer.parseInt(string10);

        //将扫描器输入的值赋值给int类型的num
        int num = a;
        //定义一个String的result，默认值为空
        String string2 = "";
        //当a=0时
        if(a==0)
            return "0";
        //将num放入到for循环里面，每次循环结束都除以2
        for(int i = num; i > 0; i/=2){
            //将i的数值对2取余，然后进行字符串的拼接，最后赋值给result
            string2 = i % 2 + string2;
        }
        return string2;
    }

    // 2 -> 10(TRUE)
    public String BIN_DEC(String string2){
        String string10 = "";
        string10 = String.valueOf( Integer.parseInt(string2,2));
        return string10;
    }


    // ************************************移位操作***********************************************
    //输入十六
    public String Shift_Right_16_1(String string16){
        String string10 = HEX_DEC(string16);
        string16 = DEC_HEX(String.valueOf(Integer.parseInt(string10)>>1));
        return string16;
    }

    //输入十六
    public String Shift_Left_16_1(String string16){
        String string10 = HEX_DEC(string16);
        string16 = DEC_HEX(String.valueOf(Integer.parseInt(string10)<<1));

        return string16;
    }


    public String Shift_16(String string16, int ShiftNum, boolean LEFT_RIGHT){
        String result = string16;
        if(LEFT_RIGHT == true) {
            for (int i = 0; i < ShiftNum; i++) {
                result = this.Shift_Left_16_1(result);
            }
        }
        else {
            for (int i = 0; i < ShiftNum; i++) {
                result = Shift_Right_16_1(result);
            }
        }
        return result;
    }

    public String Shift_10(String string10, int ShiftNum, boolean LEFT_RIGHT){
        String result = string10;
        if(LEFT_RIGHT == true) {
            for (int i = 0; i < ShiftNum; i++) {
                result = Shift_Left_10_1(result);
            }
        }
        else {
            for (int i = 0; i < ShiftNum; i++) {
                result = Shift_Right_10_1(result);
            }
        }
        return result;
    }

    public String Shift_Left_10_1(String string10){
        return String.valueOf(Integer.parseInt(string10)<<1);
    }
    public String Shift_Right_10_1(String string10){
        return String.valueOf(Integer.parseInt(string10)>>1);
    }

    // 十进制和十六进制的左右移
    public String Shift(String string, boolean MODE, int ShiftNum, boolean LEFT_RIGHT){
        if(MODE == Calculator.DEC){
            return Shift_10(string, ShiftNum, LEFT_RIGHT);
        }
        else {
            return Shift_16(string, ShiftNum, LEFT_RIGHT);
        }
    }

    // ************************************移位操作***********************************************


    public static void main(String[] args) {
        JinZhiZhuanHuan z= new JinZhiZhuanHuan();

        System.out.println(z.DEC_BIN("100"));
    }

}
