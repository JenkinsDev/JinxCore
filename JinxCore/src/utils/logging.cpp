#include "logging.h"

// GOD, Call macros within cpp files, not header files.
INITIALIZE_EASYLOGGINGPP

namespace jinx { namespace utils {

    std::string Logging::signature = "JinxCore: ";

    void Logging::init() {
        el::Configurations defaultConf;

        defaultConf.setToDefault();
        defaultConf.setGlobally(el::ConfigurationType::Format, "%date %level %msg");

        el::Loggers::reconfigureLogger("default", defaultConf);
        el::Helpers::setCrashHandler(Logging::crashHandler);
    }

    void Logging::error(const char message[]) {
        LOG(ERROR) << Logging::signature << message;
    }

    void Logging::warning(const char message[]) {
        LOG(WARNING) << Logging::signature << message;
    }

    void Logging::debug(const char message[]) {
        LOG(DEBUG) << Logging::signature << message;
    }

    void Logging::info(const char message[]) {
        LOG(INFO) << Logging::signature << message;
    }

    void Logging::crashHandler(int sig) {
        Logging::error("Fatal Error.  Exiting with sig: " + sig);

        system("PAUSE");

        el::Helpers::crashAbort(sig);
    }

} }