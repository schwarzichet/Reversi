//
// Created by yzy on 4/27/18.
//

#include <thread>

#include <boost/beast.hpp>

constexpr auto ADDR_LISTEN = "0.0.0.0";
constexpr unsigned short PORT = 8012;

auto should_exit = false;

void do_session(boost::asio::ip::tcp::socket &sock)
{
    namespace http = boost::beast::http;

    boost::system::error_code ec;
    boost::beast::flat_buffer buffer;

    http::request<http::string_body> req;
    http::read(socket, buffer, req, ec);
}

void server()
{
    namespace http = boost::beast::http;
    using tcp = boost::asio::ip::tcp;

    auto const address = boost::asio::ip::make_address_v4(ADDR_LISTEN);
    auto const port = PORT;
    boost::asio::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};

    while (true)
    {
        if (should_exit)
        {
            break;
        }
        tcp::socket socket{ioc};
        acceptor.accept(socket);
        std::thread(std::bind(
                &do_session,
                std::move(socket)
                )).detach();
    }
}
