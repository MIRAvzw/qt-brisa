
This file explains how to generate BRisa Documentation latex and html formats
using Sphinx and Doxygen documentation tools.

#### Installing Sphinx ####
 	You can install Sphinx typing one of the following
	commands on your terminal:
		$ sudo apt-get install python-sphinx
		$ easy_install -U Sphinx

#### Installing Doxywizard ####
	An easy way to use doxygen is installing Doxywizard, just type on your terminal:
	$ sudo apt-get install doxygen-gui


>> Creating BRisa Documentation latex format using Sphinx <<

	You just need to follow these steps to generate latex output:
	- enter /docSource directory
	- type the following command:
	$ make latex

	To create the pdf file from the latex output do the following:
	- enter /docSource/.build/latex directory 
	- type:
	$ make all-pdf

	the pdf file will be created inside this same directory


>> Creating BRisa Documentation html format using Sphinx <<
	
	All you need to do is:
	- enter /docSource directory
	- type the following command:
	$ make html

	the html folder will be created in side /docSource/.build folder

>> Creating html and latex output using Doxywizard <<
	- Specify Doxygen working directory on top of wizard screen
	- At Wizard tab on Project topic type Project name and version
	- Choose qt-brisa src folder as Source code directory and check scan recursively
	- Specify the output directory
	- At Wizard tab on Mode topic check All Entities and Include cross-referenced source code
	- At Expert tab on Project topic uncheck FULL_PATH_NAMES
	- At Expert tab on HTML topic check GENERATE_TREEVIEW
	- At Run tab click Run doxygen



