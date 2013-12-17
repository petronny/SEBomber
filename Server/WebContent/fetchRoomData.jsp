<%@ page contentType="text/html; charset=gb2312" %> 
<%@ page language="java" %> 
<%@ page import="com.mysql.jdbc.Driver" %> 
<%@ page import="java.sql.*" %> 
<% 
//驱动程序名 
String driverName="com.mysql.jdbc.Driver"; 
//数据库用户名 
String userName="root"; 
//密码 
String userPasswd="root"; 
//数据库名 
String dbName="seboomer"; 
//表名 
String tableName="roomdata"; 
//联结字符串 
String input=request.getParameter("roomid");
String url="jdbc:mysql://localhost/"+dbName+"?user="+userName+"&password="+userPasswd; 
Class.forName("com.mysql.jdbc.Driver").newInstance(); 
Connection connection=DriverManager.getConnection(url); 
Statement statement = connection.createStatement(); 
String sql="SELECT * FROM "+tableName +" where id= "+input;

ResultSet rs = statement.executeQuery(sql); 
//获得数据结果集合 
ResultSetMetaData rmeta = rs.getMetaData(); 
//确定数据集的列数，亦字段数 
int numColumns=rmeta.getColumnCount(); 
// 输出每一个数据值 
String ans="";
if(rs.next()) {
	ans+=rs.getString("pos_1")+" "+rs.getString("pos_2")+" "+rs.getString("pos_3")+" "+rs.getString("pos_4")+" "+rs.getString("pos_5")+" "+rs.getString("pos_6")+" "+rs.getString("pos_7")+" "+rs.getString("pos_8");
} 
else{ 
	out.print(-1);
}
out.print(ans);
System.out.println(ans);

rs.close(); 
statement.close(); 
connection.close(); 
%> 