

#include <iostream>
#include <winsock.h>
#include <thread>


#define PORT 9980
using namespace std;


int listens = 0;
struct sockaddr_in svr;
int maxfd = 0;
FD_SET fr;
int client[50] = { 0, };
bool accecpt_check = false;
bool accecpt_check2 = false, accecpt_check3 = false, accecpt_check4 = false, revcheck = false, userpass_check = false;


int acceptsssssssssss(int li,int maxk, const fd_set& fr)
{
  
  
    accecpt_check = true;
    int clientSocket = accept(li, NULL, NULL);
    if (clientSocket < 0) {
        cout << "ERROR OUCREECED (ACCEPT)\n EXITING SERVER";
        return EXIT_FAILURE;
    }
    int index;
    for (index = 0; index < 50; index++) {
        if (client[index] == 0) {
            client[index] = clientSocket;
            FD_SET(client[index], &fr);
            if (maxk < clientSocket) {
                maxk = clientSocket + 1;
            }
            cout << client[index];
            cout << "connected \n";
            break;
        }
    }
    if (index == 50)
    {
        cout << endl << "Server is busy..";

        
    }
    cout << "recvcheck called\n";
    if (revcheck != true) {
        cout << "called\n";
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        thread recc(revrespon,fr);
        recc.join();
    }
    accecpt_check = false;
}

int wait_for_new_client(int rr, int lis, int maxl)
{
    while (true)
    {
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        // setting fr to zero
        FD_ZERO(&fr);
        FD_SET(lis, &fr);
        int index = 0;
        for (index; index < 50; index++)
        {
            if (client[index] != 0)
            {
                FD_SET(client[index], &fr); // sets client to fD
            }
        }

        rr = select(maxl, &fr, NULL, NULL, &tv);// selects the client 
        if (rr < 0)
        {
            cout << "Select failed";
            return EXIT_FAILURE;
        }
        else if (rr == 0)
        {
            //cout << "No client available\n";
            
        }
        else
        {
            if (FD_ISSET(lis, &fr)) {
                if (accecpt_check == false) {
                    thread accept(acceptsssssssssss,lis, maxl, fr);
                    accept.join();
                    
                }
               
            }
        }
    }
}
int main()
{
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {//initiating enviroment
        cout << "WsaStartup faild";
        return EXIT_FAILURE;
    }
    listens = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//initilizing socket
    if (listens < 0) {
        cout << "socket faliaer";
        return EXIT_FAILURE;
    }

    svr.sin_family = AF_INET;
    svr.sin_addr.s_addr = INADDR_ANY; // address of server and port initilizing
    svr.sin_port = htons(PORT);
    memset(svr.sin_zero, 0, 10);

    int r = bind(listens, (struct sockaddr*)&svr, sizeof(sockaddr)); // binding to get ready for clients
    if (r < 0)
    {
        cout << "bind failed";
        return EXIT_FAILURE;
    }
    r = listen(listens, 50);// listining to the socket 
    if (r < 0) {
        cout << "listen faild";
        return EXIT_FAILURE;
    }
    maxfd = listens + 1;// file discripter setting at 1 byte up

    thread wait(wait_for_new_client,r, listens, maxfd);
    wait.join();
    

    return 0;
}
