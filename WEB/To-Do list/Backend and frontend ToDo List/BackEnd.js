 var express = require('express');

var app = express();
var fs = require('fs');
var bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true }));
var session = require('express-session');
app.use(session({secret: 'SecurityKeyIDontKnowWhatIsHappening',resave: true,saveUninitialized : false}));

app.use(express.static('public'));
function row(email,name,pass){
        this.email = email;
        this.name = name;
		this.pass = pass;
		this.plist = [];
		this.clist = [];
		this.alist = [];
  }

  
 function sortingMyList(list) {
	 list.sort(function(a,b) {
	if(a.date === "" && b.date === "") {
		return a.name.localeCompare(b.name);
	}else if(a.date === "") {
		return 1;
	} else if(b.date === "") {
		return -1;
	} else if(a.date < b.date) {
		return -1;
	} else if(a.date > b.date) {
		return 1;
	} else if(a.date === b.date) {
		return a.name.localeCompare(b.name);
		}});
 }
  
  
 app.get('/logout', function (req, res) {
	 if(req.session.email) {
		delete req.session.email; 
	 }
	res.redirect('/');
});      
  
   
app.get('/home', function(req, res) {
	if(req.session.email) {
		res.sendFile(__dirname +'/UsersDB/'+req.session.email+'.html');
	} else {
		res.redirect('/');
	}
})
 

app.get('/', function (req, res) {
	if(req.session.email) {
		res.redirect('/home');
	} else {
		res.sendFile( __dirname + "/" + "SignIn.html" );
	}
})


app.post('/', function (req, res) {
	
	var file_content = fs.readFileSync(__dirname +'/public/users.json');
	var content = JSON.parse(file_content);
	var obj = content;
	var newrow = new row(req.body.user.email,req.body.user.name,req.body.user.pass);
	obj.push(newrow);
	content = obj;
   fs.writeFileSync(__dirname +'/public/users.json', JSON.stringify(content, null, 4));
   
   
   var htmlfile = '<!DOCTYPE html ><html><head lang="en"><title>To-do App</title><link rel="stylesheet" href="jquery-ui.css" /><script src="jquery.js"></script><script src="jquery-ui.js"></script><link rel="stylesheet" href="jquery.dataTables.min.css" />';
	htmlfile +=	'<link rel="stylesheet" href="MyPoor.css" /><script src="jquery.dataTables.min.js"></script><script src="bootstrap.min.js"></script><meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" ><link rel="stylesheet" href="bootstrap.min.css"><script src="max.js"></script><meta charset="utf-8"><link href="shop-item.css" rel="stylesheet"><link href="navbar-top-fixed.css" rel="stylesheet"><link href="simple-sidebar.css" rel="stylesheet">';
	htmlfile +=	'<style>tr.ex:hover {background-color: red;color : white;}tr.ex1:hover {background-color: blue; color : white;}tr.ex2:hover {background-color: purple; color : white;}tr.ex3:hover {background-color: orange; color : white;}.Chosen {background-color: #FCF6A2;}#myTableHead {background-color: black;}#myTable {table-layout:fixed;width: 100%;}td {word-wrap:break-word;}</style></head>';
	htmlfile += '<body><nav class="navbar navbar-inverse navbar-fixed-top" role="navigation" style = "background-color : white ; border : white"><div class="container" align = "center"><h1 class = "userDecide" id ="'+(obj.length-1)+'"> <strong>To-Do App</strong> </h1><br>	</div></nav>';
	htmlfile += '<div id="wrapper"><div id="sidebar-wrapper"><ul class="sidebar-nav"><br> <h1 style ="text-align : center ; font-family : arial ; color : white "> <strong>   To-do Filter </strong> </h1><br> <br>';
    htmlfile +=       '<li><a>'+req.body.user.name.toUpperCase()+'</a></li><br><li class = "ShowAll"><a href="#" id = "AllText">All tasks</a></input></li><br><li class = "ShowDone"><a href="#" id = "DText">Completed</a></input></li><br><li class = "ShowInProgress"><a href="#" id = "PText">In Progress</a></li><br><li class = "ShowArch"><a href="#" id = "AText">Archived</a></li><li><a href="/logout">Sign Out</a></li></ul></div>';

    htmlfile +=    '<div id="page-content-wrapper"><div class="container-fluid"><div class="row"><div class="col-lg-12"><br><h1 id = "Current" class = "container-fluid">All Tasks<div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown">Sort By<span class="caret"></span></button><ul class="dropdown-menu"><li><a href="#" onclick = "mySortButton(1)">Name</a></li><li><a href="#" onclick = "mySortButton(2)">Date</a></li></ul></div></h1>';
						
						
			
	htmlfile +=		'<table id = "myTable" style = "background-color: #FFFFFF ;  width : 100%" class="table table-hover" ><thead id = "myTableHead"><th style = "color : white; width:10%;" ></th><th style = " color : white ;width : 45%">Task</th><th style = " color : white ; width : 30%" >Due Date</th><th style = "color : white;width:5%;">Select Task</th></thead><tbody id="tabody"></tbody></table>';
			
htmlfile +=			'<p class = "ADDGROUP" style = "">Task : </p>';
htmlfile +=			'<table width = "15%">';
htmlfile +=			'<tr><td>';
htmlfile +=			'<input type="text" name="task" id = "task" class = "ADDGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter your task.."/>';
htmlfile +=			'</td></tr>';
htmlfile +=			'</table ><br>';
htmlfile +=			'<p class = "ADDGROUP">Due Date : </p>';
htmlfile +=			'<table width = "15%"><tr><td>';
htmlfile +=			'<input type="text" name ="date"id = "datepicker" class = "ADDGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter date.." />';
htmlfile +=			'</td></tr></table><br>';
htmlfile +=			'<p class = "ADDGROUP">Description : </p>';
htmlfile +=			'<table width = "15%"><tr><td>';
htmlfile +=			'<textarea type="text" name ="desc"id = "desc" class = "ADDGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter Description.."></textarea><!--<input type="text" name ="desc"id = "desc" class = "ADDGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter Description.." />-->';
htmlfile +=			'</td></tr></table><br>';
htmlfile +=			'<input type="submit" value="Add" name="button" id = "addRow" class = "ADDGROUP ; btn btn-primary" />';
htmlfile +=			'<input type="submit" value="Cancel" name="button" id = "hideaddrow"  class = "ADDGROUP ; btn btn-primary" />';
htmlfile +=			'<div id = "selected"><input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()" class="btn btn-primary" /></div>';
			
			
htmlfile +=			'<p class = "EditGROUP" style = "">Task : </p>';
htmlfile +=			'<table width = "15%">';
htmlfile +=			'<tr><td>';
htmlfile +=			'<input type="text" name="edittask" id = "edittask" class = "EditGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter your task.."/>';
htmlfile +=			'</td></tr>';
htmlfile +=			'</table ><br>';
htmlfile +=			'<p class = "EditGROUP">Due Date : </p>';
htmlfile +=			'<table width = "15%"><tr><td>';
htmlfile +=			'<input type="text" name ="editdate"id = "editdatepicker" class = "EditGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter date.." />';
htmlfile +=			'</td></tr></table><br>';
htmlfile +=			'<p class = "EditGROUP">Description : </p>';
htmlfile +=			'<table width = "15%"><tr><td>';
htmlfile +=			'<textarea type="text" name ="editdesc"id = "editdesc" class = "EditGROUP ; form-control" style = "border : 1px solid black" placeholder="Enter description.." ></textarea>';
htmlfile +=			'</td></tr></table><br>';
htmlfile +=			'<input type="submit" value="Edit" name="button" id = "editRow" onclick = "yesEdit()" class = "EditGROUP ; btn btn-primary" />';
htmlfile +=			'<input type="submit" value="Cancel" name="button" id = "hideeditrow" onclick = "noEdit()" class = "EditGROUP ; btn btn-primary" />';
htmlfile +=			'</div></div></div></div></div></body></html>';
   
   fs.writeFileSync(__dirname +'/UsersDB/'+req.body.user.email+'.html', htmlfile);
   res.sendFile( __dirname + "/" + "SignIn.html" );
})


