#include "stdafx.h"
#include "Server.h"
#include "Utils.h"

using boost::lexical_cast;

int main(int argc, char* argv[]) {

    string ini_file(Utils::app_path() + "\\..\\scripts\\cgi4lcd.ini");
    unsigned int port = lexical_cast<unsigned int>(Utils::ini_read(ini_file, "cgi4lcd.port", "65432"));
    bool show_window = Utils::ini_read(ini_file, "cgi4lcd.show_window", "0") == "1";
    bool add_and_run = Utils::ini_read(ini_file, "cgi4lcd.add_and_run", "1") == "1";

    if (!show_window) {
        HWND hWnd = GetConsoleWindow();
        ShowWindow( hWnd, SW_HIDE );
    }

    try {
        boost::asio::io_service io_service;
        Server s(io_service, port, add_and_run);
        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}