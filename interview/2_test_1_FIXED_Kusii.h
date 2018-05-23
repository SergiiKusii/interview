//Please, make a review of this code. 
// You need to find all problems and describe them.
// Please write how to fix this problem in code.

#include <string>
#include <vector>
#include <sstream>
#include <memory>

#define _WIN_EMULATOR_
#ifndef _WIN_EMULATOR_
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <strings.h>
#include <unistd.h>
#endif
 
struct Client {
 
    struct Factory;
 
	enum{
		eDefaultBufferSize = 512
	};

    Client(const std::string &host, const short port)
#ifndef _WIN_EMULATOR_
        : mSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
    {
        if (mSocket < 0)
            throw std::runtime_error("Failed to create socket");
 
        sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_aton(host.c_str(), &addr.sin_addr);
        int rc = connect(mSocket, (struct sockaddr*)&addr, sizeof(addr));
 
        if (rc < 0)
            throw std::runtime_error("Failed to connect to host");
    }
#else
	{}
#endif
    ~Client()
    {
#ifndef _WIN_EMULATOR_
        if (mSocket > 0)
	    	close(mSocket);
#endif    
	}
 
    std::string send(const std::string &msg)
    {
#ifndef _WIN_EMULATOR_
        int rc = ::send(mSocket, &msg.front(), msg.length() + 1, 0);
        if (rc < 0)
            throw std::runtime_error("Failed to send message");
 
        const int bufSize = mDefaultBufSize; 
 
        char *buf = new char[bufSize];
        rc = ::recv(mSocket, buf, bufSize, 0);

        std::string response;
        if (rc > 0)
            response = std::string(buf, rc);
        delete[] buf; 

		if (rc < 0)
			throw std::runtime_error("Failed to receive response");
#else
		std::string response = "{file1 : uri1, file2 : uri2}";
#endif
        return response;
    }
 
private:
    int mSocket;
    int mDefaultBufSize = eDefaultBufferSize;
};
 

struct Client::Factory {
 
    static Factory & get()
    {
        static Factory factory;
        return factory;
    }
 
    std::unique_ptr<Client> httpClient(const std::string &host, const short port) 
	{
        return std::make_unique<Client>(host, port); 
    }
};
 
struct Request {
 
    struct Apps;
    struct Users;
    struct UriForFile;
 
    virtual std::string execute(const std::string &host, const short port)
    {
        throw std::runtime_error("Request is not implemented");
    }

	virtual ~Request() {};
};
 
struct Request::Apps : Request {
 
    std::string execute(const std::string &host, const short port)
    {
        auto client = Client::Factory::get().httpClient(host, port);
        return client->send("GET /Apps HTTP/1.1\n\n");
    }
};
 
struct Request::Users : Request {
 
    std::string execute(const std::string &host, const short port)
    {
        auto client = Client::Factory::get().httpClient(host, port);
        return client->send("GET /Users HTTP/1.1\n\n");
    }
};
 
struct Request::UriForFile : Request {
 
    UriForFile(const std::string &fileName)
        : mFileName(fileName)
    {
    }
 
    std::string execute(const std::string &host, const short port)
    {
        auto client = Client::Factory::get().httpClient(host, port);
        std::string urls = client->send("GET /Files HTTP/1.1\n\n");
 
 
        // Assuming we've got some JSON response like "{file1 : uri1, file2 : uri2}"
 
        int beg = urls.find(mFileName);
        if (beg == std::string::npos) 
            return std::string();
 
        beg = urls.find(":", beg);
        for (; !isalnum(urls.at(beg)); ++beg);
 
        int end = beg;
        for (; end < (int)urls.length() && isalnum(urls.at(end)); ++end);
 
        return urls.substr(beg, end - beg);
    }
 
private:
    std::string mFileName;
};
 
// int main(int argc, char **argv)
//{
//	try {
//		std::shared_ptr<Request> request = std::make_shared<Request::UriForFile>("file3");
//		/*std::string response = */ request->execute("10.4.46.17", 1430); // TODO Kusii: Analysis of response
//	}
//	catch(std::exception& /*exc*/){
//		// TODO Kusii: Analysis of exception	
//	}
//	catch(...){
//		// TODO Kusii: Analysis of unknown exception
//	}
//	return 0;
//}