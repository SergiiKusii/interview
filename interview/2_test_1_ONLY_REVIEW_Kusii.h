//Please, make a review of this code. 
// You need to find all problems and describe them.
// Please write how to fix this problem in code.

#include <string>
#include <vector>
#include <sstream>
#include <memory>
 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*TODO Kusii :
	1. #include <strings.h> // bzero(&addr, sizeof(addr));
	2. #include <unistd.h> // close()
 */
struct Client {
 
    struct Factory;
 
    Client(const std::string &host, short port)
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

    ~Client()
    {
        if (mSocket < 0)
            throw std::runtime_error("Invalid logic"); //TODO Kusii: DO NOT throw exceptions in destructor!

        close(mSocket);
    }
 
    std::string send(const std::string &msg)
    {
        int rc = ::send(mSocket, &msg.front(), msg.length() + 1, 0);
        if (rc < 0)
            throw std::runtime_error("Failed to send message");
 
        const int bufSize = mDefaultBufSize; 
 
        char *buf = new char[bufSize];
		// TODO Kusii: Problem: sizeof(bufSize) = sizeof(int)
		// right call: ::recv(mSocket, buf, bufSize, 0);
        rc = ::recv(mSocket, buf, sizeof(bufSize), 0);

		// TODO Kusii: Memory leak!!! Need to delete[] array
        if (rc < 0)
            throw std::runtime_error("Failed to receive response");
 
        std::string response;
 
        if (rc > 0)
            response = std::string(buf, rc);
        else
        {
            delete buf; // TODO Kusii: You have to delete array: "delete[] buf"
            return std::string(); // TODO Kusii: Bad code style, Beter way is return and delete[] in one place. For it you should delete branch "else".
		}
 
        delete buf; // TODO Kusii: You have to delete array: "delete[] buf"
        return response;
    }
 
private:
    int mSocket;
    int mDefaultBufSize; // TODO Kusii: Need to initialise default size. For example "int mDefaultBufSize = 512;"
};
 
/*TODO Kusii: In this case you should use Singelton 
			You can write as "static Factory factory;"
*/
struct Client::Factory {
 
    static Factory & get()
    {
        Factory factory;
        return factory;
    }
 
    Client * httpClient(const std::string &host, short port)
    {
        return new Client(host, port); // TODO Kusii: Potential memory leak. You should use std::unique_ptr to avoid problems.
    }
};
 
struct Request {
 
    struct Apps;
    struct Users;
    struct UriForFile;
 
	// TODO Kusii : use const input parameters "const short port"
    virtual std::string execute(const std::string &host, short port)
    {
        throw std::runtime_error("Request is not implemented");
    }

	/*TODO Kusii: default constructor does not apropriate at all! 
				You have to declare virtual destructor for Base class.
				In other case derived class destructor is not called

		virtual ~Request() {};
	*/
};
 
struct Request::Apps : Request {
 
    std::string execute(const std::string &host, short port)
    {
        Client *client = Client::Factory::get().httpClient(host, port);
        return client->send("GET /Apps HTTP/1.1\n\n");
    }
};
 
struct Request::Users : Request {
 
    std::string execute(const std::string &host, short port)
    {
        Client *client = Client::Factory::get().httpClient(host, port);
        return client->send("GET /Users HTTP/1.1\n\n");
    }
};
 
// TODO Kusii: 
// 1. Use same identifier for class/struct declaration. Change to struct.
// 2. Use public inheritance, see comments below.
class Request::UriForFile : Request {
 
    UriForFile(const std::string &fileName)
        : mFileName(fileName)
    {
    }
 
    std::string execute(const std::string &host, short port)
    {
        Client *client = Client::Factory::get().httpClient(host, port);
        std::string urls = client->send("GET /Files HTTP/1.1\n\n");
 
 
        // Assuming we've got some JSON response like "{file1 : uri1, file2 : uri2}"
 
        int beg = urls.find(mFileName);
        if (beg = std::string::npos) //TODO Kusii: use operator "==" for comparison
            return 0; //TODO Kusii: right return type is std::string
 
        beg = urls.find(":", beg);
        for (; !isalnum(urls.at(beg)); ++beg);
 
        int end = beg;
        for (; end < urls.length() && isalnum(urls.at(end)); ++end);
 
        return urls.substr(beg, end - beg);
    }
 
private:
    std::string mFileName;
};
 
int main(int argc, char **argv)
{
    //TODO Kusii: catch exceptions
    
	// TODO Kusii: if you want to use public interface, you have to add "public" identifier for inheritance "Request::UriForFile : public Request"
	std::shared_ptr<Request> request = std::make_shared<Request::UriForFile>("file3");
    std::string response = request->execute("91.198.174.192", 80); 
    (void)response; //TODO Kusii: if you do not want to see warning, simply do not use variable
    return 0;
}