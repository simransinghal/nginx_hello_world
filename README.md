# nginx Hello World!

Update system:

	$ sudo apt update && sudo apt upgrade -y

NGINX is a program written in C, so we need to install the C compiler (GCC).

	$ sudo apt install build-essential -y

Download the NGINX source code and extract it:

	$ wget https://nginx.org/download/nginx-1.13.1.tar.gz && tar zxvf nginx-1.13.1.tar.gz

Install pcre3:

	$ sudo apt-get install libpcre3 libpcre3-dev

Go to the NGINX source directory:

	$ cd ~/nginx-1.13.1

Clone the repository:

	$ git clone https://github.com/simransinghal/nginx_hello_world.git

Compile the module:

	$ ./configure --with-compat --add-dynamic-module=./nginx_hello_world/ngx_module
	$ sudo make
	$ sudo make install
	$ sudo make modules

Copy the module library (.so file) to <nginx_install_location>:

	$ sudo cp objs/ngx_module.so <nginx_install_location>/modules

In my case:

	$ sudo cp objs/ngx_module.so /usr/local/nginx/modules

Add load module directive in nginx.conf configuration file. For ex. load_module option has be set before the events configuration block like this:

	load_module "modules/ngx_module.so";

	events {
		 worker_connections  1024;
	}


The module provides a print_hello_world directive that returns the response ‘Hello World!’ from a location block:

	http {
		include       mime.types;
		default_type  application/octet-stream;

		sendfile        on;

		keepalive_timeout  65;

		server {
			listen       80;
			server_name  localhost;

			location / {
				root   html;
				index  index.html index.htm;
			}

			location /test {
				print_hello_world;
			}

			error_page   500 502 503 504  /50x.html;

			location = /50x.html {
				root   html;
			}
		}

	}

Run nginx and test it:
	
	$ sudo /usr/local/nginx/sbin/nginx
	$ curl http://localhost/test

This will return *Hello World!*.

I have uploaded my nginx.conf file.
