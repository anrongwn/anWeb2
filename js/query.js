function init()
{
    document.getElementById("bn1").onclick=onclear;
    document.getElementById("bn2").onclick=onquery;
    document.getElementById("bn3").onclick=onback;

    document.ondblclick=function(){return false;};
};

function onclear(){
     document.getElementById("in1").value = "";
}

function onquery(){
    var tmp = document.getElementById("in1").value;

};

function onback(){
    var tmp = document.getElementById("in1").value;
    var cmd = {
        id:"mainmenu",
        page:"index.html",
        js:"mainmenu.js",
        param:tmp
    };

    context.caller(cmd);
    cmd=null;
};