app.get('/register', function (req, res) {
   res.sendFile( __dirname + "/" + "Register.html" );
})


app.post('/home', function (req, res) {
	if (req.body.myobject == undefined && req.body.email != undefined) {
		req.session.email = req.body.email;
		res.sendFile(__dirname +'/UsersDB/'+req.body.email+'.html');
	} else {
		if (req.session.email) {
			var file_content = fs.readFileSync(__dirname +'/public/users.json');
			var content = JSON.parse(file_content);
			sortingMyList(content[req.body.index].plist);
			sortingMyList(content[req.body.index].clist);
			sortingMyList(content[req.body.index].alist);
			var copyC = JSON.parse(req.body.cclist);
			sortingMyList(copyC);
			var copyA = JSON.parse(req.body.calist);
			sortingMyList(copyA);
			var copyP = JSON.parse(req.body.cplist);
			sortingMyList(copyP);
			var equal = false;
			if (JSON.stringify(copyA) == JSON.stringify(content[req.body.index].alist) && JSON.stringify(copyP) == JSON.stringify(content[req.body.index].plist) && JSON.stringify(copyC) == JSON.stringify(content[req.body.index].clist)){
				equal = true;
			}
			if(content[req.body.index].email != req.session.email) {
				equal = false;
			}
			if(equal) {
			content[req.body.index].plist = JSON.parse(req.body.myplist);
			content[req.body.index].alist = JSON.parse(req.body.myalist);
			content[req.body.index].clist = JSON.parse(req.body.myclist);
			fs.writeFileSync(__dirname +'/public/users.json', JSON.stringify(content, null, 4));
			res.json({success:true,text:":D"});
			} else {
				res.json({success:false,text:":("});
			}
	}
	else {
			res.redirect('/');
		}
	}
	
})

app.post('/dbl',function (req, res) {
	res.sendFile(__dirname +'/dbl.html');
})

app.get('*',function(req, res) {
	res.send('Error 404 : This Page is like my grades....NON-EXISTANT');
})
var server = app.listen(8081, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Example app listening at http://%s:%s", host, port)

})