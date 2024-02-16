

public class Work {

    private final int Bit = 32;

    private JinZhiZhuanHuan z=new JinZhiZhuanHuan();



    public int Add(int g1, int g2,boolean MODE){
        return g1+g2;
    }

    public int Sub(int g1, int g2,boolean MODE){
        return g1-g2;
    }

    public int Multi(int g1, int g2,boolean MODE){
        return g1*g2;
    }

    public int Div(int g1, int g2,boolean MODE){
        return g1/g2;
    }




    // ************************************ 与部分 ***************************************************
    // 与
    public String And(String g1, String g2,boolean MODE){
        if(MODE == Calculator.DEC){
            return z.BIN_DEC(And10(g1,g2));
        }
        else{
            return z.BIN_HEX(And16(g1,g2));
        }
    }

    //输入十六进制  输出二进制
    public String And16(String g1,String g2){
        g1 = z.HEX_DEC(g1);
        g2 = z.HEX_DEC(g2);
        return And10(g1,g2);

    }

    //与 ： 10 -> 2
    public String And10(String g1, String g2){
        int i = 0;
        int j = 0;

        g1 = z.DEC_BIN(g1);
        g2 = z.DEC_BIN(g2);

        String temp = "";

        for(i = g1.length()-1,j = g2.length()-1;i >= 0 && j >= 0; i--,j--){
            if(g1.charAt(i) == '1' && g2.charAt(j) == '1')
                temp = "1" + temp;
            else
                temp = "0" + temp;
        }
        if(i<0 && j<0){
            return temp;
        }
        if(i < 0 && j >= 0){
            return temp;
        }
        if(i >= 0 && j < 0){
            return temp;
        }
        return null;
    }







    // ************************************ 或部分 ***************************************************
    //或 ：10/16 -> 10/16
    public String Or(String g1, String g3, boolean MODE){
        if(MODE == Calculator.DEC){
            return z.BIN_DEC(Or10(g1,g3));
        }
        else {
            return z.DEC_HEX(z.BIN_DEC(Or16(g1, g3)));
        }
    }

    //或 16 -> 2
    public String Or16(String g1,String g2){
        g1 = z.HEX_DEC(g1);
        g2 = z.HEX_DEC(g2);

        return Or10(g1,g2);

    }

    //或 2 -> 10
    public String Or10(String g1,String g3){


        int i=0,j=0;

        g1 = z.DEC_BIN(g1);
        g3 = z.DEC_BIN(g3);
        String temp="";

        //System.out.println(g1.length());

        for(i=g1.length()-1,j=g3.length()-1 ;i>=0 && j>=0; i--,j--){
            //System.out.println(temp);
            if(g1.charAt(i)== '0' && g3.charAt(j) == '0')
                temp="0"+temp;
            else
                temp="1"+temp;

        }
        if(i < 0 && j < 0){
            //System.out.println(temp);
            return temp;
        }
        if(i<0&&j>=0){
            return g3.substring(0,j+1)+temp;
        }
        if(i>=0&&j<0){
            return g1.substring(0,i+1)+temp;
        }
        return null;
    }




    // ************************************ 异或部分 ***************************************************
    // 异或 ： 16/2 -> 16/2
    public String Xor(String g1,String g3, boolean MODE){
        if(MODE==true){
            return z.BIN_DEC(Xor10(g1,g3));
        }
        else if(MODE==false){
            return z.DEC_HEX(z.BIN_DEC(Xor16(g1,g3)));
        }

        return null;
    }

    //异或 ： 16 -> 16
    public String Xor16(String g1,String g3){
        g1 = z.HEX_DEC(g1);
        g3 = z.HEX_DEC(g3);

        return Xor10(g1,g3);

    }

    //异或  10 -> 10
    public String Xor10(String g1,String g3){
        String temp="";

        g1=z.DEC_BIN(g1);
        g3=z.DEC_BIN(g3);
        int i=0 ,j=0;
        for(i=g1.length()-1,j=g3.length()-1;i>=0&&j>=0;i--,j--){
            if(g1.charAt(i)=='0'&&g3.charAt(j)=='0'||g1.charAt(i)=='1'&&g3.charAt(j)=='1')
                temp="0"+temp;
            else
                temp="1"+temp;
        }



        if(i<0 && j<0){
            return temp;
        }
        if(i<0&&j>=0) {
            for(int k=j;k>=0;k--){
                if(g3.charAt(k)=='1')
                    temp="1"+temp;
                else
                    temp="0"+temp;
            }
            return temp;
        }

        if(i>=0&&j<0){
            for(int k=i;k>=0;k--){
                if(g1.charAt(k)=='1')
                    temp="1"+temp;
                else
                    temp="0"+temp;
            }
            return temp;
        }
        return null;
    }




    // ************************************ 反码部分 ***************************************************
    //反码 ：输入十进制与十六进制输出十六进制反码
    public String ICode(String g,boolean MODE){
        return MODE?ICode_10_16(g):ICode_16_16(g);
    }

    //反码 输入十进制  输出十六进制
    public String ICode_10_16(String g10){
        if(g10.charAt(0)!='-'){
            return z.DEC_HEX(g10);
        }
        String g2 = ICode(g10);
        return z.BIN_HEX(g2);
    }

    //反码 输入十六进制  输出十六进制
    public String ICode_16_16(String g16){
        if(g16.charAt(0)!='-'){
            return g16;
        }
        String g10 = "-" + z.HEX_DEC(g16.substring(1));

        return ICode_10_16(g10);
    }

    //反码(输入g是操作数)  输入十进制  输出二进制
    public String ICode(String g){
        String g2 = z.DEC_BIN(g.substring(1));

        while (g2.length() < Bit - 1){
            g2= "0" + g2;
        }
        g2 = "1" + g2;   //加入符号位
        String result ="";

        for(int i = 1; i < g2.length(); i++){
            if(g2.charAt(i)=='0')
                result = result + "1";
            else
                result = result+"0";
        }
        System.out.println("二进制补码 = " +result);
        return "1" +  result;
    }
    // ***************************************************************************************

    // 补码 ： 输入十进制与十六进制输出十六进制补码
    public String BCode(String g, boolean MODE){
        if(g.charAt(0) == '-'){
            return MODE ? z.BIN_HEX(Bin_Increase(z.HEX_BIN(ICode_10_16(g)))) :  z.BIN_HEX(Bin_Increase(z.HEX_BIN(ICode_16_16(g))));
        }
        else {
            return MODE? z.DEC_HEX(g):g;
        }

    }

    // 二进制自增运算
    public String Bin_Increase(String g2){
        System.out.println("412行 输入 = " + g2);
        String result = "";
        String add = "1";
        for (int i = g2.length() - 1; i >= 0; i--) {
            System.out.println(add);
            String _this = String.valueOf(g2.charAt(i));
            if(_this.equals("1") && add.equals("1")){
                result = "0" + result;
                add = "1";
            }
            else if(add.equals("1") || _this.equals("1")){
                result = "1" + result;
                add = "0";
            }
            else {
                result =  "0" + result;
                add = "0";
            }

        }
        return result;
    }


    public static void main(String[] args) {

        Work work = new Work();

        System.out.println(work.ICode_10_16("752"));
    }

}

