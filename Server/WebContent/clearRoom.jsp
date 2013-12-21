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
String sql = "update "+tableName+" set pos_1=0 ,pos_2=0 ,pos_3=0 ,pos_4=0 ,pos_5=0 ,pos_6=0 ,pos_7=0 ,pos_8=0,"+
	"hero_1=1,hero_2=1,hero_3=1,hero_4=1,hero_5=1,hero_6=1,hero_7=1,hero_8=1,"+
	"team_1=0,team_2=0,team_3=0,team_4=0,team_5=0,team_6=0,team_7=0,team_8=0　"+
	"where id="+input;
System.out.println(sql);
PreparedStatement ps = null;
Statement stmt = connection.createStatement();  
ps = connection.prepareStatement(sql);
int a = ps.executeUpdate();
stmt.close();  
%> 
