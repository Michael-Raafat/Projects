 //Initializing variables
 function task(name,date,disc){
        this.name = name;
        this.date = date;
		this.disc = disc
    }
var obj;

var InProgressList = [];
var DoneList = [];
var ArcList = [];
var userbasenumber = 0;
$(document).ready(
	function() {
$.getJSON('users.json',function (data) {
		obj2 = data;
		
		});
});
$(document).ready(
	function() {
	$.getJSON('users.json',function (data) {
		obj = data;
		userbasenumber = $(".userDecide")[0].id;
	InProgressList = obj[userbasenumber].plist.slice();
	DoneList = obj[userbasenumber].clist.slice();
	ArcList = obj[userbasenumber].alist.slice();
	updateCount();
	sortanddraw();
	});
	});
  /* This is the function that will get executed after the DOM is fully loaded */
  $(document).ready(
  function () {
	  
	  
    $( "#datepicker" ).datepicker({
	  minDate: new Date(), 
      changeMonth: true,//this option for allowing user to select month
      changeYear: true //this option for allowing user to select from year range
    });
 });
 $(document).ready(
  
  /* This is the function that will get executed after the DOM is fully loaded */
  function () {
    $( "#editdatepicker" ).datepicker({
	  minDate: new Date(), 
      changeMonth: true,//this option for allowing user to select month
      changeYear: true //this option for allowing user to select from year range
    });
 });
 
	
	var pageStatus = 1;
	var sorttype = 2;
	var rowtoedit;
