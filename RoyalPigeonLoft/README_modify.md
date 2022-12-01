### Client commands ###

To change the commands that are available for selected clients on the website, you have to edit 2 files.

1)
The file RoyalPigeonLoft\src\server_api.py contains a conversion list named client_commands.
It contains a list of all commands that are known to this website.

For example   "abort": "cAbort"
The first  "abort" is the internal name of the command in these website sources. (see next section)
You can choose any name.
The second "cAbort" is the name of the command that will be send to RR.
This name is taken from the Python SDK docs.

2)
RoyalPigeonLoft\templates\includes\_client_btnstoolbar.html
This is the actual website visible to the user.
The commands of the dropdown are added with this line:
<a class="dropdown-item" href="#" onclick="execute_command_on_selected_clients('abort')">Abort</a>

'abort' is the internal name of the command in these website sources. (see last section).
>Abort< is the name displayed to the end user.


