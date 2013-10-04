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
String acc_x=request.getParameter("Acl_x");
String acc_y=request.getParameter("Acl_y");
String acc_z=request.getParameter("Acl_z");
String wifi_name=request.getParameter("wifi_name");
String wifi_str=request.getParameter("wifi_str");
String longitude=request.getParameter("longitude");
String latitude=request.getParameter("latitude");
String url="jdbc:mysql://localhost/"+dbName+"?user="+userName+"&password="+userPasswd; 
Class.forName("com.mysql.jdbc.Driver").newInstance(); 
Connection connection=DriverManager.getConnection(url); 
Statement statement = connection.createStatement(); 
String sql = "insert into "+tableName+"(userID,deviceID,date,time,longitude,latitude," +
			"acceleration_x,acceleration_y,acceleration_z,magnetic_x,magnetic_y,magnetic_z,pressure,light_intensity,wifi_name, wifi_signal,wifi_mac) " +
			"values('"+userid+"','0','"+date+"','"+time+"" +
			"','"+longitude+"','"+latitude+"" + "','"+acc_x+"','"+acc_y+"','"+acc_z+"','0','0','0','0','0','"+wifi_name+"','"
			+wifi_str+"','"+0+"')";
System.out.println(sql);
PreparedStatement ps = null;
	Statement stmt = connection.createStatement();  
	ps = connection.prepareStatement(sql);
	int a = ps.executeUpdate();
stmt.close();  
%> 