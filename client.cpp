int Ret = 0;

		sockaddr_in srv;

		Ret = WSAStartup(MAKEWORD(2, 2), &w);
		if (Ret < 0)
		{
	      cout<<"Can Not connect to the server");
        
		}
		//Open a socket - listener
		int Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Socket < 0)
		{
			cout<<"Can Not connect to the server", "Error";
		}

		srv.sin_family = AF_INET;
		srv.sin_addr.s_addr = inet_addr(YOUR_SERVER_IPADDRESS);
		srv.sin_port = htons(PORT);
		memset(&(srv.sin_zero), 0, 10);

		
		Ret = connect(Socket, (struct sockaddr*)&srv, sizeof(srv));
		if (Ret < 0)
		{
			cout<<"Can Not connect to the server plsease retry";
			//Application->exi
		}
			
		
		int nErr = send(Socket, "Username and password sign", 600, 0);
		if (nErr < 0) {
			cout<<"no response form server";

		}
		
