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
String dbName="test"; 
//表名 
String tableName="usermessage"; 
//联结字符串 
String userid=request.getParameter("userid");
String date=request.getParameter("date");
String time=request.getParameter("time");
String url="jdbc:mysql://localhost/"+dbName+"?user="+userName+"&password="+userPasswd; 
Class.forName("com.mysql.jdbc.Driver").newInstance(); 
Connection connection=DriverManager.getConnection(url); 
Statement statement = connection.createStatement();
String sql="select * from "+tableName+" where date="+"'"+date+"' and time='"+time+"'";
System.out.println(sql);
ResultSet rs = statement.executeQuery(sql); 
//获得数据结果集合 
ResultSetMetaData rmeta = rs.getMetaData(); 
//确定数据集的列数，亦字段数 
int numColumns=rmeta.getColumnCount(); 
// 输出每一个数据值
String ans="";
while(rs.next()) {
	ans+="longitude "+rs.getString("longitude")+" "+
			"latitude " +rs.getString("latitude")+" "+
			"acceleration_x "+rs.getString("acceleration_x")+" "+
			"acceleration_y "+rs.getString("acceleration_y")+" "+
			"acceleration_z "+rs.getString("acceleration_z")+" "+
			"magnetic_x "+rs.getString("magnetic_x")+" "+
			"magnetic_y "+rs.getString("magnetic_y")+" "+
			"magnetic_z "+rs.getString("magnetic_z")+" "+
			"pressure "+rs.getString("pressure")+" "+
			"light_intensity "+rs.getString("light_intensity")+" "+
			"wifi_name "+rs.getString("wifi_name")+" "+
			"wifi_signal "+rs.getString("wifi_signal")+" "+
			"wifi_mac "+rs.getString("wifi_mac")+"  ";
} 
out.print(ans);
System.out.println(ans);

rs.close(); 
statement.close(); 
connection.close(); 

%> 