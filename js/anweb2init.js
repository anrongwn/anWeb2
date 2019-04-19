var context;

function anweb2init()
{
    if (typeof QWebChannel != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
        context = channel.objects.context;
        }
        );
    }
    else
    {
        console.error("qt object created failed!");
    }
	
};

anweb2init();