//Drawing,Sorting and updating table and counts Functions
function drawTable(){
        var text = '<table id = "myTable" style = "background-color: #FFFFFF;" class="table table-hover" >';
        text += '<thead id = "myTableHead">';
		text += '<th style = "color : white ; width:10% " ></th>';
		text += '<th style = "color : white ; width : 45%" >';
		text += "Task</th>";
		text += '<th style = "color : white ; width : 30%">Due Date</th>';
		text += '<th style = "color : white ; width : 5% ">Select Task</th>';
		text +=	'</thead>';
		text += '<tbody id="tabody">';
		var m = 0;
		if(pageStatus === 1 || pageStatus === 2) {
        for(i = 0; i< InProgressList.length; i++){
            text += "<tr onmouseover='hoveringRow(this)' onmouseout='nothoveringRow(this)' id ='"+ m + "'>";
			text +='<td style = "width:10%"><div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown" id="options'+m+'" >Options';
			text +='  <span class="caret"></span></button>';
			text +=' <ul class="dropdown-menu">';
			text +='  <li><a href="#" onclick = "CompleteMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Completed</a></li>';
			text +='  <li><a href="#" onclick = "ArchiveMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Archive</a></li>';
			text +='  <li><a href="#" onclick = "DeleteMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Delete</a></li>';
			text +='  <li><a href="#" onclick = "EditMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Edit</a></li>';
			text +=' </ul></div></td>';
            text += '<td style = "width : 45%;cursor:pointer;color:blue;text-decoration: underline;" data-toggle = "tooltip" title = "'+InProgressList[i].disc+'"  >'+InProgressList[i].name+ "</td>";
            text += '<td style = "width : 30%" >'+InProgressList[i].date + "</td>";
			text += "<td style = 'width:5%'><input type = 'CheckBox' onclick = 'checkboxes(this,this.parentNode.parentNode)'></input></td>";
			m++;
            text += "</tr>";        }
		}
		m = InProgressList.length
		if(pageStatus === 3) {
		for(i = 0; i< DoneList.length; i++){
            text += "<tr onmouseover='hoveringRow(this)' onmouseout='nothoveringRow(this)' id ='"+ m + "'>";
            text +='<td style = "width:10%"><div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown" id="options'+m+'">Options';
			text +='  <span class="caret"></span></button>';
			text +=' <ul class="dropdown-menu">';
			text +='  <li><a href="#" onclick = "ArchiveMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Archive</a></li>';
			text +='  <li><a href="#" onclick = "DeleteMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Delete</a></li>';
			text +='  <li><a href="#" onclick = "EditMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Edit</a></li>';
			text +=' </ul></div></td>';
            text += '<td style = "width : 45%;cursor:pointer;color:blue;text-decoration: underline;" data-toggle = "tooltip" title = " '+DoneList[i].disc+'"  >'+DoneList[i].name +"</td>";
            text += "<td style = 'width : 30%'>"+DoneList[i].date + "</td>";
			text += "<td style = 'width:5%'><input type = 'CheckBox' onclick = 'checkboxes(this,this.parentNode.parentNode)'></input></td>";
			m++;
            text += "</tr>";        }
		}
		if(pageStatus === 1) {
		for(i = 0; i< DoneList.length; i++){
            text += "<tr onmouseover='hoveringRow(this)' onmouseout='nothoveringRow(this)'  id ='"+ m + "'>";
            text +='<td style = "width:10%"><div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown" id="options'+m+'">Options';
			text +='  <span class="caret"></span></button>';
			text +=' <ul class="dropdown-menu">';
			text +='  <li><a href="#" onclick = "ArchiveMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Archive</a></li>';
			text +='  <li><a href="#" onclick = "DeleteMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Delete</a></li>';
			text +='  <li><a href="#" onclick = "EditMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Edit</a></li>';
			text +=' </ul></div></td>';
            text += '<td style = "width : 45%;cursor:pointer;color:blue;text-decoration: underline;" data-toggle = "tooltip" title = " '+DoneList[i].disc+'"  >'+"<s>"+DoneList[i].name + "</s></td>";
            text += "<td style = 'width : 30%' ><s>"+DoneList[i].date + "</s></td>";
			text += "<td style = 'width:5%'><input type = 'CheckBox' onclick = 'checkboxes(this,this.parentNode.parentNode)'></input></td>";
			m++;
            text += "</tr>";        }
		}
		m += DoneList.length;
		if(pageStatus === 4) {
			for(i = 0; i< ArcList.length; i++){
            text += "<tr onmouseover='hoveringRow(this)' onmouseout='nothoveringRow(this)' id ='"+ m + "'>";
			text +='<td style = "width:10%"><div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown" id="options'+m+'">Options';
			text +='  <span class="caret"></span></button>';
			text +=' <ul class="dropdown-menu">';
			text +='  <li><a href="#" onclick = "DeleteMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Delete</a></li>';
			text +='  <li><a href="#" onclick = "EditMe(this.parentNode.parentNode.parentNode.parentNode.parentNode)">Edit</a></li>';
			text +=' </ul></div></td>';
            text += '<td style = "width : 45%;cursor:pointer;color:blue;text-decoration: underline;" data-toggle = "tooltip" title = " '+ArcList[i].disc+'"  >'+ArcList[i].name + "</td>";
            text += "<td style = 'width : 30%'>"+ArcList[i].date + "</td>";
            text += "<td style = 'width:5%'><input type = 'CheckBox' onclick = 'checkboxes(this,this.parentNode.parentNode)'></input></td>";
			m++;
            text += "</tr>";        }
		}
        text+= "</tbody></table>";
        document.getElementById("myTable").innerHTML = text;
		m--;
		$("#deschead").hide();
		while(m >= 0) {
			var idds = "#options";
			idds += m;
			$(idds).hide();
			$("#descr"+m).hide();
			m--;
		}
		$(".EditGROUP").hide();
    }
	
