<h1 align="center">Header42</h1>

<p align="center">A simple script for ADD,UPDATE or DELETE your headers to files just with one click(or typing command). Works cross-platform for Linux,MacOS or Windows.*</p>



#### **Build & Run**

To build/compile type following command in your command prompt
>Make  
or  
CMake  

And change your directory to repository path
Then run ./HeaderReplacer *


    cd /Desktop/Header42
    ./HeaderReplacer *

This command detect all .c files in root directory(Desktop/Header42) and will add headers to them. You can configure it with **Flags**

#### **Flags**

> USER **-u**  
Default Value: value of $USER  

------------

> Source Files **-f**  
Default Value: .c  
Note: File extensions separate by , so you can specify multiple files with -f  .c,.h  

    ./HeaderReplacer -u Trou95 main.c
	or
	./HeaderReplacer -u Trou95 -f  .c
	# Both commands above is same because .c default value of -f 

This command will out main.c at /output/main.c


------------
> Output Path **-o**  
Default Value: /output  

------------
> Recursive **-r**  
Default Value: None  

With -r flag you can enable scan subdirectories recursively 
So if your have file structure like this;

 ┣ 📂Libft  
 ┃ ┗ 📜ft_split.c  
 ┃ ┗ 📜ft_strjoin.c  
 ┃ ┗ 📜...  
 ┣ 📂Utils  
 ┃ ┗ 📜utils.c  
 ┃ ┣ 📂math  
 ┃ ┗ 📜math.c  
 ┣ 📜.main.c  
 
     ./HeaderReplacer -r *
 After run command above will out; 
                

+ main.c
+ output/Libft
    + ft_split.c
    + ft_strjoin.c
    + ...
+ output/Utils
 + output/Utils/math
    * math.c
  + utils.c
  
  

------------

> Header **-h**  
Default Value: false  
Add header to target files. (this flag for removing headers from files automatically)  

------------

> Logging **-l**  
Default Value: true  
