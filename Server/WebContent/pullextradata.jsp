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
String ans;
out.print(ans);  //返回请求的信息
System.out.println(ans);


%> 