# RoyalRender-OpenExtensions
Extensions for Royal Render by Customers



===========

# What is this?
===========


This git repo should be used by RR customer or the RR staff to make custom extensions available to other RR customers.


===========

# Usage
===========


If you have any file that you want to share, then you have to create a folder for your files.
The folder always starts with the date in reverse. The 1. June 2015 woud be 150601.
Then add a descriptive name, e.g.  150601_Maya2016_Particlecaching.
Add a ReadMe.txt file with your name, company, the RR version you used and a description.

The location of your folder in this git depends on which files the extension includes.

\ _plugins \ control \ 150601_MyLittleImprovement
A plugin file for rrControl, this can be a client or job, a once or perjob/perclient script.

\ _plugins \ server_notify \ 150601_MyLittleImprovement
A notification plugin.

\ _plugins \ submitter \ 150601_MyLittleImprovement
A onSubmission plugin or scene parser.

\ _pre_postscripts \ 150601_MyLittleImprovement
A Pre, Preview, Post, Finished script file

\ _render_app \ 150601_MyLittleImprovement
A render config, submission plugin, installation location file, render script, ...

\ _sub \ 150601_MyLittleImprovement
A config file for RR like a submitter preset file or a website template

\ 150601_MyLittleImprovement
Your Extension covers files from multiple areas. 
Or it can even be a pull of your whole RR folder
In this case you should use .gitignore files in each folder to ignore the official RR release files.



