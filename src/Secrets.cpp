
// #if __has_include("SecretsImpl.cpp")
//     #include "SecretsImpl.cpp"

#include "SecretsImpl.h"
#ifdef INCLUDE_DEFAULT_SECRETS 
#include "Secrets.h" 
    const char *Secrets::SSID = "ssid";
    const char *Secrets::PASSWORD = "passcode";
    const char *Secrets::SECRET = "aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee";
    const char *Secrets::HOST = "example.com";
    const char *Secrets::HOST_INFO = "Host: example.com:443";
    const bool Secrets::USE_SSL = true;
    const int Secrets::PORT = 443;
    const char *Secrets::ENTITY_ID = "ffffffffffffffffffffffff";
    const char *Secrets::ENTITY_OWNER = 
        "abababababababababababababababababababab";
    const char *Secrets::SSL_FP = 
        "AA BB CC DD EE FF AA BB CC DD EE FF AA BB CC DD EE FF AA BB"; 
#endif