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
String input2=request.getParameter("userid");
String input3=request.getParameter("opos");
String input4=request.getParameter("pos");
String url="jdbc:mysql://localhost/"+dbName+"?user="+userName+"&password="+userPasswd; 
Class.forName("com.mysql.jdbc.Driver").newInstance(); 
Connection connection=DriverManager.getConnection(url); 
Statement statement = connection.createStatement();
String sql = "update "+tableName+" set pos_"+input3+"=0 ,pos_"+input4+"="+input2+" where id="+input;
System.out.println(sql);
PreparedStatement ps = null;
Statement stmt = connection.createStatement();  
ps = connection.prepareStatement(sql);
int a = ps.executeUpdate();
stmt.close();  
%> 