function sortlist(list , type) {
	if(type === 1) {
		list.sort(function(a,b) {
	if(a.name.localeCompare(b.name) == 0) {
		if(a.date === "" && b.date === "") {
		return 0;
		}else if(a.date === "") {
		return 1;
		} else if(b.date === "") {
		return -1;
		} else if(a.date < b.date) {
		return -1;
		} else if(a.date > b.date) {
		return 1;
		} else if(a.date === b.date) {
		return 0;
		}
	} else {
		return a.name.localeCompare(b.name);
		}});
	} else {
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
}

function mySortButton(type) {
	if(type === 1) {
		sorttype = 1;
		sortanddraw();
	} else {
		sorttype = 2;
		sortanddraw();
	}
}


function sortanddraw() {
	if(pageStatus === 1) {
		sortlist(InProgressList,sorttype);
		sortlist(DoneList,sorttype);
	} else if(pageStatus === 2) {
		sortlist(InProgressList,sorttype);
	} else if(pageStatus === 3) {
		sortlist(DoneList,sorttype);
	} else if(pageStatus === 4) {
		sortlist(ArcList,sorttype);
	}
	drawTable();
}
function updateCount() {
	var numItemsP = InProgressList.length;
		var numItemsD = DoneList.length;
		var numItemsA = ArcList.length;
		var totalnum =numItemsD + numItemsP;
		$("#PText").html("In Progress <span class='badge'>"+numItemsP+" </span>");
		$("#DText").html("Completed <span class='badge'>" + numItemsD+" </span>" );
		$("#AText").html("Archived <span class='badge'>" + numItemsA +" </span>");
		$("#AllText").html("All Tasks <span class='badge'>" + totalnum +" </span>");
}

//Options button functions,appearing && Disappearing
function hoveringRow(x) {
	x.setAttribute("style","background-color: #929292");
	$("#options"+x.id).show();
	$("#descr"+x.id).show();
	$("#deschead").show();
}
	
function nothoveringRow(x){
	if(x.className !== 'Chosen') {
	x.setAttribute("style","background-color: #FFFFFF");
	$("#options"+x.id).hide();
	$("#descr"+x.id).hide();
	$("#deschead").hide();
	} else {
		x.setAttribute("style","background-color: #FCF6A2");
		$("#options"+x.id).hide();
		$("#descr"+x.id).hide();
		$("#deschead").hide();
	}
}
	
function EditMe(x) {
	var slide = Number(x.id);
	rowtoedit = slide;
	var inpro = InProgressList.length;
	var dopro = DoneList.length;
	var arc = ArcList.length;
	var curtask;
	var curdate;
	var curdesc;
	if( slide< inpro) {
		curtask = InProgressList[slide].name;
		curdate = InProgressList[slide].date;
		curdesc = InProgressList[slide].disc;
	} else if( slide < inpro + dopro) {
		curtask = DoneList[slide -inpro].name;
		curdate = DoneList[slide -inpro].date;
		curdesc = DoneList[slide -inpro].disc;
	} else {
		curtask = ArcList[slide -inpro - dopro].name;
		curdate = ArcList[slide -inpro - dopro].date;
		curdesc = ArcList[slide -inpro - dopro].disc;
	}
	document.getElementById("task").value = "";
	document.getElementById("datepicker").value="";
	document.getElementById("desc").value="";
	$(".ADDGROUP").hide();	
	$("#showaddrow").hide();
	$(".EditGROUP").show();
	document.getElementById("edittask").value = curtask;
	document.getElementById("editdatepicker").value = curdate;
	document.getElementById("editdesc").value = curdesc;
}

function yesEdit() {
	$(".EditGROUP").hide();
	$("#showaddrow").show();
	myCopyFunction();
	var n = rowtoedit;
	var inpro = InProgressList.length;
	var dopro = DoneList.length;
	var ttask=document.getElementById("edittask").value;
	var date=document.getElementById("editdatepicker").value;
	var desc = document.getElementById("editdesc").value;
	if (ttask.trim() == "") {
		alert("Can't edit to empty task");
		updateCount();
	sortanddraw();
	} else {
	var newTask = new task(ttask,date,desc);
	if( n < inpro) {
		InProgressList[n] = newTask ; 
	} else if( n < inpro + dopro) {
		DoneList[n -inpro] = newTask ; 
	} else {
		ArcList[n -inpro - dopro] = newTask ; 
	}
	upgradedatabase();
	}
}

function noEdit() {
	$(".EditGROUP").hide();
	$("#showaddrow").show();
}

function CompleteMe(x) {
	if(confirm("Are you sure you want to mark as done the selected item ?")) {
			myCopyFunction();
			var slide = x.id;
			var inpro = InProgressList.length;
			var dopro = DoneList.length;
			var arc = ArcList.length;
			var num = Number(slide)
			if( num < inpro) {
				DoneList[DoneList.length] = InProgressList[num];
				InProgressList.splice(num,1);
			}
			upgradedatabase();
		}
}	
	
function ArchiveMe(x) {
	if(confirm("Are you sure you want to Archive the selected item ?")) {
			myCopyFunction();
			var slide = x.id;
			var inpro = InProgressList.length;
			var dopro = DoneList.length;
			var arc = ArcList.length;
			var num = Number(slide)
			if( num < inpro) {
				ArcList[ArcList.length] = InProgressList[num];
				InProgressList.splice(num,1);
			} else if( num < inpro + dopro) {
				ArcList[ArcList.length] = DoneList[num -inpro];
				DoneList.splice(num -inpro,1);
			}
			upgradedatabase();
		}
}	
	
function DeleteMe(x) {
	if(confirm("Are you sure you want to delete the selected item ?")) {
			myCopyFunction();
			var slide = x.id;
			var inpro = InProgressList.length;
			var dopro = DoneList.length;
			var arc = ArcList.length;
			if( slide< inpro) {
				InProgressList.splice(slide,1);
			} else if( slide < inpro + dopro) {
				DoneList.splice(slide -inpro,1);
			} else {
				ArcList.splice(slide -inpro - dopro,1);
			}
			upgradedatabase();
		}
}	

//Selecting tasks and deleting them
function checkboxes(x , y) {
	
    if(x.checked) {
       y.className = "Chosen";
	   document.getElementById("task").value = "";
		document.getElementById("datepicker").value="";
		$(".ADDGROUP").hide();	
		$("#showaddrow").show();
		$("#selected").html('<input type="button" value="Delete Selected rows" onclick = "delrows()" id="delRows" class="btn btn-primary" />');
    } else {
		y.className = "";
		if($(".Chosen").length === 0) {
			$("#selected").html('<input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()"class="btn btn-primary" />');
		}
	}
	}

function delrows(){
		if(confirm("Are you sure you want to delete all the selected items ?")) {
			myCopyFunction();
			var slides = document.getElementsByClassName("Chosen");
			var inpro = InProgressList.length;
			var dopro = DoneList.length;
			var arc = ArcList.length;
			for(var i = slides.length - 1; i >= 0; i--)
			{
				if( slides.item(i).id < inpro) {
					InProgressList.splice(slides.item(i).id,1);
				} else if( slides.item(i).id < inpro + dopro) {
					DoneList.splice(slides.item(i).id -inpro,1);
				} else {
					ArcList.splice(slides.item(i).id -inpro - dopro,1);
				}
			}
			upgradedatabase();
		}
	}
//Adding new tasks,Add Button and showing the add objects
$(document).ready(function(){
	$("#hideaddrow").click(function(){
		document.getElementById("task").value = "";
		document.getElementById("datepicker").value="";
		$(".ADDGROUP").hide();	
		$("#showaddrow").show();
	}); 
});

$(document).ready(function(){
	$('#addRow').on( 'click', function () {
		myCopyFunction();
		var ttask=document.getElementById("task").value;
		var date=document.getElementById("datepicker").value;
		var disc = document.getElementById("desc").value;
		var newTask = new task(ttask,date,disc);
		if(ttask.trim() == "") {
			alert("can't add empty task");
			document.getElementById("task").value = "";
			document.getElementById("datepicker").value="";
			document.getElementById("desc").value="";
			$(".ADDGROUP").hide();	
			$("#showaddrow").show();
		} else {
		InProgressList[InProgressList.length] = newTask;
		document.getElementById("task").value = "";
		document.getElementById("datepicker").value="";
		document.getElementById("desc").value="";
		$(".ADDGROUP").hide();	
		$("#showaddrow").show();
		upgradedatabase();
		}
    } );
});
var obj2;
var copyP = [];
var copyC = [];
var copyA = [];

function myCopyFunction () {
	copyP = [];
	copyC = [];
	copyA = [];
	for (var i = 0 ; i < InProgressList.length ; i++) {
		copyP.push(InProgressList[i]);
	}
	for (var i = 0 ; i < ArcList.length ; i++) {
		copyA.push(ArcList[i]);
	}
	for (var i = 0 ; i < DoneList.length ; i++) {
		copyC.push(DoneList[i]);
	}
}
function upgradedatabase() {
	
	obj2[userbasenumber].plist = InProgressList.slice();
	obj2[userbasenumber].clist = DoneList.slice();
	obj2[userbasenumber].alist = ArcList.slice() ;
	$.ajax({
        url: '/home',
        data: {myplist : JSON.stringify(obj2[userbasenumber].plist, null, 4), index : userbasenumber,myalist : JSON.stringify(obj2[userbasenumber].alist, null, 4),myclist : JSON.stringify(obj2[userbasenumber].clist, null, 4),cclist : JSON.stringify(copyC, null, 4),calist :JSON.stringify(copyA, null, 4),cplist : JSON.stringify(copyP, null, 4)},
        type: 'POST',
        success: function (data) {
			if(!data.success) {
			post('/dbl',null);
			}
        },
        error: function (xhr, status, error) {
			if(error.message!= undefined) {
            alert(console.log('Error: ' + error.message));}
        },
    });
	updateCount();
	sortanddraw();
	}

function showaddrow(){
		$("#showaddrow").hide();		
		$(".ADDGROUP").show();
	}
$(document).ready(function(){
	$(".ADDGROUP").hide();
	$(".EditGROUP").hide();
	$("#showaddrow").show();
});

//Chossing elements of the table
$(document).ready(function(){
	$(".ShowDone").click(function(){
		pageStatus = 3;
		$(".InProgress").hide();
		$(".EditGROUP").hide();
		$(".Archived").hide();		
		$(".Done").show();		
		$(".ADDGROUP").hide();
		$("#Current").html('<h1 id = "Current" class = "container-fluid">Completed Tasks<div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown">Sort By<span class="caret"></span></button><ul class="dropdown-menu"><li><a href="#" onclick = "mySortButton(1)">Name</a></li><li><a href="#" onclick = "mySortButton(2)">Date</a></li></ul></div></h1>');
		$("#selected").html('<input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()"class="btn btn-primary" />');
		sortanddraw();
	}); 
});
$(document).ready(function(){
	$(".ShowArch").click(function(){
		pageStatus = 4;
		$(".InProgress").hide();
		$(".EditGROUP").hide();
		$(".Done").hide();
		$(".Archived").show();
		$("#selected").html('<input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()"class="btn btn-primary" />');		
		$(".ADDGROUP").hide();
		$("#Current").html('<h1 id = "Current" class = "container-fluid">Archived Tasks<div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown">Sort By<span class="caret"></span></button><ul class="dropdown-menu"><li><a href="#" onclick = "mySortButton(1)">Name</a></li><li><a href="#" onclick = "mySortButton(2)">Date</a></li></ul></div></h1>');
		sortanddraw();
	}); 
}); 
$(document).ready(function(){
	$(".ShowInProgress").click(function(){
		pageStatus = 2;
		$(".Done").hide();
		$(".EditGROUP").hide();
		$(".Archived").hide();
		$(".InProgress").show();
		$("#selected").html('<input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()"class="btn btn-primary" />');		
		$(".ADDGROUP").hide();
		$("#Current").html('<h1 id = "Current" class = "container-fluid">In-Progress Tasks<div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown">Sort By<span class="caret"></span></button><ul class="dropdown-menu"><li><a href="#" onclick = "mySortButton(1)">Name</a></li><li><a href="#" onclick = "mySortButton(2)">Date</a></li></ul></div></h1>');
		sortanddraw();
	}); 
});


$(document).ready(function(){
	$(".ShowAll").click(function(){
		pageStatus = 1;
		$(".Done").show();
		$(".Archived").hide();
		$(".EditGROUP").hide();
		$(".InProgress").show();
		$("#selected").html('<input type="button" value="Add Task" id="showaddrow" onclick = "showaddrow()"class="btn btn-primary" />');		
		$(".ADDGROUP").hide();
		$("#Current").html('<h1 id = "Current" class = "container-fluid">All Tasks<div class="dropdown"><button class="btn btn-primary dropdown-toggle" type="button" data-toggle= "dropdown">Sort By<span class="caret"></span></button><ul class="dropdown-menu"><li><a href="#" onclick = "mySortButton(1)">Name</a></li><li><a href="#" onclick = "mySortButton(2)">Date</a></li></ul></div></h1>');
		sortanddraw();
	}); 
});

 function post(path, parameters) {
        var form = $('<form></form>');

        form.attr("method", "post");
        form.attr("action", path);

        $.each(parameters, function(key, value) {
            if ( typeof value == 'object' || typeof value == 'array' ){
                $.each(value, function(subkey, subvalue) {
                    var field = $('<input />');
                    field.attr("type", "hidden");
                    field.attr("name", key+'[]');
                    field.attr("value", subvalue);
                    form.append(field);
                });
            } else {
                var field = $('<input />');
                field.attr("type", "hidden");
                field.attr("name", key);
                field.attr("value", value);
                form.append(field);
            }
        });
        $(document.body).append(form);
        form.submit();
    }
