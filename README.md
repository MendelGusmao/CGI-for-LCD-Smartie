CGI FOR LCD SMARTIE 0.1-alpha

    This document describes the basic concept and usage of CGI for LCD Smartie.

    CGI for LCD Smartie is designed to be a fast gateway between LCD Smartie and language 
    interpreters such as PHP, Ruby and Python, making it easier to gather information to 
    show on the display without the need to create new plugins.

    The software is made from two parts: a server (cgi4lcd.exe) and a plugin (cgi.dll).
    The plugin is responsible for sending the command to the server, receiving a response and
    relaying it to LCD Smartie.
    The server receives the command, executes the specified interpreter and stores the command 
    and its response in a queue. At a specified time it will run the command, caching its result. 
    When the plugin asks the server for the response of a command, it will deliver the cached 
    result instead of executing the interpreter again.

WHY PHP FOR LCD SMARTIE IS NOW CGI FOR LCD SMARTIE?

    In the previous version, the plugin was responsible for executing the interpreter. This way of 
    operation had many problems because it freezes LCD Smartie until the interpreter has finished 
    its execution. The time between interpreter initialization and output display depends on many 
    factors but mainly by the complexity of the script that was run.

WHEN IT WILL BE USEFUL?

    - If you want to gather data from databases or internet applications
    - You want to do that in a short timespan, using your preferred programming language
    - You don't have patience to build complex plugins using C++, Delphi or VB
    - You are really not interested in worrying about pointers, variable types, compilation and other 
      things that strongly typed languages has to bother you

WHEN IT WILL NOT BE USEFUL?

    - Basically, for everything that demands fast or realtime data displaying of data, like graph bars

INSTALLING

    Download plugins and scripts folder and copy them to your LCD Smartie folder

CONFIGURING

    All configuration is done by cgi4lcd.ini (avaliable in scripts folder).

    The first section is [cgi4lcd] and it has the following attributes:
    
      - interval (numeric, milliseconds)
	Value to tell the server of how often a command it will be executed

      - timeout (numeric, milliseconds)
	Value to tell the server of how long after the command is not requested by the
	plugin to remove it from the queue

      - port (numeric, 1-65535)
	A numeric value representing the UDP port that will be used for the communication between
	server and plugin

      - default (text)
	The default file extension to be considered by the plugin if not specified in the filename passed
	to $dll

      - show_window (boolean, 0/1)
	If the value is 1, the server window will appear when it's executed, showing the queue
	processing and incoming requests

    The subsequent sections are named with the common file extension of the language. They have the following
    properties:

      - language (text)
	Language name for the extension. Not used right now

      - interpreter (text)
	Absolute path for the language interpreter

      - command
	The command line to execute the script. It has variables that are replaced when the plugin sends the
	command to the server. They are:

	  - %scripts_path%
	    The absolute path to <LCD Smartie path>\scripts folder

	  - %bootstraps_path%
	    The absolute path to <LCD Smartie path>\scripts\bootstraps folder

	  - %script%
	    The absolute path to <LCD Smartie path>\scripts\<script> file

	  - %params%
	    Function name or function name and parameters specified in the last argument passed to $dll

	  - %interpreter%
	    The path specified in the property interpreter

      - version
	Command line to get the interpreter version

    CGI4LCD comes with the basic settings to run PHP, Ruby, Python, Perl and DOS Batch scripts. You must
    only change the interpreter path and it will be ready to use.

USING

    There is only one working function in the plugin and it takes 2 parameters:

        - filename - mandatory. it must exist in scripts folder.
	  The extension is optional. If not passed, the plugin will use the default extension
	  set in the section cgi4lcd of the configuration file
        - function (optional) and arguments (separated by semicolons), also optional

        Syntax: $dll(cgi,1,filename[.extension],[function[#arg1;arg2;...]])

    There are three possible usages for code executing:

        1 - Executing a PHP file

            > $dll(cgi,1,file[.ext],)

        2 - Executing a function of a PHP file without arguments

            > $dll(cgi,1,file[.ext],function)

        3 - Executing a function of a PHP file with arguments

            > $dll(cgi,1,file[.php],function#arg1;arg2;argX)

WRITING SCRIPTS

    First of all, you'll need to know what is a bootstrap. It's a piece of code responsible for
    calling a function, retrieving its result and printing to the screen, so the server can grab
    it and relay it to the plugin. Bootstraps are optional if your script directly outputs data 
    but mandatory if you want to group functions in a file.

    For now, CGI4LCD comes with bootstraps written in PHP, Ruby, Python and Perl. A Go version is
    in the repository - but still just a concept.

    The script must be saved in scripts folder and has the following structure:

	<include bootstrap>
	
	<declare functions>

	main(); # Execute bootstrap

    or

	<write code that writes directly to the screen>

    The scripts directory is full of test.<extension> files that describes the basics of writing 
    functions. Try it yourself:

    $dll(cgi,1,test,hello) -> Hello, world!
    $dll(cgi,1,test,hi#Mendel) -> Hi, Mendel
    $dll(cgi,1,test,do_some_math#1;2;3) -> 5

LANGUAGE SPECIFICS

    - PHP
      To give some boost in PHP process startup, I decided to include a php.ini in scripts
      directory. This is a stripped version that doesn't make PHP load too many extensions.
      However, if you need to load a specific extension, just uncomment the line, as you would
      do normally.

    - Python
      While PHP, Ruby and Perl allows to pass a file from the command line to be included in the
      called script, Python doesn't. When writing a Python script, write in the first line:
  
	  from bootstraps import main

ISSUES

    - It works only with LCD Smartie 5.4 (I mean not with the recent 5.4.2.92b)
    - <Your complaint here>

TODO

    - Rewrite almost every function or method to use char* instead of strings
    - Make the plugin run cgi4lcd.exe if it's not being executed
    - <Your suggestion here>

FINALLY

    if ($questions || $suggestions)
        send_email("mendelsongusmao+cgi4lcd@gmail.com");