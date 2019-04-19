
function init()
{
    document.getElementById("bn1").onclick=onwithdrawal;
    document.getElementById("bn2").onclick=onquery;
};

function onwithdrawal(){
    var tmp = document.getElementById("in1").value;
    var cmd = {
        id:"withdrawal",
        page:"withdrawal.html",
        js:"withdrawal.js",
        param:tmp
    };

    context.caller(cmd);
    cmd=null;
};

function onquery(){
    var tmp = document.getElementById("in1").value;
    var cmd = {
        id:"query",
        page:"query.html",
        js:"query.js",
        param:tmp
    };

    context.caller(cmd);
    cmd=null;
};
init();
