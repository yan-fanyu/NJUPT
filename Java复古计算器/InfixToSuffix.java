import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class InfixToSuffix {
    // 将操作数与操作符分割开来
    public List<String> toInfixExpression(String infixExpression){
        List<String> ls = new ArrayList<>();
        char c;
        String str;
        int i=0;
        do{
            // 存符号
            if ((c=infixExpression.charAt(i)) < 48 || ((c=infixExpression.charAt(i)) > 57 && (c=infixExpression.charAt(i)) < 'A') || (c=infixExpression.charAt(i)) > 'F'){
                ls.add("" + c);
                i++;
            }else{
                // 存数
                str = "";
                while (i<infixExpression.length() && (((c=infixExpression.charAt(i)) >= 48 && (c=infixExpression.charAt(i)) <= 57) ||((c=infixExpression.charAt(i)) >= 'A' &&(c=infixExpression.charAt(i)) <= 'F' ))){
                    str += c;
                    i++;
                }
                ls.add(str);
            }
        }while (i<infixExpression.length());

        System.out.println("中缀 = " + ls);
        return ls;
    }

    // 将操作符与操作数按后缀表达式存入栈
    public  List<String> change(String string){
        List<String> list = toInfixExpression(string);
        Stack<String> operStack = new Stack<>();
        List<String> resList = new ArrayList<>();
        for (String item : list){
            if (item.matches("^[A-F0-9]+")){
                resList.add(item);
            }else if (item.equals("(")){
                operStack.push(item);
                //如果是右括号“）”，则依次弹出s1栈顶的运算符，并压入s2,直到遇到左括号，此时将这一对括号丢弃；
            }else if (item.equals(")")){
                while (!operStack.peek().equals("(")){
                    resList.add(operStack.pop());
                }
                operStack.pop();
            }else{
                while (operStack.size()!=0 && Operation.getValue(operStack.peek()) >= Operation.getValue(item)){
                    resList.add(operStack.pop());
                }
                operStack.push(item);

                System.out.println("operStack"+operStack);
            }
        }
        while (operStack.size()!=0){
            resList.add(operStack.pop());
        }
        return resList;
    }

}


